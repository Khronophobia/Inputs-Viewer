#pragma once
#include "IVInputsViewLayer.hpp"
#include "IVTransformSlider.hpp"
#include "IVLevelSettings.hpp"

GEODE_NS_IV_BEGIN

class SettingsLayer : public geode::Popup<GJBaseGameLayer*> {
public:
    SettingsLayer(LevelSettingsType settingType);
    static SettingsLayer* create(LevelSettingsType, GJBaseGameLayer* gameLayer);
public:
    void onModSettings(cocos2d::CCObject*);
    void onClassic(cocos2d::CCObject*);
    void onPlatformer(cocos2d::CCObject*);
public:
    void onExit() override;
protected:
    bool setup(GJBaseGameLayer* gameLayer) override;
    void setLevelSettings(LevelSettingsType type);
    void updateSettingNodes();
    CCMenuItemToggler* createCheckbox(bool LevelSettings::* member, char const* text, std::optional<SettingEventType> postEvent, cocos2d::Anchor anchor, cocos2d::CCPoint const& offset = {}, char const* description = nullptr);
protected:
    LevelSettingsType m_currentSettingType;
    std::reference_wrapper<LevelSettings> m_currentSetting;
    CCMenuItemSpriteExtra* m_classicBtn = nullptr;
    CCMenuItemSpriteExtra* m_platformerBtn = nullptr;
    InputsViewLayer* m_inputsLayer = nullptr;
    TransformSlider* m_p1Slider = nullptr;
    TransformSlider* m_p2Slider = nullptr;
    CCMenuItemToggler* m_totalInputsCheckbox = nullptr;
    CCMenuItemToggler* m_cpsCheckbox = nullptr;
    CCMenuItemToggler* m_hideLRCheckbox = nullptr;
};

GEODE_NS_IV_END