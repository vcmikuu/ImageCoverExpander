#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(Active, bool, "Disable the Mod (RESTART REQUIRED FOR DISABLING)", false);
)