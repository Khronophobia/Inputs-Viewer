#pragma once
#include <IVEvent.hpp>

GEODE_NS_IV_BEGIN

class BackgroundSprite : public cocos2d::CCNode {
public:
    BackgroundSprite(
        cocos2d::ccColor4B const& backgroundColor,
        cocos2d::ccColor4B const& outlineColor,
        cocos2d::ccColor4B const& textColor
    );
    BackgroundSprite();
    static BackgroundSprite* create(
        cocos2d::ccColor4B const& backgroundColor,
        cocos2d::ccColor4B const& outlineColor,
        cocos2d::ccColor4B const& textColor
    );
    static BackgroundSprite* create();
    bool init() override;
public:
    void addBackgroundNode(cocos2d::CCNode* node);
    void addOutlineNode(cocos2d::CCNode* node);
    void addTextNode(cocos2d::CCNode* node);
    void removeBackgroundNode(cocos2d::CCNode* node);
    void removeOutlineNode(cocos2d::CCNode* node);
    void removeTextNode(cocos2d::CCNode* node);
    void setBackgroundColor(cocos2d::ccColor4B const& color);
    void setOutlineColor(cocos2d::ccColor4B const& color);
    void setTextColor(cocos2d::ccColor4B const& color);
public:
    void setContentSize(cocos2d::CCSize const& size) override;
    void visit() override;
protected:
    void updateBackgroundColorNodes();
    void updateOutlineColorNodes();
    void updateTextColorNodes();
protected:
    cocos2d::extension::CCScale9Sprite* m_fill = nullptr;
    cocos2d::extension::CCScale9Sprite* m_outline = nullptr;
    bool m_shouldUpdateLayout = false;
    std::reference_wrapper<cocos2d::ccColor4B const> m_backgroundColor;
    std::reference_wrapper<cocos2d::ccColor4B const> m_outlineColor;
    std::reference_wrapper<cocos2d::ccColor4B const> m_textColor;
    geode::cocos::CCArrayExt<cocos2d::CCNode*> m_backgroundColorNodes;
    geode::cocos::CCArrayExt<cocos2d::CCNode*> m_outlineColorNodes;
    geode::cocos::CCArrayExt<cocos2d::CCNode*> m_textColorNodes;
    geode::EventListener<IVSettingFilter> m_colorListener;
};

GEODE_NS_IV_END