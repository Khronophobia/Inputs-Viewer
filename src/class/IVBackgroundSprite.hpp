#pragma once

GEODE_NS_IV_BEGIN

class BackgroundSprite : public cocos2d::CCNodeRGBA {
public:
    static BackgroundSprite* create();
    bool init() override;
    void setOutlineColor(cocos2d::ccColor3B const& color);
    void setOutlineOpacity(GLubyte opacity);
public:
    void setColor(cocos2d::ccColor3B const& color) override;
    void setOpacity(GLubyte opacity) override;
protected:
    cocos2d::extension::CCScale9Sprite* m_fill = nullptr;
    cocos2d::extension::CCScale9Sprite* m_outline = nullptr;
};

GEODE_NS_IV_END