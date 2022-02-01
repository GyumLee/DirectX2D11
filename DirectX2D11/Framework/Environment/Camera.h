#pragma once

class Camera : public Transform
{
private:
	MatrixBuffer* viewBuffer;
	Matrix invView;

	float speed;

	Vector2 leftTop;
	Vector2 rightBottom;

	Transform* target;

	Vector2 targetOffset;

public:
	Camera();
	~Camera();

	void Update();
	void PostRender();

	Vector2 ScreenToWorld(Vector2 pos);
	Vector2 WorldToScreen(Vector2 pos);

	void SetLeftTop(float x, float y) { leftTop = { x, y }; }
	void SetRightBottom(float x, float y) { rightBottom = { x, y }; }

	void SetTarget(Transform* target) { this->target = target; }

private:
	void FreeMode();
	void FollowMode();

	void SetView();
	void FixPosition(Vector2& position);
};