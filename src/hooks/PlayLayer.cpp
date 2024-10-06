#include <Geode/modify/PlayLayer.hpp>
#include "GJBaseGameLayer.hpp"

using namespace geode::prelude;

struct IVPlayLayer : Modify<IVPlayLayer, PlayLayer> {
    $override
    void pauseGame(bool p0) {
        PlayLayer::pauseGame(p0);
        if (auto ivLayer = static_cast<IVGJBaseGameLayer*>(static_cast<GJBaseGameLayer*>(this))->m_fields->m_ivLayer) {
            ivLayer->releaseAllButtons();
        }
    }
};