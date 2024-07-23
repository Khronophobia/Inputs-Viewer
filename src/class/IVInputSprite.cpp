#include "IVInputSprite.hpp"
#include "IVManager.hpp"
#include <IVUtils.hpp>
#include <IVConstants.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputSprite::InputSprite()
    : m_colorListener(this, &InputSprite::onSettingChange, IVSettingFilter(SettingEventType::Color))
{}

InputSprite* InputSprite::create(InputType input) {
    auto ret = new (std::nothrow) InputSprite;
    if (ret && ret->init(input)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputSprite::init(InputType input) {
    if (!BackgroundSprite::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.f));

    m_inputSymbol = CCSprite::create("symbol_arrow.png"_spr);
    this->addChildAtPosition(m_inputSymbol, Anchor::Top);

    switch (input) {
    case InputType::Jump: break;
    case InputType::Left:
        m_inputSymbol->setRotation(-90.f); break;
    case InputType::Right:
        m_inputSymbol->setRotation(90.f); break;
    }

    m_totalInputsText = CCLabelBMFont::create("0", "chatFont.fnt");
    this->addChildAtPosition(m_totalInputsText, Anchor::Bottom, ccp(0.f, 6.f));

    this->press(false, false);
    return true;
}

void InputSprite::press(bool pressed, bool updateTotalInputs) {
    m_pressed = pressed;
    if (pressed) {
        utils::setColor4(this, IVManager::get().m_backgroundPressColor);
        utils::setOutlineColor4(this, IVManager::get().m_outlinePressColor);
        utils::setColor4(m_inputSymbol, IVManager::get().m_textPressColor);
        utils::setColor4(m_totalInputsText, IVManager::get().m_textPressColor);
        if (updateTotalInputs) {
            ++m_totalInputs;
            this->updateInputDisplay();
        }
    } else {
        utils::setColor4(this, IVManager::get().m_backgroundReleaseColor);
        utils::setOutlineColor4(this, IVManager::get().m_outlineReleaseColor);
        utils::setColor4(m_inputSymbol, IVManager::get().m_textReleaseColor);
        utils::setColor4(m_totalInputsText, IVManager::get().m_textReleaseColor);
    }
}

void InputSprite::updateInputDisplay() {
    if (!IVManager::get().m_showTotalInputs) return;

    m_totalInputsText->setString(std::to_string(m_totalInputs).c_str());
    m_totalInputsText->limitLabelWidth(16.f, 0.5f, 0.1f);
}

void InputSprite::setShowTotalInputs(bool show) {
    if (show) {
        m_totalInputsText->setVisible(true);
        this->updateInputDisplay();
        static_cast<AnchorLayoutOptions*>(m_inputSymbol->getLayoutOptions())
            ->setOffset(ccp(0.f, -7.5f));
        this->setContentHeight(constants::buttonHeightTall);
    } else {
        m_totalInputsText->setVisible(false);
        static_cast<AnchorLayoutOptions*>(m_inputSymbol->getLayoutOptions())
            ->setOffset(ccp(0.f, -constants::buttonHeightNormal * 0.5f));
        this->setContentHeight(constants::buttonHeightNormal);
    }
    this->updateLayout();
}

void InputSprite::onSettingChange(SettingEventType type) {
    this->press(m_pressed, false);
}

GEODE_NS_IV_END