#pragma once

class Tank : public AnimObject
{
private:
	float speed;
	Collider* collider;

	vector<Vector2> path;

public:
	Tank();
	~Tank();

	void Update();
	void Render();

	Collider* GetCollider() { return collider; }
	
	void SetPath(vector<Vector2> path);

private:
	void KeyboardMove();
	void AutoMove();

	void SavePos();
	void LoadPos();
};