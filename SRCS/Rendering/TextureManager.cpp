#include "TextureManager.hpp"
#include <array>

constexpr std::array<std::string_view, 4> DEFAULT_PATHS = {
	MISSING_TEXTURE,
	PLAYER_TEXTURE,
	HELICOPTER_LEFT_TEXTURE,
	HELICOPTER_RIGHT_TEXTURE
};

TextureManager::TextureManager(void)
{
	for (const std::string_view& path : DEFAULT_PATHS)
		loadTexture(static_cast<std::string>(path));
}

TextureManager::~TextureManager(void)
{
	for (auto [key, value] : m_textureMap)
		UnloadTexture(value);
}

void	TextureManager::loadTexture(const std::string& texturePath)
{
	auto it = m_textureMap.find(texturePath);

	if (it != m_textureMap.end())
		return ;
	m_textureMap[texturePath] = LoadTexture(texturePath.c_str());
}

void	TextureManager::unloadTexture(const std::string& texturePath)
{
	auto it = m_textureMap.find(texturePath);

	if (it == m_textureMap.end())
		return ;
	m_textureMap.erase(it);
}

const Texture2D*	TextureManager::get(const std::string& texturePath) const
{
	auto it = m_textureMap.find(texturePath);

	if (it == m_textureMap.end())
		return &m_textureMap.at(static_cast<std::string>(MISSING_TEXTURE));
	return &it->second;
}