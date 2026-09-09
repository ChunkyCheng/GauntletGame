#include "GameState.hpp"
#include "raylib.h"
#include <iostream>
#include <fstream>

GameState::GameState(void)
	: m_playState(GameState::Init)
	, m_gameStartTime(0)
	, m_score(0)
	, m_renderer(*this)
	, m_showDebug(false)
{
	std::ifstream	saveFile("save.hyperwau");

	if (!saveFile.is_open())
		m_highScore = 0;
	else
	{
		std::string	saveData;

		std::getline(saveFile, saveData);
		try
		{
			m_highScore = std::stoi(saveData);
		}
		catch (std::exception& e)
		{
			m_highScore = 0;
		}
	}
	InitAudioDevice();
	m_sfxGameEnd = LoadSound("sfx/game_over.mp3");
	m_sfxNewHighScore = LoadSound("sfx/new_high_score.mp3");
}

GameState::~GameState(void)
{
	UnloadSound(m_sfxNewHighScore);
	UnloadSound(m_sfxGameEnd);
	CloseAudioDevice();

	std::ofstream	saveFile("save.hyperwau");

	if (m_score > m_highScore)
		m_highScore = m_score;
	if (saveFile.is_open())
		saveFile << std::to_string(m_highScore);
	else
		std::cerr << "Failed to save high score" << std::endl;
}

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
	m_renderer.renderTextCentered("Use the arrow keys to move", WIN_WIDTH / 2, WIN_HEIGHT / 2 + 60, 30, WHITE);
	EndDrawing();
}

void	GameState::runInGameState(void)
{
	float	timeElapsed = GetTime() - m_gameStartTime;	
	m_score = timeElapsed * timeElapsed;
	
	float	dt = GetFrameTime();
	m_player.updatePos(dt);
	for (auto& e : m_obstacleManager.entities())
		e->updatePos(dt);
	for (auto& e : m_decorationManager.entities())
		e->updatePos(dt);
	m_obstacleManager.removeDespawned();
	m_decorationManager.removeDespawned();
	m_obstacleManager.spawn(timeElapsed);
	m_decorationManager.spawn(timeElapsed);
	m_player.runCollisionEvents(m_obstacleManager.entities());
	if (!m_player.isAlive())
	{
		m_player.reset();
		m_obstacleManager.reset();
		m_decorationManager.reset();
		if (m_score > m_highScore)
			PlaySound(m_sfxNewHighScore);
		PlaySound(m_sfxGameEnd);
		m_playState = GameState::GameOver;
		return ;
	}
	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, MAP_RADIUS, BLUE);
	m_renderer.renderMap(
		{WIN_WIDTH / 2, WIN_HEIGHT / 2},
		MAP_RADIUS,
		m_decorationManager.entities()
	);
	m_renderer.renderMap(
		{WIN_WIDTH / 2, WIN_HEIGHT / 2},
		MAP_RADIUS,
		m_obstacleManager.entities()
	);
	m_renderer.renderEntity(
		{WIN_WIDTH / 2, WIN_HEIGHT / 2},
		MAP_RADIUS,
		m_player
	);
	if (m_showDebug)
		DrawFPS(5, 5);
	DrawText(("Score: " + std::to_string(m_score)).c_str(), 10, 50, 20, WHITE);

	EndDrawing();
}

void	GameState::runGameOverState(void)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		m_playState = GameState::InGame;		
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