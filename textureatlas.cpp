#include "textureatlas.h"
#include "fielsystem.h"
#include "pixmap.h"
#include "prefecences.h"

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

    Pixmap atlas(glm::vec2(2048, 2048));

    int x = 0, y = 0;
    for(std::string file: files)
    {
        Pixmap tex(Prefecences::Instance()->getTexturesDir() + file);
        atlas.Blit(tex, glm::vec2(x * 32, y * 32));
        x++;
        if(x + 1 >= 2048/32)
        {
            x = 0;
            y++;
        }
    }
    tex.Load(atlas);
}
