#include "Framework.h"
#include "Camera.h"

Camera::Camera()
	: speed(5.0f), rightBottom(WIN_WIDTH, WIN_HEIGHT), target(nullptr),
	targetOffset(CENTER_X, CENTER_Y)
{
	viewBuffer = new MatrixBuffer();
	viewBuffer->SetVS(1);
}

Camera::~Camera()
{
	delete viewBuffer;
}

void Camera::Update()
{
	if (target)
		FollowMode();
	else
		FreeMode();

	SetView();
}

void Camera::PostRender()
{
	ImGui::Text("Camera Info");
	ImGui::Text("Position(X : %d, Y : %d", (int)position.x, (int)position.y);
	ImGui::SliderFloat("CamSpeed", &speed, 0, 500);
	ImGui::SliderFloat("OffsetX", &targetOffset.x, 0, WIN_WIDTH);
	ImGui::SliderFloat("OffsetY", &targetOffset.y, 0, WIN_HEIGHT);
}

Vector2 Camera::ScreenToWorld(Vector2 pos)
{
	return Vector2::TransformCoord(pos, world);
}

Vector2 Camera::WorldToScreen(Vector2 pos)
{
	return Vector2::TransformCoord(pos, invView);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
		{
			position.y -= speed * DELTA;
		}
		if (KEY_PRESS('S'))
		{
			position.y += speed * DELTA;
		}
		if (KEY_PRESS('A'))
		{
			position.x -= speed * DELTA;
		}
		if (KEY_PRESS('D'))
		{
			position.x += speed * DELTA;
		}
	}

	FixPosition(position);
}

void Camera::FollowMode()
{
	Vector2 targetPos = target->GlobalPos() - targetOffset;

	FixPosition(targetPos);

	position = LERP(position, targetPos, speed * DELTA);
}

void Camera::SetView()
{
	UpdateWorld();

	invView = XMMatrixInverse(nullptr, world);

	viewBuffer->Set(invView);
	viewBuffer->SetVS(1);
}

void Camera::FixPosition(Vector2& position)
{
	if (position.x < leftTop.x)
		position.x = leftTop.x;
	if (position.y < leftTop.x)
		position.y = leftTop.x;
	if (position.x > rightBottom.x - WIN_WIDTH)
		position.x = rightBottom.x - WIN_WIDTH;
	if (position.y > rightBottom.y - WIN_HEIGHT)
		position.y = rightBottom.y - WIN_HEIGHT;
}
