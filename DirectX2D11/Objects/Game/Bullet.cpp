#include "Framework.h"

Bullet::Bullet(wstring textureFile) : Quad(textureFile), speed(300)
{
	isActive = false;

	collider = new RectCollider(Size());
	collider->SetParent(&world);
	collider->scale.x = 0.5f;
	collider->scale.y = 0.7f;
}

Bullet::~Bullet()
{
	delete collider;
}

void Bullet::Update()
{
	if (!isActive) return;

	//position.x += cos(rotation.z - XM_PI * 0.5f) * speed * DELTA;
	//position.y += sin(rotation.z - XM_PI * 0.5f) * speed * DELTA;
	position -= Up() * speed * DELTA;

	if (position.x < 0 || position.x > WIN_WIDTH)
		isActive = false;

	if (position.y < 0 || position.y > WIN_HEIGHT)
		isActive = false;

	UpdateWorld();
	collider->UpdateWorld();
}

void Bullet::Render()
{
	Quad::Render();

	if (isActive)
		collider->Render();
}

void Bullet::Fire(Vector2 pos, float angle)
{
	position = pos;
	rotation.z = angle;

	isActive = true;
}

bool Bullet::Collision(Collider* collider)
{
	if (!isActive) return false;

	if (this->collider->IsCollision(collider))
	{
		isActive = false;
		return true;
	}
		
	return false;
}
