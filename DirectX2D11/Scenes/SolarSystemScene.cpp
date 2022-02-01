#include "Framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	sun = new TestRect(Float2(0, 0), Float2(200, 200));
	sun->SetColor(1, 0, 0);

	earth = new TestRect(Float2(0, 0), Float2(150, 150));
	earth->SetParent(&sun->GetWorld());
	earth->position.x = 400.0f;
	earth->SetColor(0, 0, 1);

	moon = new TestRect(Float2(0, 0), Float2(50, 50));
	moon->SetParent(&earth->GetWorld());
	moon->position.x = 200.0f;
	moon->SetColor(1, 1, 0);
}

SolarSystemScene::~SolarSystemScene()
{
	delete sun;
	delete earth;
	delete moon;
}

void SolarSystemScene::Update()
{
	if (GetAsyncKeyState('D'))
		sun->position.x += 0.1f;
	if (GetAsyncKeyState('A'))
		sun->position.x -= 0.1f;
	if (GetAsyncKeyState('W'))
		sun->position.y -= 0.1f;
	if (GetAsyncKeyState('S'))
		sun->position.y += 0.1f;

	sun->rotation.z += 0.0001f;
	earth->rotation.z += 0.0002f;
	moon->rotation.z -= 0.001f;

	sun->UpdateWorld();
	earth->UpdateWorld();
	moon->UpdateWorld();
}

void SolarSystemScene::Render()
{
	sun->Render();
	earth->Render();
	moon->Render();
}
