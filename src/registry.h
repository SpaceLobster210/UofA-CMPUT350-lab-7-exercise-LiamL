#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <memory>

template <typename T>
class Registry {
    public:
        // Copy
        size_t store(const T& entity) {
            auto dEnt = find(deletedEntities.begin(), deletedEntities.end(), true);
            if (dEnt != deletedEntities.end()) {
                size_t index = dEnt - deletedEntities.begin();
                components[index] = entity;
                deletedEntities[index] = false;
                return index;
            }
            else {
                components.push_back(entity);
                compLength += 1;
                return compLength - 1;
            }
        }
        // Move
        size_t store(T&& entity) {
            auto dEnt = find(deletedEntities.begin(), deletedEntities.end(), true);
            if (dEnt != deletedEntities.end()) {
                size_t index = dEnt - deletedEntities.begin();
                components[index] = entity;
                deletedEntities[index] = false;
                return index;
            }
            else {
                components.push_back(entity);
                compLength += 1;
                return compLength - 1;
            }
        }

        // Remove
        void remove(size_t index) {
            if (valid(index)) {
                components.erase(index);
                deletedEntities[index] = true;
            }
        }

        // Access operator
        T& operator[](size_t index) {
            return components[index];
        }
        const T& operator[](size_t index) const {
            return components[index];
        }

        // Check if a slot is valid
        bool valid(size_t index) {
            if (deletedEntities[index] || index >= compLength) {
                return false;
            }
            return true;
        }

        size_t size() {
            return compLength - std::count(deletedEntities.cbegin(), deletedEntities.cend(), true);
        }



    private:
        std::Vector<std::shared_ptr<T>> components; // Stored entity components
        std::Vector<bool> deletedEntities; // List of the indexes of entities that have been removed
        size_t compLength = 0; // Length of the components vector, including inactive entities

};

#endif  // REGISTRY_H
