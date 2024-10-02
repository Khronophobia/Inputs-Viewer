#include "UILayer.hpp"
#include <class/IVManager.hpp>

using namespace geode::prelude;

void IVUILayer::setupInputsViewer(bool isPlatformer) {
    if (m_fields->m_ivLayer) return;

    if (isPlatformer) {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::LevelSettingsType::Platformer);
    } else {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::LevelSettingsType::Classic);
    }
    m_fields->m_ivLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->addChild(m_fields->m_ivLayer);
}