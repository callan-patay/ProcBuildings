////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////
#include<Windows.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "TextureShaderClass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "ObjExporter.h"
#include <AntTweakBar.h>
#include <vector>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	void moveCamera(float x, float y, float z);
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float&);
	//static void TW_CALL Callback(void *clientData);
	void makeBuilding();
	void addBase();
	void addRoof();
private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	std::vector<ModelClass*> m_Models;
	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ColorShaderClass* m_ColorShader;
	bool makeModel = false;
};

static void TW_CALL MakeModel(void *clientData)
{

	auto creater = static_cast<GraphicsClass*>(clientData);


	creater->makeBuilding();

}

static void TW_CALL AddBase(void *clientData)
{

	auto base = static_cast<GraphicsClass*>(clientData);
	base->addBase();
}

static void TW_CALL AddRoof(void *clientData)
{
	auto roof = static_cast<GraphicsClass*>(clientData);
	roof->addRoof();
}




#endif