#pragma once
#include <vector>
#include "ModelClass.h"
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;



class Skyscraper
{
public:
	Skyscraper();
	~Skyscraper();

	void Initialize(ID3D11Device*, ID3D11DeviceContext*, int);

	void Render(ID3D11DeviceContext*);


	void Tick();

	vector<ModelClass*> getSkyscraperParts();


private:


	vector<ModelClass*> m_Skyscraper;
	XMFLOAT3 m_pos;
	XMFLOAT3 m_scale;
	int height;
	float width;
	float depth;
};