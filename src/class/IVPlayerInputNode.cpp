#include "IVPlayerInputNode.hpp"
#include <IVConstants.hpp>
#include <IVUtils.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

PlayerInputNode::PlayerInputNode(LevelSettings const& setting)
    : m_currentSetting(setting)
    , m_settingListener([this](auto) { this->refreshAppearance(); }, IVSettingFilter(SettingEventType::KeyAppearance)) {}

PlayerInputNode* PlayerInputNode::create(LevelSettings const& setting, char const* playerText) {
    auto ret = new (std::nothrow) PlayerInputNode(setting);
    if (ret && ret->init(playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool PlayerInputNode::init(char const* playerText) {
    if (!CCNode::init()) return false;

    m_jumpButton = InputSprite::create(this, PlayerButton::Jump, playerText);
    m_jumpButton->setPositionY(20.5f);
    this->addChild(m_jumpButton);
    m_leftButton = InputSprite::create(this, PlayerButton::Left, nullptr);
    m_leftButton->setPositionX(-constants::buttonWidth - 0.25f);
    this->addChild(m_leftButton);
    m_rightButton = InputSprite::create(this, PlayerButton::Right, nullptr);
    m_rightButton->setPositionX(constants::buttonWidth + 0.25f);
    this->addChild(m_rightButton);

    m_playerIndicator = BackgroundSprite::create();
    m_playerIndicator->setAnchorPoint(ccp(0.5f, 0.f));
    m_playerIndicator->setContentWidth(constants::buttonWidth);
    this->addChild(m_playerIndicator);
    if (playerText) {
        auto playerIndicatorText = CCLabelBMFont::create(playerText, "chatFont.fnt");
        playerIndicatorText->setScale(0.75f);
        m_playerIndicator->addTextNode(playerIndicatorText);
        m_playerIndicator->addChildAtPosition(playerIndicatorText, Anchor::Center);
    }

    this->refreshAppearance();
    return true;
}

void PlayerInputNode::handleButton(bool down, PlayerButton input, bool updateCounters) {
    switch (input) {
    case PlayerButton::Jump:
        m_jumpButton->press(down, updateCounters); break;
    case PlayerButton::Left:
        m_leftButton->press(down, updateCounters); break;
    case PlayerButton::Right:
        m_rightButton->press(down, updateCounters); break;
    }
}

bool PlayerInputNode::isMinimalMode() const {
    return m_currentSetting.get().hideLeftRight;
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

void PlayerInputNode::releaseAllButtons() {
    m_jumpButton->press(false, false);
    m_leftButton->press(false, false);
    m_rightButton->press(false, false);
}

void PlayerInputNode::setLevelSettings(LevelSettings const& settings) {
    m_currentSetting = settings;

    this->refreshAppearance();
}

LevelSettings const& PlayerInputNode::getLevelSettings() const noexcept {
    return m_currentSetting;
}

void PlayerInputNode::refreshAppearance() {
    if (this->isMinimalMode()) {
        m_jumpButton->setMinimal(true);
        m_playerIndicator->setVisible(false);
        m_rightButton->setVisible(false);
        m_leftButton->setVisible(false);

        m_jumpButton->setPositionY(0.f);
    } else {
        m_jumpButton->setMinimal(false);
        m_playerIndicator->setVisible(true);
        m_rightButton->setVisible(true);
        m_leftButton->setVisible(true);

        if (m_currentSetting.get().showTotalInputs || m_currentSetting.get().showCPS) {
            m_jumpButton->setPositionY(constants::buttonHeightTall + 0.5f);
            m_playerIndicator->setContentHeight(constants::buttonHeightTall);
        } else {
            m_jumpButton->setPositionY(constants::buttonHeightNormal + 0.5f);
            m_playerIndicator->setContentHeight(constants::buttonHeightNormal);
        }
    }
    this->setShowTotalInputs(m_currentSetting.get().showTotalInputs);
    this->setShowCPS(m_currentSetting.get().showCPS);

    m_jumpButton->updateButtonAppearance();
    m_leftButton->updateButtonAppearance();
    m_rightButton->updateButtonAppearance();
}

GEODE_NS_IV_END