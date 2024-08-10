#include "IVTransformSlider.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

TransformSlider::TransformSlider(LevelSettings& setting)
    : m_currentSetting(setting) {}

TransformSlider* TransformSlider::create(LevelSettings& setting, NodeTransform LevelSettings::* transform, PlayerInputNode* inputNode, char const* text, MiniFunction<NodeTransform()>&& defaultPosFunc) {
    auto ret = new (std::nothrow) TransformSlider(setting);
    if (ret && ret->init(transform, inputNode, text, std::move(defaultPosFunc))) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool TransformSlider::init(NodeTransform LevelSettings::* transform, PlayerInputNode* inputNode, char const* text, MiniFunction<NodeTransform()>&& defaultPosFunc) {
    m_transform = transform;
    m_inputNode = inputNode;
    m_defaultPosFunc = std::move(defaultPosFunc);
    auto winSize = CCDirector::get()->getWinSize();

    m_xPosSlider = FloatSlider::create(
        "X:",
        (m_currentSetting.get().*m_transform).position.x,
        -winSize.width * 0.5f,
        winSize.width * 0.5f,
        [this](FloatSlider* slider) {
            (m_currentSetting.get().*m_transform).position.x = slider->getValue();
            (m_currentSetting.get().*m_transform).applyTransform(m_inputNode);
        }
    );
    m_xPosSlider->setPositionY(18.f);
    this->addChild(m_xPosSlider);

    m_yPosSlider = FloatSlider::create(
        "Y:",
        (m_currentSetting.get().*m_transform).position.y,
        -winSize.height * 0.5f,
        winSize.height * 0.5f,
        [this](FloatSlider* slider) {
            (m_currentSetting.get().*m_transform).position.y = slider->getValue();
            (m_currentSetting.get().*m_transform).applyTransform(m_inputNode);
        }
    );
    m_yPosSlider->setPositionY(-12.f);
    this->addChild(m_yPosSlider);

    m_scaleSlider = FloatSlider::create(
        "Scale:",
        (m_currentSetting.get().*m_transform).scale,
        0.f,
        2.f,
        [this](FloatSlider* slider) {
            (m_currentSetting.get().*m_transform).scale = slider->getValue();
            (m_currentSetting.get().*m_transform).applyTransform(m_inputNode);
        }
    );
    m_scaleSlider->setPositionY(-42.f);
    this->addChild(m_scaleSlider);

    m_textLabel = CCLabelBMFont::create(text, "goldFont.fnt");
    m_textLabel->setScale(0.6f);
    m_textLabel->setPositionY(56.f);
    this->addChild(m_textLabel);

    m_buttonMenu = CCMenu::create();
    m_buttonMenu->setPosition(0.f, m_textLabel->getPositionY());
    this->addChild(m_buttonMenu);

    auto visibilityCheckbox = CCMenuItemToggler::createWithStandardSprites(
        this, menu_selector(TransformSlider::onSetVisibility),
        0.4f
    );
    visibilityCheckbox->toggle((m_currentSetting.get().*m_transform).isVisible);
    visibilityCheckbox->setPositionX(-m_textLabel->getScaledContentWidth() * 0.5f - 10.f);
    m_buttonMenu->addChild(visibilityCheckbox);

    if (m_defaultPosFunc) {
        auto resetSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
        resetSpr->setScale(0.25f);
        auto resetBtn = CCMenuItemSpriteExtra::create(
            resetSpr,
            this, menu_selector(TransformSlider::onDefaultPosition)
        );
        resetBtn->setPositionX(m_textLabel->getScaledContentWidth() * 0.5f + 10.f);

        m_buttonMenu->addChild(resetBtn);
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
                m_currentSetting.get().*m_transform = m_defaultPosFunc();
                m_xPosSlider->setValue((m_currentSetting.get().*m_transform).position.x);
                m_yPosSlider->setValue((m_currentSetting.get().*m_transform).position.y);
                m_scaleSlider->setValue((m_currentSetting.get().*m_transform).scale);
                (m_currentSetting.get().*m_transform).applyTransform(m_inputNode);
            }
        }
    );
}

void TransformSlider::onSetVisibility(CCObject* sender) {
    auto btn = static_cast<CCMenuItemToggler*>(sender);
    (m_currentSetting.get().*m_transform).isVisible = !btn->isToggled();
    m_inputNode->setVisible((m_currentSetting.get().*m_transform).isVisible);
}

GEODE_NS_IV_END