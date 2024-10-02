#include "GJBaseGameLayer.hpp"
#include "UILayer.hpp"

using namespace geode::prelude;

$override
void IVGJBaseGameLayer::handleButton(bool down, int button, bool isP1) {
    GJBaseGameLayer::handleButton(down, button, isP1);
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    ivLayer->handleButton(down, static_cast<PlayerButton>(button), isP1);
}

$override
void IVGJBaseGameLayer::resetLevelVariables() {
    GJBaseGameLayer::resetLevelVariables();
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    ivLayer->releaseAllButtons();
}

void IVGJBaseGameLayer::setupLevelStart(LevelSettingsObject* levelSettings) {
    GJBaseGameLayer::setupLevelStart(levelSettings);

    static_cast<IVUILayer*>(m_uiLayer)->setupInputsViewer(levelSettings);
}