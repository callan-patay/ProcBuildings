#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include<DirectXMath.h>
#include "TextureClass.h"
#include "LightShaderClass.h"
#include <fstream>
using namespace std;

using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};



public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();	
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void SetTexture(TextureClass*);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	bool InitializeBuffers(ID3D11Device*);
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	bool LoadModel(char*);
	void ReleaseModel();
	XMMATRIX getWorldMat();
	void setPosition(float, float, float);
	void Tick();
private:
	void ShutdownBuffers();
	void ReleaseTexture();
	void RenderBuffers(ID3D11DeviceContext*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	XMMATRIX m_worldMat, m_fudge;
	XMFLOAT3 m_pos, m_scale;
	
	float m_roll, m_pitch, m_yaw;



};

#endif