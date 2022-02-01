#pragma once

class TutorialScene : public Scene
{
private:
	MatrixBuffer* world;
	MatrixBuffer* view;
	MatrixBuffer* projection;

	//TestRect* rect;
	TestCircle* circle;

	XMFLOAT4X4 worldMatrix;

public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
};