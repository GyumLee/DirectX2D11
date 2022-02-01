#pragma once

class Button : public Quad
{
protected:
	enum State
	{
		NONE, DOWN, OVER
	}state;

	Collider* collider;

	function<void()> Event;
	function<void(void*)> VoidEvent;

	void* voidParam;

	Float4 noneColor;
	Float4 downColor;
	Float4 overColor;

	bool isDownCheck;

	wstring text;

public:
	Button(wstring textureFile);
	~Button();

	void Update();
	void Render();

	void SetEvent(function<void()> Event) { this->Event = Event; }
	void SetVoidEvent(function<void(void*)> Event) { VoidEvent = Event; }

	void SetVoidParam(void* value) { voidParam = value; }

	void SetText(wstring text) { this->text = text; }

	Collider* GetCollider() { return collider; }
};