#pragma once
#include "IVBackgroundSprite.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class InputSprite : public BackgroundSprite {
public:
    static InputSprite* create(PlayerButton input, char const* playerText);
    bool init(PlayerButton input, char const* playerText);
    void press(bool pressed, bool updateInputs = true);
    void updateInputDisplay();
    void setShowTotalInputs(bool show);
    void setMinimal(bool minimal);
    void onSettingChange(SettingEventType type);
protected:
    bool m_pressed = false;
    unsigned m_totalInputs = 0;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_playerText = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
};

GEODE_NS_IV_END