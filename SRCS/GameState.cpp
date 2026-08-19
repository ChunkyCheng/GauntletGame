#include "GameState.hpp"

GameState::GameState(void) : m_showDebug(false) {}
GameState::~GameState(void) {}

bool	GameState::showDebug(void) const { return m_showDebug; }