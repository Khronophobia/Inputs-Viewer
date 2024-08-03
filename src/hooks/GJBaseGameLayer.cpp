#include "GJBaseGameLayer.hpp"
#include "UILayer.hpp"

using namespace geode::prelude;

$override
void IVGJBaseGameLayer::handleButton(bool down, int button, bool isP1) {
    GJBaseGameLayer::handleButton(down, button, isP1);
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    if (isP1) {
        ivLayer->m_p1InputNode->handleButton(down, static_cast<PlayerButton>(button));
    } else {
        ivLayer->m_p2InputNode->handleButton(down, static_cast<PlayerButton>(button));
    }
}

$override
void IVGJBaseGameLayer::resetLevelVariables() {
    GJBaseGameLayer::resetLevelVariables();
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    ivLayer->m_p1InputNode->releaseAllButtons();
    ivLayer->m_p2InputNode->releaseAllButtons();
}

void IVGJBaseGameLayer::loadLevelSettings() {
    GJBaseGameLayer::loadLevelSettings();

    static_cast<IVUILayer*>(m_uiLayer)->setupInputsViewer();
}