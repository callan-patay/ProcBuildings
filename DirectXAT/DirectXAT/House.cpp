#include "House.h"
#include <AntTweakBar.h>
#include <string>
#include <sstream>

House::House()
{
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_scale = { 1.0f, 1.0f, 1.0f };
}

House::~House()
{
	for (int i = 0; i < m_House.size(); i++)
	{
		delete m_House[i];
		m_House[i] = 0;
	}
	TwTerminate();
}

void House::Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, int modelNum)
{

	m_House.reserve(2);

	ModelClass* Base = new ModelClass();

	Base->Initialize(device, deviceContext, "../DirectXAT/Exports/House.tga", "../DirectXAT/cube.txt");

	m_House.push_back(Base);

	ModelClass* Roof = new ModelClass();

	Roof->Initialize(device, deviceContext, "../DirectXAT/Exports/House.tga", "../DirectXAT/Roof.txt");
	Roof->TextureType = Texture::WOOD;

	m_House.push_back(Roof);

	TwInit(TW_DIRECT3D11, device);
	TwWindowSize(800, 600);


	std::stringstream strs;
	strs << "House " << modelNum;

	std::string barname = strs.str();

	TwBar *myBar;
	myBar = TwNewBar(barname.c_str());
	int barSize[2] = { 150, 100 };
	TwSetParam(myBar, NULL, "size", TW_PARAM_INT32, 2, barSize);


	TwEnumVal TextureTypeEV[] = { {BRICK, "Brick"}, {HOUSE, "House"}, {WOOD, "Wood"}, {SKYSCRAPER, "Skyscraper"} };
	TwType TextureTypeTw = TwDefineEnum("TextureType", TextureTypeEV, 4);



	TwAddVarRW(myBar, "House Texture", TextureTypeTw, &m_House[0]->TextureType, NULL);
	TwAddVarRW(myBar, "Roof Texture", TextureTypeTw, &m_House[1]->TextureType, NULL);

	TwAddVarRW(myBar, "X", TW_TYPE_FLOAT, &m_pos.x, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Y", TW_TYPE_FLOAT, &m_pos.y, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Z", TW_TYPE_FLOAT, &m_pos.z, "Group='Position' min=-100 max=100 step=0.1");

	TwAddVarRW(myBar, "scale X", TW_TYPE_FLOAT, &m_scale.x, "Group='Scale' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "scale Y", TW_TYPE_FLOAT, &m_scale.y, "Group='Scale' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "scale Z", TW_TYPE_FLOAT, &m_scale.z, "Group='Scale' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Roof Scale Y", TW_TYPE_FLOAT, &m_House[1]->m_scale.y, "Group='Scale' min =-100 max=100 step=0.1");







}

void House::Render(ID3D11DeviceContext * deviceContext)
{

	//for (int i = 0; i < m_House.size(); i++)
	//{
	//	m_House[i].RenderBuffers(deviceContext);
	//}



	TwDraw();
}

void House::Tick()
{

	m_House[0]->setPosition(m_pos.x, m_pos.y, m_pos.z);
	m_House[1]->setPosition(m_pos.x, m_pos.y + m_House[1]->getScale().y + m_House[0]->getScale().y, m_pos.z);

	m_House[0]->setScale(m_scale.x, m_scale.y, m_scale.z);
	m_House[1]->setScale(m_scale.x, m_House[1]->getScale().y, m_scale.z);


	for (int i = 0; i < m_House.size(); i++)
	{
		m_House[i]->Tick();
	}




}

vector<ModelClass*> House::getHouseParts()
{
	return m_House;
}
