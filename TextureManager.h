#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using namespace std;

class TextureManager
{
	// Static means one and only one in memory
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string fileName);
public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

