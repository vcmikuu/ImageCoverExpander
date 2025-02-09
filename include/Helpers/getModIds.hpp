#pragma once

#include "scotland2/shared/loader.hpp"
#include <cstring>
#include <vector>

/**
 * @brief Retrieves a list of loaded mod IDs.
 *
 * @return A vector of C-style strings containing the IDs of the loaded mods.
 */
inline const std::vector<const char*>& getModIds() {
    // Static variable to ensure the vector is initialized only once
    static std::vector<const char*> modIds = []() {
        auto mods = modloader::get_loaded();
        std::vector<const char*> ids;

        // Populate the vector with mod.info.id
        for (const auto& mod : mods) {
            // Duplicate the string and add it to the vector
            ids.push_back(strdup(mod.info.id.c_str())); // Dynamically allocate memory for each string
        }

        return ids;
    }();

    // Return the static vector
    return modIds;
}
