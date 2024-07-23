#pragma once
#include <Geode/loader/SettingEvent.hpp>
#include <json/NodeTransform.hpp>

GEODE_NS_IV_BEGIN

using RGBASettingFilter = geode::GeodeSettingChangedFilter<cocos2d::ccColor4B>;
using RGBASettingListener = geode::EventListener<RGBASettingFilter>;

class IVManager {
public:
    IVManager();
    static IVManager& get();
public:
    cocos2d::ccColor4B m_backgroundPressColor;
    cocos2d::ccColor4B m_backgroundReleaseColor;
    cocos2d::ccColor4B m_outlinePressColor;
    cocos2d::ccColor4B m_outlineReleaseColor;
    cocos2d::ccColor4B m_textPressColor;
    cocos2d::ccColor4B m_textReleaseColor;

    NodeTransform m_p1Transform;
    NodeTransform m_p2Transform;
    bool m_showTotalInputs;
protected:
    RGBASettingListener m_backgroundPressListener;
    RGBASettingListener m_backgroundReleaseListener;
    RGBASettingListener m_outlinePressListener;
    RGBASettingListener m_outlineReleaseListener;
    RGBASettingListener m_textPressListener;
    RGBASettingListener m_textReleaseListener;
};

GEODE_NS_IV_END