#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/Resources.hpp"

/**
 * @brief Retrieves the MainFlowCoordinator object.
 *
 * @return A pointer to the MainFlowCoordinator object, or nullptr if not found.
 */
inline GlobalNamespace::MainFlowCoordinator* GetMainFlowCoordinator() {
    auto flowCoordinators = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::MainFlowCoordinator*>();
    if (flowCoordinators.size() > 0) {
        return flowCoordinators[0];
    }

    return nullptr;
}
