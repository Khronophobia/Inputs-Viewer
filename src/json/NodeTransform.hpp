#pragma once

struct NodeTransform {
    cocos2d::CCPoint position{};
    float scale{1.f};
    bool isVisible = true;

    // Apply transform to a node
    void applyTransform(cocos2d::CCNode* node) const;
    // Set transform from a node
    void setValues(cocos2d::CCNode* node);
};

template<>
struct matjson::Serialize<NodeTransform> {
    static matjson::Value toJson(NodeTransform const& value);
    static geode::Result<NodeTransform> fromJson(matjson::Value const& value);
};