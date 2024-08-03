#include "IVSettingsLayer.hpp"
#include "IVManager.hpp"
#include <Geode/ui/GeodeUI.hpp>
#include <IVEvent.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

SettingsLayer* SettingsLayer::create() {
    auto ret = new (std::nothrow) SettingsLayer;
    if (ret && ret->initAnchored(350.f, 260.f, "square02_001.png")) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool SettingsLayer::setup() {
    this->setTitle("Inputs Viewer Config");
    this->setColor({127, 127, 127});
    this->setOpacity(255);
    m_noElasticity = true;
    m_bgSprite->setOpacity(63);

    auto modSettingsBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png"),
        this, menu_selector(SettingsLayer::onModSettings)
    );
    m_buttonMenu->addChildAtPosition(modSettingsBtn, Anchor::TopRight, ccp(-3.f, -3.f));

    m_inputsLayer = InputsViewLayer::create();
    m_inputsLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->insertBefore(m_inputsLayer, m_mainLayer);

    m_p1Slider = TransformSlider::create(IVManager::get().m_p1Transform, m_inputsLayer->m_p1InputNode, "P1 Input", IVManager::getDefaultP1Transform);
    m_mainLayer->addChildAtPosition(m_p1Slider, Anchor::Center, ccp(-80.f, 20.f));

    m_p2Slider = TransformSlider::create(IVManager::get().m_p2Transform, m_inputsLayer->m_p2InputNode, "P2 Input", IVManager::getDefaultP2Transform);
    m_mainLayer->addChildAtPosition(m_p2Slider, Anchor::Center, ccp(80.f, 20.f));

    this->createCheckbox(IVManager::get().m_showTotalInputs, "Show Total Inputs", SettingEventType::TotalInputsCounter, Anchor::Center, ccp(-70.f, -70.f));

    return true;
}

CCMenuItemToggler* SettingsLayer::createCheckbox(bool& checkValue, char const* text, std::optional<SettingEventType> postEvent, Anchor anchor, CCPoint const& offset) {
    auto checkbox = CCMenuItemExt::createTogglerWithStandardSprites(0.7f, [this, &checkValue, postEvent](CCMenuItemToggler* btn) {
        checkValue = !btn->isToggled();
        if (postEvent) {
            IVSettingEvent(*postEvent).post();
        }
    });
    checkbox->toggle(checkValue);
    m_buttonMenu->addChildAtPosition(checkbox, anchor, offset);

    auto label = CCLabelBMFont::create(text, "bigFont.fnt");
    label->setScale(0.5f);
    label->setAnchorPoint(ccp(0.f, 0.5f));
    m_mainLayer->addChildAtPosition(label, anchor, offset + ccp(14.f, 0.f));

    return checkbox;
}

void SettingsLayer::onModSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void SettingsLayer::onExit() {
    IVSettingEvent(SettingEventType::RefreshView).post();
    Popup::onExit();
}

GEODE_NS_IV_END