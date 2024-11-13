#pragma once
#include "IVPlayerInputNode.hpp"
#include "IVFloatSlider.hpp"
#include "IVLevelSettings.hpp"

GEODE_NS_IV_BEGIN

struct LevelSettings;

class TransformSlider : public cocos2d::CCNode {
public:
    TransformSlider(LevelSettings& setting);
    static TransformSlider* create(LevelSettings& setting, NodeTransform LevelSettings::* transform, PlayerInputNode* inputNode, char const* text, std::function<NodeTransform()>&& defaultPosFunc);
    bool init(NodeTransform LevelSettings::* transform, PlayerInputNode* inputNode, char const* text, std::function<NodeTransform()>&& defaultPosFunc);
public:
    void setLevelSettings(LevelSettingsType type);
    void onDefaultPosition(cocos2d::CCObject*);
    void onSetVisibility(cocos2d::CCObject*);
protected:
    void updateSettingNodes();
protected:
    std::reference_wrapper<LevelSettings> m_currentSetting;
    NodeTransform LevelSettings::* m_transform;
    PlayerInputNode* m_inputNode = nullptr;
    FloatSlider* m_xPosSlider = nullptr;
    FloatSlider* m_yPosSlider = nullptr;
    FloatSlider* m_scaleSlider = nullptr;
    CCMenuItemToggler* m_visibilityCheckbox = nullptr;
    cocos2d::CCLabelBMFont* m_textLabel = nullptr;
    cocos2d::CCMenu* m_buttonMenu = nullptr;
    std::function<NodeTransform()> m_defaultPosFunc = nullptr;
};

GEODE_NS_IV_END