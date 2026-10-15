#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <filesystem>
#include <map>
#include <string>
#include "DebugMgr.h"

struct AnimationData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	int OffsetX = 0;
	int OffsetY = 0;
	int AnimationSpriteCount = 0;
	int SpriteOnLine = 0;
	bool IsReverted = false;
	float TimeBetweenAnimationInS = 0.f;
};

struct StaticTileData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	bool IsRevertedX = false;
	bool IsRevertedY = false;
};



struct TextureData
{
	enum Type
	{
		Animation,
		Background,
	};
	TextureData() {}
	~TextureData() {}

	sf::Texture texture;
	Type type;
	std::map<std::string, AnimationData> animationsData;
	std::map<std::string, StaticTileData> staticTilesData;
	// AnimationData animationsData;
	// StaticTileData staticTilesData;

	friend class TextureMgr;
};

class TextureMgr final : public IDebugable
{
public:
	void Init();
	void Shut();
	
	virtual void DrawDebug() override;

	/*
	 * Loads the texture using the given path, including its metadata.
	 * Obviously, this function will also store the loaded data
	 * If errors occur during the loading process, this function must return false.
	 * Return true otherwise.
	*/
	bool LoadTexture(const std::filesystem::path& path);
	bool isFileExists(const std::filesystem::path& path);
	bool isMetaExists(const std::string& path);
	void parseStaticData(TextureData& textureData, const rapidxml::xml_node<>* firstNode);
	void parseAnimData(TextureData& textureData, const rapidxml::xml_node<>* firstNode);
	TextureData createTextureData(rapidxml::xml_document<>& doc);

	/*
	 * Returns the corresponding TextureData using the name of the texture. Returns the default TextureData in case of an unknown name
	 */
	const TextureData& GetTextureData(const std::string& name) const;
	std::map<std::string, TextureData> textures;
};