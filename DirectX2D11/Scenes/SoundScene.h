#pragma once

class SoundScene : public Scene
{
private:
	System* soundSystem;
	Sound* sound;
	Channel* channel;

public:
	SoundScene();
	~SoundScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void Start() override;
	virtual void End() override;
};