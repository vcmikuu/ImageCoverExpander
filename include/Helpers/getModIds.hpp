#pragma once

#include <cstring>
#include <vector>

#include "scotland2/shared/loader.hpp"

/**
 * @brief Retrieves a list of loaded mod IDs.
 *
 * @return A vector of C-style strings containing the IDs of the loaded mods.
 */
inline std::vector<char const*> const& getModIds() {
    // Static variable to ensure the vector is initialized only once
    static std::vector<char const*> modIds = []() {
        auto mods = modloader::get_loaded();
        std::vector<char const*> ids;

        // Populate the vector with mod.info.id
        for (auto const& mod : mods) {
            // Duplicate the string and add it to the vector
            ids.push_back(strdup(mod.info.id.c_str()));  // Dynamically allocate memory for each string
        }

        return ids;
    }();

    // Return the static vector
    return modIds;
}
