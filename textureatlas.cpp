#include "textureatlas.h"
#include "fielsystem.h"
#include "pixmap.h"
#include "prefecences.h"
#include "logger.h"

TextureAtlas::TextureAtlas()
{

}

TextureAtlas::~TextureAtlas()
{

}

void TextureAtlas::LoadAll()
{
    std::vector<std::string> files;
    getFiles(Prefecences::Instance()->getTexturesDir(), files);
    LOG(info) << "texatlas found " << files.size() << " files";

    Pixmap atlas(glm::vec2(2048, 2048));

    int x = 0, y = 0, i = 0;
    for(std::string file: files)
    {
        Pixmap tex(Prefecences::Instance()->getTexturesDir() + file);
        atlas.Blit(tex, glm::vec2(x * 32, y * 32));
        refs[file] = i;
        x++;
        if(x >= 2048/32)
        {
            x = 0;
            y++;
        }
        ++i;
    }
    LOG(info) << "texatlas load " << i << " pixmaps";

    tex->Load(atlas, false, false);
    LOG(info) << "texatlas load texture";
}

std::shared_ptr<Texture> TextureAtlas::tex = std::make_shared<Texture>();
std::unordered_map<std::string, int> TextureAtlas::refs;

