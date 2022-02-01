#pragma once

class AnimationScene : public Scene
{
private:
	Mario* mario;
	Knight* knight;

public:
	AnimationScene();
	~AnimationScene();

	virtual void Update() override;
	virtual void Render() override;
};