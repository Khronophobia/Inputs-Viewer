#pragma once
#include "IVBackgroundSpriteColored.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class InputSprite : public BackgroundSpriteColored {
public:
    static InputSprite* create(PlayerButton input);
    bool init(PlayerButton input);
    void press(bool pressed, bool updateInputs = true);
    void updateInputDisplay();
    void setShowTotalInputs(bool show);
    void onSettingChange(SettingEventType type);
protected:
    bool m_pressed = false;
    unsigned m_totalInputs = 0;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
};

GEODE_NS_IV_END