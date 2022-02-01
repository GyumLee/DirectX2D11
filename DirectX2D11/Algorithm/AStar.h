#pragma once

class AStar
{
private:
	vector<Node*> nodes;
	//vector<int> openNodes;
	Heap* heap;

public:
	AStar(vector<Node*> nodes, UINT width);
	~AStar();

	void Update();
	void Render();

	void Reset();
	int FindCloseNode(Vector2 pos);

	vector<Vector2> GetPath(int start, int end);

private:
	float GetManhattanDistance(int start, int end);
	float GetDistance(int start, int end);

	int GetMinNode();
	void Extend(int center, int end);

	void SetEdge(UINT width);
};