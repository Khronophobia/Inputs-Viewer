#include <Geode/modify/GJBaseGameLayer.hpp>
#include <class/IVInputsViewLayer.hpp>

struct GJBaseGameLayerHook : geode::Modify<GJBaseGameLayerHook, GJBaseGameLayer> {
    struct Fields {
        geode::Ref<inputs_viewer::InputsViewLayer> m_ivLayer = nullptr;
        float m_currentTimeWarp = 1.f;
    };

    $override
    void resetLevelVariables();
    $override
    void setupLevelStart(LevelSettingsObject* levelSettings);
    $override
    void applyTimeWarp(float timeWarp);
};