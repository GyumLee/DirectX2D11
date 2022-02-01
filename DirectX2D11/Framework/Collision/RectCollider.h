#pragma once

class RectCollider : public Collider
{
private:
	struct  ObbDesc
	{
		Vector2 position;
		Vector2 axis[2];
		Vector2 halfSize;
	}obbDesc;

	Vector2 size;

public:
	RectCollider(Vector2 size);

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap = nullptr) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;

	Vector2 Size() { return Vector2(size.x * GlobalScale().x, size.y * GlobalScale().y); }

	float R() { return GlobalPos().x + Size().x * 0.5f; }
	float L() { return GlobalPos().x - Size().x * 0.5f; }
	float T() { return GlobalPos().y - Size().y * 0.5f; }
	float B() { return GlobalPos().y + Size().y * 0.5f; }

	ObbDesc GetObb();

private:
	virtual void SetVertices() override;

	bool IsAABB(RectCollider* rect, Vector2* overlap);
	bool IsOBB(RectCollider* rect);

private:
	bool IsSeparateAxis(Vector2 separate, Vector2 distance, Vector2 eb1, Vector2 eb2);
	bool IsBetweenPoint(Vector2 edge, Vector2 point, Vector2 e1, Vector2 e2);
};