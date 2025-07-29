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
#include <array>
#include <memory>
#include <type_traits>
#include <unordered_map>

#include "define.h"
// ========================type traits========================
template <typename T, typename... Types>
constexpr bool is_one_of_v = (std::is_same_v<T, Types> || ...);
// ============================================================

using EntityID = uint64_t;

struct Handle
{
    EntityID entity_id              = 0;
    const std::type_info* type_info = nullptr;
    EntityID Id() const { return entity_id; }
};

class Component
{
 public:
    virtual ~Component() = default;
};

class BaseEntity : public Handle
{
 public:
    virtual ~BaseEntity() = default;
};

template <typename... T>
    requires(std::is_base_of_v<Component, T> && ...)
class Entity : public BaseEntity
{
 public:
    Entity()
    {
        static_assert(sizeof...(T) > 0, "Entity must have at least one component");
        [&]<std::size_t... I>(std::index_sequence<I...>) {
            ((components_[I] = std::make_shared<T>()), ...);
        }(std::index_sequence_for<T...>{});
    }
    virtual ~Entity() = default;

    template <typename U>
        requires(is_one_of_v<U, T...>)
    U* GetComponent()
    {
        std::size_t index            = 0;
        [[maybe_unused]] auto result = ((std::is_same_v<U, T> ? true : (++index, false)) || ...);
        return static_cast<U*>(components_[index].get());
    }

 private:
    std::array<std::shared_ptr<Component>, sizeof...(T)> components_;
};

template <typename... T>
    requires(std::is_base_of_v<BaseEntity, T> && ...)
class System
{
 public:
    template <typename U>
        requires(is_one_of_v<U, T...>)
    U* CreateEntity()
    {
        EntityID id                        = NextEntityID();
        std::shared_ptr<BaseEntity> entity = std::make_shared<U>();
        entity->entity_id                  = id;
        entity->type_info                  = &typeid(U);
        entities_[id]                      = entity;
        return static_cast<U*>(entity.get());
    }

    template <typename U>
        requires(is_one_of_v<U, T...>)
    U* GetEntity(EntityID id)
    {
        auto it = entities_.find(id);
        if (it != entities_.end())
        {
            assert(it->second->type_info == &typeid(U) && "Entity type mismatch");
            return static_cast<U*>(it->second.get());
        }
        return nullptr;
    }

    void DestroyEntity(EntityID id)
    {
        auto it = entities_.find(id);
        if (it != entities_.end())
        {
            entities_.erase(it);
            recycled_ids_.push(id);
        }
    }

 private:
    EntityID NextEntityID()
    {
        if (recycled_ids_.size() > 1024)  // id recycling threshold
        {
            EntityID id = recycled_ids_.front();
            recycled_ids_.pop();
            return id;
        }
        static EntityID next_id = 1;
        return next_id++;
    }

 private:
    std::unordered_map<EntityID, std::shared_ptr<BaseEntity>> entities_;
    std::queue<EntityID> recycled_ids_;
};