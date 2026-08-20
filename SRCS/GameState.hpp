#pragma once

#include "Player.hpp"
#include "ObstacleManager.hpp"
#include "DecorationManager.hpp"
#include "Renderer.hpp"

constexpr int	WIN_WIDTH = 1280;
constexpr int	WIN_HEIGHT = 800;
constexpr int	MAP_RADIUS = WIN_HEIGHT / 2 - 10;

class	GameState
{
	public:
		GameState(void);
		GameState(const GameState& other);
		GameState&	operator=(const GameState& other);
		~GameState(void);

		void	runGameEvents(void);
		void	runInitState(void);
		void	runInGameState(void);
		void	runGameOverState(void);

		enum	PlayState
		{
			Init,
			InGame,
			GameOver
		};
	
		PlayState	playState(void) const;
		bool		showDebug(void)	const;

	private:
		PlayState	m_playState;
		float		m_gameStartTime;
		int			m_score;
		int			m_highScore;

		Player				m_player;
		ObstacleManager		m_obstacleManager;
		DecorationManager	m_decorationManager;
		Renderer			m_renderer;
		
		bool		m_showDebug;
};

