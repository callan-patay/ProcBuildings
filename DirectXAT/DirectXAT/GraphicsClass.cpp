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

	int posX = 0;
	int posY = 0;

	int row = 1;
	int col = 1;


	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			ModelClass* m_Model = new ModelClass();
			// Initialize the model objct.
			m_Model->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), "../DirectXAT/House.tga", "../DirectXAT/cube.txt");
			m_Model->setPosition(posX, posY, 0.0f);
			m_Models.push_back(m_Model);
			posY += 5;
		}
		posY = 0;
		posX += 5;
	}

	

	// Create the model object.




	TwInit(TW_DIRECT3D11, m_D3D->GetDevice());
	TwWindowSize(screenWidth, screenHeight);


	TwBar *myBar;
	myBar = TwNewBar("Model");
	int barSize[2] = { 250, 550 };
	TwSetParam(myBar, NULL, "size", TW_PARAM_INT32, 2, barSize);


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

	TwAddVarRW(myBar, "Roll", TW_TYPE_FLOAT, &m_Models[0]->m_roll, "Group='Rotation' min=0 max=360 step=0.1");
	TwAddVarRW(myBar, "Pitch", TW_TYPE_FLOAT, &m_Models[0]->m_pitch, "Group='Rotation' min=0 max=360 step=0.1");
	TwAddVarRW(myBar, "Yaw", TW_TYPE_FLOAT, &m_Models[0]->m_yaw, "Group='Rotation' min=0 max=360 step=0.1");

	TwAddVarRW(myBar, "X", TW_TYPE_FLOAT, &m_Models[0]->m_pos.x, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Y", TW_TYPE_FLOAT, &m_Models[0]->m_pos.y, "Group='Position' min=-100 max=100 step=0.1");
	TwAddVarRW(myBar, "Z", TW_TYPE_FLOAT, &m_Models[0]->m_pos.z, "Group='Position' min=-100 max=100 step=0.1");

	TwAddVarRW(myBar, "Direction", TW_TYPE_DIR3F, &m_Light->m_direction, "Group='Light' opened=true axisz=-z showval=false");
	TwAddVarRW(myBar, "Light R", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.x, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Light G", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.y, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Light B", TW_TYPE_FLOAT, &m_Light->m_diffuseColor.z, "Group='Light' min=0 max=1.0 step=0.05");

	TwAddVarRW(myBar, "Ambient R", TW_TYPE_FLOAT, &m_Light->m_ambientColor.x, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Ambient G", TW_TYPE_FLOAT, &m_Light->m_ambientColor.y, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddVarRW(myBar, "Ambient B", TW_TYPE_FLOAT, &m_Light->m_ambientColor.z, "Group='Light' min=0 max=1.0 step=0.05");
	TwAddButton(myBar, "Create Model", MakeModel, this, "Group='Create' label='Creates Model'");
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
	for (int i = 0; i < m_Models.size(); i++)
	{
		delete m_Models[i];
		m_Models[i] = 0;
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




	// Update the rotation variable each frame.
	for (int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Tick(dt);
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
	ObjExporter::Create(m_Models[0]->GetModel(), m_Models[0]->GetIndices());
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



	for (int i = 0; i < m_Models.size(); i++)
	{

		worldMatrix = m_Models[i]->getWorldMat();

		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Models[i]->Render(m_D3D->GetDeviceContext());


		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[i]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Models[i]->GetTexture(), m_Light->GetDirection(),m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	}


	if (!result)
	{
		return false;
	}


	TwDraw();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	return true;
}