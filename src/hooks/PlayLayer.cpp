#include <Geode/modify/PlayLayer.hpp>
#include "GJBaseGameLayer.hpp"

using namespace geode::prelude;

struct PlayLayerHook : Modify<PlayLayerHook, PlayLayer> {
    $override
    void pauseGame(bool p0) {
        PlayLayer::pauseGame(p0);
        if (auto ivLayer = static_cast<GJBaseGameLayerHook*>(static_cast<GJBaseGameLayer*>(this))->m_fields->m_ivLayer) {
            ivLayer->releaseAllButtons();
        }
    }
};