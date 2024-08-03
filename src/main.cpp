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




static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be
// removed if those are in use
Configuration &getConfig() {
  static Configuration config(modInfo);
  return config;
}

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


// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  getConfig().Load();

  // File logging
  Paper::Logger::RegisterFileContextId(PaperLogger.tag);

  PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
  il2cpp_functions::Init();

  PaperLogger.info("Installing hooks...");

  PaperLogger.info("Installed all hooks!");
}