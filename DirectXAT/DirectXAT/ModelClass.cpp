////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"
#include <AntTweakBar.h>
#include <sstream>
#include <string>;

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_Texture1 = 0;
	m_Texture2 = 0;
	m_Texture3 = 0;
	m_worldMat = XMMatrixIdentity();
	m_identity = XMMatrixIdentity();
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, char* modelFilename)
{
	bool result;


	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}
	TextureType = Texture::HOUSE;
	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device,deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}


	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;



	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
	m_scale.z = 1.0f;

	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;
	return true;
}

void ModelClass::Shutdown()
{	
	// Release the model texture.
	ReleaseTexture();
	// Release the vertex and index buffers.
	ShutdownBuffers();
	// Release the model data.
	ReleaseModel();

	delete indices;
	indices = 0;

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

void ModelClass::SetTexture(TextureClass * _texture)
{
	m_Texture = _texture;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	if (TextureType == Texture::HOUSE)
	{
		return m_Texture->GetTexture();
	}
	if (TextureType == Texture::BRICK)
	{
		return m_Texture1->GetTexture();
	}
	if (TextureType == Texture::WOOD)
	{
		return m_Texture2->GetTexture();
	}
	if (TextureType == Texture::SKYSCRAPER)
	{
		return m_Texture3->GetTexture();
	}
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	// Load the vertex array and index array with data.
	indicesVector.reserve(m_indexCount);
	for (int i = 0; i<m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		indices[i] = i;
		indicesVector.push_back(indices[i]);
	}




					 // Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

vector<ModelType> ModelClass::GetModel()
{
	return m_model;
}

vector<long> ModelClass::GetIndices()
{
	return indicesVector;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}



	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.


	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}


	m_Texture1 = new TextureClass;
	if (!m_Texture1)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture1->Initialize(device, deviceContext, "../DirectXAT/Exports/brick.tga");
	if (!result)
	{
		return false;
	}

	m_Texture2= new TextureClass;
	if (!m_Texture2)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture2->Initialize(device, deviceContext, "../DirectXAT/Exports/Wood.tga");
	if (!result)
	{
		return false;
	}


	m_Texture3 = new TextureClass;
	if (!m_Texture3)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture3->Initialize(device, deviceContext, "../DirectXAT/Exports/Skyscraper.tga");
	if (!result)
	{
		return false;
	}



	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	if (m_Texture1)
	{
		m_Texture1->Shutdown();
		delete m_Texture1;
		m_Texture1 = 0;
	}
	if (m_Texture2)
	{
		m_Texture2->Shutdown();
		delete m_Texture2;
		m_Texture2 = 0;
	}
	if (m_Texture3)
	{
		m_Texture3->Shutdown();
		delete m_Texture3;
		m_Texture3 = 0;
	}
	return;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model.reserve(m_vertexCount);


	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i<m_vertexCount; i++)
	{
		ModelType m_modelData;


		fin >> m_modelData.x >> m_modelData.y >> m_modelData.z;
		fin >> m_modelData.tu >> m_modelData.tv;
		fin >> m_modelData.nx >> m_modelData.ny >> m_modelData.nz;

		m_model.push_back(m_modelData);

	}

	// Close the model file.
	fin.close();








	//createModel();
	return true;
}

void ModelClass::ReleaseModel()
{
	delete m_vertexBuffer;
	delete m_indexBuffer;

	return;
}

XMMATRIX ModelClass::getWorldMat()
{
	return m_worldMat;
}

XMMATRIX ModelClass::getTransMat()
{
	return transMat;
}

void ModelClass::setPosition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void ModelClass::Tick()
{
	XMMATRIX scaleMat = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(m_roll, m_pitch, m_yaw);
	transMat = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	m_worldMat = m_identity *scaleMat* rotMat*  transMat;
}

float ModelClass::getRoll()
{
	return m_roll;
}

float ModelClass::getYaw()
{
	return m_yaw;
}

float ModelClass::getPitch()
{
	return m_pitch;
}

Texture ModelClass::getTextureType()
{
	return TextureType;
}

XMFLOAT3 ModelClass::getScale()
{
	return m_scale;
}

void ModelClass::setScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}



//ModelType* ModelClass::GetModel()
//{
//	return m_model;
//}
