#include "IVBackgroundSpriteColored.hpp"
#include "IVManager.hpp"
#include <IVUtils.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

BackgroundSpriteColored::BackgroundSpriteColored(ccColor4B const& backgroundColor, ccColor4B const& outlineColor, ccColor4B const& textColor)
    : m_backgroundColor(backgroundColor)
    , m_outlineColor(outlineColor)
    , m_textColor(textColor)
    , m_colorListener(
        [this](auto) {
            this->updateBackgroundColorNodes();
            this->updateOutlineColorNodes();
            this->updateTextColorNodes();
        }, IVSettingFilter(SettingEventType::Color)
    )
{}

BackgroundSpriteColored::BackgroundSpriteColored()
    : BackgroundSpriteColored(
        IVManager::get().m_backgroundReleaseColor,
        IVManager::get().m_outlineReleaseColor,
        IVManager::get().m_textReleaseColor
    )
{}

BackgroundSpriteColored* BackgroundSpriteColored::create() {
    auto ret = new (std::nothrow) BackgroundSpriteColored;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

BackgroundSpriteColored* BackgroundSpriteColored::create(ccColor4B const& backgroundColor, ccColor4B const& outlineColor, ccColor4B const& textColor) {
    auto ret = new (std::nothrow) BackgroundSpriteColored(backgroundColor, outlineColor, textColor);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BackgroundSpriteColored::init() {
    if (!BackgroundSprite::init()) return false;

    this->addBackgroundNode(m_fill);
    this->addOutlineNode(m_outline);

    return true;
}

void BackgroundSpriteColored::setBackgroundColor(ccColor4B const& color) {
    m_backgroundColor = color;
    this->updateBackgroundColorNodes();
}

void BackgroundSpriteColored::setOutlineColor(ccColor4B const& color) {
    m_outlineColor = color;
    this->updateOutlineColorNodes();
}

void BackgroundSpriteColored::setTextColor(ccColor4B const& color) {
    m_textColor = color;
    this->updateTextColorNodes();
}

void BackgroundSpriteColored::addBackgroundNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        utils::setColor4(protocol, m_backgroundColor);
        m_backgroundColorNodes.push_back(node);
    }
}

void BackgroundSpriteColored::addOutlineNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        utils::setColor4(protocol, m_outlineColor);
        m_outlineColorNodes.push_back(node);
    }
}

void BackgroundSpriteColored::addTextNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        utils::setColor4(protocol, m_textColor);
        m_textColorNodes.push_back(node);
    }
}

void BackgroundSpriteColored::removeBackgroundNode(CCNode* node) {
    m_backgroundColorNodes.inner()->removeObject(node);
}

void BackgroundSpriteColored::removeOutlineNode(CCNode* node) {
    m_outlineColorNodes.inner()->removeObject(node);
}

void BackgroundSpriteColored::removeTextNode(CCNode* node) {
    m_textColorNodes.inner()->removeObject(node);
}

void BackgroundSpriteColored::updateBackgroundColorNodes() {
    if (m_backgroundColorNodes.size() == 0) return;

    for (auto node : m_backgroundColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            utils::setColor4(protocol, m_backgroundColor);
        }
    }
}

void BackgroundSpriteColored::updateOutlineColorNodes() {
    if (m_outlineColorNodes.size() == 0) return;

    for (auto node : m_outlineColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            utils::setColor4(protocol, m_outlineColor);
        }
    }
}

void BackgroundSpriteColored::updateTextColorNodes() {
    if (m_textColorNodes.size() == 0) return;

    for (auto node : m_textColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            utils::setColor4(protocol, m_textColor);
        }
    }
}

GEODE_NS_IV_END