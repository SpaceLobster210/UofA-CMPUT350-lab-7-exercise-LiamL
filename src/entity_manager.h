#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "registry.h"

#include <cstddef>  // size_t
#include <limits>
#include <vector>

#include "pack.h"  // Pack from prep

using EntityID = size_t;

template <typename... ComponentTypes>
class EntityManager {
    public:
        static constexpr size_t invalidCompIndex = std::numeric_limits<size_t>::max();
        static constexpr size_t numComponents = sizeof...(ComponentTypes);

        // Return index of map location of type in mComponentMap
        template <typename QueryType>
        constexpr size_t mapComponent(EntityID e) {
            return (e * numComponents) + pack_detail::packTypeToIndex<QueryType, ComponentTypes...>;
        }

        // Returns the next available entity ID and updates deletedIDs
        EntityID createEntity() {
            auto dEnt = find(deletedIDs.begin(), deletedIDs.end(), true);
            size_t index = dEnt - deletedIDs.begin();
            deletedIDs[index] = false;

            // Initialize components to ivalidCompIndex
            for (size_t i = 0; i < numComponents; ++i) {
                mComponentMap[(index * numComponents) + i] = invalidCompIndex;
            }

            return index;
        }

        // Return true iff the EntityID is currently alive
        bool validEntity(EntityID e) {
            if (deletedIDs[e]) {
                return false;
            }
            return true;
        }

        // Return true iff entity has a component of the given type
        template <typename ComponentType>
        bool hasComponent(EntityID e) {
            return (mapComponent<ComponentType>(e) != invalidCompIndex);
        }

        // Gets a reference to the component of ComponentType, if it exists
        template <typename ComponentType>
        ComponentType& getComponent(EntityID e) {
            static_assert(hasComponent<ComponentType>(e), "Entity does not have component of given type.");

            return mRegistries[pack_detail::packTypeToIndex<ComponentType, ComponentTypes...>][mComponentMap[mapComponent<ComponentType>(e)]];
        }

        // Add a new component to an entity, if it does not already have that component
        template <typename ComponentType>
        void addComponent(EntityID id, ComponentType&& component) {
            static_assert(!(getComponent<ComponentType>(id)), "Entity already has component of given type.");

            mRegistries[pack_detail::packTypeToIndex<ComponentType, ComponentTypes...>][mComponentMap[mapComponent<ComponentType>(id)]] = 
                            std::remove_reference_t<ComponentType> (std::forward<ComponentType>(component));
        }

    private:
        std::tuple<Registry<ComponentTypes>...> mRegistries;
        std::vector<size_t> mComponentMap;
        std::vector<bool> deletedIDs;
};

#endif  // ENTITY_MANAGER_H
