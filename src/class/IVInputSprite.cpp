#include "IVInputSprite.hpp"
#include "IVManager.hpp"
#include <IVUtils.hpp>
#include <IVConstants.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputSprite* InputSprite::create(PlayerButton input, char const* playerText) {
    auto ret = new (std::nothrow) InputSprite;
    if (ret && ret->init(input, playerText)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputSprite::init(PlayerButton input, char const* playerText) {
    if (!BackgroundSprite::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.f));

    m_inputSymbol = CCSprite::create("symbol_arrow.png"_spr);
    this->addTextNode(m_inputSymbol);
    this->addChildAtPosition(m_inputSymbol, Anchor::Top);

    switch (input) {
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

    this->press(false, false);
    this->setContentWidth(constants::buttonWidth);
    return true;
}

void InputSprite::press(bool pressed, bool updateInputs) {
    m_pressed = pressed;
    if (pressed) {
        this->setBackgroundColor(IVManager::get().m_backgroundPressColor);
        this->setOutlineColor(IVManager::get().m_outlinePressColor);
        this->setTextColor(IVManager::get().m_textPressColor);
        if (updateInputs) {
            ++m_totalInputs;
            ++m_clicksPerSecond;
            this->updateInputDisplay();
        }
    } else {
        this->setBackgroundColor(IVManager::get().m_backgroundReleaseColor);
        this->setOutlineColor(IVManager::get().m_outlineReleaseColor);
        this->setTextColor(IVManager::get().m_textReleaseColor);
    }
}

void InputSprite::updateInputDisplay() {
    if (!IVManager::get().m_showTotalInputs) return;

    m_totalInputsText->setString(std::to_string(m_totalInputs).c_str());
    this->updateLabelWidth(m_totalInputsText);
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
        this->updateInputDisplay();
    } else {
        m_totalInputsText->setVisible(false);
    }
}

void InputSprite::setShowCPS(bool show) {
    if (show) {
        m_cpsText->setVisible(true);
        this->schedule(schedule_selector(InputSprite::updateCPS), 1.f);
        m_clicksPerSecond = 0;
        m_cpsText->setString("0");
    } else {
        m_cpsText->setVisible(false);
        this->unschedule(schedule_selector(InputSprite::updateCPS));
    }
}

void InputSprite::updateButtonAppearance() {
    if (IVManager::get().m_showTotalInputs || IVManager::get().m_showCPS) {
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

    if (IVManager::get().m_showTotalInputs ^ IVManager::get().m_showCPS) {
        m_textScale = 0.55f;
        static_cast<AnchorLayoutOptions*>(m_totalInputsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 8.f));
        static_cast<AnchorLayoutOptions*>(m_cpsText->getLayoutOptions())
            ->setOffset(ccp(0.f, 8.f));
    } else if (IVManager::get().m_showTotalInputs && IVManager::get().m_showCPS) {
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

void InputSprite::updateCPS(float dt) {
    m_cpsText->setString(std::to_string(m_clicksPerSecond).c_str());
    this->updateLabelWidth(m_cpsText);

    m_clicksPerSecond = 0;
}

void InputSprite::updateLabelWidth(CCLabelBMFont* font) {
    font->limitLabelWidth(16.f, m_textScale, 0.1f);
}

GEODE_NS_IV_END