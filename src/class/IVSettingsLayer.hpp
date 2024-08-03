#pragma once
#include "IVInputsViewLayer.hpp"
#include "IVTransformSlider.hpp"

GEODE_NS_IV_BEGIN

class SettingsLayer : public geode::Popup<GJBaseGameLayer*> {
public:
    static SettingsLayer* create(GJBaseGameLayer* gameLayer);
public:
    void onModSettings(cocos2d::CCObject*);
public:
    void onExit() override;
protected:
    bool setup(GJBaseGameLayer* gameLayer) override;
    CCMenuItemToggler* createCheckbox(bool& checkValue, char const* text, std::optional<SettingEventType> postEvent, cocos2d::Anchor anchor, cocos2d::CCPoint const& offset = {}, char const* description = nullptr);
protected:
    InputsViewLayer* m_inputsLayer = nullptr;
    TransformSlider* m_p1Slider = nullptr;
    TransformSlider* m_p2Slider = nullptr;
};

GEODE_NS_IV_END