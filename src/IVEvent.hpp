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

class TimeWarpEvent: public geode::Event<TimeWarpEvent, bool(float)> {
    using Event::Event;
};

GEODE_NS_IV_END