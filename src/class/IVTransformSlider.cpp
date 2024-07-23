#include "IVTransformSlider.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

TransformSlider::TransformSlider(NodeTransform& transform)
    : m_transform(transform) {}

TransformSlider* TransformSlider::create(NodeTransform& transform, PlayerInputNode* inputNode, char const* text) {
    auto ret = new (std::nothrow) TransformSlider(transform);
    if (ret && ret->init(inputNode, text)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool TransformSlider::init(PlayerInputNode* inputNode, char const* text) {
    m_inputNode = inputNode;
    auto winSize = CCDirector::get()->getWinSize();

    m_xPosSlider = FloatSlider::create(
        "X:",
        m_transform.position.x,
        -winSize.width * 0.5f,
        winSize.width * 0.5f,
        [this](FloatSlider* slider) {
            this->setValueAndUpdatePos(m_transform.position.x, slider->getValue());
        }
    );
    m_xPosSlider->setPositionY(18.f);
    this->addChild(m_xPosSlider);

    m_yPosSlider = FloatSlider::create(
        "Y:",
        m_transform.position.y,
        -winSize.height * 0.5f,
        winSize.height * 0.5f,
        [this](FloatSlider* slider) {
            this->setValueAndUpdatePos(m_transform.position.y, slider->getValue());
        }
    );
    m_yPosSlider->setPositionY(-12.f);
    this->addChild(m_yPosSlider);

    m_scaleSlider = FloatSlider::create(
        "Scale:",
        m_transform.scale,
        0.f,
        2.f,
        [this](FloatSlider* slider) {
            this->setValueAndUpdatePos(m_transform.scale, slider->getValue());
        }
    );
    m_scaleSlider->setPositionY(-42.f);
    this->addChild(m_scaleSlider);

    m_textLabel = CCLabelBMFont::create(text, "goldFont.fnt");
    m_textLabel->setScale(0.6f);
    m_textLabel->setPositionY(56.f);
    this->addChild(m_textLabel);

    return true;
}

void TransformSlider::setValueAndUpdatePos(float& value, float setter) {
    value = setter;

    m_transform.applyTransform(m_inputNode);
}

GEODE_NS_IV_END