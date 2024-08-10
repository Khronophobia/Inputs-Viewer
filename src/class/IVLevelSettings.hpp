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
    static matjson::Value to_json(inputs_viewer::LevelSettings const& value);
    static inputs_viewer::LevelSettings from_json(matjson::Value const& value);
    static bool is_json(matjson::Value const& value);
};