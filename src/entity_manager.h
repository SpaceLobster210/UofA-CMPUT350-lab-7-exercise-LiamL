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

        // Map each componenet to its location in mComponentMap
        size_t mapComponents(EntityID e) {
            size_t base = e * numComponents;
        }

        // Returns the next available entity ID and updates deletedIDs
        EntityID createEntity() {
            auto dEnt = find(deletedIDs.begin(), deletedIDs.end(), true);
            size_t index = dEnt - deletedIDs.begin();
            deletedIDs[index] = false;
            return index
        }

        // Return true iff the EntityID is currently alive
        bool validEntity(EntityID e) {
            if (deletedIDs[e]) {
                return false;
            }
            return true;
        }

        template <typename ComponentType>
        bool hasComponent(EntityID e) {
            return true; // TODO FINISH THIS
        }

    private:
        std::tuple<Registry<ComponentTypes>...> mRegistries;
        std::vector<size_t> mComponentMap;
        std::vector<bool> deletedIDs;
};

#endif  // ENTITY_MANAGER_H
