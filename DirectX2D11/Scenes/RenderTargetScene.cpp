#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
	bg = new Quad(L"Textures/background.png");
	bg->position = { CENTER_X,CENTER_Y };

	plane = new Quad(L"Textures/airplane.png");
	plane->position = { CENTER_X,CENTER_Y };

	player = new KnightPlayer();
	player->position = { CENTER_X,CENTER_Y };

	CAM->SetTarget(player);
	CAM->SetLeftTop(-1000, -1000);
	CAM->SetRightBottom(2000, 2000);

	renderTarget = new RenderTarget();

	targetTexture[0] = new Quad(Vector2(CENTER_X, CENTER_Y));
	targetTexture[0]->position = { CENTER_X * 0.5f, CENTER_Y * 0.5f };
	targetTexture[0]->SetTexture(Texture::Add(L"Target", renderTarget->GetSRV()));
	targetTexture[0]->SetPixelShader(L"Shaders/PixelGrayscale.hlsl");

	targetTexture[1] = new Quad(Vector2(CENTER_X, CENTER_Y));
	targetTexture[1]->position = { CENTER_X * 1.5f, CENTER_Y * 0.5f };
	targetTexture[1]->SetTexture(Texture::Add(L"Target", renderTarget->GetSRV()));
	targetTexture[1]->SetPixelShader(L"Shaders/PixelFilter.hlsl");

	selectBuffer = new IntBuffer();
}

RenderTargetScene::~RenderTargetScene()
{
	delete bg;
	delete plane;
	delete player;

	delete renderTarget;
	delete targetTexture[0];
	delete targetTexture[1];
}

void RenderTargetScene::Update()
{
	bg->UpdateWorld();
	plane->UpdateWorld();
	player->Update();

	targetTexture[0]->UpdateWorld();
	targetTexture[1]->UpdateWorld();
}

void RenderTargetScene::PreRender()
{
	renderTarget->Set();

	bg->Render();
	plane->Render();
	player->Render();
}

void RenderTargetScene::Render()
{
	
}

void RenderTargetScene::PostRender()
{
	selectBuffer->SetPS(1);
	targetTexture[0]->Render();
	targetTexture[1]->Render();

	ImGui::InputInt("Select", &selectBuffer->data.values[0]);
	ImGui::InputInt("Scale", &selectBuffer->data.values[1]);
}
