#pragma once

#include <vector>
#include "ModelClass.h"
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;



class House
{
public:
	House();
	~House();

	void Initialize(ID3D11Device*, ID3D11DeviceContext*, int);

	void Render(ID3D11DeviceContext*);


	void Tick();

	vector<ModelClass*> getHouseParts();

	string getBuildingName();
private:


	vector<ModelClass*> m_House;
	string barname = " ";
	XMFLOAT3 m_pos;
	XMFLOAT3 m_scale;

};