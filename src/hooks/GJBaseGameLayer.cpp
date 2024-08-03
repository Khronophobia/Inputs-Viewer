#include "GJBaseGameLayer.hpp"
#include "UILayer.hpp"

using namespace geode::prelude;

void IVGJBaseGameLayer::handleButton(bool down, int button, bool isP1) {
    GJBaseGameLayer::handleButton(down, button, isP1);
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    if (isP1) {
        ivLayer->m_p1InputNode->handleButton(down, static_cast<PlayerButton>(button));
    } else {
        ivLayer->m_p2InputNode->handleButton(down, static_cast<PlayerButton>(button));
    }
}

static void resetInputNode(inputs_viewer::PlayerInputNode* node) {
    node->handleButton(false, PlayerButton::Jump, false);
    node->handleButton(false, PlayerButton::Left, false);
    node->handleButton(false, PlayerButton::Right, false);
}

void IVGJBaseGameLayer::resetLevelVariables() {
    GJBaseGameLayer::resetLevelVariables();
    auto ivLayer = static_cast<IVUILayer*>(m_uiLayer)->m_fields->m_ivLayer;

    resetInputNode(ivLayer->m_p1InputNode);
    resetInputNode(ivLayer->m_p2InputNode);
}