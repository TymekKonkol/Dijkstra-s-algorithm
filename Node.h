#pragma once
#include <iostream>
class Path;
class Node
{
	//Node jest wezlem, ale tez kolejka jednokierunkowa do odwiedzania kolejnych wezlow
	double length_from_start;
	bool visited;
	//kolejka
	Path *next_path;
	//polozenie na mapie, z ktorej jest liczona odleglosc miedzy wezlami
	int x;
	int y;
	int nr;
	
	//dijskra
	Node *next_node;
	Node *prev_node;	
public:
	Node();
	Node(int x, int y);
	Node(int x, int y, int nr);
	~Node();
	void visit();
	void unvisit();
	void set_length_from_start(double length);
	double get_length_from_start();	
	void set_next_path(double length, Node *to_which_node);
	Path* get_next_path();
	int get_x();
	int get_y();
	bool is_Visited();
	int get_nr();

	//dijkstra
	Node * get_next_node();
	//wstawia kolejny wezel do kolejki
	void set_next_node(Node *node);
	void remove_first_node();
	//jak zmieniono wartosc wezla to nalezy sprawdzic jego pozycje w kolejce i ewentualnie przestawic,
	//robia to dwie ponizsze funkcie
	//sprawdza czy w ogóle zmienic pozycjê
	void go_up();
	//jak zmienic pozycje to przechodzi po wszystkich elementach wyzej w kolejce az natrafi na taki z ktorym moze sie zamienic
	void go_up_futher(Node *node);
};