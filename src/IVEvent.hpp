#pragma once

GEODE_NS_IV_BEGIN

enum class SettingEventType {
    Color,
    TotalInputsCounter,
    RefreshView
};

class IVSettingEvent : public geode::Event {
public:
    IVSettingEvent(SettingEventType type);
    SettingEventType getType() const noexcept;
protected:
    SettingEventType m_type;
};

class IVSettingFilter : public geode::EventFilter<IVSettingEvent> {
public:
    IVSettingFilter();
    IVSettingFilter(SettingEventType type);
public:
    using Callback = void(SettingEventType);
    geode::ListenerResult handle(geode::utils::MiniFunction<Callback> func, IVSettingEvent* event);
protected:
    std::optional<SettingEventType> m_type;
};

GEODE_NS_IV_END