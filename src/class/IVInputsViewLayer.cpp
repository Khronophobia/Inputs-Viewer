#include "IVInputsViewLayer.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputsViewLayer::InputsViewLayer(LevelSettings const& settings)
    : m_currentSetting(settings)
    , m_settingListener(this, &InputsViewLayer::onSettingEvent, IVSettingFilter(SettingEventType::RefreshView)) {}

InputsViewLayer* InputsViewLayer::create(LevelSettings const& settings, GJBaseGameLayer* gameLayer) {
    auto ret = new (std::nothrow) InputsViewLayer(settings);
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

    m_p1InputNode = PlayerInputNode::create(m_currentSetting, gameLayer, "P1");
    this->addChild(m_p1InputNode);
    m_p2InputNode = PlayerInputNode::create(m_currentSetting, gameLayer, "P2");
    this->addChild(m_p2InputNode);

    this->refreshDisplay();
    return true;
}

void InputsViewLayer::setLevelSettings(LevelSettings const& settings) {
    m_currentSetting = settings;
    m_p1InputNode->setLevelSettings(settings);
    m_p2InputNode->setLevelSettings(settings);

    this->refreshDisplay();
}

void InputsViewLayer::refreshDisplay() {
    m_currentSetting.get().p1Transform.applyTransform(m_p1InputNode);
    m_currentSetting.get().p2Transform.applyTransform(m_p2InputNode);
}

void InputsViewLayer::onSettingEvent(SettingEventType) {
    this->refreshDisplay();
}

GEODE_NS_IV_END