#pragma once
#include "IVInputSprite.hpp"
#include "IVLevelSettings.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class PlayerInputNode : public cocos2d::CCNode {
public:
    PlayerInputNode(LevelSettings const& setting);
    static PlayerInputNode* create(LevelSettings const& setting, GJBaseGameLayer* gameLayer, char const* playerText);
    bool init(GJBaseGameLayer* gameLayer, char const* playerText);
public:
    void handleButton(bool down, PlayerButton input, bool updateTotalInputs = true);
    void refreshAppearance();
    void setShowTotalInputs(bool show);
    void setShowCPS(bool show);
    void releaseAllButtons();
    void setLevelSettings(LevelSettings const& settings);
protected:
    bool isMinimalMode() const;
protected:
    std::reference_wrapper<LevelSettings const> m_currentSetting;
    GJBaseGameLayer* m_gameLayer = nullptr;
    InputSprite* m_jumpButton = nullptr;
    InputSprite* m_leftButton = nullptr;
    InputSprite* m_rightButton = nullptr;
    BackgroundSprite* m_playerIndicator = nullptr;
    cocos2d::CCLabelBMFont* m_playerIndicatorText = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END