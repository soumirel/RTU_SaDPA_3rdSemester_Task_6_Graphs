
#include <iostream>
#include <locale.h>
#include "Graph.h"

using namespace std;


void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;

	//Переменные для работы программы

	// Главный меню-цикл.
	while (userMenuChoice != 7)
	{
		std::system("cls");
		cout << "Практическая работа #4 ИКБО-03-21 Мазанов А.Е. Вариант 15\n\n"
			"Задание - Деревья.\n"
			"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n";

		cout << "Введите [0] - ТЕСТ создания графа\n"
			<< "Введите [1], чтобы создать граф вручную с клавиатуры\n"
			"\nВведите [7], чтобы закончить работу программы."
			"\nВаш выбор: ";

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 0:
		{
			//Тест на 10ом графе из таблицы предложенных графов
			Graph graph;
			graph.addEdge(1, 2, 23);
			graph.addEdge(1, 3, 12);
			graph.addEdge(2, 3, 25);
			graph.addEdge(2, 5, 22);
			graph.addEdge(2, 8, 35);
			graph.addEdge(3, 4, 18);
			graph.addEdge(4, 6, 20);
			graph.addEdge(5, 6, 23);
			graph.addEdge(5, 7, 14);
			graph.addEdge(6, 7, 24);
			graph.addEdge(7, 8, 16);

			cout << "Граф в виде списка вершин и связей: \n";
			graph.print();

			int vID = 5;
			cout << "Степень вершины " << vID << ": "
				<< graph.calculateVertexDegree(vID) << '\n';

			cout << "Кратчайший путь из вершины 1 в вершину 8: ";
			graph.showShortestPath(1, 8);

			break;
		}

		case 1:
		{
			Graph graph;
			int firstID, secondID, weight;
			char userChoice = 'Y';
			while (userChoice == 'Y')
			{
				cout << "Введите ID первой вершины: ";
				cin >> firstID;
				cout << "Введите ID второй вершины: ";
				cin >> secondID;
				cout << "Введите вес ребра: ";
				cin >> weight;
				try
				{
					graph.addEdge(firstID, secondID, weight);
				}
				catch (const std::exception& e)
				{
					cout << e.what();
				}
				
				cout << "Добавить еще ребро? (Y/N): ";
				cin >> userChoice;
			}
			cout << "Граф в виде списка вершин и связей: \n";
			graph.print();

			int ID;
			cout << "Введите ID вершины, для которой нужно посчитать степень: ";
			cin >> ID;
			cout << "Степень вершины " << ID << ": "
				<< graph.calculateVertexDegree(ID) << '\n';

			cout << "Введите ID первой вершины: ";
			cin >> firstID;
			cout << "Введите ID второй вершины: ";
			cin >> secondID;
			cout << "Кратчайший путь из вершины " << firstID
				<< " в вершину " << secondID << ": ";
			graph.showShortestPath(firstID, secondID);

			break;
		}

		case 7:
			cout << "\nДо свидания!\n";
			break;

		default:
			cout << "\nЯ не понимаю вас.\n";
			cin.clear();
			break;
		}
		std::system("pause");
	}
}


