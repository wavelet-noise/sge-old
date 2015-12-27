#include "remsnd.h"
#include <fstream>
#include <map>
#include <boost/filesystem.hpp>
#include "logger.h"

bool RemSnd::Open(const std::string &Filename, bool Looped, bool Streamed)
{
    std::ifstream a((Filename+".ogg").c_str());
    if (!a.is_open())
        return false;
    a.close();

    mLooped    = Looped;

    alGenSources(1, &mSourceID);
    if (!AL::CheckALError())
        return false;

    alSourcef (mSourceID, AL_PITCH,    1.0f);
    alSourcef (mSourceID, AL_GAIN,    1.0f);
    alSourcefv(mSourceID, AL_POSITION,  &mPos[0]);
    alSourcefv(mSourceID, AL_VELOCITY,  &mVel[0]);
    alSourcei (mSourceID, AL_LOOPING,  mLooped);

    mStreamed = Streamed;
    return LoadOggFile(Filename+".ogg", Streamed);
}

bool RemSnd::IsStreamed()
{
    return mStreamed;
}

void RemSnd::Play() const
{
    ALint state;
    alGetSourcei(mSourceID, AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING)
        alSourcePlay(mSourceID);
}

void RemSnd::Close()
{
    alSourceStop(mSourceID);
    if (alIsSource(mSourceID)) alDeleteSources(1, &mSourceID);
}

void RemSnd::Stop()
{
    alSourceStop(mSourceID);
}

void RemSnd::Pitch(float t) const
{
    alSourcef(mSourceID, AL_PITCH, t);
}

void RemSnd::NearFar(int n, int f)
{
    alSourcei(mSourceID, AL_REFERENCE_DISTANCE, n);
    alSourcei(mSourceID, AL_MAX_DISTANCE, f);
}

void RemSnd::Move(const glm::vec3 &pos)
{
    ALint state;
    alGetSourcei(mSourceID, AL_SOURCE_STATE, &state);
    if(state != AL_PLAYING)
    {
        if(glm::distance(pos, AL::listener) < glm::distance(mPos, AL::listener))
        {
            mPos = pos;
            Stop();
        }
        else
            return;
    }
    else
        mPos = pos;
    alSourcefv(mSourceID, AL_POSITION, &pos[0]);
}

void RemSnd::Update()
{
    alListenerfv(AL_POSITION, &AL::listener[0]);
    if (!mStreamed) return;

    int				Processed = 0;
    ALuint			BufID;

    alGetSourcei(mSourceID, AL_BUFFERS_PROCESSED, &Processed);

    while (Processed--)
    {
        alSourceUnqueueBuffers(mSourceID, 1, &BufID);
        if (!AL::CheckALError()) return;
        if (ReadOggBlock(BufID, DYNBUF_SIZE) != 0)
        {
            alSourceQueueBuffers(mSourceID, 1, &BufID);
            if (!AL::CheckALError()) return;
        }
        else
        {
            ov_pcm_seek(mVF, 0);
            alSourceQueueBuffers(mSourceID, 1, &BufID);
            if (!AL::CheckALError()) return;

            if (!mLooped) Stop();
        }
    }
}

RemSnd::RemSnd()
{

}

RemSnd::~RemSnd()
{
    Close();
}

bool RemSnd::ReadOggBlock(ALuint BufID, size_t Size)
{
    char		eof = 0;
    int			current_section;
    long		TotalRet = 0, ret;
    char		*PCM;

    if (Size < 1) return false;
    PCM = new char[Size];

    while (TotalRet < Size)
    {
        ret = ov_read(mVF, PCM + TotalRet, Size - TotalRet, 0, 2, 1, &current_section);

        if (ret == 0) break;
        else if (ret < 0)
        {

        }
        else
        {
            TotalRet += ret;
        }
    }
    if (TotalRet > 0)
    {
        alBufferData(BufID, AL::Buffers[BufID].Format, (void *)PCM,
                     TotalRet, AL::Buffers[BufID].Rate);
        AL::CheckALError();
    }
    delete [] PCM;
    return (ret > 0);
}

size_t ReadOgg(void *ptr, size_t size, size_t nmemb, void *datasource)
{
    std::istream *File = reinterpret_cast<std::istream*>(datasource);
    File->read((char *)ptr, size * nmemb);
    return File->gcount();
}

int SeekOgg(void *datasource, ogg_int64_t offset, int whence)
{
    std::istream *File = reinterpret_cast<std::istream*>(datasource);
    std::ios_base::seekdir Dir;
    File->clear();
    switch (whence)
    {
    case SEEK_SET: Dir = std::ios::beg;  break;
    case SEEK_CUR: Dir = std::ios::cur;  break;
    case SEEK_END: Dir = std::ios::end;  break;
    default: return -1;
    }
    File->seekg((std::streamoff)offset, Dir);
    return (File->fail() ? -1 : 0);
}

long TellOgg(void *datasource)
{
    std::istream *File = reinterpret_cast<std::istream*>(datasource);
    return File->tellg();
}

int CloseOgg(void *datasource)
{
    return 0;
}

bool RemSnd::LoadOggFile(const std::string &Filename, bool Streamed)
{
    int        i, DynBuffs = 1, BlockSize;
    AL::SndInfo      buffer;
    ALuint      BufID = 0;
    ov_callbacks  cb;

    cb.close_func  = CloseOgg;
    cb.read_func  = ReadOgg;
    cb.seek_func  = SeekOgg;
    cb.tell_func  = TellOgg;

    mVF = new OggVorbis_File;

    OggFile.open(Filename.c_str(), std::ios_base::in | std::ios_base::binary);

    if (ov_open_callbacks(&OggFile, mVF, NULL, -1, cb) < 0)
    {
        return false;
    }

    if (!Streamed)
    {
        for (AL::TBuf::iterator i = AL::Buffers.begin(); i != AL::Buffers.end(); i++)
        {
            if (i->second.Filename == Filename) BufID = i->first;
        }
        BlockSize = ov_pcm_total(mVF, -1) * 4;
    }
    else
    {
        BlockSize  = DYNBUF_SIZE;
        DynBuffs  = NUM_OF_DYNBUF;
        alSourcei(mSourceID, AL_LOOPING, AL_FALSE);
    }

    mComment    = ov_comment(mVF, -1);
    mInfo      = ov_info(mVF, -1);

    buffer.Rate    = mInfo->rate;
    buffer.Filename  = Filename;
    buffer.Format = (mInfo->channels == 1) ? AL_FORMAT_MONO16
                                           : AL_FORMAT_STEREO16;

    if (Streamed || !BufID)
    {
        for (i = 0; i < DynBuffs; i++)
        {
            alGenBuffers(1, &buffer.ID);
            if (!AL::CheckALError())
                return false;
            AL::Buffers[buffer.ID] = buffer;
            ReadOggBlock(buffer.ID, BlockSize);
            if (!AL::CheckALError())
                return false;

            if (Streamed)
            {
                alSourceQueueBuffers(mSourceID, 1, &buffer.ID);
                if (!AL::CheckALError())
                    return false;
            }
            else
                alSourcei(mSourceID, AL_BUFFER, buffer.ID);
        }
    }
    else
    {
        alSourcei(mSourceID, AL_BUFFER, AL::Buffers[BufID].ID);
    }
    LOG(trace) << Filename << " loaded";

    return true;
}

ALboolean AL::CheckALCError()
{
    ALenum ErrCode;
    std::string Err = "ALC error: ";
    if ((ErrCode = alcGetError(pDevice)) != ALC_NO_ERROR)
    {
        Err += (char *)alcGetString(pDevice, ErrCode);
        LOG(error) << Err.data();
        return AL_FALSE;
    }
    return AL_TRUE;
}

ALboolean AL::CheckALError()
{
    ALenum ErrCode;
    std::string Err = "OpenAL error: ";
    if ((ErrCode = alGetError()) != AL_NO_ERROR)
    {
        Err += (char *)alGetString(ErrCode);
        LOG(error) << Err.data();
        return AL_FALSE;
    }
    return AL_TRUE;
}

bool AL::InitializeOpenAL()
{
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

    pDevice = alcOpenDevice(nullptr);

    if (!pDevice)
    {
        LOG(error) << "Default sound device not present";
        return false;
    }
    pContext = alcCreateContext(pDevice, nullptr);
    if (!CheckALCError()) return false;

    alcMakeContextCurrent(pContext);

    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    LOG(trace) << "OpenAL init complete";
    return true;
}

void AL::DestroyOpenAL()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(pContext);
    alcCloseDevice(pDevice);
    LOG(trace) << "OpenAL destroyed";
}

ALCdevice *AL::pDevice;
ALCcontext *AL::pContext;
AL::TBuf AL::Buffers;
glm::vec3 AL::listener;
