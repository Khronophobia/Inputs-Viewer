#include "IVFloatSlider.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

FloatSlider* FloatSlider::create(char const* text, float defaultValue, float min, float max, std::function<Callback>&& callback) {
    auto ret = new (std::nothrow) FloatSlider;
    if (ret && ret->init(text, defaultValue, min, max, std::move(callback))) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool FloatSlider::init(char const* text, float defaultValue, float min, float max, std::function<Callback>&& callback) {
    m_callback = std::move(callback);
    m_minValue = min;
    m_maxValue = max;

    m_slider = Slider::create(this, menu_selector(FloatSlider::onSlider), 0.5f);
    m_slider->m_sliderBar->setVisible(false);
    this->addChild(m_slider);

    m_textInput = TextInput::create(80.f, "Value");
    m_textInput->setPosition(26.f, 16.f);
    m_textInput->setCommonFilter(CommonFilter::Float);
    m_textInput->setScale(0.65f);
    m_textInput->setCallback(std::bind(&FloatSlider::onTextInput, this, std::placeholders::_1));
    this->addChild(m_textInput);

    m_textLabel = CCLabelBMFont::create(text, "bigFont.fnt");
    m_textLabel->setAnchorPoint(ccp(0.f, 0.5f));
    m_textLabel->setPosition(-50.f, 16.f);
    m_textLabel->limitLabelWidth(45.f, 0.6f, 0.1f);
    this->addChild(m_textLabel);

    this->setValueInternal(defaultValue, false);
    return true;
}

void FloatSlider::setValue(float value, bool clamp, bool triggerCallback) {
    if (clamp) {
        this->setValueInternal(std::clamp(value, m_minValue, m_maxValue), triggerCallback);
    } else {
        this->setValueInternal(value, triggerCallback);
    }
}

void FloatSlider::setValueInternal(float value, bool triggerCallback) {
    m_textInput->setString(numToString(value));
    m_slider->setValue(this->rangeValueToSliderValue(value));

    if (triggerCallback) this->activate();
}

float FloatSlider::getValue() const {
    return this->sliderValueToRangeValue(m_slider->getThumb()->getValue());
}

float FloatSlider::sliderValueToRangeValue(float value) const noexcept {
    return value * (m_maxValue - m_minValue) + m_minValue;
}

float FloatSlider::rangeValueToSliderValue(float value) const noexcept {
    return (value - m_minValue) / (m_maxValue - m_minValue);
}

void FloatSlider::onSlider(CCObject*) {
    m_textInput->setString(numToString(this->getValue()));

    this->activate();
}

void FloatSlider::onTextInput(std::string const& string) {
    auto res = numFromString<float>(string);
    if (auto num = res.ok()) {
        if (*num < m_minValue) {
            *num = m_minValue;
            m_textInput->setString(numToString(m_minValue));
        }
        else if (*num > m_maxValue) {
            *num = m_maxValue;
            m_textInput->setString(numToString(m_maxValue));
        }

        m_slider->setValue(this->rangeValueToSliderValue(*num));

        this->activate();
    }
}

void FloatSlider::activate() {
    if (m_callback) m_callback(this);
}

GEODE_NS_IV_END