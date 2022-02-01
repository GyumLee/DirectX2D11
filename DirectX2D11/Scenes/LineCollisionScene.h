#pragma once

class LineCollisionScene : public Scene
{
private:
	LineCollider* line1;
	LineCollider* line2;

	CircleCollider* circle;

public:
	LineCollisionScene();
	~LineCollisionScene();

	virtual void Update() override;
	virtual void Render() override;
};