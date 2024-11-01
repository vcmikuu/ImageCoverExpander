#include "UI/Settings.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Color.hpp"
#include "bsml/shared/BSML/MainThreadScheduler.hpp"
#include "config.hpp"
#include "bsml/shared/BSML/SharedCoroutineStarter.hpp"
#include "bsml/shared/BSML-Lite/Creation/Text.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "assets.hpp"


DEFINE_TYPE(ImageCoverExpander::UI, Settings);

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace ImageCoverExpander;

//this might be stealed from graphictweaks
void ImageCoverExpander::UI::Settings::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemDisabling)
{
    if (!firstActivation)
        return;

    BSML::parse_and_construct(Assets::Settings_bsml, this->get_transform(), this);

    //#ifdef HotReload
    //    fileWatcher->checkInterval = 0.5f;
    //    fileWatcher->filePath = "/sdcard/bsml/GraphicsTweaks/SettingsView.bsml";
    //#endif
};


void ImageCoverExpander::UI::Settings::UpdateSettings() {
    //
}


void ImageCoverExpander::UI::Settings::PostParse() {
    //
}

bool ImageCoverExpander::UI::Settings::get_enabledValue() {
    return getModConfig().Active.GetValue();
}

void ImageCoverExpander::UI::Settings::set_enabledValue(bool value) {
    return getModConfig().Active.SetValue(value);
    //if (value) {
    //    Logger.info("ImageCoverExpander Set Value True");
    //    getModConfig().Active.SetValue(true);
    //} else {
    //    Logger.info("ImageCoverExpander Set Value False");
    //    getModConfig().Active.SetValue(false);
    //}
}
