#include "NodeTransform.hpp"
#include "Cocos.hpp" // IWYU pragma: keep
#include "helper.hpp"

using namespace geode::prelude;

void NodeTransform::applyTransform(CCNode* node) const {
    node->setPosition(position);
    node->setScale(scale);
    node->setVisible(isVisible);
}

void NodeTransform::setValues(CCNode* node) {
    position = node->getPosition();
    scale = node->getScale();
    isVisible = node->isVisible();
}

bool matjson::Serialize<NodeTransform>::is_json(matjson::Value const& value) {
    return verifyJsonObject<CCPoint>(value, "position") &&
        verifyJsonObject<float>(value, "scale") &&
        verifyJsonObject<bool>(value, "visible");
}

matjson::Value matjson::Serialize<NodeTransform>::to_json(NodeTransform const& value) {
    return matjson::Object{
        {"position", value.position},
        {"scale", value.scale},
        {"visible", value.isVisible}
    };
}

NodeTransform matjson::Serialize<NodeTransform>::from_json(matjson::Value const& value) {
    return {
        .position = value["position"].as<CCPoint>(),
        .scale = static_cast<float>(value["scale"].as_double()),
        .isVisible = value["visible"].as_bool()
    };
}