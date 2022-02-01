#pragma once

class InstancingScene : public Scene
{
private:
	const static UINT COUNT = 1000;

	//vector<Quad*> quads;

	struct InstanceData
	{
		Matrix transform;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

	vector<InstanceData> instances;

	Quad* quad;

	VertexBuffer* instanceBuffer;

public:
	InstancingScene();
	~InstancingScene();

	virtual void Update() override;
	virtual void Render() override;
};