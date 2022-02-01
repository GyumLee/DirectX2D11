#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	/*quads.resize(COUNT);
	for (Quad*& quad : quads)
	{
		quad = new Quad(L"Textures/background.png");
		quad->position.x = Random(0, WIN_WIDTH);
		quad->position.y = Random(0, WIN_HEIGHT);

		quad->scale *= Random(0.1f, 0.5f);

		quad->UpdateWorld();
	}*/

	quad = new Quad(L"Textures/mario.png");
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	instances.resize(COUNT);

	for (InstanceData& instance : instances)
	{
		Transform transform;
		transform.position.x = Random(0, WIN_WIDTH);
		transform.position.y = Random(0, WIN_HEIGHT);

		transform.scale *= Random(0.3f, 1.0f);

		transform.UpdateWorld();

		instance.transform = XMMatrixTranspose(transform.GetWorld());

		instance.maxFrame = { 8, 4 };
		instance.curFrame.x = Random(0, 8);
		instance.curFrame.y = Random(0, 4);
	}

	instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), COUNT);
}

InstancingScene::~InstancingScene()
{
	/*for (Quad* quad : quads)
		delete quad;*/

	delete quad;
	delete instanceBuffer;
}

void InstancingScene::Update()
{

}

void InstancingScene::Render()
{
	/*for (Quad* qaud : quads)
		qaud->Render();*/

	instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, COUNT, 0, 0, 0);
}
