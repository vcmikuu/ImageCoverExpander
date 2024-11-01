#pragma once

#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Settings/SliderSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/DropdownListSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/ListSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/StringSetting.hpp"
#include "bsml/shared/BSML/ViewControllers/HotReloadViewController.hpp"
#include "bsml/shared/BSML/Components/ClickableText.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "HMUI/ViewController.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(ImageCoverExpander::UI, Settings, HMUI::ViewController,

    DECLARE_SIMPLE_DTOR();
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemDisabling);

    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, UpdateSettings);

    DECLARE_INSTANCE_FIELD(UnityW<BSML::BoolSetting>, enabledSetting);

    DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, imageCoverExpanderText);
    DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, versionText);

    DECLARE_INSTANCE_FIELD(UnityW<BSML::TextMeshPro>, restartHintText);

    DECLARE_BSML_PROPERTY(bool, enabledValue);



)
