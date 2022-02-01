#pragma once

class Dijkstra
{
private:
	vector<DNode*> nodes;

	DNode* selectNode;

public:
	Dijkstra();
	~Dijkstra();

	void Update();
	void Render();

	void ResetNodes();
	int FindCloseNode(Vector2 pos);
	void SetEdgeInfo(int curIndex);
	int FindMinCostNode();

	vector<Vector2> GetPath(int start, int end);

private:
	void CreateNode(Vector2 pos);
};