#include "Skyscraper.h"

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
	m_device = 0;
	m_deviceContext = 0;

	TwTerminate();
}

void Skyscraper::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, int modelNum)
{
	m_Skyscraper.reserve(height);

	for (int i = 0; i < height; i++)
	{
		ModelClass* buildingblock = new ModelClass();
		buildingblock->Initialize(device, deviceContext, "../DirectXAT/Exports/House.tga", "../DirectXAT/cube.txt");
		buildingblock->TextureType = Texture::SKYSCRAPER;
		buildingblock->setPosition(0.0f, i * 2.0f, 0.0f);
		buildingblock->setScale(width, 1.0f, depth);
		m_Skyscraper.push_back(buildingblock);
	}
	m_device = device;
	m_deviceContext = deviceContext;

	TwInit(TW_DIRECT3D11, device);
	TwWindowSize(800, 600);


	std::stringstream strs;
	strs << "Skyscraper " << modelNum;

	std::string barname = strs.str();

	TwBar *myBar;
	myBar = TwNewBar(barname.c_str());
	int barSize[2] = { 150, 100 };
	TwSetParam(myBar, NULL, "size", TW_PARAM_INT32, 2, barSize);


	TwAddVarRW(myBar, "X", TW_TYPE_FLOAT, &m_pos.x, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Y", TW_TYPE_FLOAT, &m_pos.y, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Z", TW_TYPE_FLOAT, &m_pos.z, "Group='Position' min=-100 max=100 step=0.1");

	TwAddVarRW(myBar, "height", TW_TYPE_INT32, &height, "Group='Size' min=0 max=100 step=1");
	TwAddVarRW(myBar, "width", TW_TYPE_FLOAT, &width, "Group='Size' min=0 max=100 step=0.1");
	TwAddVarRW(myBar, "depth", TW_TYPE_FLOAT, &depth, "Group='Size' min=0 max=100 step=0.1");
	TwAddButton(myBar, "Apply Values", ApplyValues, this, "Group='Reset' label='Resets Values'");


}

void Skyscraper::Render(ID3D11DeviceContext *)
{
	TwDraw();
}

void Skyscraper::applyValues()
{
	for (int i = 0; i < m_Skyscraper.size(); i++)
	{
		delete m_Skyscraper[i];
		m_Skyscraper[i] = 0;
	}

	m_Skyscraper.clear();


	for (int i = 0; i < height; i++)
	{
		ModelClass* buildingblock = new ModelClass();
		buildingblock->Initialize(m_device, m_deviceContext, "../DirectXAT/Exports/House.tga", "../DirectXAT/cube.txt");
		buildingblock->TextureType = Texture::SKYSCRAPER;
		buildingblock->setPosition(m_pos.x, m_pos.y + (i * 2.0), m_pos.z);
		buildingblock->setScale(width, 1.0f, depth);
		m_Skyscraper.push_back(buildingblock);
	}
}

void Skyscraper::Tick()
{
	for (int i = 0; i < m_Skyscraper.size(); i++)
	{
		m_Skyscraper[i]->setPosition(m_pos.x,m_pos.y + (i* 2.0f), m_pos.z);
		m_Skyscraper[i]->setScale(m_Skyscraper[i]->getScale().x, 1.0f, m_Skyscraper[i]->getScale().z);
		m_Skyscraper[i]->Tick();
	}
}

vector<ModelClass*> Skyscraper::getSkyscraperParts()
{
	return m_Skyscraper;
}
