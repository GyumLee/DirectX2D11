#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
	friend class Singleton;

	map<string, vector<Effect*>> totalEffect;

	EffectManager();
	~EffectManager();

public:
	void Update();
	void Render();

	void Add(string key, UINT poolCount, wstring textureFile,
		Vector2 maxFrame, float delayTime = 0.1f, bool isAdditive = false);

	void Play(string key, Vector2 pos);
};