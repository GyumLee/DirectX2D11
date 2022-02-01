#pragma once

class RotationScene : public Scene
{
private:
	Quad* plane;

public:
	RotationScene();
	~RotationScene();

	virtual void Update() override;
	virtual void Render() override;
};