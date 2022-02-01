#pragma once

class Transform
{
public:
	bool isActive;

	Vector2 position;
	Float3 rotation;
	Vector2 scale;

protected:
	Vector2 pivot;

	Matrix world;
	XMFLOAT4X4 matWorld;

	Matrix* parent;

	Matrix S, R, T;
	Matrix P, IP; //(pivot, inverse pivot)

	Vector2 right;
	Vector2 up;

	Vector2 globalPosition;
	Vector2 globalScale;

public:
	Transform();

	void UpdateWorld();

	void SetParent(Matrix* matrix) { parent = matrix; }
	void SetParent(Transform* parent);

	void SetPivot(float x, float y) { pivot = { x, y }; }

	Matrix& GetWorld() { return world; }

	Vector2 Right() { return right.Normalized(); }
	Vector2 Up() { return up.Normalized(); }
	Vector2 Left() { return right.Normalized() * -1.0f; }
	Vector2 Down() { return up.Normalized() * -1.0f; }

	//Vector2 GlobalPos() { return Vector2(matWorld._41, matWorld._42); }
	Vector2 GlobalPos() { return globalPosition; }
	Vector2 GlobalScale() { return globalScale; }
};