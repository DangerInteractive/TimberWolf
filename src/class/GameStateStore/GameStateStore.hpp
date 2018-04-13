#ifndef H_CLASS_GAMESTATESTORE
#define H_CLASS_GAMESTATESTORE

#include <map>
#include <string>
#include "../GameState/GameState.hpp"

namespace tw {
class GameStateStore {

public:

    GameStateStore () = delete; // static only
    ~GameStateStore () = delete;

    GameStateStore (GameStateStore&&) = delete;
    GameStateStore& operator = (GameStateStore&&) = delete;

    GameStateStore (const GameStateStore&) = delete;
    GameStateStore& operator = (const GameStateStore&) = delete;

    static bool stateExists (std::string);
    static GameState* getState (std::string);

    static bool registerState (std::string, GameState*);
    static void deleteState (std::string);

private:

    static std::map<std::string, GameState*> m_stateMap;

};
}

#endif
