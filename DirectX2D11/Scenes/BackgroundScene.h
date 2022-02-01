#pragma once

class BackgroundScene : public Scene
{
private:
	float speed;

	Quad* backgrounds[2];

	Mario* mario;

public:
	BackgroundScene();
	~BackgroundScene();

	virtual void Update() override;
	virtual void Render() override;
};