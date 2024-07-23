#include "UILayer.hpp"

using namespace geode::prelude;

bool IVUILayer::init(GJBaseGameLayer* gameLayer) {
    if (!UILayer::init(gameLayer)) return false;

    m_fields->m_ivLayer = inputs_viewer::InputsViewLayer::create();
    m_fields->m_ivLayer->setPosition(CCDirector::get()->getWinSize() * 0.5f);
    this->addChild(m_fields->m_ivLayer);

    return true;
}