#pragma once

class ImageFont : public Transform
{
private:
	const UINT LENGTH = 10;

	UINT value;

	vector<Quad*> quads;
	vector<Texture*> images;

	float interval;

public:
	ImageFont(vector<Texture*> images, Vector2 size = Vector2(50, 50));
	~ImageFont();

	void Update();
	void Render();

	void SetValue(UINT value) { this->value = value; }
};