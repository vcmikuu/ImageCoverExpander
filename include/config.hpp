#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig) {
    CONFIG_VALUE(Active, bool, "Enable the Mod", true);
};
