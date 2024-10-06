#include <Geode/modify/GJBaseGameLayer.hpp>
#include <class/IVInputsViewLayer.hpp>

struct IVGJBaseGameLayer : geode::Modify<IVGJBaseGameLayer, GJBaseGameLayer> {
    struct Fields {
        inputs_viewer::InputsViewLayer* m_ivLayer = nullptr;
    };

    $override
    void handleButton(bool down, int button, bool isP1);
    $override
    void resetLevelVariables();
    $override
    void setupLevelStart(LevelSettingsObject* levelSettings);
};