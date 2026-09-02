#pragma once

#include <string>
#include <unordered_map>
#include "raylib.h"

constexpr std::string_view MISSING_TEXTURE			= "textures/undefined.png";
constexpr std::string_view PLAYER_TEXTURE			= "textures/wau.png";
constexpr std::string_view HELICOPTER_LEFT_TEXTURE	= "textures/helicopter-left.png";
constexpr std::string_view HELICOPTER_RIGHT_TEXTURE	= "textures/helicopter-right.png";

class	TextureManager
{
	public:
		TextureManager(void);
		TextureManager(const TextureManager& other) = delete;
		TextureManager&	operator=(const TextureManager& other) = delete;
		~TextureManager(void);

		void	loadTexture(const std::string& texturePath);
		void	unloadTexture(const std::string& texturePath);

		const Texture2D*	get(const std::string& texturePath) const;

	private:
		std::unordered_map<std::string, Texture2D>	m_textureMap;
};