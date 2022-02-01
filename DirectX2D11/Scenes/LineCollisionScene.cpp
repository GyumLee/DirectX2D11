#include "Framework.h"
#include "LineCollisionScene.h"

LineCollisionScene::LineCollisionScene()
{
	line1 = new LineCollider(Vector2(100, 100), Vector2(600, 600));
	line2 = new LineCollider(Vector2(100, 500), Vector2());

	circle = new CircleCollider(10);
}

LineCollisionScene::~LineCollisionScene()
{
	delete line1;
	delete line2;

	delete circle;
}

void LineCollisionScene::Update()
{
	line2->SetEnd(mousePos);

	Vector2 point;
	if (line1->IsCollision(line2, point))
	{
		line1->SetColor(1, 0, 0);

		circle->position = point;
	}
	else
	{
		line1->SetColor(0, 1, 0);
	}

	line1->UpdateWorld();
	line2->UpdateWorld();

	circle->UpdateWorld();
}

void LineCollisionScene::Render()
{
	line1->Render();
	line2->Render();

	circle->Render();
}
