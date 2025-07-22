/**
 * ***************************************************************************
 * *
 * Laranee - A fast C++ server game engine
 * *
 * ***************************************************************************
 *
 * @file ecs.h
 * @author lyall (lyall.liu@gmail.com)
 * @date 2025-07-22
 * @brief ecs framework
 *
 */
#pragma once
#include <type_traits>

#include "define.h"
#include "singleton.h"
// ========================type traits========================
template <typename T, typename... Types>
constexpr bool is_one_of_v = (std::is_same_v<T, Types> || ...);
// ============================================================

using EntityID = std::size_t;

struct Handle
{
    EntityID entity_id = 0;
};

using EntityPtr = std::shared_ptr<Entity>;

class Entity : public Handle
{
};

class Component : public Handle
{
};

template <typename... T>
    requires(std::is_base_of_v<Entity, T> && ...)
class System : public Singleton<System<T>>
{
 public:
    template <typename U>
        requires(std::is_base_of_v<Entity, U> && is_one_of_v<U, T...>)
    EntityPtr CreateEntity()
    {
        EntityID id       = NextEntityID();
        EntityPtr entity  = std::make_shared<T>();
        entity->entity_id = id;
        entities_[id]     = entity;
        return entity;
    }

    void DestoryEntity(EntityID id)
    {
        auto it = entities_.find(id);
        if (it != entities_.end())
        {
            entities_.erase(it);
        }
    }

 private:
    EntityID NextEntityID()
    {
        static EntityID next_id = 1;
        return next_id++;
    }

 private:
    std::unordered_map<EntityID, EntityPtr> entities_;
};