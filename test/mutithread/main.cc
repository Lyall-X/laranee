#include <iostream>
#include <vector>

#include "base/ecs.h"
#include "base/singleton.h"

class Comp1 : public Component
{
 public:
    void Print() const
    {
        GDEBUG("Comp1 Print called, EntityID");
    }
};

class NetEntity : public Entity<Comp1>
{
 public:
    void Print() const
    {
        GDEBUG("NetEntity Print called, EntityID: {}", Id());
    }
};
using NetEntityPtr = std::shared_ptr<NetEntity>;

class TestSystem : public System<NetEntity>,
                   public Singleton<TestSystem>
{
};

int main()
{
    Logging::Instance().Init("test_multithread");
    for (int i = 0; i < 10; ++i)
    {
        NetEntity* entity = TestSystem::Instance().CreateEntity<NetEntity>();
        entity->Print();
        Comp1* comp1 = entity->GetComponent<Comp1>();
        comp1->Print();
        TestSystem::Instance().DestroyEntity(entity->Id());
    }
    return 0;
}
