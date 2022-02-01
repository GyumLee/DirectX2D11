#pragma once

class LineCollider : public Collider
{
private:
	Vector2 start;
	Vector2 end;

public:
	LineCollider(Vector2 start, Vector2 end);
	~LineCollider();

	virtual bool IsPointCollision(Vector2 point) override;
	virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
	virtual bool IsCircleCollision(CircleCollider* circle) override;

	void SetStart(Vector2 pos);
	void SetEnd(Vector2 pos);

	bool IsBetween(LineCollider* line);
	bool IsCollision(LineCollider* line, Vector2& crossPoint);

	Vector2 GetStart() { return Vector2::TransformCoord(start, world); }
	Vector2 GetEnd() { return Vector2::TransformCoord(end, world); }

private:
	virtual void SetVertices() override;
};