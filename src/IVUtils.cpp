#include "IVUtils.hpp"
#include "class/IVBackgroundSprite.hpp"

GEODE_NS_IV_BEGIN

namespace utils {
    void setColor4(cocos2d::CCRGBAProtocol* node, cocos2d::ccColor4B const& color) {
        node->setColor({color.r, color.g, color.b});
        node->setOpacity(color.a);
    }

    void setOutlineColor4(BackgroundSprite* node, cocos2d::ccColor4B const& color) {
        node->setOutlineColor({color.r, color.g, color.b});
        node->setOutlineOpacity(color.a);
    }
}

GEODE_NS_IV_END