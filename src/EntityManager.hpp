#pragma once

#include "Entity.hpp"
#include <memory>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager
{
    EntityVec                       m_entities;
    EntityVec                       m_entitiesToAdd;
    std::map<std::string, EntityVec> m_entityMap;
    size_t                          m_totalEntities = 0;

    void removeDeadEntities(EntityVec& vec)
    {
        const auto new_vec = std::remove_if(vec.begin(), vec.end(), 
                                    [](const std::shared_ptr<Entity>& entity) {
                                        return !(entity->isActive());
                                    });
        vec.erase(new_vec, vec.end());
    }

public:
    EntityManager() = default;

    void update()
    {
        for (auto& entity : m_entitiesToAdd)
        {
            m_entities.push_back(entity);
            m_entityMap[entity->tag()].push_back(entity);
        }
        m_entitiesToAdd.clear();

        removeDeadEntities(m_entities);
        
        // C++20 way of iterating through [key,value] pairs in a map
        for (auto& [tag, entityVec] : m_entityMap)
        {
            removeDeadEntities(entityVec);
        }
    }

    std::shared_ptr<Entity> addEntity(const std::string& tag)
    {
        // creat the entity shared pointer
        auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

        // add it to the vec of all entities
        m_entitiesToAdd.push_back(entity);

        // add it to the entity map
        if (m_entityMap.find(tag) == m_entityMap.end()) { m_entityMap[tag] = EntityVec(); }
        m_entityMap[tag].push_back(entity);

        return entity;
    }

    const EntityVec& getEntities()
    {
        return m_entities;
    }

    const EntityVec& getEntities(const std::string& tag)
    {
        if (m_entityMap.find(tag) == m_entityMap.end()) { m_entityMap[tag] = EntityVec(); }
        return m_entityMap[tag];
    }

    const std::map<std::string, EntityVec>& getEntityMap()
    {
        return m_entityMap;
    }
};