////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "TextureClass.h"




GraphicsClass::GraphicsClass()
{

	m_D3D = 0;
	m_Camera = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

//static void TW_CALL GraphicsClass::Callback(void *clientData)
//{
//	ObjExporter::Create(m_Models[0]->GetModel(), m_Models[0]->GetIndices());
//
//	
//}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);


	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	//ModelClass* m_Model = new ModelClass();
	//// Initialize the model objct.
	//m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "../DirectXAT/Exports/House.tga", "../DirectXAT/cube.txt");
	//		
	//m_Models.push_back(m_Model);



	TwInit(TW_DIRECT3D11, m_D3D->GetDevice());
	TwWindowSize(screenWidth, screenHeight);

	TwBar *myBar;
	myBar = TwNewBar("Menu");
	int barSize[2] = { 250, 250 };
	TwSetParam(myBar, NULL, "size", TW_PARAM_INT32, 2, barSize);

	House* m_House = new House();
	m_House->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), 1);
	m_Houses.push_back(m_House);

	// Create the model object.



	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);


	TwAddVarRW(myBar, "Direction", TW_TYPE_DIR3F, &m_Light->m_direction, "Group='Light' opened=true axisz=-z showval=false");
	TwAddVarRW(myBar, "Light R", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.x, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Light G", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.y, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Light B", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.z, "Group='Light' min=0 max=1.0 step=0.05");

	TwAddButton(myBar, "Add House", AddHouse, this, "Group='Create' label='Adds a House'");
	TwAddButton(myBar, "Add Skyscraper", AddSkyscraper, this, "Group='Create' label='Adds a Roof'");
	TwAddButton(myBar, "Export", MakeModel, this, "Group='Create' label='Creates Model'");
	//TwAddVarRW(myBar, "CreateModel", TW_TYPE_BOOLCPP, &makeModel, "key=space");

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}



void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	TwTerminate();
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	// Release the model object.

	for (int i = 0; i < m_Houses.size(); i++)
	{
		delete m_Houses[i];
		m_Houses[i] = 0;
	}



	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}

void GraphicsClass::moveCamera(float x, float y, float z)
{
	m_Camera->move(x, y, z);
}

bool GraphicsClass::Frame(float& dt)
{
	bool result;
	// Render the graphics scene.


	//if (makeModel)
	//{
	//	//m_Models[0]->createModel(m_Models[0]->GetModel(), m_Models[0]->GetIndices());
	//	ObjExporter::Create(m_Models[0]->GetModel(), m_Models[0]->GetIndices());
	//	makeModel = false;
	//}


	for (int i = 0; i < m_Houses.size(); i++)
	{
		m_Houses[i]->Tick();
	}
	
	for (int i = 0; i < m_Skyscrapers.size(); i++)
	{
		m_Skyscrapers[i]->Tick();
	}


	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}

void GraphicsClass::makeBuilding()
{
	ObjExporter::Create(m_Houses, m_Skyscrapers);
}

void GraphicsClass::addHouse()
{
	House* m_Model = new House();
	// Initialize the model objct.
	m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), m_Houses.size()+1);
	//m_Model->setPosition(posX, posY, 0.0f);
	m_Houses.push_back(m_Model);
}

void GraphicsClass::addSkyscraper()
{
	Skyscraper* m_Model = new Skyscraper();
	// Initialize the model objct.
	m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), m_Houses.size() + 1);
	//m_Model->setPosition(posX, posY, 0.0f);
	m_Skyscrapers.push_back(m_Model);
}




bool GraphicsClass::Render()
{
	XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.25f, 0.5f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);




	for (int i = 0; i < m_Houses.size(); i++)
	{



		for (int p = 0; p < m_Houses[i]->getHouseParts().size(); p++)
		{

			worldMatrix = m_Houses[i]->getHouseParts()[p]->getWorldMat();

			m_Houses[i]->getHouseParts()[p]->Render(m_D3D->GetDeviceContext());


			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Houses[i]->getHouseParts()[p]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Houses[i]->getHouseParts()[p]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		}
		m_Houses[i]->Render(m_D3D->GetDeviceContext());
	}

	for (int i = 0; i < m_Skyscrapers.size(); i++)
	{



		for (int p = 0; p < m_Skyscrapers[i]->getSkyscraperParts().size(); p++)
		{

			worldMatrix = m_Skyscrapers[i]->getSkyscraperParts()[p]->getWorldMat();

			m_Skyscrapers[i]->getSkyscraperParts()[p]->Render(m_D3D->GetDeviceContext());


			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Skyscrapers[i]->getSkyscraperParts()[p]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Skyscrapers[i]->getSkyscraperParts()[p]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		}
		m_Skyscrapers[i]->Render(m_D3D->GetDeviceContext());
	}





	//if (!result)
	//{
	//	return false;
	//}


	TwDraw();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	return true;
}