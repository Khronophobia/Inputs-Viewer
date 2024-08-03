#include "UILayer.hpp"

using namespace geode::prelude;

void IVUILayer::setupInputsViewer() {
    if (m_fields->m_ivLayer) return;

    m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create();
    m_fields->m_ivLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->addChild(m_fields->m_ivLayer);
}