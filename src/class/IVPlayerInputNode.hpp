#pragma once
#include "IVInputSprite.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class PlayerInputNode : public cocos2d::CCNode {
public:
    PlayerInputNode();
    static PlayerInputNode* create(char const* playerText);
    bool init(char const* playerText);
    void handleButton(bool down, PlayerButton input, bool updateTotalInputs = true);
    void onSettingEvent(SettingEventType type);
    void setShowTotalInputs(bool show);
    void releaseAllButtons();
protected:
    InputSprite* m_jumpButton = nullptr;
    InputSprite* m_leftButton = nullptr;
    InputSprite* m_rightButton = nullptr;
    BackgroundSprite* m_playerIndicator = nullptr;
    cocos2d::CCLabelBMFont* m_playerIndicatorText = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END