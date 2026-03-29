#include <Geode/modify/PauseLayer.hpp>
#include <class/IVSettingsLayer.hpp>

using namespace geode::prelude;

struct PauseLayerHook : Modify<PauseLayerHook, PauseLayer> {
    $override
    void customSetup() {
        PauseLayer::customSetup();
        if (!Mod::get()->getSettingValue<bool>("ui-setting-in-pause")) return;

        if (auto menu = getChildByID("right-button-menu")) {
            auto settingBtn = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSprite("settingsIcon.png"_spr, 1.f, CircleBaseColor::Green, CircleBaseSize::Tiny),
                this, menu_selector(PauseLayerHook::onIVSetting)
            );
            menu->addChild(settingBtn);

            menu->updateLayout();
        }
    }
    void onIVSetting(CCObject*) {
        if (PlayLayer::get()->m_levelSettings->m_platformerMode) {
            inputs_viewer::SettingsLayer::create(inputs_viewer::LevelSettingsType::Platformer, true)->show();
        } else {
            inputs_viewer::SettingsLayer::create(inputs_viewer::LevelSettingsType::Classic, true)->show();
        }
    }
};