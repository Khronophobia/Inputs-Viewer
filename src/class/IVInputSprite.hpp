#pragma once
#include "IVBackgroundSprite.hpp"
#include "IVLevelSettings.hpp"
#include <IVEvent.hpp>
#include <Geode/loader/SettingV3.hpp>

GEODE_NS_IV_BEGIN

enum class CPSCalculation {
    RealTime,
    PerSecond,
};

class InputSprite : public BackgroundSprite {
public:
    InputSprite(LevelSettings const& setting);
    static InputSprite* create(LevelSettings const& setting, PlayerButton input, char const* playerText);
    bool init(PlayerButton input, char const* playerText);
public:
    void press(bool pressed, bool updateCounters = true);
    void setShowTotalInputs(bool show);
    void setCPSMode(CPSCalculation mode);
    void setShowCPS(bool show);
    void setMinimal(bool minimal);
    void setLevelSettings(LevelSettings const& settings);
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
    std::reference_wrapper<LevelSettings const> m_currentSetting;
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