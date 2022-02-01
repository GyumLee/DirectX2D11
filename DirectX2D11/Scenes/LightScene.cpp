#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	bg = new Quad(L"Textures/background.png");
	bg->scale *= 3.0f;

	halfSize = bg->Size() * 3.0f * 0.5f;

	CAM->SetLeftTop(-halfSize.x, -halfSize.y);
	CAM->SetRightBottom(halfSize.x, halfSize.y);

	EffectManager::Get()->Add("exp", 10, L"Textures/Effect/explosion.png",
		Vector2(5, 3));
	EffectManager::Get()->Add("fire", 10, L"Textures/Effect/fire_8x2.png",
		Vector2(8, 2), 0.05f, true);

	renderTarget = new RenderTarget();
	targetTexture = new Quad(Vector2(WIN_WIDTH, WIN_HEIGHT));
	targetTexture->position = { CENTER_X, CENTER_Y };
	targetTexture->SetTexture(Texture::Add(L"Target", renderTarget->GetSRV()));
	targetTexture->SetPixelShader(L"Shaders/PixelLight.hlsl");

	selectBuffer = new IntBuffer();
	selectBuffer->data.values[0] = 2;
	selectBuffer->data.values[1] = 500;
	sizeBuffer = new ValueBuffer();
	sizeBuffer->data.values[0] = WIN_WIDTH;
	sizeBuffer->data.values[1] = WIN_HEIGHT;
	sizeBuffer->data.values[2] = CENTER_X;
	sizeBuffer->data.values[3] = CENTER_Y;
}

LightScene::~LightScene()
{
	delete bg;

	delete renderTarget;
	delete targetTexture;
}

void LightScene::Update()
{
	bg->UpdateWorld();

	player->Update();

	Vector2 playerScreenPos = CAM->WorldToScreen(player->GlobalPos());
	sizeBuffer->data.values[2] = playerScreenPos.x;
	sizeBuffer->data.values[3] = playerScreenPos.y;

	for (knightMonster* monster : monsters)
		monster->Update();

	targetTexture->UpdateWorld();
}

void LightScene::PreRender()
{
	renderTarget->Set();

	bg->Render();

	player->Render();

	for (knightMonster* monster : monsters)
		monster->Render();
}

void LightScene::Render()
{
	
}

void LightScene::PostRender()
{
	selectBuffer->SetPS(1);
	sizeBuffer->SetPS(2);
	targetTexture->Render();

	player->PostRender();

	for (knightMonster* monster : monsters)
		monster->PostRender();
}

void LightScene::Start()
{
	player = new KnightPlayer();
	CAM->SetTarget(player);

	monsters.resize(10);
	for (knightMonster*& monster : monsters)
	{
		monster = new knightMonster();
		monster->position.x = Random(-halfSize.x, halfSize.x);
		monster->position.y = Random(-halfSize.y, halfSize.y);
		monster->SetTarget(player);
	}
}

void LightScene::End()
{
	delete player;

	for (knightMonster* monster : monsters)
		delete monster;
}
