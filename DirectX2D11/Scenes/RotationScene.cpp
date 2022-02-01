#include "Framework.h"
#include "RotationScene.h"

RotationScene::RotationScene()
{
	plane = new Quad(L"Textures/location.png");
	plane->position = { CENTER_X, CENTER_Y };
	plane->scale *= 3.0f;
}

RotationScene::~RotationScene()
{
	delete plane;
}

void RotationScene::Update()
{
	Vector2 dir = mousePos - plane->position;

	Vector2 right = plane->Right();

	if (Vector2::Cross(right, dir) < 0)
		plane->rotation.z -= DELTA;
	else if (Vector2::Cross(right, dir) > 0)
		plane->rotation.z += DELTA;

	plane->position += right * 100.0f * DELTA;

	plane->UpdateWorld();
}

void RotationScene::Render()
{
	plane->Render();
}
