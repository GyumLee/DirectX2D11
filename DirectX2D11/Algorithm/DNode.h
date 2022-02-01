#pragma once

class DNode
{
private:
	friend class Dijkstra;

	struct Edge
	{
		DNode* node;
		float cost;
		LineCollider* line;

		Edge(Vector2 start, Vector2 end)
		{
			line = new LineCollider(start, end);
		}
		~Edge()
		{
			delete line;
		}
	};

	Vector2 pos;
	bool isClosed;
	int via;
	float cost;

	int index;

	vector<Edge*> edges;

	Collider* collider;

public:
	DNode(Vector2 pos);
	~DNode();

	void Render();

	void AddEdge(DNode* node);
};