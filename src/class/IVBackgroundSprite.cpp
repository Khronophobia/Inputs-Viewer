#include "IVBackgroundSprite.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

BackgroundSprite::BackgroundSprite(ccColor4B const& backgroundColor, ccColor4B const& outlineColor, ccColor4B const& textColor)
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

BackgroundSprite::BackgroundSprite()
    : BackgroundSprite(
        IVManager::get().m_backgroundReleaseColor,
        IVManager::get().m_outlineReleaseColor,
        IVManager::get().m_textReleaseColor
    )
{}

BackgroundSprite* BackgroundSprite::create() {
    auto ret = new (std::nothrow) BackgroundSprite;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BackgroundSprite::init() {
    if (!CCNode::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.5f));

    m_fill = CCScale9Sprite::create("background_fill.png"_spr);
    this->addChild(m_fill);
    this->addBackgroundNode(m_fill);
    m_outline = CCScale9Sprite::create("background_outline.png"_spr);
    this->addChild(m_outline);
    this->addOutlineNode(m_outline);

    this->setContentSize(m_outline->getContentSize());
    this->setLayout(
        CopySizeLayout::create()
            ->add(m_fill)
            ->add(m_outline),
        false
    );
    m_shouldUpdateLayout = true;
    return true;
}

void BackgroundSprite::setContentSize(CCSize const& size) {
    CCNode::setContentSize(size);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::visit() {
    if (m_shouldUpdateLayout) {
        this->updateLayout();
        m_shouldUpdateLayout = false;
    }
    CCNode::visit();
}

void BackgroundSprite::setBackgroundColor(ccColor4B const& color) {
    m_backgroundColor = color;
    this->updateBackgroundColorNodes();
}

void BackgroundSprite::setOutlineColor(ccColor4B const& color) {
    m_outlineColor = color;
    this->updateOutlineColorNodes();
}

void BackgroundSprite::setTextColor(ccColor4B const& color) {
    m_textColor = color;
    this->updateTextColorNodes();
}

void BackgroundSprite::addBackgroundNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_backgroundColor);
        m_backgroundColorNodes.push_back(node);
    }
}

void BackgroundSprite::addOutlineNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_outlineColor);
        m_outlineColorNodes.push_back(node);
    }
}

void BackgroundSprite::addTextNode(CCNode* node) {
    if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
        protocol->setColor(m_textColor);
        m_textColorNodes.push_back(node);
    }
}

void BackgroundSprite::removeBackgroundNode(CCNode* node) {
    m_backgroundColorNodes.inner()->removeObject(node);
}

void BackgroundSprite::removeOutlineNode(CCNode* node) {
    m_outlineColorNodes.inner()->removeObject(node);
}

void BackgroundSprite::removeTextNode(CCNode* node) {
    m_textColorNodes.inner()->removeObject(node);
}

void BackgroundSprite::updateBackgroundColorNodes() {
    if (m_backgroundColorNodes.size() == 0) return;

    for (auto node : m_backgroundColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_backgroundColor);
        }
    }
}

void BackgroundSprite::updateOutlineColorNodes() {
    if (m_outlineColorNodes.size() == 0) return;

    for (auto node : m_outlineColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_outlineColor);
        }
    }
}

void BackgroundSprite::updateTextColorNodes() {
    if (m_textColorNodes.size() == 0) return;

    for (auto node : m_textColorNodes) {
        if (auto protocol = typeinfo_cast<CCRGBAProtocol*>(node)) {
            protocol->setColor(m_textColor);
        }
    }
}

GEODE_NS_IV_END