#pragma once
#include "IVPlayerInputNode.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

struct LevelSettings;

class InputsViewLayer : public cocos2d::CCLayer {
public:
    InputsViewLayer(LevelSettings const& settings);
    static InputsViewLayer* create(LevelSettings const& settings, GJBaseGameLayer* gameLayer);
    bool init(GJBaseGameLayer* gameLayer);
public:
    void setLevelSettings(LevelSettings const& settings);
    void refreshDisplay();
    void onSettingEvent(SettingEventType type);
public:
    std::reference_wrapper<LevelSettings const> m_currentSetting;
    PlayerInputNode* m_p1InputNode = nullptr;
    PlayerInputNode* m_p2InputNode = nullptr;
    GJBaseGameLayer* m_gameLayer = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END