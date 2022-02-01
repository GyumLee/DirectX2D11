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
	float f;//������� : g + h
	float g;//��������� �������� ��� : S->N
	float h;//������������ ���� ����ġ : N->E

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