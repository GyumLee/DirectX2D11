#pragma once

class SelectScene : public Scene
{
private:
	Button* plane;

	IntBuffer* selectBuffer;
	ValueBuffer* sizeBuffer;
	ColorBuffer* colorBuffer;

public:
	SelectScene();
	~SelectScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	void ClickPlane();
};