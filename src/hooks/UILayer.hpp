#include <Geode/modify/UILayer.hpp>
#include <class/IVInputsViewLayer.hpp>

struct IVUILayer : geode::Modify<IVUILayer, UILayer> {
    struct Fields {
        inputs_viewer::InputsViewLayer* m_ivLayer = nullptr;
    };

    $override
    bool init(GJBaseGameLayer* gameLayer);
};