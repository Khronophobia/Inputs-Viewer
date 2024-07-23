#pragma once
#include "IVBackgroundSprite.hpp"
#include "IVInputType.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class InputSprite : public BackgroundSprite {
public:
    InputSprite();
    static InputSprite* create(InputType input);
    bool init(InputType input);
    void press(bool pressed, bool updateTotalInputs = true);
    void updateInputDisplay();
    void setShowTotalInputs(bool show);
    void onSettingChange(SettingEventType type);
protected:
    bool m_pressed = false;
    unsigned m_totalInputs = 0;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
    geode::EventListener<IVSettingFilter> m_colorListener;
};

GEODE_NS_IV_END