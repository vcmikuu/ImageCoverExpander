// Include necessary headers
#include "main.hpp"

#include "autohooks/shared/hooks.hpp"
#include "bsml/shared/BSML.hpp"
#include "config.hpp"
#include "custom-types/shared/macros.hpp"
#include "logger.hpp"
#include "modInfo.hpp"
#include "scotland2/shared/modloader.h"
#include "UI/Settings.hpp"

// GlobalNamespace
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
using namespace GlobalNamespace;

// HMUI
#include "HMUI/ImageView.hpp"
#include "HMUI/ViewController.hpp"
using namespace HMUI;

// UnityEngine
#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
using namespace UnityEngine;

// Helpers
#include "Helpers/getModIds.hpp"
#include "Helpers/logTransform.hpp"
#include "Helpers/shiftTransform.hpp"
using namespace Helpers;

// Standard library
#include <cmath>

// Macro to check if the mod is enabled
#define MOD_ENABLED getModConfig().Active.GetValue()

// Map to store extra widths for different mods
static std::unordered_map<std::string, float> modExtraWidths = {{"", 2}, {"PlaylistManager", 9}, {"Replay", 7}};

// Hook for the DidActivate method of StandardLevelDetailViewController
MAKE_LATE_HOOK_MATCH(
    m_DidActivate,
    &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
    void,
    GlobalNamespace::StandardLevelDetailViewController* self,
    bool firstActivation,
    bool addedToHeirarchy,
    bool screenSystemEnabling
) {
    // Call the original DidActivate method
    m_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    // Skip if not the first activation
    if (!firstActivation) {
        Logger.info("Not first activation, skipping.");
        return;
    }

    // Check if the mod is enabled
    if (MOD_ENABLED) {
        // Calculate the extra width needed for the image cover
        static float_t extraWidth = []() {
            auto width = modExtraWidths[""];
            for (auto mod : modloader::get_loaded()) {
                auto modExtraWidth = modExtraWidths.find(mod.info.id);
                if (modExtraWidth != modExtraWidths.end() && modExtraWidths[mod.info.id] > width) {
                    width = modExtraWidths[mod.info.id];
                }
            }

            return width;
        }();

        // Calculate the x-axis shift for the image cover
        static float_t xShift = []() {
            auto const modIds = getModIds();
            if (std::find_if(modIds.begin(), modIds.end(), [](char const* modId) {
                    return std::strcmp(modId, "PlaylistManager") == 0;
                }) != modIds.end()) {
                return 0.0f;
            }
            return extraWidth / 2.0f;
        }();

        Logger.info("ImageCoverExpander Found Value Set As False, expanding Image");

        // Get the RectTransform of the image cover
        auto* imageCoverTransform = self->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

        // Log the transform of the image cover
        logTransform(imageCoverTransform);

        // Shift the song title left to fill where the artwork was
        for (auto name :
             {"LevelDetail/LevelBarBig/SingleLineTextContainer",
              "LevelDetail/LevelBarBig/SongArtwork",
              "LevelDetail/LevelBarBig/MultipleLineTextContainer"}) {
            auto transform = self->get_transform()->Find(name)->GetComponent<RectTransform*>();
            if (transform) {
                logTransform(transform);
                shiftTransform(transform, Vector3(-14 + xShift, 0, 0));
            }
        }

        // Shift the various elements right to center them
        for (auto name :
             {"LevelDetail/ActionButtons",
              "LevelDetail/BeatmapCharacteristic",
              "LevelDetail/BeatmapDifficulty",
              "LevelDetail/BeatmapParamsPanel",
              "LevelDetail/BeatmapParamsPanel(Clone)",
              "LevelDetail/LoadingControl",
              "LevelDetail/ModifierSelection"}) {
            auto component = self->get_transform()->Find(name);
            if (!component) {
                continue;
            }
            auto transform = component->GetComponent<RectTransform*>();
            if (transform) {
                logTransform(transform);
                shiftTransform(transform, Vector3(xShift, 0, 0));
            }
        }

        // Set the size and position of the image cover
        imageCoverTransform->set_sizeDelta(Vector2(68.5 + extraWidth, 58.0));
        imageCoverTransform->set_localPosition(Vector3(-34.4, -56, 0));
        imageCoverTransform->SetAsFirstSibling();

        // Get the ImageView component of the image cover and set its properties
        auto* imageView = imageCoverTransform->GetComponent<ImageView*>();
        imageView->set_color(Color(0.5, 0.5, 0.5, 1));
        imageView->set_preserveAspect(false);
        imageView->_skew = 0.0f;

        // Log the transform of the image cover and refresh the ImageView
        logTransform(imageCoverTransform);
        imageView->__Refresh();
    } else {
        Logger.info("ImageCoverExpander Found Value Set As True, not expanding");
    }
}

/// @brief Called at the early stages of game loading
/// @param info
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info = modInfo.to_c();
    Logger.info("Completed setup!");
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();
    getModConfig().Init(modInfo);
    BSML::Init();

    // Register the button on the main menu
    BSML::Register::RegisterMainMenu<ImageCoverExpander::UI::Settings*>("Image Cover Expander", "Image Cover Expander", "");

    // Install the hooks
    Logger.info("Installing hooks...");
    INSTALL_LATE_HOOKS();

    Logger.info("Installed all hooks!");
}
