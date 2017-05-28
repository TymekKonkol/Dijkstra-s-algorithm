#include <iostream>
#include <random>
#include <functional>  
#include "Node.h"
#include "Path.h"
#include <math.h>
#include <ctime>

using namespace std;

//max 140
#define SIZE_OF_MAP 140
#define NUMBER_OF_NODES ((SIZE_OF_MAP*SIZE_OF_MAP)/3)
#define NUMBER_OF_CONNECTIONS (NUMBER_OF_NODES*4)

void prepare_nodes(Node ***map, Node **set_of_nodes);
void make_connections(Node **set_of_nodes);
void display_map(Node ***map);
void display_connections(Node **set_of_nodes);
double dijkstra(Node *first, Node *last);

int main()
{
	srand(time(NULL));
	Node ***map;
	Node **set_of_nodes;

	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, SIZE_OF_MAP - 1);
	auto random = bind(distribution, generator);

	// generowanie mapy		
	map = new Node**[SIZE_OF_MAP];
	set_of_nodes = new Node*[NUMBER_OF_NODES];

	for (int i = 0; i < NUMBER_OF_NODES; i++)
		set_of_nodes[i] = NULL;

	for (int i = 0; i < SIZE_OF_MAP; i++)
		map[i] = new Node*[SIZE_OF_MAP];

	for (int i = 0; i < SIZE_OF_MAP; i++)
		for (int j = 0; j < SIZE_OF_MAP; j++)
			map[i][j] = NULL;

	prepare_nodes(map, set_of_nodes);	
	make_connections(set_of_nodes);	
	//display_connections(set_of_nodes);
	cout << endl << dijkstra(set_of_nodes[0], set_of_nodes[NUMBER_OF_NODES-1])<<endl;
	//usuwanie
	
	for (int i = 0; i < SIZE_OF_MAP; i++)
		for (int j = 0; j < SIZE_OF_MAP; j++)
			delete map[i][j];

	for (int i = 0; i < SIZE_OF_MAP; i++)
		delete[] map[i];

	delete[] set_of_nodes;
	delete[] map;	

	return 0;
}
void prepare_nodes(Node ***map, Node **set_of_nodes)
{
	int pos_x;
	int pos_y;

	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		do
		{
			pos_x = rand() % SIZE_OF_MAP;
			pos_y = rand() % SIZE_OF_MAP;
		} while (map[pos_x][pos_y] != NULL);
		delete map[pos_x][pos_y];
		map[pos_x][pos_y] = new Node(pos_x, pos_y, i);
		set_of_nodes[i] = map[pos_x][pos_y];
	}
}

void make_connections(Node **set_of_nodes)
{
	double length;
	int node_1;
	int node_2;

	int delta_x, delta_y;
	for (int i = 0; i < NUMBER_OF_CONNECTIONS; i++)
	{
		do
		{
			node_1 = rand() % NUMBER_OF_NODES;
			node_2 = rand() % NUMBER_OF_NODES;

			//sprawdzenie czy nie generujemy sciezki miedzy tym samym wezlem, oraz czy juz taka sciezka nie istnieje
		} while (node_1 == node_2 ||
			set_of_nodes[node_1]->get_next_path()->
			check_if_already_is_path(set_of_nodes[node_2]) ||

			set_of_nodes[node_2]->get_next_path()->
			check_if_already_is_path(set_of_nodes[node_1]));

		//obliczenie dlugosci z pitagorasa

		delta_x = set_of_nodes[node_1]->get_x() - set_of_nodes[node_2]->get_x();
		delta_y = set_of_nodes[node_1]->get_y() - set_of_nodes[node_2]->get_y();
		length = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
		//przypisanie sciezki do obu wierzcholkow 
		//tak na prawde stworzenie nowej dla kazdego, ale przy pracy algorytmow nalezy sprawdzac czy wezel zostal odwiedzony, a nie czy sciezka
		set_of_nodes[node_1]->set_next_path(length, set_of_nodes[node_2]);
		set_of_nodes[node_2]->set_next_path(length, set_of_nodes[node_1]);
	}

}

//funkcja do wyswietlania mapy, niebezpieczna pryz duzej wartosci SIZE_OF_MAP
void display_map(Node ***map)
{
	for (int i = 0; i < SIZE_OF_MAP; i++) {
		for (int j = 0; j < SIZE_OF_MAP; j++)
			if (map[i][j] != NULL)
				cout << "X";
			else
				cout << "_";
		cout << endl;
	}
}
//funkcja do wyswietlania POLACZEN, niebezpieczna przy duzej wartosci SIZE_OF_MAP
void display_connections(Node **set_of_nodes)
{
	Path *p;
	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		p = set_of_nodes[i]->get_next_path();
		while (p != NULL)
		{
			cout << set_of_nodes[i]->get_nr() << " " << p->get_length() << " " << p->get_end()->get_nr() << endl;
			p = p->get_next_path();
		}
		cout << endl;
	}
}

//funkcje do dijkstry
double dijkstra(Node *first, Node *last)
{
	if (first->get_next_path() == NULL)
		return 0;
	first->set_length_from_start(0);
	Node* n, *actual = first;
	Path* p;
	do
	{
		p = actual->get_next_path();
		actual->visit();
		while (p != NULL)
		{
			//pobranie wierzcholka polaczonego z aktualnym
			n = p->get_end();
			//tylko jesli jest nieodwiedzony ustwiamy nowa wartosc i miejsce w kolejce
			if (n->is_Visited() == false)
			{
				//jezeli jeszcze nie ustalono wartosci to ustaw i wstaw do kolejki
				if (n->get_length_from_start() == NULL)
				{
					n->set_length_from_start(actual->get_length_from_start() + p->get_length());
					first->set_next_node(n);
				}//jesli juz ustalono wartosc to sprawdz czy nowa wartosc jest lepsza
				else if (n->get_length_from_start() > (actual->get_length_from_start() + p->get_length()))
				{//jesli jest to ja ustal i popraw pozycje w kolejce
					n->set_length_from_start(actual->get_length_from_start() + p->get_length());
					n->go_up();
				}
			}
			p = p->get_next_path();
		}
		//pobierz nastepny wezel
		actual = first->get_next_node();
		first->remove_first_node();
		//wyjdz jesli juz nie ma nieodwiedzonych wezlow lub gdy natrafilismy na koniec
	} while (actual != NULL && actual != last);
	//jak osiagnieto koniec to zwrocona wartosc bedzie > 0, jesli nie ma sciezki do konca to zwrocone zostanie 0
	return last->get_length_from_start();
}