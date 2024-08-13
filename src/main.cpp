#include "main.hpp"

#include "scotland2/shared/modloader.h"

#include "custom-types/shared/register.hpp"

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
using namespace GlobalNamespace;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
using namespace UnityEngine;

#include "UnityEngine/UI/Button.hpp"
using namespace UnityEngine::UI;

#include "HMUI/ImageView.hpp"
using namespace HMUI;


MAKE_HOOK_MATCH(m_DidActivate,
                &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
                void,
                GlobalNamespace::StandardLevelDetailViewController* self,
                bool firstActivation,
                bool addedToHeirarchy,
                bool screenSystemEnabling) {

    m_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    if(getModConfig().Active.GetValue()){
        Logger.info("ImageCoverExpander Set Value True");
        getModConfig().Active.SetValue(true);
    } else{
        Logger.info("ImageCoverExpander Set Value False");
        getModConfig().Active.SetValue(false);
    }

    if(getModConfig().Active.GetValue()){
        Logger.info("ImageCoverExpander Found Value Set As True, expanding Image");
        auto* imageCoverTransform = self->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

        imageCoverTransform->set_sizeDelta(Vector2(70.5, 58.0));
        imageCoverTransform->set_localPosition(Vector3(-34.4, -56, 0));
        imageCoverTransform->SetAsFirstSibling();

        auto* imageView = imageCoverTransform->GetComponent<ImageView*>();

        imageView->set_color(Color(0.5, 0.5, 0.5, 1));
        imageView->set_preserveAspect(false);
        imageView->_skew = 0.0f;
        imageView->__Refresh();
    } else{
        Logger.info("ImageCoverExpander Found Value Set As False, skipping expanding Image");
    }

}



void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){
        // Make Touchable
        self->get_gameObject()->AddComponent<HMUI::Touchable*>();

        // Create Container
        auto* container = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());
        
        // Add Options
        AddConfigValueToggle(container->get_transform(), getModConfig().Active);

    }
}


#pragma region Mod setup
/// @brief Called at the early stages of game loading
/// @param info
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;

    Logger.info("Completed setup!");
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();
    getModConfig().Init(modInfo);
    BSML::Init();

    BSML::Register::RegisterMainMenu("ImageCoverExpander", "ImageCoverExpander", "Hide/Show Bigger Image Cover Art", DidActivate);
    Logger.info("Installing hooks...");

    INSTALL_HOOK(Logger, m_DidActivate);

    Logger.info("Installed all hooks!");
}
#pragma endregion