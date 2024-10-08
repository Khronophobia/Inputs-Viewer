#pragma once
#include "IVPlayerInputNode.hpp"
#include "IVLevelSettings.hpp"
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class InputsViewLayer : public cocos2d::CCLayer {
public:
    InputsViewLayer(LevelSettingsType type);
    static InputsViewLayer* create(LevelSettingsType type);
    bool init() override;
public:
    void handleButton(bool down, PlayerButton input, bool isP1, bool updateCounters = true);
    LevelSettings const& getLevelSettings() const noexcept;
    void setLevelSettings(LevelSettingsType type);
    void releaseAllButtons();
    void refreshDisplay();
    void onSettingEvent(SettingEventType type);
public:
    std::reference_wrapper<LevelSettings const> m_currentSetting;
    PlayerInputNode* m_p1InputNode = nullptr;
    PlayerInputNode* m_p2InputNode = nullptr;
    geode::EventListener<IVSettingFilter> m_settingListener;
};

GEODE_NS_IV_END