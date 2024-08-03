#include <Geode/modify/PlayLayer.hpp>
#include "UILayer.hpp"

using namespace geode::prelude;

struct IVPlayLayer : Modify<IVPlayLayer, PlayLayer> {
    $override
    void pauseGame(bool p0) {
        PlayLayer::pauseGame(p0);
        auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

        ivLayer->m_p1InputNode->releaseAllButtons();
        ivLayer->m_p2InputNode->releaseAllButtons();
    }
};