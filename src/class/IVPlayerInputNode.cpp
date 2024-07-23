#include "IVPlayerInputNode.hpp"
#include "IVManager.hpp"
#include <IVConstants.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

PlayerInputNode::PlayerInputNode()
    : m_settingListener(this, &PlayerInputNode::onSettingEvent, IVSettingFilter(SettingEventType::TotalInputsCounter)) {}

PlayerInputNode* PlayerInputNode::create() {
    auto ret = new (std::nothrow) PlayerInputNode;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool PlayerInputNode::init() {
    if (!CCNode::init()) return false;

    m_jumpButton = InputSprite::create(InputType::Jump);
    m_jumpButton->setPositionY(20.f);
    this->addChild(m_jumpButton);
    m_leftButton = InputSprite::create(InputType::Left);
    m_leftButton->setPositionX(-20.f);
    this->addChild(m_leftButton);
    m_rightButton = InputSprite::create(InputType::Right);
    m_rightButton->setPositionX(20.f);
    this->addChild(m_rightButton);

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
        m_jumpButton->setPositionY(constants::buttonHeightTall);
    } else {
        m_jumpButton->setPositionY(constants::buttonHeightNormal);
    }
}

void PlayerInputNode::onSettingEvent(SettingEventType type) {
    this->setShowTotalInputs(IVManager::get().m_showTotalInputs);
}

GEODE_NS_IV_END