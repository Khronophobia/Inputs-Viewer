#include "Cocos.hpp"
#include "NodeTransform.hpp"
#include "helper.hpp"

using namespace geode::prelude;

// CCPoint

bool matjson::Serialize<CCPoint>::is_json(matjson::Value const& value) {
    if (value.is_object()) {
        return value.contains("x") && value.contains("y");
    } else if (value.is_array()) {
        return value.as_array().size() == 2;
    }

    return false;
}

matjson::Value matjson::Serialize<CCPoint>::to_json(CCPoint const& value) {
    return matjson::Object{
        {"x", value.x},
        {"y", value.y}
    };
}

CCPoint matjson::Serialize<CCPoint>::from_json(matjson::Value const& value) {
    if (value.is_object()) {
        if (value.is<CCSize>()) return value.as<CCSize>();
        else {
            return {
                static_cast<float>(value["x"].as_double()),
                static_cast<float>(value["y"].as_double())
            };
        }
    } else if (value.is_array()) {
        if (value.as_array().size() != 2) throw matjson::JsonException("Expected array to have 2 elements");

        return {
            static_cast<float>(value[0].as_double()),
            static_cast<float>(value[1].as_double())
        };
    }

    throw matjson::JsonException("Expected json to be an object or array");
}

// CCSize

bool matjson::Serialize<CCSize>::is_json(matjson::Value const& value) {
    if (value.is_object()) {
        return value.contains("width") && value.contains("height");
    } else if (value.is_array()) {
        return value.as_array().size() == 2;
    }

    return value.is_number();
}

matjson::Value matjson::Serialize<CCSize>::to_json(CCSize const& value) {
    return matjson::Object{
        {"width", value.width},
        {"height", value.height}
    };
}

CCSize matjson::Serialize<CCSize>::from_json(matjson::Value const& value) {
    if (value.is_object()) {
        if (value.is<CCPoint>()) return value.as<CCPoint>();
        else {
            return {
                static_cast<float>(value["width"].as_double()),
                static_cast<float>(value["height"].as_double())
            };
        }
    } else if (value.is_array()) {
        if (value.as_array().size() != 2) throw matjson::JsonException("Expected array to have 2 elements");

        return {
            static_cast<float>(value[0].as_double()),
            static_cast<float>(value[1].as_double())
        };
    } else if (value.is_number()) {
        return {
            static_cast<float>(value.as_double()),
            static_cast<float>(value.as_double())
        };
    }

    throw matjson::JsonException("Expected json to be an object, array, or a number");
}

// NodeTransform

bool matjson::Serialize<NodeTransform>::is_json(matjson::Value const& value) {
    return verifyJsonObject<CCPoint>(value, "position") &&
        verifyJsonObject<float>(value, "scale");
}

matjson::Value matjson::Serialize<NodeTransform>::to_json(NodeTransform const& value) {
    return matjson::Object{
        {"position", value.position},
        {"scale", value.scale}
    };
}

NodeTransform matjson::Serialize<NodeTransform>::from_json(matjson::Value const& value) {
    return {
        .position = value["position"].as<CCPoint>(),
        .scale = static_cast<float>(value["scale"].as_double()),
    };
}