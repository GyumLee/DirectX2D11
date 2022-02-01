#include "Framework.h"
#include "Program.h"

//#include "Scenes/TutorialScene.h"
//#include "Scenes/SRTScene.h"
//#include "Scenes/SolarSystemScene.h"
//#include "Scenes/TextureScene.h"
#include "Scenes/PlaneScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/BreakOutScene.h"
#include "Scenes/BackgroundScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/KnightScene.h"
#include "Scenes/SoundScene.h"
#include "Scenes/RotationScene.h"
#include "Scenes/FontScene.h"
#include "Scenes/PixelShaderScene.h"
#include "Scenes/SelectScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/MapToolScene.h"
#include "Scenes/TankScene.h"
#include "Scenes/DijkstraScene.h"
#include "Scenes/LineCollisionScene.h"
#include "Scenes/TileScene.h"
#include "Scenes/InstancingScene.h"

Program::Program()
{
	Create();

	//scene = new TutorialScene();
	//scene = new SRTScene();
	//scene = new SolarSystemScene();
	//scene = new TextureScene();
	//scene = new PlaneScene();
	//scene = new CollisionScene();
	//scene = new BreakOutScene();
	//scene = new BackgroundScene();
	//scene = new AnimationScene();
	//scene = new KnightScene();
	//scene = new SoundScene();

	//SceneManager::Get()->Add("Start", new SoundScene());
	//SceneManager::Get()->Add("Knight", new KnightScene());
	SceneManager::Get()->Add("Start", new KnightScene());
	//SceneManager::Get()->Add("Start", new RotationScene());
	//SceneManager::Get()->Add("Start", new FontScene());
	//SceneManager::Get()->Add("Start", new PixelShaderScene());
	//SceneManager::Get()->Add("Start", new SelectScene());
	//SceneManager::Get()->Add("Start", new RenderTargetScene());
	//SceneManager::Get()->Add("Start", new LightScene());
	//SceneManager::Get()->Add("Start", new InventoryScene());
	//SceneManager::Get()->Add("Start", new MapToolScene());
	//SceneManager::Get()->Add("Start", new TankScene());
	//SceneManager::Get()->Add("Start", new DijkstraScene());
	//SceneManager::Get()->Add("Start", new LineCollisionScene());
	//SceneManager::Get()->Add("Start", new AnimationScene());
	//SceneManager::Get()->Add("Start", new TileScene());
	//SceneManager::Get()->Add("Start", new InstancingScene());

	SceneManager::Get()->Change("Start");
}

Program::~Program()
{
	Release();
}

void Program::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();
	Audio::Get()->Update();
	EffectManager::Get()->Update();

	SceneManager::Get()->Update();

	CAM->Update();
}

void Program::Render()
{
	SceneManager::Get()->PreRender();

	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Font::Get()->GetDC()->BeginDraw();

	//string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	//ImGui::Text(fps.c_str());
	wstring fps = L"FPS : " + to_wstring(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, "default", Vector2(50, 20));

	Environment::Get()->SetViewport();
	Environment::Get()->SetOrthographic();

	SceneManager::Get()->Render();
	EffectManager::Get()->Render();

	viewBuffer->SetVS(1);
	SceneManager::Get()->PostRender();

	CAM->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();

	Device::Get()->Present();
}

void Program::Create()
{
	Device::Get();
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	Audio::Get();
	EffectManager::Get();
	SceneManager::Get();
	Font::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->Add("default", L"¸¼Àº °íµñ");

	viewBuffer = new MatrixBuffer();
}

void Program::Release()
{
	Device::Delete();
	Keyboard::Delete();
	Timer::Delete();
	Texture::Delete();
	Shader::Delete();
	Environment::Delete();
	Audio::Delete();
	EffectManager::Delete();
	SceneManager::Delete();
	Font::Delete();

	ImGui_ImplDX11_Shutdown;
	ImGui_ImplWin32_Shutdown;
	ImGui::DestroyContext();
}
