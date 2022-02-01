#pragma once

class DijkstraScene : public Scene
{
private:
	Dijkstra* dijkstra;
	Tank* tank;

public:
	DijkstraScene();
	~DijkstraScene();

	virtual void Update() override;
	virtual void Render() override;
};