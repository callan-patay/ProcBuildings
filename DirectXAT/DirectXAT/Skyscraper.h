#pragma once
#include <vector>
#include "ModelClass.h"
#include <DirectXMath.h>
#include <AntTweakBar.h>
using namespace std;
using namespace DirectX;



class Skyscraper
{
public:
	Skyscraper();
	~Skyscraper();

	void Initialize(ID3D11Device*, ID3D11DeviceContext*, int);

	void Render(ID3D11DeviceContext*);
	void applyValues();

	void Tick();

	vector<ModelClass*> getSkyscraperParts();
	string getBuildingName();

private:

	ID3D11Device * m_device;
	ID3D11DeviceContext * m_deviceContext;
	vector<ModelClass*> m_Skyscraper;
	XMFLOAT3 m_pos;
	string barname = " ";
	int height;
	float width;
	float depth;
};


static void TW_CALL ApplyValues(void *clientData)
{
	auto skyscraper = static_cast<Skyscraper*>(clientData);
	skyscraper->applyValues();
}