#ifndef TW_CLASS_GAMESTATESTORE
#define TW_CLASS_GAMESTATESTORE

/**
 * @file
 *
 * Header file for the tw::GameStateStore class.
 */

#include <unordered_map>
#include <string>
#include <memory>
#include "GameState.hpp"
#include "../Log/Log.hpp"

namespace tw {
class GameStateStore {

public:

    GameStateStore () = delete; // static only
    ~GameStateStore () = delete;

    GameStateStore (GameStateStore&&) = delete;
    GameStateStore& operator = (GameStateStore&&) = delete;

    GameStateStore (const GameStateStore&) = delete;
    GameStateStore& operator = (const GameStateStore&) = delete;

    // state getters
    static bool stateExists (const std::string&);
    static std::shared_ptr<GameState> getState (const std::string&);

    // state setters
    template <typename TState, typename ...TArg>
    static std::shared_ptr<GameState> makeState (const std::string& key, TArg&&... args) {

        if (stateExists(key)) {
            logStateAlreadyExists(key);
            return nullptr;
        }

        auto state = std::make_shared<TState>(std::forward<TArg>(args)...);

        if (registerState(key, state)) {
            return state;
        } else {
            return nullptr;
        }

    }
    static bool registerState (const std::string&, const std::shared_ptr<GameState>&);
    static bool registerState (const std::string&, GameState*);
    static void deleteState (const std::string&);

private:

    static void logStateAlreadyExists (const std::string&);

    static std::unordered_map<std::string, std::shared_ptr<GameState>> m_stateMap;

};
}

#endif
