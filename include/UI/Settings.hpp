#pragma once

#include "bsml/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(ImageCoverExpander::UI, Settings, HMUI::ViewController){
    DECLARE_SIMPLE_DTOR();

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemDisabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate, &HMUI::ViewController::DidDeactivate, bool removedFromHierarchy, bool screenSystemDisabling);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, versionText);

    DECLARE_BSML_PROPERTY(bool, enabledValue);
    DECLARE_BSML_PROPERTY(float, brightnessValue);
    DECLARE_BSML_PROPERTY(float, opacityValue);
};
