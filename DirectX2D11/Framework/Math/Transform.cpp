#include "Framework.h"

Transform::Transform()
	: scale(1, 1), parent(nullptr), isActive(true), right(1, 0), up(0, 1)
{
	world = XMMatrixIdentity();
}

void Transform::UpdateWorld()
{
	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	T = XMMatrixTranslation(position.x, position.y, 0.0f);

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
	IP = XMMatrixInverse(nullptr, P);

	world = IP * S * R * T * P;

	if (parent != nullptr)
		world *= *parent;

	XMStoreFloat4x4(&matWorld, world);
	right = Vector2(matWorld._11, matWorld._12);
	up = Vector2(matWorld._21, matWorld._22);

	//행렬 분해
	XMVECTOR outS, outR, outT;
	XMMatrixDecompose(&outS, &outR, &outT, world);

	XMStoreFloat2(&globalPosition, outT);
	XMStoreFloat2(&globalScale, outS);
}

void Transform::SetParent(Transform* parent)
{
	SetParent(&parent->GetWorld());
}
