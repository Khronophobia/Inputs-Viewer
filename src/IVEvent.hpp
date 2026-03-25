#pragma once

GEODE_NS_IV_BEGIN

enum class SettingEventType {
    Color,
    KeyAppearance,
    RefreshView,
};

class IVSettingEvent : public geode::Event<IVSettingEvent, bool(), SettingEventType> {
public:
    using Event::Event;
};

GEODE_NS_IV_END