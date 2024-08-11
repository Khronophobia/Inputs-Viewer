#pragma once
#include "IVInputSprite.hpp"
#include "IVLevelSettings.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class PlayerInputNode : public cocos2d::CCNode {
public:
    PlayerInputNode(LevelSettings const& setting);
    static PlayerInputNode* create(LevelSettings const& setting, char const* playerText);
    bool init(char const* playerText);
public:
    void handleButton(bool down, PlayerButton input, bool updateCounters = true);
    void refreshAppearance();
    void setShowTotalInputs(bool show);
    void setShowCPS(bool show);
    void releaseAllButtons();
    void setLevelSettings(LevelSettings const& settings);
protected:
    bool isMinimalMode() const;
protected:
    std::reference_wrapper<LevelSettings const> m_currentSetting;
    InputSprite* m_jumpButton = nullptr;
    InputSprite* m_leftButton = nullptr;
    InputSprite* m_rightButton = nullptr;
    BackgroundSprite* m_playerIndicator = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END