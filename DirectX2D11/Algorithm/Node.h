#pragma once

class Node
{
public:
	enum State
	{
		NONE, OPEN, CLOSED, USING, OBSTACLE
	};

private:
	friend class AStar;

	struct Edge
	{
		Node* node;
		float cost;
		LineCollider* line;

		Edge(Vector2 start, Vector2 end)
		{
			line = new LineCollider(start, end);
			line->SetColor(1, 0, 1);
		}
		~Edge()
		{
			delete line;
		}
	};

	Vector2 pos;

	int index;
	int via;

	//Cost
	float f;//최종비용 : g + h
	float g;//출발지부터 노드까지의 비용 : S->N
	float h;//목적지까지의 추정 가중치 : N->E

	State state;

	vector<Edge*> edges;

	Collider* collider;

public:
	Node(Vector2 pos, int index);
	~Node();

	void Render();

	void AddEdge(Node* node);

	void SetState(State state) { this->state = state; }
	float GetCost() { return f; }
};