#include <Geode/loader/SettingV3.hpp>
#include <class/IVManager.hpp>
#include <class/IVSettingsLayer.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

class UISettingsButtonSettingV3 : public SettingV3 {
public:
    static Result<std::shared_ptr<SettingV3>> parse(std::string const& key, std::string const& modID, matjson::Value const& json) {
        auto res = std::make_shared<UISettingsButtonSettingV3>();
        auto root = checkJson(json, "UISettingsButton");

        res->init(key, modID, root);
        res->parseNameAndDescription(root);

        root.checkUnknownKeys();
        return root.ok(std::static_pointer_cast<SettingV3>(res));
    }

    bool load(matjson::Value const&) override {
        return true;
    }
    bool save(matjson::Value&) const override {
        return true;
    }

    bool isDefaultValue() const override {
        return true;
    }
    void reset() override {}

    SettingNodeV3* createNode(float width) override;
};

class UISettingsButtonSettingNodeV3 : public SettingNodeV3 {
public:
    static UISettingsButtonSettingNodeV3* create(std::shared_ptr<UISettingsButtonSettingV3> setting, float width) {
        auto ret = new (std::nothrow) UISettingsButtonSettingNodeV3();
        if (ret && ret->init(setting, width)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
    bool hasUncommittedChanges() const override {
        return false;
    }
    bool hasNonDefaultValue() const override {
        return false;
    }
protected:
    bool init(std::shared_ptr<UISettingsButtonSettingV3> setting, float width) {
        if (!SettingNodeV3::init(setting, width)) return false;

        if (IVManager::get().m_isInSetting) {
            m_disableText = CCLabelBMFont::create("Already Inside", "bigFont.fnt");
            m_disableText->setScale(0.4f);

            this->getButtonMenu()->addChildAtPosition(m_disableText, Anchor::Center);
        } else {
            auto sprite = ButtonSprite::create("Open", "bigFont.fnt", "GJ_button_05.png");
            sprite->setScale(0.5f);
            m_button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(UISettingsButtonSettingNodeV3::onButton));

            this->getButtonMenu()->addChildAtPosition(m_button, Anchor::Center);
        }

        return true;
    }
    void onCommit() override {}
    void onResetToDefault() override {}

    void onButton(CCObject*) {
        SettingsLayer::create(LevelSettingsType::Classic, false)->show();
    }
protected:
    CCMenuItemSpriteExtra* m_button{};
    CCLabelBMFont* m_disableText{};
};

SettingNodeV3* UISettingsButtonSettingV3::createNode(float width) {
    return UISettingsButtonSettingNodeV3::create(std::static_pointer_cast<UISettingsButtonSettingV3>(shared_from_this()), width);
}

$execute {
    (void)Mod::get()->registerCustomSettingType("ui-setting-button", &UISettingsButtonSettingV3::parse);
}

GEODE_NS_IV_END