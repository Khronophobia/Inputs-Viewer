#include "IVInputSprite.hpp"
#include "IVManager.hpp"
#include "IVPlayerInputNode.hpp"
#include <IVUtils.hpp>
#include <IVConstants.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

namespace CPSCalculationString {
    [[maybe_unused]]
    std::string_view constexpr RealTime = "Real-Time";
    [[maybe_unused]]
    std::string_view constexpr PerSecond = "Per Second";
}

static CPSCalculation convertCPSCalculation(std::string const& str) {
    if (str == CPSCalculationString::RealTime) return CPSCalculation::RealTime;
    else if (str == CPSCalculationString::PerSecond) return CPSCalculation::PerSecond;

    return CPSCalculation::RealTime;
}

InputSprite::InputSprite()
    : m_cpsSettingListener([this](std::shared_ptr<SettingV3> setting) {
        using SettingType = SettingTypeForValueType<std::string>::SettingType;
        this->setCPSMode(convertCPSCalculation(std::static_pointer_cast<SettingType>(setting)->getValue()));
    },
    SettingChangedFilterV3(Mod::get()->getID(), "cps-calculation"))
{}

InputSprite* InputSprite::create(PlayerInputNode* inputNode, PlayerButton button, char const* playerText) {
    auto ret = new (std::nothrow) InputSprite;
    if (ret && ret->init(inputNode, button, playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputSprite::init(PlayerInputNode* inputNode, PlayerButton button, char const* playerText) {
    if (!BackgroundSprite::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.f));
    this->setCPSMode(convertCPSCalculation(Mod::get()->getSettingValue<std::string>("cps-calculation")));
    m_inputNode = inputNode;

    m_inputSymbol = CCSprite::create("symbol_arrow.png"_spr);
    this->addTextNode(m_inputSymbol);
    this->addChildAtPosition(m_inputSymbol, Anchor::Top);

    switch (button) {
    case PlayerButton::Jump: break;
    case PlayerButton::Left:
        m_inputSymbol->setRotation(-90.f); break;
    case PlayerButton::Right:
        m_inputSymbol->setRotation(90.f); break;
    }

    if (playerText) {
        m_playerText = CCLabelBMFont::create(playerText, "chatFont.fnt");
        m_playerText->setScale(0.6f);
        this->addTextNode(m_playerText);
        this->addChildAtPosition(m_playerText, Anchor::Top);
    }

    m_totalInputsText = CCLabelBMFont::create("0", "chatFont.fnt");
    this->addTextNode(m_totalInputsText);
    this->addChildAtPosition(m_totalInputsText, Anchor::Bottom);

    m_cpsText = CCLabelBMFont::create("0", "chatFont.fnt");
    this->addTextNode(m_cpsText);
    this->addChildAtPosition(m_cpsText, Anchor::Bottom);

    this->setContentWidth(constants::buttonWidth);
    this->scheduleUpdate();
    return true;
}

void InputSprite::setCPSMode(CPSCalculation mode) {
    m_currentCPSCalculation = mode;
    switch (m_currentCPSCalculation) {
    case CPSCalculation::RealTime:
        this->unschedule(schedule_selector(InputSprite::cpsSchedule));
        break;
    case CPSCalculation::PerSecond:
        this->stopAllActions();
        this->schedule(schedule_selector(InputSprite::cpsSchedule), 1.f);
        break;
    }
    m_clicksPerSecond = 0;
    m_displayedCPS = 0;
    m_shouldUpdateCPSDisplay = true;
}

void InputSprite::updateCPSCounter() {
    ++m_clicksPerSecond;
    if (m_currentCPSCalculation == CPSCalculation::RealTime) {
        m_displayedCPS = m_clicksPerSecond;
        this->runAction(
            CCSequence::createWithTwoActions(
                CCDelayTime::create(1.f),
                CCCallFunc::create(this, callfunc_selector(InputSprite::subtractCPS)
            ))
        );
        m_shouldUpdateCPSDisplay = true;
    }
}

void InputSprite::press(bool pressed, bool updateCounters) {
    if (pressed) {
        this->setBackgroundColor(IVManager::get().m_backgroundPressColor);
        this->setOutlineColor(IVManager::get().m_outlinePressColor);
        this->setTextColor(IVManager::get().m_textPressColor);
        if (updateCounters) {
            ++m_totalInputs;
            m_shouldUpdateTotalInputsDisplay = true;
            this->updateCPSCounter();
        }
    } else {
        this->setBackgroundColor(IVManager::get().m_backgroundReleaseColor);
        this->setOutlineColor(IVManager::get().m_outlineReleaseColor);
        this->setTextColor(IVManager::get().m_textReleaseColor);
    }
}

void InputSprite::setMinimal(bool minimal) {
    if (m_playerText) {
        m_inputSymbol->setVisible(!minimal);
        m_playerText->setVisible(minimal);
    }
}

void InputSprite::setShowTotalInputs(bool show) {
    if (show) {
        m_totalInputsText->setVisible(true);
    } else {
        m_totalInputsText->setVisible(false);
    }
}

void InputSprite::setShowCPS(bool show) {
    if (show) {
        m_cpsText->setVisible(true);
    } else {
        m_cpsText->setVisible(false);
    }
}

void InputSprite::updateButtonAppearance() {
    if (m_inputNode->getLevelSettings().showTotalInputs || m_inputNode->getLevelSettings().showCPS) {
        static_cast<AnchorLayoutOptions*>(m_inputSymbol->getLayoutOptions())
            ->setOffset(ccp(0.f, -7.5f));
        if (m_playerText) static_cast<AnchorLayoutOptions*>(m_playerText->getLayoutOptions())
            ->setOffset(ccp(0.f, -7.5f));
        this->setContentHeight(constants::buttonHeightTall);
    } else {
        static_cast<AnchorLayoutOptions*>(m_inputSymbol->getLayoutOptions())
            ->setOffset(ccp(0.f, -constants::buttonHeightNormal * 0.5f));
        if (m_playerText) static_cast<AnchorLayoutOptions*>(m_playerText->getLayoutOptions())
            ->setOffset(ccp(0.f, -constants::buttonHeightNormal * 0.5f));
        this->setContentHeight(constants::buttonHeightNormal);
    }

    if (m_inputNode->getLevelSettings().showTotalInputs ^ m_inputNode->getLevelSettings().showCPS) {
        m_textScale = 0.55f;
        static_cast<AnchorLayoutOptions*>(m_totalInputsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 8.f));
        static_cast<AnchorLayoutOptions*>(m_cpsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 8.f));
    } else if (m_inputNode->getLevelSettings().showTotalInputs && m_inputNode->getLevelSettings().showCPS) {
        m_textScale = 0.45f;
        static_cast<AnchorLayoutOptions*>(m_totalInputsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 11.5f));
        static_cast<AnchorLayoutOptions*>(m_cpsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 5.f));
    }   

    this->updateLabelWidth(m_totalInputsText);
    this->updateLabelWidth(m_cpsText);
    m_shouldUpdateLayout = true;
}

void InputSprite::updateLabelWidth(CCLabelBMFont* font) {
    font->limitLabelWidth(16.f, m_textScale, 0.1f);
}

void InputSprite::cpsSchedule(float) {
    m_displayedCPS = m_clicksPerSecond;
    m_clicksPerSecond = 0;
    m_shouldUpdateCPSDisplay = true;
}

void InputSprite::subtractCPS() {
    --m_clicksPerSecond;
    m_displayedCPS = m_clicksPerSecond;
    m_shouldUpdateCPSDisplay = true;
}

void InputSprite::updateTotalInputsDisplay() {
    m_totalInputsText->setString(std::to_string(m_totalInputs).c_str());
    this->updateLabelWidth(m_totalInputsText);
}

void InputSprite::updateCPSDisplay() {
    m_cpsText->setString(std::to_string(m_displayedCPS).c_str());
    this->updateLabelWidth(m_cpsText);
}

void InputSprite::visit() {
    if (m_shouldUpdateTotalInputsDisplay && m_totalInputsText->isVisible()) {
        this->updateTotalInputsDisplay();
        m_shouldUpdateTotalInputsDisplay = false;
    }
    if (m_shouldUpdateCPSDisplay && m_cpsText->isVisible()) {
        this->updateCPSDisplay();
        m_shouldUpdateCPSDisplay = false;
    }
    BackgroundSprite::visit();
}

GEODE_NS_IV_END