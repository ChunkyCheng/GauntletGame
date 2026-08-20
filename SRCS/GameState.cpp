#include "GameState.hpp"
#include "raylib.h"
#include <iostream>

GameState::GameState(void)
	: m_playState(GameState::Init)
	, m_gameStartTime(0)
	, m_highScore(0)
	, m_renderer(*this)
	, m_showDebug(false)
{}
GameState::~GameState(void) {}

void	GameState::runGameEvents(void)
{
	switch(m_playState)
	{
		case GameState::Init:
			runInitState();
			break ;
		case GameState::InGame:
			runInGameState();
			break ;
		case GameState::GameOver:
			runGameOverState();
			break ;
		default:
			break ;
	}
}

void	GameState::runInitState(void)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		m_playState = GameState::InGame;
		m_gameStartTime = GetTime();
	}
	BeginDrawing();
	ClearBackground(BLACK);
	m_renderer.renderTextCentered("Press Enter to Start", WIN_WIDTH / 2, WIN_HEIGHT / 2, 50, WHITE);
	EndDrawing();
}

void	GameState::runInGameState(void)
{
	float	timeElapsed = GetTime() - m_gameStartTime;	
	m_score = timeElapsed * timeElapsed;
	
	float	dt = GetFrameTime();
	m_player.updatePos(dt);
	for (auto& e : m_obstacleManager.obstacles())
		e->updatePos(dt);
	m_obstacleManager.removeDespawned();
	m_obstacleManager.spawn(timeElapsed);
	m_player.runCollisionEvents(m_obstacleManager.obstacles());
	if (!m_player.isAlive())
	{
		m_playState = GameState::GameOver;
		return ;
	}
	BeginDrawing();
	ClearBackground(BLACK);
	
	m_renderer.renderMap(
		{WIN_WIDTH / 2, WIN_HEIGHT / 2},
		MAP_RADIUS,
		m_obstacleManager.obstacles()
	);
	m_renderer.renderEntity(
		{WIN_WIDTH / 2, WIN_HEIGHT / 2},
		MAP_RADIUS,
		m_player
	);
	DrawFPS(5, 5);
	DrawText(("Score: " + std::to_string(m_score)).c_str(), 10, 50, 20, WHITE);

	EndDrawing();

}

void	GameState::runGameOverState(void)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		m_playState = GameState::InGame;		
		m_player.reset();
		m_obstacleManager.reset();
		if (m_score > m_highScore)
			m_highScore = m_score;
		m_gameStartTime = GetTime();
	}
	BeginDrawing();
	ClearBackground(BLACK);
	m_renderer.renderTextCentered("Score: " + std::to_string(m_score), WIN_WIDTH / 2, WIN_HEIGHT / 2 - 50, 50, YELLOW);
	if (m_score > m_highScore)
		m_renderer.renderTextCentered("New High Score!", WIN_WIDTH / 2, WIN_HEIGHT / 2, 50, YELLOW);
	else
		m_renderer.renderTextCentered("High score: " + std::to_string(m_highScore), WIN_WIDTH / 2, WIN_HEIGHT / 2, 20, WHITE);
	m_renderer.renderTextCentered("Press Enter to Play Again", WIN_WIDTH / 2, WIN_HEIGHT / 2 + 70, 20, WHITE);
	EndDrawing();
}

GameState::PlayState	GameState::playState(void) const { return m_playState; }
bool					GameState::showDebug(void) const { return m_showDebug; }