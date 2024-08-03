#include "IVInputsViewLayer.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputsViewLayer::InputsViewLayer()
    : m_settingListener(this, &InputsViewLayer::onSettingEvent, IVSettingFilter(SettingEventType::RefreshView)) {}

InputsViewLayer* InputsViewLayer::create(GJBaseGameLayer* gameLayer) {
    auto ret = new (std::nothrow) InputsViewLayer;
    if (ret && ret->init(gameLayer)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputsViewLayer::init(GJBaseGameLayer* gameLayer) {
    if (!CCLayer::init()) return false;
    m_gameLayer = gameLayer;

    m_p1InputNode = PlayerInputNode::create(gameLayer, "P1");
    this->addChild(m_p1InputNode);
    m_p2InputNode = PlayerInputNode::create(gameLayer, "P2");
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