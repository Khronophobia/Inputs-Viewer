#pragma once

template<>
struct matjson::Serialize<cocos2d::CCPoint> {
    static matjson::Value toJson(cocos2d::CCPoint const& value);
    static geode::Result<cocos2d::CCPoint> fromJson(matjson::Value const& value);
};