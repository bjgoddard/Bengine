#pragma once
#include "Layer.h"
#include <vector>

class GameMap
{
public:
	void Render()
	{
		for (int i = 0; i < m_MapLayers.size(); i++)
		{
			m_MapLayers[i]->Render();
		}
	}
	void Update()
	{
		for (int i = 0; i < m_MapLayers.size(); i++)
		{
			m_MapLayers[i]->Update();
		}
	}
	std::vector<Layer*> GetLayers() { return m_MapLayers; }
private:
	friend class MapParser;
	std::vector<Layer*> m_MapLayers;
};
