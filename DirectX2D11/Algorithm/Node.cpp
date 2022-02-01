#include "Framework.h"

Node::Node(Vector2 pos, int index)
	: pos(pos), index(index), via(-1), f(0), g(0), h(0), state(NONE)
{
	collider = new CircleCollider(10);
	collider->position = pos;
	collider->UpdateWorld();
}

Node::~Node()
{
	for (Edge* edge : edges)
		delete edge;

	delete collider;
}

void Node::Render()
{
	switch (state)
	{
	case Node::NONE:
		collider->SetColor(1, 1, 1);
		break;
	case Node::OPEN:
		collider->SetColor(0, 1, 0);
		break;
	case Node::CLOSED:
		collider->SetColor(0, 0, 0);
		break;
	case Node::USING:
		collider->SetColor(0, 0, 1);
		break;
	case Node::OBSTACLE:
		collider->SetColor(1, 0, 0);
		break;
	default:
		break;
	}

	collider->Render();

	for (Edge* edge : edges)
		edge->line->Render();
}

void Node::AddEdge(Node* node)
{
	Edge* edge = new Edge(node->pos, pos);
	edge->node = node;
	edge->cost = (node->pos - pos).Length();
	edges.push_back(edge);
}
