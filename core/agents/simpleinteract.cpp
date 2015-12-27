#include "simpleinteract.h"
#include "core/objectstatic.h"
#include "core/db.h"

void SimpleInteract::Deserialize(rapidjson::Value &val)
{
    DESERIALIZE(NVP(afterid), NVP(sound));
}

void SimpleInteract::onInteract(Object *par, Level *l, const glm::vec3 &pos, const GameTimer &gt)
{
    if(activate)
    {
        activate->Move(pos);
        activate->Play();
    }
}

void SimpleInteract::onLoad(Object *par, Level *, const glm::vec3 &pos, const GameTimer& gt)
{
    activate = nullptr;
    if(const ObjectStatic *os = DB::Get(sound))
    {
        if(const Sound *o = os->GetAgent<Sound>())
            activate = o;
    }
}
