#include "Logger.hpp"
#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "config.hpp"
#include "UI/Settings.hpp"
#include "git-info.h"
#include "Helpers/getMainFlowCoordinator.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"

// Define the Settings type in the ImageCoverExpander::UI namespace
DEFINE_TYPE(ImageCoverExpander::UI, Settings);

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace ImageCoverExpander;

// Global variables to track settings updates and original enabled value
bool updatedSettings = false;
bool originalEnabledValue = false;

// Method called when the view is activated
void ImageCoverExpander::UI::Settings::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling)
{
    if (!firstActivation)
        return;

    // Parse and construct the settings UI from the BSML file
    BSML::parse_and_construct(Assets::Settings_bsml, this->get_transform(), this);

    // Initialize settings state
    updatedSettings = false;
    originalEnabledValue = get_enabledValue();
    versionText->text = GIT_VERSION;

    // Uncomment the following lines for hot reload functionality
    //#ifdef HotReload
    //    fileWatcher->checkInterval = 0.5f;
    //    fileWatcher->filePath = "/sdcard/bsml/GraphicsTweaks/SettingsView.bsml";
    //#endif
}

// Method called when the settings view is deactivated
void ImageCoverExpander::UI::Settings::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
{
    if (updatedSettings) {
        auto mfc = GetMainFlowCoordinator();

        // Restart the game if the enabled value has changed
        if (mfc && originalEnabledValue != get_enabledValue()) {
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
