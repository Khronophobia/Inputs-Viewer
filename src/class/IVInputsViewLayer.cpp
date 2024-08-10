#include "IVInputsViewLayer.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputsViewLayer::InputsViewLayer(LevelSettingsType type)
    : m_currentSetting(IVManager::get().getLevelSettings(type))
    , m_settingListener(this, &InputsViewLayer::onSettingEvent, IVSettingFilter(SettingEventType::RefreshView)) {}

InputsViewLayer* InputsViewLayer::create(LevelSettingsType type) {
    auto ret = new (std::nothrow) InputsViewLayer(type);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputsViewLayer::init() {
    if (!CCLayer::init()) return false;

    m_p1InputNode = PlayerInputNode::create(m_currentSetting, "P1");
    this->addChild(m_p1InputNode);
    m_p2InputNode = PlayerInputNode::create(m_currentSetting, "P2");
    this->addChild(m_p2InputNode);

    this->refreshDisplay();
    return true;
}

void InputsViewLayer::setLevelSettings(LevelSettingsType type) {
    m_currentSetting = IVManager::get().getLevelSettings(type);
    m_p1InputNode->setLevelSettings(IVManager::get().getLevelSettings(type));
    m_p2InputNode->setLevelSettings(IVManager::get().getLevelSettings(type));

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