#pragma once
#include "IVPlayerInputNode.hpp"
#include "IVFloatSlider.hpp"
#include <json/NodeTransform.hpp>

GEODE_NS_IV_BEGIN

class TransformSlider : public cocos2d::CCNode {
public:
    TransformSlider(NodeTransform& transform);
    static TransformSlider* create(NodeTransform& transform, PlayerInputNode* inputNode, char const* text);
    bool init(PlayerInputNode* inputNode, char const* text);
    void setValueAndUpdatePos(float& value, float setter);
protected:
    NodeTransform& m_transform;
    PlayerInputNode* m_inputNode = nullptr;
    FloatSlider* m_xPosSlider = nullptr;
    FloatSlider* m_yPosSlider = nullptr;
    FloatSlider* m_scaleSlider = nullptr;
    cocos2d::CCLabelBMFont* m_textLabel = nullptr;
};

GEODE_NS_IV_END