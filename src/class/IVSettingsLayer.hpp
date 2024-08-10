#pragma once
#include "IVInputsViewLayer.hpp"
#include "IVTransformSlider.hpp"
#include "IVLevelSettings.hpp"

GEODE_NS_IV_BEGIN

class SettingsLayer : public geode::Popup<GJBaseGameLayer*> {
public:
    SettingsLayer();
    static SettingsLayer* create(GJBaseGameLayer* gameLayer);
public:
    void onModSettings(cocos2d::CCObject*);
public:
    void onExit() override;
protected:
    bool setup(GJBaseGameLayer* gameLayer) override;
    void updateSettingValues();
    CCMenuItemToggler* createCheckbox(bool LevelSettings::* member, char const* text, std::optional<SettingEventType> postEvent, cocos2d::Anchor anchor, cocos2d::CCPoint const& offset = {}, char const* description = nullptr);
protected:
    std::reference_wrapper<LevelSettings> m_currentSetting;
    InputsViewLayer* m_inputsLayer = nullptr;
    TransformSlider* m_p1Slider = nullptr;
    TransformSlider* m_p2Slider = nullptr;
    CCMenuItemToggler* m_totalInputsCheckbox = nullptr;
    CCMenuItemToggler* m_cpsCheckbox = nullptr;
    CCMenuItemToggler* m_hideLRCheckbox = nullptr;
};

GEODE_NS_IV_END