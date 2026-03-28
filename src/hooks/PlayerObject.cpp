#include <Geode/modify/PlayerObject.hpp>
#include "GJBaseGameLayer.hpp"

using namespace geode::prelude;

struct PlayerObjectHook : Modify<PlayerObjectHook, PlayerObject> {
    bool pushButton(PlayerButton button) {
        auto result = PlayerObject::pushButton(button);
        auto gameLayer = static_cast<IVGJBaseGameLayer*>(GJBaseGameLayer::get());
        if (!gameLayer) return result;
        if (!gameLayer->m_fields->m_ivLayer) return result;

        if (this == gameLayer->m_player1) {
            gameLayer->m_fields->m_ivLayer->handleButton(true, button, true);
        } else if (this == gameLayer->m_player2 && gameLayer->m_level->m_twoPlayerMode) {
            gameLayer->m_fields->m_ivLayer->handleButton(true, button, false);
        }

        return result;
    }
    bool releaseButton(PlayerButton button) {
        auto result = PlayerObject::releaseButton(button);
        auto gameLayer = static_cast<IVGJBaseGameLayer*>(GJBaseGameLayer::get());
        if (!gameLayer) return result;
        if (!gameLayer->m_fields->m_ivLayer) return result;

        if (this == gameLayer->m_player1) {
            gameLayer->m_fields->m_ivLayer->handleButton(false, button, true);
        } else if (this == gameLayer->m_player2 && gameLayer->m_level->m_twoPlayerMode) {
            gameLayer->m_fields->m_ivLayer->handleButton(false, button, false);
        }
        
        return result;
    }
};
