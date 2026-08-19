#pragma once

class	GameState
{
	public:
		GameState(void);
		GameState(const GameState& other);
		GameState&	operator=(const GameState& other);
		~GameState(void);

		bool	showDebug(void)	const;
	protected:
	private:
		bool	m_showDebug;
};

