#pragma once

struct NodeTransform {
    cocos2d::CCPoint position{};
    float scale{1.f};

    // Apply transform to a node
    void applyTransform(cocos2d::CCNode* node);
    // Set transform from a node
    void setValues(cocos2d::CCNode* node);
};

template<>
struct matjson::Serialize<NodeTransform> {
    static matjson::Value to_json(NodeTransform const& value);
    static NodeTransform from_json(matjson::Value const& value);
    static bool is_json(matjson::Value const& value);
};