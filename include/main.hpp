#pragma once

#include "HMUI/ViewController.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

/// @brief Stores the ID and version of our mod, and is sent to the modloader upon startup
modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

#define MOD_EXPORT __attribute__((visibility("default")))
#ifdef __cplusplus
#define MOD_EXPORT_FUNC extern "C" MOD_EXPORT
#else
#define MOD_EXPORT_FUNC MOD_EXPORT
#endif
