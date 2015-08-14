#ifndef SGE_TEXTURE_LAB_H
#define SGE_TEXTURE_LAB_H
#include "sge_ui/wins.h"
#include "sge_ui/image_box.h"
#include "sge_ui/connector.h"
#include "TextureGenerator.h"

class sge_texlab_heightmap : public Win
{
public:
    sge_texlab_heightmap(WContainer *par);

    void Draw() const;
    void Update(const GameTimer &gt);
    ImageBox *ib;
    Connector<float> *scale, *offsetx, *offsety;
    Connector<std::shared_ptr<Texture>> *out;
    TextureGenerator tg;
};

#endif // SGE_TEXTURE_LAB_H
