#pragma once
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser
{
public:
	bool Load();
	void Clean();

	inline GameMap* GetMap(std::string id) { return m_MapDict[id]; }

	inline static MapParser* get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new MapParser();
		}
		return s_instance;
	}

private:
	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

private:
	MapParser() {}
	static MapParser* s_instance;
	std::map<std::string, GameMap*> m_MapDict;
};