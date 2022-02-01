#include "Framework.h"

LineCollider::LineCollider(Vector2 start, Vector2 end)
	:start(start), end(end)
{
	SetVertices();
}

LineCollider::~LineCollider()
{
}

bool LineCollider::IsPointCollision(Vector2 point)
{
	return false;
}

bool LineCollider::IsRectCollision(RectCollider* rect, Vector2* overlap = nullptr)
{
	return false;
}

bool LineCollider::IsCircleCollision(CircleCollider* circle)
{
	return false;
}

void LineCollider::SetStart(Vector2 pos)
{
	start = pos;
	vertices[0].pos = Float3(pos.x, pos.y, 0.0f);

	vertexBuffer->Update(vertices.data(), vertices.size());
}

void LineCollider::SetEnd(Vector2 pos)
{
	end = pos;
	vertices[1].pos = Float3(pos.x, pos.y, 0.0f);

	vertexBuffer->Update(vertices.data(), vertices.size());
}

bool LineCollider::IsBetween(LineCollider* line)
{
	Vector2 A = line->GetEnd() - GetStart();;
	Vector2 B = line->GetStart() - GetStart();
	Vector2 C = GetEnd() - GetStart();

	float crossA = Vector2::Cross(C, A);
	float crossB = Vector2::Cross(C, B);

	return crossA * crossB < 0;
}

bool LineCollider::IsCollision(LineCollider* line, Vector2& crossPoint)
{
	if (!IsBetween(line) || !line->IsBetween(this))
		return false;

	Vector2 A = GetEnd() - GetStart();
	Vector2 B = line->GetEnd() - line->GetStart();
	Vector2 C = line->GetStart() - GetStart();
	Vector2 D = line->GetEnd() - line->GetStart();

	float crossAB = Vector2::Cross(A, B);

	if (fabs(crossAB) < 0.0001f)
		return false;

	float crossCD = Vector2::Cross(C, D);

	crossPoint = GetStart() + A * (crossCD / crossAB);

	return true;
}

void LineCollider::SetVertices()
{
	vertices.push_back(VertexPos(start.x, start.y));
	vertices.push_back(VertexPos(end.x, end.y));

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), vertices.size());
}
