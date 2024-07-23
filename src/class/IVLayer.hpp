#pragma once
#include "IVPlayerInputNode.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class InputsViewLayer : public cocos2d::CCLayer {
public:
    InputsViewLayer();
    static InputsViewLayer* create();
    bool init() override;
    void refreshDisplay();
    void onSettingEvent(SettingEventType type);
public:
    PlayerInputNode* m_p1InputNode = nullptr;
    PlayerInputNode* m_p2InputNode = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END