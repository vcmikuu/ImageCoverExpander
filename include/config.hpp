#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig) {
    CONFIG_VALUE(Active, bool, "Enable the Mod", true);
    CONFIG_VALUE(Brightness, float, "Brightness of the cover", 0.5);
    CONFIG_VALUE(Opacity, float, "Opacity of the cover", 0.8);
};
