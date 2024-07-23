#pragma once
#include "IVInputSprite.hpp"
#include "IVInputType.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class PlayerInputNode : public cocos2d::CCNode {
public:
    PlayerInputNode();
    static PlayerInputNode* create();
    bool init() override;
    void handleButton(bool down, InputType input, bool updateTotalInputs = true);
    void onSettingEvent(SettingEventType type);
    void setShowTotalInputs(bool show);
protected:
    InputSprite* m_jumpButton = nullptr;
    InputSprite* m_leftButton = nullptr;
    InputSprite* m_rightButton = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END