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
    void setShowCPS(bool show);
    void setMinimal(bool minimal);
    void updateButtonAppearance();
    void onSettingChange(SettingEventType type);
    void updateCPS(float dt);
protected:
    void updateLabelWidth(cocos2d::CCLabelBMFont* font);
protected:
    bool m_pressed = false;
    unsigned m_totalInputs = 0;
    unsigned m_clicksPerSecond = 0;
    float m_textScale = 0.5f;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_playerText = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
    cocos2d::CCLabelBMFont* m_cpsText = nullptr;
};

GEODE_NS_IV_END