#include <iostream>

#include "entity_manager.h"

int main() {
    // test here...
    EntityManager<int, float, bool> entityManager;
    EntityID e = entityManager.createEntity();
    //entityManager.addComponent(e, 5); // template argument deduction can tell this is addComponent<int>
    //std::cout << entityManager.hasComponent<int>(e) << '\n';   // prints '1'
    //std::cout << entityManager.hasComponent<float>(e) << '\n'; // prints '0'
    //std::cout << entityManager.hasComponent<bool>(e) << '\n';  // prints '0'
    // std::cout << entityManager.getComponent<bool>(e) << '\n'; // should fail an assertion (HINT)
    //std::cout << entityManager.getComponent<int>(e) << '\n';     // prints '5'
    return 0;
}
