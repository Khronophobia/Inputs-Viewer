#pragma once

template<>
struct matjson::Serialize<cocos2d::CCPoint> {
    static matjson::Value to_json(cocos2d::CCPoint const& value);
    static cocos2d::CCPoint from_json(matjson::Value const& value);
    static bool is_json(matjson::Value const& value);
};

template<>
struct matjson::Serialize<cocos2d::CCSize> {
    static matjson::Value to_json(cocos2d::CCSize const& value);
    static cocos2d::CCSize from_json(matjson::Value const& value);
    static bool is_json(matjson::Value const& value);
};