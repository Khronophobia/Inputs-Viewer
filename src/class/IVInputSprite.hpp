#pragma once
#include "IVBackgroundSprite.hpp"
#include <IVEvent.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include <Geode/loader/SettingEvent.hpp>
#pragma GCC diagnostic pop

GEODE_NS_IV_BEGIN

enum class CPSCalculation {
    RealTime,
    PerSecond,
};

class InputSprite : public BackgroundSprite {
public:
    InputSprite();
    static InputSprite* create(PlayerButton input, char const* playerText);
    bool init(PlayerButton input, char const* playerText);
public:
    void press(bool pressed, bool updateInputs = true);
    void setShowTotalInputs(bool show);
    void setShowCPS(bool show);
    void setMinimal(bool minimal);
    void updateButtonAppearance();
    void onSettingChange(SettingEventType type);
public:
    void visit() override;
protected:
    void updateTotalInputsDisplay();
    void updateCPSDisplay();
    void cpsSchedule(float dt);
    void subtractCPS();
    void updateLabelWidth(cocos2d::CCLabelBMFont* font);
protected:
    bool m_shouldUpdateTotalInputsDisplay = false;
    bool m_shouldUpdateCPSDisplay = false;
    unsigned m_totalInputs = 0;
    unsigned m_clicksPerSecond = 0;
    unsigned m_displayedCPS;
    CPSCalculation m_currentCPSCalculation;
    float m_textScale = 0.5f;
    cocos2d::CCSprite* m_inputSymbol = nullptr;
    cocos2d::CCLabelBMFont* m_playerText = nullptr;
    cocos2d::CCLabelBMFont* m_totalInputsText = nullptr;
    cocos2d::CCLabelBMFont* m_cpsText = nullptr;
    geode::EventListener<geode::GeodeSettingChangedFilter<std::string>> m_cpsSettingListener;
};

GEODE_NS_IV_END