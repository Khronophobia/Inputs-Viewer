#include <Geode/modify/GJBaseGameLayer.hpp>

struct IVGJBaseGameLayer : geode::Modify<IVGJBaseGameLayer, GJBaseGameLayer> {
    $override
    void handleButton(bool down, int button, bool isP1);
    $override
    void resetLevelVariables();
    $override
    void setupLevelStart(LevelSettingsObject* levelSettings);
};