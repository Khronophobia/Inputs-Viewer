#pragma once
#include "IVLevelSettings.hpp"
#include <Geode/loader/SettingV3.hpp>

GEODE_NS_IV_BEGIN

using RGBASettingFilter = geode::SettingChangedFilterV3;
using RGBASettingListener = geode::EventListener<RGBASettingFilter>;

class IVManager {
public:
    IVManager();
    static IVManager& get();
    static NodeTransform getDefaultP1Transform();
    static NodeTransform getDefaultP2Transform();
    LevelSettings& getLevelSettings(LevelSettingsType type) noexcept;
public:
    bool m_isInSetting;
    cocos2d::ccColor4B m_backgroundPressColor;
    cocos2d::ccColor4B m_backgroundReleaseColor;
    cocos2d::ccColor4B m_outlinePressColor;
    cocos2d::ccColor4B m_outlineReleaseColor;
    cocos2d::ccColor4B m_textPressColor;
    cocos2d::ccColor4B m_textReleaseColor;

    LevelSettings m_settingClassic;
    LevelSettings m_settingPlatformer;
protected:
    RGBASettingListener m_backgroundPressListener;
    RGBASettingListener m_backgroundReleaseListener;
    RGBASettingListener m_outlinePressListener;
    RGBASettingListener m_outlineReleaseListener;
    RGBASettingListener m_textPressListener;
    RGBASettingListener m_textReleaseListener;
};

GEODE_NS_IV_END