#pragma once

class FontScene : public Scene
{
private:
	float time;

	ImageFont* imageFont;

public:
	FontScene();
	~FontScene();

	virtual void Update() override;
	virtual void Render() override;
};