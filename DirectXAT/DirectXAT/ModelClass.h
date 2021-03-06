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
#include "ObjExporter.h"
#include <vector>
#include <fstream>
using namespace std;

using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	enum Texture
	{
		HOUSE,
		BRICK,
		WOOD,
		SKYSCRAPER
	};

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
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
	XMMATRIX getTransMat();
	void setPosition(float, float, float);
	void Tick();
	float getRoll();
	float getYaw();
	float getPitch();
	Texture getTextureType();
	XMFLOAT3 getScale();
	void setScale(float, float, float);

	float m_roll;
	float m_pitch, m_yaw;
	XMFLOAT3 m_pos, m_scale;
	vector<ModelType> GetModel();
	vector<long> GetIndices();
	Texture TextureType;
	void RenderBuffers(ID3D11DeviceContext*);
private:
	void ShutdownBuffers();
	void ReleaseTexture();
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	unsigned long* indices;
	vector<long> indicesVector;
	TextureClass* m_Texture, *m_Texture1, *m_Texture2, *m_Texture3;
	vector<ModelType> m_model;
	XMMATRIX m_worldMat, m_identity;
	XMMATRIX transMat;
	



};

#endif