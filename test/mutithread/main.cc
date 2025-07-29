#include <iostream>
#include <vector>

#include "base/ecs.h"
#include "base/singleton.h"

class Comp1 : public Component
{
 public:
    void Print() const { std::cout << "Comp1 Print" << std::endl; }
};

class NetEntity : public Entity<Comp1>
{
 public:
    void Print() const { std::cout << "NetEntity ID: " << Id() << "\n"; }
};
using NetEntityPtr = std::shared_ptr<NetEntity>;

class TestSystem : public System<NetEntity>,
                   public Singleton<TestSystem>
{
};

int main()
{
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
