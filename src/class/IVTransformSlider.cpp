#include "IVTransformSlider.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

TransformSlider::TransformSlider(NodeTransform& transform)
    : m_transform(transform) {}

TransformSlider* TransformSlider::create(NodeTransform& transform, PlayerInputNode* inputNode, char const* text, MiniFunction<NodeTransform()>&& defaultPosFunc) {
    auto ret = new (std::nothrow) TransformSlider(transform);
    if (ret && ret->init(inputNode, text, std::move(defaultPosFunc))) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool TransformSlider::init(PlayerInputNode* inputNode, char const* text, MiniFunction<NodeTransform()>&& defaultPosFunc) {
    m_inputNode = inputNode;
    m_defaultPosFunc = std::move(defaultPosFunc);
    auto winSize = CCDirector::get()->getWinSize();

    m_xPosSlider = FloatSlider::create(
        "X:",
        m_transform.position.x,
        -winSize.width * 0.5f,
        winSize.width * 0.5f,
        [this](FloatSlider* slider) {
            m_transform.position.x = slider->getValue();
            m_transform.applyTransform(m_inputNode);
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
            m_transform.position.y = slider->getValue();
            m_transform.applyTransform(m_inputNode);
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
            m_transform.scale = slider->getValue();
            m_transform.applyTransform(m_inputNode);
        }
    );
    m_scaleSlider->setPositionY(-42.f);
    this->addChild(m_scaleSlider);

    m_textLabel = CCLabelBMFont::create(text, "goldFont.fnt");
    m_textLabel->setScale(0.6f);
    m_textLabel->setPositionY(56.f);
    this->addChild(m_textLabel);

    if (m_defaultPosFunc) {
        auto resetSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
        resetSpr->setScale(0.25f);
        auto resetBtn = CCMenuItemSpriteExtra::create(
            resetSpr,
            this, menu_selector(TransformSlider::onDefaultPosition)
        );
        auto menu = CCMenu::create();
        menu->setPosition(m_textLabel->getPosition() + ccp(m_textLabel->getScaledContentWidth() * 0.5f + 10.f, 0.f));
        this->addChild(menu);

        menu->addChild(resetBtn);
    }

    return true;
}

void TransformSlider::onDefaultPosition(CCObject*) {
    createQuickPopup(
        "Reset Position",
        "Reset to default position? <cb>(The default position is based on your aspect ratio)</c>",
        "No", "Yes",
        [this](auto, bool btn2) {
            if (btn2) {
                m_transform = m_defaultPosFunc();
                m_xPosSlider->setValue(m_transform.position.x);
                m_yPosSlider->setValue(m_transform.position.y);
                m_scaleSlider->setValue(m_transform.scale);
                m_transform.applyTransform(m_inputNode);
            }
        }
    );
}

GEODE_NS_IV_END