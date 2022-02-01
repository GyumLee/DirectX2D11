#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
	: size(size)
{
	type = Type::RECT;

	SetVertices();
}

bool RectCollider::IsPointCollision(Vector2 point)
{
	Matrix invWorld = XMMatrixInverse(nullptr, world);

	Vector2 tempPos = Vector2::TransformCoord(point, invWorld);

	Vector2 half = size * 0.5f;

	if (abs(tempPos.x) < half.x && abs(tempPos.y) < half.y)
		return true;

	return false;
}

/*
bool RectCollider::IsPointCollision(Vector2 point)
{
	float left = size.x * -0.5f;
	float right = size.x * +0.5f;
	float top = size.y * -0.5f;
	float bottom = size.y * +0.5f;

	Vector2 leftTop = Vector2::TransformCoord(Vector2(left, top), world);
	Vector2 leftBottom = Vector2::TransformCoord(Vector2(left, bottom), world);
	Vector2 rightBottom = Vector2::TransformCoord(Vector2(right, bottom), world);
	Vector2 rightTop = Vector2::TransformCoord(Vector2(right, top), world);

	if (IsBetweenPoint(leftTop, point, Up(), Right())) return false;
	if (IsBetweenPoint(leftBottom, point, Down(), Right())) return false;
	if (IsBetweenPoint(rightBottom, point, Down(), Left())) return false;
	if (IsBetweenPoint(rightTop, point, Up(), Left())) return false;

	return true;
}
*/

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
	if (overlap)
		return IsAABB(rect, overlap);

	return IsOBB(rect);
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
	ObbDesc obb = GetObb();

	Vector2 ne1 = obb.axis[0];
	Vector2 e1 = ne1 * obb.halfSize.x;
	Vector2 ne2 = obb.axis[1];
	Vector2 e2 = ne2 * obb.halfSize.y;

	Vector2 distance = obb.position - circle->GlobalPos();

	float lengthA = abs(Vector2::Dot(ne1, distance));
	float lengthB = abs(Vector2::Dot(ne2, distance));

	float radius = circle->Radius();

	if (lengthA > obb.halfSize.x + radius) return false;
	if (lengthB > obb.halfSize.y + radius) return false;

	if (lengthA < obb.halfSize.x) return true;
	if (lengthB < obb.halfSize.y) return true;

	Vector2 edgeToCircle(lengthA - obb.halfSize.x, lengthB - obb.halfSize.y);

	return edgeToCircle.Length() < radius;
}

RectCollider::ObbDesc RectCollider::GetObb()
{
	obbDesc.position = GlobalPos();

	obbDesc.halfSize = Size() * 0.5f;

	obbDesc.axis[0] = Right();
	obbDesc.axis[1] = Up();

	return obbDesc;
}

void RectCollider::SetVertices()
{
	Vector2 half = size * 0.5f;

	vertices.emplace_back(-half.x, -half.y);
	vertices.emplace_back(+half.x, -half.y);
	vertices.emplace_back(+half.x, +half.y);
	vertices.emplace_back(-half.x, +half.y);
	vertices.emplace_back(-half.x, -half.y);

	vertexBuffer = new VertexBuffer(vertices.data(),
		sizeof(VertexPos), vertices.size());
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
	float aR = max(L(), R());
	float aL = min(L(), R());
	float aB = max(B(), T());
	float aT = min(B(), T());
	float bR = max(rect->L(), rect->R());
	float bL = min(rect->L(), rect->R());
	float bB = max(rect->B(), rect->T());
	float bT = min(rect->B(), rect->T());

	float minRight = min(aR, bR);
	float maxLeft = max(aL, bL);
	float minBottom = min(aB, bB);
	float maxTop = max(aT, bT);

	Vector2 temp(minRight - maxLeft, minBottom - maxTop);

	if (overlap != nullptr)
		*overlap = temp;

	if (temp.x > 0 && temp.y > 0)
		return true;

	return false;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
	ObbDesc obbA = GetObb();
	ObbDesc obbB = rect->GetObb();

	Vector2 nea1 = obbA.axis[0];
	Vector2 ea1 = nea1 * obbA.halfSize.x;
	Vector2 nea2 = obbA.axis[1];
	Vector2 ea2 = nea2 * obbA.halfSize.y;

	Vector2 neb1 = obbB.axis[0];
	Vector2 eb1 = neb1 * obbB.halfSize.x;
	Vector2 neb2 = obbB.axis[1];
	Vector2 eb2 = neb2 * obbB.halfSize.y;

	Vector2 distance = obbA.position - obbB.position;

	//분리축 : nea1
	if (IsSeparateAxis(ea1, distance, eb1, eb2)) return false;
	//분리축 : nea2
	if (IsSeparateAxis(ea2, distance, eb1, eb2)) return false;
	//분리축 : neb1
	if (IsSeparateAxis(eb1, distance, ea1, ea2)) return false;
	//분리축 : neb2
	if (IsSeparateAxis(eb2, distance, ea1, ea2)) return false;

	return true;
}

bool RectCollider::IsSeparateAxis(Vector2 separate, Vector2 distance, Vector2 eb1, Vector2 eb2)
{
	float lengthA = separate.Length();

	Vector2 nSeparate = separate.Normalized();

	float r1 = abs(Vector2::Dot(nSeparate, eb1));
	float r2 = abs(Vector2::Dot(nSeparate, eb2));
	float lengthB = r1 + r2;
	float length = abs(Vector2::Dot(nSeparate, distance));

	return length > lengthA + lengthB;
}

bool RectCollider::IsBetweenPoint(Vector2 edge, Vector2 point, Vector2 e1, Vector2 e2)
{
	Vector2 toPoint = point - edge;

	float crossA = Vector2::Cross(e1, toPoint);
	float crossB = Vector2::Cross(e2, toPoint);

	return crossA * crossB > 0;
}
