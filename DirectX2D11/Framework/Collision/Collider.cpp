#include "Framework.h"

Collider::Collider()
{
	vertexShader = Shader::AddVS(L"Shaders/VertexPos.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/PixelPos.hlsl");

	colorBuffer = new ColorBuffer();
	colorBuffer->Set(0, 1, 0);

	worldBuffer = new MatrixBuffer();
}

Collider::~Collider()
{
	delete colorBuffer;
	delete worldBuffer;
}

void Collider::Render()
{
	if (!isActive) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	colorBuffer->SetPS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->Set();
	pixelShader->Set();

	DC->Draw(vertices.size(), 0);
}

bool Collider::IsCollision(Collider* collider)
{
	if (!isActive) return false;

	collider->UpdateWorld();
	UpdateWorld();

	switch (collider->type)
	{
	case Type::RECT:
		return IsRectCollision((RectCollider*)collider);
	case Type::CIRCLE:
		return IsCircleCollision((CircleCollider*)collider);
	}

	return false;
}
