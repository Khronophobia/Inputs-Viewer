#include "UILayer.hpp"
#include <class/IVManager.hpp>

using namespace geode::prelude;

void IVUILayer::setupInputsViewer() {
    if (m_fields->m_ivLayer) return;

    if (m_gameLayer->m_levelSettings->m_platformerMode) {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::IVManager::get().m_settingPlatformer, m_gameLayer);
    } else {
        m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create(inputs_viewer::IVManager::get().m_settingClassic, m_gameLayer);
    }
    m_fields->m_ivLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->addChild(m_fields->m_ivLayer);
}