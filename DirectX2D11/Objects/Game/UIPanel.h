#pragma once

class UIPanel : public Transform
{
protected:
	Quad* panel;
	Collider* collider;

	Vector2 offset;
	bool isDrag;

public:
	UIPanel(wstring textureFile);
	~UIPanel();

	void Update();
	void Render();
};