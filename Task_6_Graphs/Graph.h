#pragma once

#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;
using std::pair;

//Класс графа
class Graph
{
public:
	//Конструктор
	Graph();

	//Деструктор
	~Graph();

	//Функция добавления ребра в граф
	void addEdge(int firstID, int secondID, int weight);

	//Вывод графа в виде списка вершин и их связей
	void print();

	//Расчёт степени вершины графа
	int calculateVertexDegree(int ID);

	//Поиск кратчайшего пути алгоритмом Дейкстры
	void showShortestPath(int firstID, int secondID);

private:

	//Структура вершины графа
	struct Vertex
	{
		//Основная структурная часть - ID вершины и список соседей
		int ID;
		vector<pair<Vertex*, int>> neighbours;

		//Поля для алгоритма Дейкстры:
		//	- расстояние от начальной вершины
		//	- указатель на предыдущую вершину в кратчайшем пути
		//	- флаг, показывающий, была ли вершина посещена
		double shortestWayToIt;
		Vertex* vertexCameFrom;
		bool isChecked;
		
		//Конструктор
		Vertex(int ID)
		{
			this->ID = ID;
			shortestWayToIt = INFINITY;
			vertexCameFrom = nullptr;
			isChecked = false;
		}
	};

	//Граф - список указателей на вершины
	vector<Vertex*> vertices;

	//Проверка на существование вершины в графе
	bool isVertexInGraph(int ID);

	//Проверка на соединенность двух вершин в графе
	bool isVerticesConnected(int firstID, int secondID);

	//Соединение двух вершин графа
	void connectVertices(int firstID, int secondID, int weight);

	//Добавление вершины в граф
	void addVertex(int ID);

	//Получение указателя на вершину по ее ID
	Vertex* getVertex(int ID);
};