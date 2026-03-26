#include <Geode/modify/GJBaseGameLayer.hpp>
#include <class/IVInputsViewLayer.hpp>

struct IVGJBaseGameLayer : geode::Modify<IVGJBaseGameLayer, GJBaseGameLayer> {
    struct Fields {
        inputs_viewer::InputsViewLayer* m_ivLayer = nullptr;
        float m_currentTimeWarp = 1.f;
    };

    $override
    void handleButton(bool down, int button, bool isP1);
    $override
    void resetLevelVariables();
    $override
    void setupLevelStart(LevelSettingsObject* levelSettings);
    $override
    void applyTimeWarp(float timeWarp);
};