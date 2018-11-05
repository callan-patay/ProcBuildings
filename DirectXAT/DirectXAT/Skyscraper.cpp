#include "Skyscraper.h"
#include <AntTweakBar.h>
#include <string>
#include <sstream>


Skyscraper::Skyscraper()
{
	height = 3;
	width = 1.0f;
	depth = 1.0f;

	m_pos = { 0.0f, 0.0f, 0.0f };
	
}

Skyscraper::~Skyscraper()
{
	for (int i = 0; i < m_Skyscraper.size(); i++)
	{
		delete m_Skyscraper[i];
		m_Skyscraper[i] = 0;
	}
}

void Skyscraper::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, int)
{
	m_Skyscraper.reserve(height);

	for (int i = 0; i < height; i++)
	{
		ModelClass* buildingblock = new ModelClass();
		buildingblock->Initialize(device, deviceContext, "../DirectXAT/Exports/House.tga", "../DirectXAT/cube.txt");
		buildingblock->TextureType = Texture::SKYSCRAPER;
		buildingblock->setPosition(0.0f, i + (height * 2), 0.0f);
		buildingblock->setScale(width, (float)height, depth);
		m_Skyscraper.push_back(buildingblock);
	}


}

void Skyscraper::Render(ID3D11DeviceContext *)
{
}

void Skyscraper::Tick()
{
}

vector<ModelClass*> Skyscraper::getSkyscraperParts()
{
	return m_Skyscraper;
}
