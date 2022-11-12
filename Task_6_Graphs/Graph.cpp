#include "Graph.h"

#include <iostream>


using std::cout;
using std::make_pair;

//Конструктор
Graph::Graph(){}


//Деструктор
Graph::~Graph(){}


//Функция добавления ребра в граф - единственный способ для его создания
// 
//Алгоритм:
//	-Есть обе вершины:
//		-Они соединены:
//			-Исключение
//		-Иначе:
//			-Соеденить ребором
//	-Иначе:
//		-Добавить недостающие вершины
//		-Соеденить их
//
void Graph::addEdge(int firstID, int secondID, int weight)
{
	if (isVertexInGraph(firstID) && isVertexInGraph(secondID))
	{
		if (isVerticesConnected(firstID, secondID))
		{
			throw std::exception("Ребро уже существует.\n");
		}
		else
		{
			connectVertices(firstID, secondID, weight);
		}
	}
	else
	{
		if (!isVertexInGraph(firstID))
		{
			addVertex(firstID);
		}
		if (!isVertexInGraph(secondID))
		{
			addVertex(secondID);
		}
		connectVertices(firstID, secondID, weight);
	}
}


//Проверка на существование вершины в графе
bool Graph::isVertexInGraph(int ID)
{
	if (getVertex(ID) != nullptr)
	{
		return true;
	}
	
	return false;
}


//Проверка на соединенность двух вершин в графе
bool Graph::isVerticesConnected(int firstID, int secondID)
{
	Vertex* firstVertex = getVertex(firstID);
	Vertex* secondVertex = getVertex(secondID);
	
	for (auto neighbour : firstVertex->neighbours)
	{
		if (neighbour.first->ID == secondVertex->ID)
		{
			return true;
		}
	}

	return false;
}


//Вывод графа в виде списка вершин и их связей
void Graph::print()
{
	for (auto vertex : vertices)
	{
		cout << vertex->ID << ": ";

		for (int i = 0; i < vertex->neighbours.size(); i++)
		{
			cout << "(" << vertex->neighbours[i].first->ID
				<< ", " << vertex->neighbours[i].second << ")";

			if (i != vertex->neighbours.size() - 1)
			{
				cout << ", ";
			}
			else
			{
				cout << ";";
			}
		}
		
		cout << '\n';
	}
}


//Добавление вершины в граф
void Graph::addVertex(int ID)
{
	Vertex* newVertex = new Vertex(ID);
	vertices.push_back(newVertex);
}


//Соединение двух вершин графа
void Graph::connectVertices(int firstID, int secondID, int weight)
{
	Vertex* firstVertex = getVertex(firstID);
	Vertex* secondVertex = getVertex(secondID);
	
	firstVertex->neighbours.push_back(make_pair(secondVertex, weight));
	secondVertex->neighbours.push_back(make_pair(firstVertex, weight));
}


//Расчёт степени вершины графа
int Graph::calculateVertexDegree(int ID)
{
	return getVertex(ID)->neighbours.size();
}


//Получение указателя на вершину по ее ID
Graph::Vertex* Graph::getVertex(int ID)
{
	for (auto vertex : vertices)
	{
		if (vertex->ID == ID)
		{
			return vertex;
		}
	}

	return nullptr;
}


//Поиск кратчайшего пути алгоритмом Дейкстры
void Graph::showShortestPath(int firstID, int secondID)
{
	Vertex* firstVertex = getVertex(firstID);
	Vertex* secondVertex = getVertex(secondID);

	if (firstVertex == nullptr)
	{
		throw std::exception("Начальной вершины нет в графе.\n");
	}

	if (secondVertex == nullptr)
	{
		throw std::exception("Конечной вершины нет в графе.\n");
	}

	if (firstVertex == secondVertex)
	{
		cout << "Кратчайший путь 0 - начало совпадает с концом.\n";
		return;
	}

	for (auto vertex : vertices)
	{
		vertex->shortestWayToIt = INFINITY;
		vertex->vertexCameFrom = nullptr;
		vertex->isChecked = false;
	}

	firstVertex->shortestWayToIt = 0;

	while (true)
	{
		Vertex* currentVertex = nullptr;
		double minDistance = INFINITY;

		for (auto vertex : vertices)
		{
			if (!vertex->isChecked && vertex->shortestWayToIt < minDistance)
			{
				currentVertex = vertex;
				minDistance = vertex->shortestWayToIt;
			}
		}

		if (currentVertex == nullptr)
		{
			break;
		}

		currentVertex->isChecked = true;

		for (auto neighbour : currentVertex->neighbours)
		{
			if (neighbour.first->shortestWayToIt > currentVertex->shortestWayToIt + neighbour.second)
			{
				neighbour.first->shortestWayToIt = currentVertex->shortestWayToIt + neighbour.second;
				neighbour.first->vertexCameFrom = currentVertex;
			}
		}
	}

	cout << secondVertex->shortestWayToIt << ", проходит: ";

	vector<int> path;

	Vertex* currentVertex = secondVertex;

	while (currentVertex != nullptr)
	{
		path.push_back(currentVertex->ID);
		currentVertex = currentVertex->vertexCameFrom;
	}

	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << path[i];

		if (i != 0)
		{
			cout << " -> ";
		}
	}

	cout << '\n';
}