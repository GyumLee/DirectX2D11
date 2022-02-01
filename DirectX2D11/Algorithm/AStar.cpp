#include "Framework.h"

AStar::AStar(vector<Node*> nodes, UINT width)
	:nodes(nodes)
{
	SetEdge(width);
	heap = new Heap();
}

AStar::~AStar()
{
	for (Node* node : nodes)
		delete node;

	delete heap;
}

void AStar::Update()
{
	if (KEY_DOWN(VK_RBUTTON))
	{
		for (Node* node : nodes)
		{
			if (node->collider->IsPointCollision(mousePos))
			{
				node->SetState(Node::OBSTACLE);
			}
		}
	}
}

void AStar::Render()
{
	for (Node* node : nodes)
		node->Render();
}

void AStar::Reset()
{
	for (Node* node : nodes)
	{
		if (node->state != Node::OBSTACLE)
		{
			node->state = Node::NONE;
		}
	}
}

int AStar::FindCloseNode(Vector2 pos)
{
	float minDist = FLT_MAX;

	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		float dist = (pos - nodes[i]->pos).Length();

		if (minDist > dist)
		{
			minDist = dist;
			index = i;
		}
	}

	return index;
}

vector<Vector2> AStar::GetPath(int start, int end)
{
	vector<Vector2> path;

	if (nodes[end]->state == Node::OBSTACLE)
		return path;

	//1. 시작노드 초기화
	float G = 0.0f;
	//float H = GetManhattanDistance(start, end);
	float H = GetDistance(start, end);
	
	nodes[start]->g = G;
	nodes[start]->h = H;
	nodes[start]->f = G + H;
	nodes[start]->via = start;
	nodes[start]->state = Node::OPEN;

	//openNodes.push_back(start);
	heap->Insert(nodes[start]);

	while (nodes[end]->state != Node::CLOSED)
	{
		if (heap->Empty())
		{
			MessageBox(hWnd, L"길막", L"Error", MB_OK);
			return path;
		}

		int curIndex = GetMinNode();//2. 오픈노드 중에서 비용이 제일 좋은 노드 찾기
		Extend(curIndex, end);//3. 선택된 노드의 엣지노드 갱신하고 오픈노드에 추가
		nodes[curIndex]->state = Node::CLOSED;//4. 확장 끝난노드 닫기
	}

	//5. BackTracking
	int curIndex = end;
	while (curIndex != start)
	{
		nodes[curIndex]->state = Node::USING;
		path.push_back(nodes[curIndex]->pos);
		curIndex = nodes[curIndex]->via;
	}

	path.push_back(nodes[start]->pos);

	//openNodes.clear();
	heap->Clear();

	return path;
}

float AStar::GetManhattanDistance(int start, int end)
{
	Vector2 startPos = nodes[start]->pos;
	Vector2 endPos = nodes[end]->pos;

	Vector2 temp = endPos - startPos;

	return fabs(temp.x) + fabs(temp.y);
}

float AStar::GetDistance(int start, int end)
{
	Vector2 startPos = nodes[start]->pos;
	Vector2 endPos = nodes[end]->pos;

	Vector2 temp = endPos - startPos;

	float x = fabs(temp.x);
	float y = fabs(temp.y);

	float minSize = min(x, y);
	float maxSize = max(x, y);

	return sqrt(minSize * minSize * 2) + (maxSize - minSize);
}

int AStar::GetMinNode()
{
	return heap->DeleteRoot()->index;

	/*int openIndex = 0;
	int nodeIndex = openNodes[openIndex];
	float minF = nodes[nodeIndex]->f;

	for (UINT i = 1; i < openNodes.size(); i++)
	{
		nodeIndex = openNodes[i];
		if (nodes[nodeIndex]->f < minF)
		{
			minF = nodes[nodeIndex]->f;
			openIndex = i;
		}
	}

	nodeIndex = openNodes[openIndex];

	openNodes.erase(openNodes.begin() + openIndex);

	return nodeIndex;*/
}

void AStar::Extend(int center, int end)
{
	vector<Node::Edge*> edges = nodes[center]->edges;

	for (Node::Edge* edge : edges)
	{
		if (edge->node->state == Node::CLOSED)
			continue;
		if (edge->node->state == Node::OBSTACLE)
			continue;

		float G = nodes[center]->g + edge->cost;
		//float H = GetManhattanDistance(edge->node->index, end);
		float H = GetDistance(edge->node->index, end);
		float F = G + H;

		if (edge->node->state == Node::OPEN)
		{
			if (F < edge->node->f)
			{
				edge->node->g = G;
				edge->node->f = F;
				edge->node->via = center;
			}
		}
		else if (edge->node->state == Node::NONE)
		{
			edge->node->g = G;
			edge->node->h = H;
			edge->node->f = F;
			edge->node->via = center;
			edge->node->state = Node::OPEN;

			//openNodes.push_back(edge->node->index);
			heap->Insert(edge->node);
		}
	}
}

void AStar::SetEdge(UINT width)
{
	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (i % width != width - 1)
		{
			nodes[i]->AddEdge(nodes[i + 1]);
			nodes[i + 1]->AddEdge(nodes[i]);
		}

		if (i < nodes.size() - width)
		{
			nodes[i]->AddEdge(nodes[i + width]);
			nodes[i + width]->AddEdge(nodes[i]);
		}

		if (i % width != width - 1 && i < nodes.size() - width)
		{
			nodes[i]->AddEdge(nodes[i + 1 + width]);
			nodes[i + 1 + width]->AddEdge(nodes[i]);
		}

		if (i % width != 0 && i < nodes.size() - width)
		{
			nodes[i]->AddEdge(nodes[i - 1 + width]);
			nodes[i - 1 + width]->AddEdge(nodes[i]);
		}
	}
}
