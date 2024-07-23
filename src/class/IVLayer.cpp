#include "IVLayer.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputsViewLayer::InputsViewLayer()
    : m_settingListener(this, &InputsViewLayer::onSettingEvent, IVSettingFilter(SettingEventType::RefreshView)) {}

InputsViewLayer* InputsViewLayer::create() {
    auto ret = new (std::nothrow) InputsViewLayer;
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputsViewLayer::init() {
    if (!CCLayer::init()) return false;

    m_p1InputNode = PlayerInputNode::create("P1");
    this->addChild(m_p1InputNode);
    m_p2InputNode = PlayerInputNode::create("P2");
    this->addChild(m_p2InputNode);

    this->refreshDisplay();
    return true;
}

void InputsViewLayer::refreshDisplay() {
    IVManager::get().m_p1Transform.applyTransform(m_p1InputNode);
    IVManager::get().m_p2Transform.applyTransform(m_p2InputNode);
}

void InputsViewLayer::onSettingEvent(SettingEventType type) {
    this->refreshDisplay();
}

GEODE_NS_IV_END