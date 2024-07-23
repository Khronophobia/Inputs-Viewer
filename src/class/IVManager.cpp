#include "IVManager.hpp"
#include <IVEvent.hpp>

using namespace geode::prelude;

#define GEODE_IV_CONSTRUCT_COLOR(__col) \
    m_##__col##PressColor(Mod::get()->getSettingValue<ccColor4B>(#__col "-press-color")), \
    m_##__col##ReleaseColor(Mod::get()->getSettingValue<ccColor4B>(#__col "-release-color")), \
    m_##__col##PressListener( \
        [this](auto color) { m_##__col##PressColor = color; IVSettingEvent(SettingEventType::Color).post(); }, \
        RGBASettingFilter(Mod::get()->getID(), #__col "-press-color") \
    ), \
    m_##__col##ReleaseListener( \
        [this](auto color) { m_##__col##ReleaseColor = color; IVSettingEvent(SettingEventType::Color).post(); }, \
        RGBASettingFilter(Mod::get()->getID(), #__col "-release-color") \
    ) \

GEODE_NS_IV_BEGIN

IVManager::IVManager()
    : GEODE_IV_CONSTRUCT_COLOR(background)
    , GEODE_IV_CONSTRUCT_COLOR(outline)
    , GEODE_IV_CONSTRUCT_COLOR(text)
    , m_p1Transform(Mod::get()->getSavedValue<NodeTransform>("p1-display", { .position{-150.f, -150.f} }))
    , m_p2Transform(Mod::get()->getSavedValue<NodeTransform>("p2-display", { .position{150.f, -150.f} }))
    , m_showTotalInputs(Mod::get()->getSavedValue("show-total-inputs", false))
{}

IVManager& IVManager::get() {
    static auto inst = std::make_unique<IVManager>();

    return *inst;
}

$on_mod(DataSaved) {
    Mod::get()->setSavedValue("p1-display", IVManager::get().m_p1Transform);
    Mod::get()->setSavedValue("p2-display", IVManager::get().m_p2Transform);
    Mod::get()->setSavedValue("show-total-inputs", IVManager::get().m_showTotalInputs);
}

GEODE_NS_IV_END