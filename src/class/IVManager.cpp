#include "IVManager.hpp"
#include <IVEvent.hpp>
#include <json/helper.hpp>

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
    , m_settingClassic(
            Mod::get()->getSavedValue<LevelSettings>("classic", {
                .p1Transform = IVManager::getDefaultP1Transform(),
                .p2Transform = IVManager::getDefaultP2Transform()
            })
        )
    , m_settingPlatformer(
            Mod::get()->getSavedValue<LevelSettings>("platformer", {
                .p1Transform = IVManager::getDefaultP1Transform(),
                .p2Transform = IVManager::getDefaultP2Transform()
            })
        )
#if 0
    , m_p1Transform(Mod::get()->getSavedValue<NodeTransform>("p1-display", IVManager::getDefaultP1Transform()))
    , m_p2Transform(Mod::get()->getSavedValue<NodeTransform>("p2-display", IVManager::getDefaultP2Transform()))
    , m_showTotalInputs(Mod::get()->getSavedValue("show-total-inputs", false))
    , m_showCPS(Mod::get()->getSavedValue("show-cps", false))
    , m_minimalIfNonPlatformer(Mod::get()->getSavedValue("minimal-if-non-platformer", false))
#endif
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
    Mod::get()->setSavedValue("classic", IVManager::get().m_settingClassic);
    Mod::get()->setSavedValue("platformer", IVManager::get().m_settingPlatformer);
    Mod::get()->setSavedValue("version", 1);
#if 0
    Mod::get()->setSavedValue("p1-display", IVManager::get().m_p1Transform);
    Mod::get()->setSavedValue("p2-display", IVManager::get().m_p2Transform);
    Mod::get()->setSavedValue("show-total-inputs", IVManager::get().m_showTotalInputs);
    Mod::get()->setSavedValue("show-cps", IVManager::get().m_showCPS);
    Mod::get()->setSavedValue("minimal-if-non-platformer", IVManager::get().m_minimalIfNonPlatformer);
#endif
}

$on_mod(Loaded) {
    int version = Mod::get()->getSavedValue("version", 0);
    if (version == 0) {
        IVManager::get().m_settingClassic.p1Transform = Mod::get()->getSavedValue<NodeTransform>("p1-display");
        IVManager::get().m_settingPlatformer.p1Transform = Mod::get()->getSavedValue<NodeTransform>("p1-display");

        IVManager::get().m_settingClassic.p2Transform = Mod::get()->getSavedValue<NodeTransform>("p2-display");
        IVManager::get().m_settingPlatformer.p2Transform = Mod::get()->getSavedValue<NodeTransform>("p2-display");

        IVManager::get().m_settingClassic.showTotalInputs = Mod::get()->getSavedValue<bool>("show-total-inputs");
        IVManager::get().m_settingPlatformer.showTotalInputs = Mod::get()->getSavedValue<bool>("show-total-inputs");

        IVManager::get().m_settingClassic.showCPS = Mod::get()->getSavedValue<bool>("show-cps");
        IVManager::get().m_settingPlatformer.showCPS = Mod::get()->getSavedValue<bool>("show-cps");

        if (Mod::get()->getSavedValue<bool>("minimal-if-non-platformer")) {
            IVManager::get().m_settingClassic.hideLeftRight = true;
            IVManager::get().m_settingPlatformer.hideLeftRight = false;
        }
    }
}

GEODE_NS_IV_END

matjson::Value matjson::Serialize<inputs_viewer::LevelSettings>::to_json(inputs_viewer::LevelSettings const& value) {
    return matjson::Object{
        {"p1-display", value.p1Transform},
        {"p2-display", value.p2Transform},
        {"show-total-inputs", value.showTotalInputs},
        {"show-cps", value.showCPS},
        {"hide-left-right", value.hideLeftRight}
    };
}

inputs_viewer::LevelSettings matjson::Serialize<inputs_viewer::LevelSettings>::from_json(matjson::Value const& value) {
    return {
        .p1Transform = value["p1-display"].as<NodeTransform>(),
        .p2Transform = value["p2-display"].as<NodeTransform>(),
        .showTotalInputs = value["show-total-inputs"].as_bool(),
        .showCPS = value["show-cps"].as_bool(),
        .hideLeftRight = value["hide-left-right"].as_bool()
    };
}

bool matjson::Serialize<inputs_viewer::LevelSettings>::is_json(matjson::Value const& value) {
    return verifyJsonObject<NodeTransform>(value, "p1-display") &&
        verifyJsonObject<NodeTransform>(value, "p2-display") &&
        verifyJsonObject<bool>(value, "show-total-inputs") &&
        verifyJsonObject<bool>(value, "show-cps") &&
        verifyJsonObject<bool>(value, "hide-left-right");
}