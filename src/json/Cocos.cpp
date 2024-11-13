#include "Cocos.hpp"

using namespace geode::prelude;

// CCPoint

matjson::Value matjson::Serialize<CCPoint>::toJson(CCPoint const& value) {
    return std::vector<matjson::Value>{value.x, value.y};
}

geode::Result<cocos2d::CCPoint> matjson::Serialize<CCPoint>::fromJson(matjson::Value const& value) {
    if (value.isObject()) {
        if (value.contains("x") && value.contains("y")) {
            auto x = GEODE_UNWRAP(value["x"].as<float>());
            auto y = GEODE_UNWRAP(value["y"].as<float>());
            return Ok(CCPoint{x, y});
        }
        return Err("Expected object to have \"x\" and \"y\" field");
    } else if (value.isArray()) {
        if (value.asArray().unwrap().size() < 2) return Err("Expected array to have 2 elements");

        auto x = GEODE_UNWRAP(value[0].as<float>());
        auto y = GEODE_UNWRAP(value[1].as<float>());
        return Ok(CCPoint{x, y});
    }

    return Err("Expected json to be an object or an array");
}