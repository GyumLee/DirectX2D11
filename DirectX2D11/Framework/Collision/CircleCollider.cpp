#include "Framework.h"

CircleCollider::CircleCollider(float radius) : radius(radius)
{
	type = Type::CIRCLE;
	SetVertices();
}

bool CircleCollider::IsPointCollision(Vector2 point)
{
	float distance = (GlobalPos() - point).Length();

	return distance < Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
	return rect->IsCircleCollision(this);
}

bool CircleCollider::IsCircleCollision(CircleCollider* circle)
{
	float distance = (GlobalPos() - circle->GlobalPos()).Length();

	return distance < Radius() + circle->Radius();
}

void CircleCollider::SetVertices()
{
	float theta = XM_PI * 2.0f / VERTEX_COUNT;

	for (UINT i = 0; i <= VERTEX_COUNT; i++)
	{
		float x = cos(theta * i) * radius;
		float y = -sin(theta * i) * radius;

		vertices.emplace_back(x, y);
	}

	vertexBuffer = new VertexBuffer(
		vertices.data(), sizeof(VertexPos), vertices.size());
}
