#include "GJBaseGameLayer.hpp"

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