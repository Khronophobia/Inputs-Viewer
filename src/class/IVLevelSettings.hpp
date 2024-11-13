#pragma once
#include <json/NodeTransform.hpp>

GEODE_NS_IV_BEGIN

struct LevelSettings {
    NodeTransform p1Transform;
    NodeTransform p2Transform;
    bool showTotalInputs = false;
    bool showCPS = false;
    bool hideLeftRight = false;
};

enum class LevelSettingsType {
    Classic,
    Platformer
};

GEODE_NS_IV_END

template<>
struct matjson::Serialize<inputs_viewer::LevelSettings> {
    static matjson::Value toJson(inputs_viewer::LevelSettings const& value);
    static geode::Result<inputs_viewer::LevelSettings> fromJson(matjson::Value const& value);
};