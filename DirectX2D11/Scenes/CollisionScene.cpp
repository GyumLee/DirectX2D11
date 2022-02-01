#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	colliders.resize(1);

	//collider = new RectCollider(Vector2(100, 200));
	//colliders[0] = new CircleCollider(100);
	colliders[0] = new RectCollider(Vector2(100, 200));
	colliders[0]->position = { CENTER_X, CENTER_Y };

	//colliders[1] = new CircleCollider(100);
	//colliders[1] = new RectCollider(Vector2(200, 100));
	//colliders[1]->position = { CENTER_X, CENTER_Y };
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;
}

void CollisionScene::Update()
{
	//colliders[1]->position = mousePos;

	//if (colliders[0]->IsCollision(colliders[1]))
	//{
	//	colliders[0]->SetColor(1, 0, 0);
	//	colliders[1]->SetColor(1, 0, 0);
	//	/*if (KEY_DOWN(VK_LBUTTON))
	//	{
	//		if (MessageBox(hWnd, L"충돌!", L"GameOver", MB_OK))
	//			DestroyWindow(hWnd);
	//	}*/
	//}
	//else
	//{
	//	colliders[0]->SetColor(0, 1, 0);
	//	colliders[1]->SetColor(0, 1, 0);
	//}

	if (colliders[0]->IsPointCollision(mousePos))
	{
		colliders[0]->SetColor(1, 0, 0);
	}
	else
	{
		colliders[0]->SetColor(0, 1, 0);
	}

	Vector2 overlap;

	//if (colliders[0]->IsRectCollision((RectCollider*)colliders[1], &overlap))
	//{
	//	if (overlap.x > overlap.y) //상하충돌
	//	{
	//		if (colliders[0]->position.y < colliders[1]->position.y)//0번이 위에 있음
	//		{
	//			colliders[0]->position.y -= overlap.y;
	//		}
	//		else
	//		{
	//			colliders[0]->position.y += overlap.y;
	//		}
	//	}
	//	else //좌우충돌
	//	{
	//		if (colliders[0]->position.x < colliders[1]->position.x)//0번이 좌에 있음
	//		{
	//			colliders[0]->position.x -= overlap.x;
	//		}
	//		else
	//		{
	//			colliders[0]->position.x += overlap.x;
	//		}
	//	}
	//}

	for (Collider* collider : colliders)
		collider->UpdateWorld();
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();

	ImGui::SliderFloat2("Pos", (float*)&colliders[0]->position, 0, WIN_WIDTH);
	ImGui::SliderFloat3("Rot", (float*)&colliders[0]->rotation, 0, XM_2PI);
	ImGui::InputFloat2("Scale", (float*)&colliders[0]->scale);
}
