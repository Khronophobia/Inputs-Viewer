#include "IVBackgroundSprite.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

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
    if (!CCNodeRGBA::init()) return false;
    this->setAnchorPoint(ccp(0.5f, 0.5f));

    m_fill = CCScale9Sprite::create("background_fill.png"_spr);
    this->addChild(m_fill);
    m_outline = CCScale9Sprite::create("background_outline.png"_spr);
    this->addChild(m_outline);

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
    CCNodeRGBA::setContentSize(size);
    m_shouldUpdateLayout = true;
}

void BackgroundSprite::setColor(ccColor3B const& color) {
    m_fill->setColor(color);
}

void BackgroundSprite::setOpacity(GLubyte opacity) {
    m_fill->setOpacity(opacity);
}

void BackgroundSprite::setOutlineColor(ccColor3B const& color) {
    m_outline->setColor(color);
}

void BackgroundSprite::setOutlineOpacity(GLubyte opacity) {
    m_outline->setOpacity(opacity);
}

void BackgroundSprite::visit() {
    if (m_shouldUpdateLayout) {
        this->updateLayout();
        m_shouldUpdateLayout = false;
    }
    CCNodeRGBA::visit();
}

GEODE_NS_IV_END