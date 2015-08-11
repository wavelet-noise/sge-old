#include "sge_texture_lab.h"
#include "resources/resourcecontroller.h"

sge_texture_lab::sge_texture_lab(WContainer *par) :
    Win(par)
{
    text = "sge_texture_lab";

    ib = new ImageBox(this);
    ib->tex = Resources::instance()->Get<Texture>("ro3ck");
}

void sge_texture_lab::Draw() const
{
    Win::Draw();
}

void sge_texture_lab::Update()
{
    Win::Update();
}
