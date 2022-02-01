#include "Framework.h"
#include "SRTScene.h"

SRTScene::SRTScene()
	: position(0, 0), scale(1, 1), angle(0), angle2(0)
{
	rect = new TestRect(Float2(50, 50), Float2(100, 100));

	worldBuffer = new MatrixBuffer();

	// 단위 행렬 작업
	//world._11 = 1;
	//world._22 = 1;
	//world._33 = 1;
	//world._44 = 1;

	//world._41 = 100;
	//world._42 = 200;

	world = XMMatrixIdentity(); // 단위 행렬 작업
	world2 = XMMatrixIdentity(); // 단위 행렬 작업
}

SRTScene::~SRTScene()
{
	delete rect;
	delete worldBuffer;
}

void SRTScene::Update()
{
	/*if (GetAsyncKeyState('D'))
		world._41 += 0.1f;
	if (GetAsyncKeyState('A'))
		world._41 -= 0.1f;
	if (GetAsyncKeyState('W'))
		world._42 -= 0.1f;
	if (GetAsyncKeyState('S'))
		world._42 += 0.1f;*/

	if (GetAsyncKeyState('D'))
		position.x += 0.1f;
	if (GetAsyncKeyState('A'))
		position.x -= 0.1f;
	if (GetAsyncKeyState('W'))
		position.y -= 0.1f;
	if (GetAsyncKeyState('S'))
		position.y += 0.1f;

	Matrix T = XMMatrixTranslation(position.x, position.y, 0.0f);

	/*if (GetAsyncKeyState('H'))
		world._11 += 0.001f;
	if (GetAsyncKeyState('F'))
		world._11 -= 0.001f;
	if (GetAsyncKeyState('T'))
		world._22 -= 0.001f;
	if (GetAsyncKeyState('G'))
		world._22 += 0.001f;*/

	if (GetAsyncKeyState('H'))
		scale.x += 0.001f;
	if (GetAsyncKeyState('F'))
		scale.x -= 0.001f;
	if (GetAsyncKeyState('T'))
		scale.y -= 0.001f;
	if (GetAsyncKeyState('G'))
		scale.y += 0.001f;

	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);

	if (GetAsyncKeyState('I'))
		angle += 0.001f;
	if (GetAsyncKeyState('K'))
		angle -= 0.001f;

	/*world._11 = cos(angle);
	world._12 = sin(angle);
	world._21 = -sin(angle);
	world._22 = cos(angle);*/
	Matrix R = XMMatrixRotationZ(angle);

	world = S * R * T;
	/*Matrix temp = XMLoadFloat4x4(&world);
	worldBuffer->Set(temp);*/
	angle2 += 0.001f;
	world2 = XMMatrixRotationZ(angle2) * XMMatrixTranslation(50, 0, 0) * world;
}

void SRTScene::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	rect->Render();

	worldBuffer->Set(world2);
	worldBuffer->SetVS(0);
	rect->Render();
}
