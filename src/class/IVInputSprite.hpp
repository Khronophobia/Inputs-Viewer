#pragma once
#include "IVBackgroundSprite.hpp"
#include <IVEvent.hpp>
#include <Geode/loader/SettingV3.hpp>

GEODE_NS_IV_BEGIN

enum class CPSCalculation {
    RealTime,
    PerSecond,
};

class PlayerInputNode;

class InputSprite : public BackgroundSprite {
public:
    InputSprite();
    static InputSprite* create(PlayerInputNode* inputNode, PlayerButton button, char const* playerText);
    bool init(PlayerInputNode* inputNode, PlayerButton button, char const* playerText);
public:
    void press(bool pressed, bool updateCounters = true);
    void setShowTotalInputs(bool show);
    void setCPSMode(CPSCalculation mode);
    void setShowCPS(bool show);
    void setMinimal(bool minimal);
    void updateButtonAppearance();
    void onSettingChange(SettingEventType type);
public:
    void visit() override;
protected:
    void updateCPSCounter();
    void updateTotalInputsDisplay();
    void updateCPSDisplay();
    void cpsSchedule(float dt);
    void subtractCPS();
    void updateLabelWidth(cocos2d::CCLabelBMFont* font);
protected:
    PlayerInputNode* m_inputNode = nullptr;
    bool m_shouldUpdateTotalInputsDisplay = false;
    bool m_shouldUpdateCPSDisplay = false;
    unsigned m_totalInputs = 0;
    unsigned m_clicksPerSecond = 0;
    unsigned m_displayedCPS = 0;
    CPSCalculation m_currentCPSCalculation;
    float m_textScale = 0.5f;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_playerText = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
    cocos2d::CCLabelBMFont* m_cpsText = nullptr;
    geode::EventListener<geode::SettingChangedFilterV3> m_cpsSettingListener;
};

GEODE_NS_IV_END