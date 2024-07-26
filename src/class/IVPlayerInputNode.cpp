#include "IVPlayerInputNode.hpp"
#include "IVManager.hpp"
#include <IVConstants.hpp>
#include <IVUtils.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

PlayerInputNode::PlayerInputNode()
    : m_settingListener(this, &PlayerInputNode::onSettingEvent, IVSettingFilter(SettingEventType::TotalInputsCounter)) {}

PlayerInputNode* PlayerInputNode::create(char const* playerText) {
    auto ret = new (std::nothrow) PlayerInputNode;
    if (ret && ret->init(playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool PlayerInputNode::init(char const* playerText) {
    if (!CCNode::init()) return false;

    m_jumpButton = InputSprite::create(InputType::Jump);
    m_jumpButton->setPositionY(20.5f);
    this->addChild(m_jumpButton);
    m_leftButton = InputSprite::create(InputType::Left);
    m_leftButton->setPositionX(-20.25f);
    this->addChild(m_leftButton);
    m_rightButton = InputSprite::create(InputType::Right);
    m_rightButton->setPositionX(20.25f);
    this->addChild(m_rightButton);

    m_playerIndicator = BackgroundSpriteColored::create();
    m_playerIndicator->setAnchorPoint(ccp(0.5f, 0.f));
    this->addChild(m_playerIndicator);
    m_playerIndicatorText = CCLabelBMFont::create(playerText, "chatFont.fnt");
    m_playerIndicatorText->setScale(0.75f);
    m_playerIndicator->addTextNode(m_playerIndicatorText);
    m_playerIndicator->addChildAtPosition(m_playerIndicatorText, Anchor::Center);

    this->setShowTotalInputs(IVManager::get().m_showTotalInputs);
    return true;
}

void PlayerInputNode::handleButton(bool down, InputType input, bool updateTotalInputs) {
    switch (input) {
    case InputType::Jump:
        m_jumpButton->press(down, updateTotalInputs); break;
    case InputType::Left:
        m_leftButton->press(down, updateTotalInputs); break;
    case InputType::Right:
        m_rightButton->press(down, updateTotalInputs); break;
    }
}

void PlayerInputNode::setShowTotalInputs(bool show) {
    m_jumpButton->setShowTotalInputs(show);
    m_leftButton->setShowTotalInputs(show);
    m_rightButton->setShowTotalInputs(show);
    if (show) {
        m_jumpButton->setPositionY(constants::buttonHeightTall + 0.5f);
        m_playerIndicator->setContentHeight(constants::buttonHeightTall);
    } else {
        m_jumpButton->setPositionY(constants::buttonHeightNormal + 0.5f);
        m_playerIndicator->setContentHeight(constants::buttonHeightNormal);
    }
}

void PlayerInputNode::onSettingEvent(SettingEventType type) {
    this->setShowTotalInputs(IVManager::get().m_showTotalInputs);
}

GEODE_NS_IV_END