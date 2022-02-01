#pragma once

class CollisionScene : public Scene
{
private:
	vector<Collider*> colliders;

public:
	CollisionScene();
	~CollisionScene();

	virtual void Update() override;
	virtual void Render() override;
};