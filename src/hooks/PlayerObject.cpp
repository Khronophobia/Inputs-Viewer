#include <Geode/modify/PlayerObject.hpp>
#include "GJBaseGameLayer.hpp"

using namespace geode::prelude;

struct PlayerObjectHook : Modify<PlayerObjectHook, PlayerObject> {
    bool pushButton(PlayerButton button) {
        if (!PlayerObject::pushButton(button)) return false;
        auto gameLayer = static_cast<IVGJBaseGameLayer*>(GJBaseGameLayer::get());
        if (!gameLayer) return true;
        if (!gameLayer->m_fields->m_ivLayer) return true;

        if (this == gameLayer->m_player1) {
            gameLayer->m_fields->m_ivLayer->handleButton(true, button, true);
        } else if (this == gameLayer->m_player2) {
            gameLayer->m_fields->m_ivLayer->handleButton(true, button, false);
        }

        return true;
    }
    bool releaseButton(PlayerButton button) {
        if (!PlayerObject::releaseButton(button)) return false;
        auto gameLayer = static_cast<IVGJBaseGameLayer*>(GJBaseGameLayer::get());
        if (!gameLayer) return true;
        if (!gameLayer->m_fields->m_ivLayer) return true;

        if (this == gameLayer->m_player1) {
            gameLayer->m_fields->m_ivLayer->handleButton(false, button, true);
        } else if (this == gameLayer->m_player2) {
            gameLayer->m_fields->m_ivLayer->handleButton(false, button, false);
        }
        
        return true;
    }
};
