#include <Geode/modify/PauseLayer.hpp>
#include <class/IVSettingsLayer.hpp>

using namespace geode::prelude;

struct IVPauseLayer : Modify<IVPauseLayer, PauseLayer> {
    $override
    void customSetup() {
        PauseLayer::customSetup();

        if (auto menu = getChildByID("right-button-menu")) {
            auto settingBtn = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSprite("settingsIcon.png"_spr, 0.8f, CircleBaseColor::Green, CircleBaseSize::Tiny),
                this, menu_selector(IVPauseLayer::onIVSetting)
            );
            menu->addChild(settingBtn);

            menu->updateLayout();
        }
    }
    void onIVSetting(CCObject*) {
        inputs_viewer::SettingsLayer::create()->show();
    }
};