#include "Framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	//for (pair<string, vector<Effect*>> effects : totalEffect)
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
	}
}

void EffectManager::Update()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render()
{
	for (auto effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render();
	}
}

void EffectManager::Add(string key, UINT poolCount, wstring textureFile, Vector2 maxFrame, float delayTime, bool isAdditive)
{
	if (totalEffect.count(key) > 0) return;

	vector<Effect*> effects(poolCount);

	for (Effect*& effect : effects)
	{
		effect = new Effect(textureFile, maxFrame, delayTime, isAdditive);
	}

	totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos)
{
	if (totalEffect.count(key) == 0) return;

	for (Effect* effect : totalEffect[key])
	{
		if (!effect->isActive)
		{
			effect->Play(pos);
			return;
		}
	}
}
