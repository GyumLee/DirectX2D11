#pragma once

class SRTScene : public Scene
{
private:
	TestRect* rect;

	MatrixBuffer* worldBuffer;
	//XMFLOAT4X4 world;
	Matrix world, world2; //XMFLOAT4X4 �� ���� ���� �Ӽ� ������ ����

	Float2 position;
	Float2 scale;
	float angle, angle2;

public:
	SRTScene();
	~SRTScene();

	virtual void Update() override;
	virtual void Render() override;
};