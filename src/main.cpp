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


    auto* imageCoverTransform = self->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

    imageCoverTransform->set_sizeDelta(Vector2(70.5, 58.0));
    imageCoverTransform->set_localPosition(Vector3(-34.4, -56, 0));
    imageCoverTransform->SetAsFirstSibling();

    auto* imageView = imageCoverTransform->GetComponent<ImageView*>();

    imageView->set_color(Color(0.5, 0.5, 0.5, 1));
    imageView->set_preserveAspect(false);
}


extern "C" __attribute__((visibility("default"))) void setup(CModInfo* info)
{
    info->version = VERSION;
    info->id = MOD_ID;
    info->version_long = 0;
    modInfo.assign(*info);

    // Init things
    getModConfig().Init(modInfo);
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" __attribute__((visibility("default"))) void late_load()
{
    il2cpp_functions::Init();


    auto logger = Paper::ConstLoggerContext("imagecoverexpander");
    // Install Hooks
    getLogger().info("Installing hooks...");
    INSTALL_HOOK(logger, m_DidActivate);
    getLogger().info("Installed all hooks!");
}