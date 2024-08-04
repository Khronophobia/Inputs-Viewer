#include "IVManager.hpp"
#include <IVEvent.hpp>

// Initializer order doesn't matter here
#pragma GCC diagnostic ignored "-Wreorder-ctor"

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
    , m_p1Transform(Mod::get()->getSavedValue<NodeTransform>("p1-display", IVManager::getDefaultP1Transform()))
    , m_p2Transform(Mod::get()->getSavedValue<NodeTransform>("p2-display", IVManager::getDefaultP2Transform()))
    , m_showTotalInputs(Mod::get()->getSavedValue("show-total-inputs", false))
    , m_showCPS(Mod::get()->getSavedValue("show-cps", false))
    , m_minimalIfNonPlatformer(Mod::get()->getSavedValue("minimal-if-non-platformer", false))
{}

IVManager& IVManager::get() {
    static auto inst = std::make_unique<IVManager>();

    return *inst;
}

NodeTransform IVManager::getDefaultP1Transform() {
    auto winSize = CCDirector::get()->getWinSize();
    auto maxWidth = winSize.width * 0.5f;
    auto maxHeight = winSize.height * 0.5f;

    return {
        .position = {-maxWidth * 0.5f, -maxHeight + 4.f},
        .scale = 1.f
    };
}

NodeTransform IVManager::getDefaultP2Transform() {
    auto winSize = CCDirector::get()->getWinSize();
    auto maxWidth = winSize.width * 0.5f;
    auto maxHeight = winSize.height * 0.5f;

    return {
        .position = {maxWidth * 0.5f, -maxHeight + 4.f},
        .scale = 1.f
    };
}

$on_mod(DataSaved) {
    Mod::get()->setSavedValue("p1-display", IVManager::get().m_p1Transform);
    Mod::get()->setSavedValue("p2-display", IVManager::get().m_p2Transform);
    Mod::get()->setSavedValue("show-total-inputs", IVManager::get().m_showTotalInputs);
    Mod::get()->setSavedValue("show-cps", IVManager::get().m_showCPS);
    Mod::get()->setSavedValue("minimal-if-non-platformer", IVManager::get().m_minimalIfNonPlatformer);
}

GEODE_NS_IV_END