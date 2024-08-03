#include "IVPlayerInputNode.hpp"
#include "IVManager.hpp"
#include <IVConstants.hpp>
#include <IVUtils.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

PlayerInputNode::PlayerInputNode()
    : m_settingListener(this, &PlayerInputNode::onRefreshAppearance, IVSettingFilter(SettingEventType::KeyAppearance)) {}

PlayerInputNode* PlayerInputNode::create(GJBaseGameLayer* gameLayer, char const* playerText) {
    auto ret = new (std::nothrow) PlayerInputNode;
    if (ret && ret->init(gameLayer, playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool PlayerInputNode::init(GJBaseGameLayer* gameLayer, char const* playerText) {
    if (!CCNode::init()) return false;
    m_gameLayer = gameLayer;

    m_jumpButton = InputSprite::create(PlayerButton::Jump, playerText);
    m_jumpButton->setPositionY(20.5f);
    this->addChild(m_jumpButton);
    m_leftButton = InputSprite::create(PlayerButton::Left, nullptr);
    m_leftButton->setPositionX(-constants::buttonWidth - 0.25f);
    this->addChild(m_leftButton);
    m_rightButton = InputSprite::create(PlayerButton::Right, nullptr);
    m_rightButton->setPositionX(constants::buttonWidth + 0.25f);
    this->addChild(m_rightButton);

    m_playerIndicator = BackgroundSprite::create();
    m_playerIndicator->setAnchorPoint(ccp(0.5f, 0.f));
    m_playerIndicator->setContentWidth(constants::buttonWidth);
    this->addChild(m_playerIndicator);
    m_playerIndicatorText = CCLabelBMFont::create(playerText, "chatFont.fnt");
    m_playerIndicatorText->setScale(0.75f);
    m_playerIndicator->addTextNode(m_playerIndicatorText);
    m_playerIndicator->addChildAtPosition(m_playerIndicatorText, Anchor::Center);

    this->onRefreshAppearance(SettingEventType::KeyAppearance);
    return true;
}

void PlayerInputNode::handleButton(bool down, PlayerButton input, bool updateTotalInputs) {
    switch (input) {
    case PlayerButton::Jump:
        m_jumpButton->press(down, updateTotalInputs); break;
    case PlayerButton::Left:
        m_leftButton->press(down, updateTotalInputs); break;
    case PlayerButton::Right:
        m_rightButton->press(down, updateTotalInputs); break;
    }
}

bool PlayerInputNode::isMinimalMode() const {
    if (!m_gameLayer) return IVManager::get().m_minimalIfNonPlatformer;

    return !m_gameLayer->m_levelSettings->m_platformerMode && IVManager::get().m_minimalIfNonPlatformer;
}

void PlayerInputNode::setShowTotalInputs(bool show) {
    m_jumpButton->setShowTotalInputs(show);
    m_leftButton->setShowTotalInputs(show);
    m_rightButton->setShowTotalInputs(show);
}

void PlayerInputNode::setShowCPS(bool show) {
    m_jumpButton->setShowCPS(show);
    m_leftButton->setShowCPS(show);
    m_rightButton->setShowCPS(show);
}

void PlayerInputNode::updateAppearance() {
    m_jumpButton->updateButtonAppearance();
    m_leftButton->updateButtonAppearance();
    m_rightButton->updateButtonAppearance();

    if (this->isMinimalMode()) {
        m_jumpButton->setPositionY(0.f);
    } else {
        if (IVManager::get().m_showTotalInputs || IVManager::get().m_showCPS) {
            m_jumpButton->setPositionY(constants::buttonHeightTall + 0.5f);
            m_playerIndicator->setContentHeight(constants::buttonHeightTall);
        } else {
            m_jumpButton->setPositionY(constants::buttonHeightNormal + 0.5f);
            m_playerIndicator->setContentHeight(constants::buttonHeightNormal);
        }
    }
}

void PlayerInputNode::releaseAllButtons() {
    m_jumpButton->press(false, false);
    m_leftButton->press(false, false);
    m_rightButton->press(false, false);
}

void PlayerInputNode::onRefreshAppearance(SettingEventType) {
    if (this->isMinimalMode()) {
        m_jumpButton->setMinimal(true);
        m_playerIndicator->setVisible(false);
        m_rightButton->setVisible(false);
        m_leftButton->setVisible(false);
    } else {
        m_jumpButton->setMinimal(false);
        m_playerIndicator->setVisible(true);
        m_rightButton->setVisible(true);
        m_leftButton->setVisible(true);
    }
    this->setShowTotalInputs(IVManager::get().m_showTotalInputs);
    this->setShowCPS(IVManager::get().m_showCPS);

    this->updateAppearance();
}

GEODE_NS_IV_END