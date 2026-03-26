#include "GJBaseGameLayer.hpp"
#include "IVEvent.hpp"

using namespace geode::prelude;

$override
void IVGJBaseGameLayer::handleButton(bool down, int button, bool isP1) {
    GJBaseGameLayer::handleButton(down, button, isP1);

    m_fields->m_ivLayer->handleButton(down, static_cast<PlayerButton>(button), isP1);
}

$override
void IVGJBaseGameLayer::resetLevelVariables() {
    GJBaseGameLayer::resetLevelVariables();
    if (m_fields->m_ivLayer) {
        m_fields->m_ivLayer->releaseAllButtons();
    }
}

$override
void IVGJBaseGameLayer::setupLevelStart(LevelSettingsObject* levelSettings) {
    GJBaseGameLayer::setupLevelStart(levelSettings);
    if (m_fields->m_ivLayer) return;

    if (m_isPlatformer) {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::LevelSettingsType::Platformer);
    } else {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::LevelSettingsType::Classic);
    }
    m_fields->m_ivLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    m_uiLayer->addChild(m_fields->m_ivLayer);
}

/*
    I would have used `GJBaseGameLayer::updateTimeWarp, which only gets called when the TimeWarp itself changes instead of being called every frame`,
    but it doesn't work properly when you die and the level restarts
*/
$override
void IVGJBaseGameLayer::applyTimeWarp(float timeWarp) {
    GJBaseGameLayer::applyTimeWarp(timeWarp);
    if (m_fields->m_currentTimeWarp != timeWarp) {
        m_fields->m_currentTimeWarp = timeWarp;
        inputs_viewer::TimeWarpEvent().send(timeWarp);
        geode::log::debug("updated timewarp to {}", timeWarp);
    }
}
