#include "IVSettingsLayer.hpp"
#include "IVManager.hpp"
#include <Geode/ui/GeodeUI.hpp>
#include <IVEvent.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

SettingsLayer::SettingsLayer(LevelSettingsType levelType)
    : m_currentSettingType(levelType)
    , m_currentSetting(IVManager::get().getLevelSettings(levelType))
{}

SettingsLayer* SettingsLayer::create(LevelSettingsType levelType) {
    auto ret = new (std::nothrow) SettingsLayer(levelType);
    if (ret && ret->initAnchored(350.f, 260.f, "square02_001.png")) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool SettingsLayer::setup() {
    IVManager::get().m_isInSetting = true;
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

    auto classicBtnSpr = ButtonSprite::create("Classic", "bigFont.fnt", "GJ_button_04.png");
    classicBtnSpr->setScale(0.5f);
    m_classicBtn = CCMenuItemSpriteExtra::create(
        classicBtnSpr, this, menu_selector(SettingsLayer::onClassic)
    );
    m_buttonMenu->addChildAtPosition(m_classicBtn, Anchor::TopLeft, ccp(62.f, 0.f));

    auto platformerBtnSpr = ButtonSprite::create("Platformer", "bigFont.fnt", "GJ_button_04.png");
    platformerBtnSpr->setScale(0.5f);
    m_platformerBtn = CCMenuItemSpriteExtra::create(
        platformerBtnSpr, this, menu_selector(SettingsLayer::onPlatformer)
    );
    m_buttonMenu->addChildAtPosition(m_platformerBtn, Anchor::TopLeft, ccp(154.f, 0.f));

    m_inputsLayer = InputsViewLayer::create(m_currentSettingType);
    m_inputsLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->insertBefore(m_inputsLayer, m_mainLayer);

    m_p1Slider = TransformSlider::create(m_currentSetting, &LevelSettings::p1Transform, m_inputsLayer->m_p1InputNode, "P1 Input", IVManager::getDefaultP1Transform);
    m_mainLayer->addChildAtPosition(m_p1Slider, Anchor::Center, ccp(-80.f, 20.f));

    m_p2Slider = TransformSlider::create(m_currentSetting, &LevelSettings::p2Transform, m_inputsLayer->m_p2InputNode, "P2 Input", IVManager::getDefaultP2Transform);
    m_mainLayer->addChildAtPosition(m_p2Slider, Anchor::Center, ccp(80.f, 20.f));

    m_totalInputsCheckbox = this->createCheckbox(&LevelSettings::showTotalInputs, "Show Total Inputs", SettingEventType::KeyAppearance, Anchor::Center, ccp(-90.f, -50.f));
    m_cpsCheckbox = this->createCheckbox(&LevelSettings::showCPS, "Show Clicks per Seconds", SettingEventType::KeyAppearance, Anchor::Center, ccp(-90.f, -80.f));
    m_hideLRCheckbox = this->createCheckbox(
        &LevelSettings::hideLeftRight, "Hide L&R Keys", SettingEventType::KeyAppearance, Anchor::Center, ccp(-90.f, -110.f),
        "Hide the left and right keys."
    );

    this->updateSettingNodes();
    return true;
}

void SettingsLayer::onClassic(CCObject*) {
    this->setLevelSettings(LevelSettingsType::Classic);
}

void SettingsLayer::onPlatformer(CCObject*) {
    this->setLevelSettings(LevelSettingsType::Platformer);
}

void SettingsLayer::setLevelSettings(LevelSettingsType type) {
    m_currentSettingType = type;
    m_currentSetting = IVManager::get().getLevelSettings(type);

    m_inputsLayer->setLevelSettings(type);
    m_p1Slider->setLevelSettings(type);
    m_p2Slider->setLevelSettings(type);
    this->updateSettingNodes();
}

void SettingsLayer::updateSettingNodes() {
    switch (m_currentSettingType) {
    case LevelSettingsType::Classic:
        static_cast<ButtonSprite*>(m_classicBtn->getNormalImage())->updateBGImage("GJ_button_01.png");
        m_classicBtn->setEnabled(false);
        static_cast<ButtonSprite*>(m_platformerBtn->getNormalImage())->updateBGImage("GJ_button_04.png");
        m_platformerBtn->setEnabled(true);
        break;
    case LevelSettingsType::Platformer:
        static_cast<ButtonSprite*>(m_platformerBtn->getNormalImage())->updateBGImage("GJ_button_01.png");
        m_platformerBtn->setEnabled(false);
        static_cast<ButtonSprite*>(m_classicBtn->getNormalImage())->updateBGImage("GJ_button_04.png");
        m_classicBtn->setEnabled(true);
        break;
    }

    m_totalInputsCheckbox->toggle(m_currentSetting.get().showTotalInputs);
    m_cpsCheckbox->toggle(m_currentSetting.get().showCPS);
    m_hideLRCheckbox->toggle(m_currentSetting.get().hideLeftRight);
}

CCMenuItemToggler* SettingsLayer::createCheckbox(bool LevelSettings::* member, char const* text, std::optional<SettingEventType> postEvent, Anchor anchor, CCPoint const& offset, char const* description) {
    auto checkbox = CCMenuItemExt::createTogglerWithStandardSprites(0.7f, [this, member, postEvent](CCMenuItemToggler* btn) {
        m_currentSetting.get().*member = !btn->isToggled();
        if (postEvent) {
            IVSettingEvent(*postEvent).post();
        }
    });
    m_buttonMenu->addChildAtPosition(checkbox, anchor, offset);

    auto label = CCLabelBMFont::create(text, "bigFont.fnt");
    label->limitLabelWidth(200.f, 0.5f, 0.1f);
    label->setAnchorPoint(ccp(0.f, 0.5f));
    m_mainLayer->addChildAtPosition(label, anchor, offset + ccp(14.f, 0.f));

    if (description) {
        auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoSpr->setScale(0.4f);

        auto infoBtn = CCMenuItemExt::createSpriteExtra(infoSpr, [text, description](CCMenuItemSpriteExtra*) {
            FLAlertLayer::create(text, description, "Ok")->show();
        });

        m_buttonMenu->addChildAtPosition(infoBtn, anchor, offset + ccp(-14.f, 14.f));
    }

    return checkbox;
}

void SettingsLayer::onModSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void SettingsLayer::onExit() {
    IVManager::get().m_isInSetting = false;
    IVSettingEvent(SettingEventType::RefreshView).post();
    Popup::onExit();
}

GEODE_NS_IV_END