#pragma once
#include "IVLevelSettings.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include <Geode/loader/SettingEvent.hpp>
#pragma GCC diagnostic pop

GEODE_NS_IV_BEGIN

using RGBASettingFilter = geode::GeodeSettingChangedFilter<cocos2d::ccColor4B>;
using RGBASettingListener = geode::EventListener<RGBASettingFilter>;

class IVManager {
public:
    IVManager();
    static IVManager& get();
    static NodeTransform getDefaultP1Transform();
    static NodeTransform getDefaultP2Transform();
public:
    cocos2d::ccColor4B m_backgroundPressColor;
    cocos2d::ccColor4B m_backgroundReleaseColor;
    cocos2d::ccColor4B m_outlinePressColor;
    cocos2d::ccColor4B m_outlineReleaseColor;
    cocos2d::ccColor4B m_textPressColor;
    cocos2d::ccColor4B m_textReleaseColor;

    LevelSettings m_settingClassic;
    LevelSettings m_settingPlatformer;
#if 0
    NodeTransform m_p1Transform;
    NodeTransform m_p2Transform;
    bool m_showTotalInputs;
    bool m_showCPS;
    bool m_minimalIfNonPlatformer;
#endif
protected:
    RGBASettingListener m_backgroundPressListener;
    RGBASettingListener m_backgroundReleaseListener;
    RGBASettingListener m_outlinePressListener;
    RGBASettingListener m_outlineReleaseListener;
    RGBASettingListener m_textPressListener;
    RGBASettingListener m_textReleaseListener;
};

GEODE_NS_IV_END