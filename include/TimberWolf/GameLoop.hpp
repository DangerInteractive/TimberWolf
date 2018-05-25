#ifndef H_PKG_TW_GAMELOOP
#define H_PKG_TW_GAMELOOP

/**
 * @file
 *
 * Auto-include header for the game loop subsystem. Represents the headers that
 * are applicable to the core game loop, including the game loop itself, game
 * state machinery, and input/output processing. The headers included in the
 * game loop package may reference the core, log, graphics, and window packages.
 */

#include "Core.hpp"
#include "Log.hpp"
#include "Graphics.hpp"
#include "Window.hpp"

#include "GameLoop/Controller.hpp"
#include "GameLoop/GameLoop.hpp"
#include "GameLoop/GameState.hpp"
#include "GameLoop/GameStateManager.hpp"
#include "GameLoop/GameStateStore.hpp"
#include "GameLoop/KeyAction.hpp"
#include "GameLoop/Keybinding.hpp"
#include "GameLoop/KeyMod.hpp"
#include "GameLoop/KeyType.hpp"

#endif
