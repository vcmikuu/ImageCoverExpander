#include "UI/Settings.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "config.hpp"
#include "git-info.h"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "Helpers/getMainFlowCoordinator.hpp"

// Define the Settings type in the ImageCoverExpander::UI namespace
DEFINE_TYPE(ImageCoverExpander::UI, Settings);

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace ImageCoverExpander;

// Global variables to track settings updates and original enabled value
bool updatedSettings = false;
bool originalEnabledValue = false;
float originalBrightnessValue = 0.0;
float originalOpacityValue = 0.0;

// Method called when the view is activated
void ImageCoverExpander::UI::Settings::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling) {
    if (!firstActivation) {
        return;
    }

    // Parse and construct the settings UI from the BSML file
    BSML::parse_and_construct(IncludedAssets::Settings_bsml, this->get_transform(), this);

    // Initialize settings state
    updatedSettings = false;
    originalEnabledValue = get_enabledValue();
    originalBrightnessValue = get_brightnessValue();
    originalOpacityValue = get_opacityValue();
    versionText->text = GIT_VERSION;

    // Uncomment the following lines for hot reload functionality
    // #ifdef HotReload
    //    fileWatcher->checkInterval = 0.5f;
    //    fileWatcher->filePath = "/sdcard/bsml/GraphicsTweaks/SettingsView.bsml";
    // #endif
}

// Method called when the settings view is deactivated
void ImageCoverExpander::UI::Settings::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling) {
    if (updatedSettings) {
        auto mfc = GetMainFlowCoordinator();
        if(!mfc) return;

        // Restart the game if the enabled value has changed
        if (originalEnabledValue != get_enabledValue() ||
            originalBrightnessValue != get_brightnessValue() ||
            originalOpacityValue != get_opacityValue()
        ) {
            mfc->_menuTransitionsHelper->RestartGame(nullptr);
        }
    }
}

// Get the current enabled value from the mod configuration
bool ImageCoverExpander::UI::Settings::get_enabledValue() {
    return getModConfig().Active.GetValue();
}

// Set the enabled value in the mod configuration and mark settings as updated
void ImageCoverExpander::UI::Settings::set_enabledValue(bool value) {
    getModConfig().Active.SetValue(value);

    updatedSettings = true;
}

// Get the current brightness value from the mod configuration
float ImageCoverExpander::UI::Settings::get_brightnessValue() {
    return getModConfig().Brightness.GetValue();
}

// Set the brightness value in the mod configuration and mark settings as updated
void ImageCoverExpander::UI::Settings::set_brightnessValue(float value) {
    getModConfig().Brightness.SetValue(value);

    updatedSettings = true;
}

// Get the current opacity value from the mod configuration
float ImageCoverExpander::UI::Settings::get_opacityValue() {
    return getModConfig().Opacity.GetValue();
}

// Set the opacity value in the mod configuration and mark settings as updated
void ImageCoverExpander::UI::Settings::set_opacityValue(float value) {
    getModConfig().Opacity.SetValue(value);

    updatedSettings = true;
}
