#pragma once

GEODE_NS_IV_BEGIN

class FloatSlider : public cocos2d::CCNode {
public:
    using Callback = void(FloatSlider*);
public:
    static FloatSlider* create(char const* text, float defaultValue, float min, float max, std::function<Callback>&& callback);
    bool init(char const* text, float defaultValue, float min, float max, std::function<Callback>&& callback);
public:
    void setValue(float value, bool clamp = true, bool triggerCallback = false);
    float getValue() const;
    void activate();
    void onSlider(cocos2d::CCObject*);
    void onTextInput(std::string const& string);
protected:
    void setValueInternal(float value, bool triggerCallback);
    float sliderValueToRangeValue(float value) const noexcept;
    float rangeValueToSliderValue(float value) const noexcept;
protected:
    std::function<Callback> m_callback;
    float m_minValue;
    float m_maxValue;
    Slider* m_slider = nullptr;
    geode::TextInput* m_textInput = nullptr;
    cocos2d::CCLabelBMFont* m_textLabel = nullptr;
};

GEODE_NS_IV_END