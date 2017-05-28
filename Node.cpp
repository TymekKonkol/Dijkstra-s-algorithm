#include "Node.h"
#include "Path.h"

Node::Node()
{
	this->length_from_start = NULL;
	this->next_path = NULL;	
	this->visited = false;
	//dijkstra
	this->next_node = NULL;
}

Node::Node(int x, int y)
{
	this->x = x;
	this->y = y;

	this->length_from_start = NULL;
	this->next_path = NULL;
	this->visited = false;
	//dijkstra
	this->next_node = NULL;
}

Node::Node(int x, int y, int nr)
{
	this->nr = nr;
	this->x = x;
	this->y = y;

	this->length_from_start = NULL;
	this->next_path = NULL;
	this->visited = false;

	//dijkstra
	this->next_node = NULL;
}

Node::~Node()
{	
	delete this->next_path;
}



//dijkstra

Node* Node::get_next_node()
{
	return this->next_node;
}
void Node::set_next_node(Node *node)
{
	if (this->next_node == NULL)
	{
		node->prev_node = this;
		this->next_node = node;
	}
	else if (this->next_node->get_length_from_start() > node->get_length_from_start())
	{
		node->prev_node = this;
		node->next_node = this->next_node;
		node->next_node->prev_node = node;
		this->next_node = node;
	}
	else
		this->next_node->set_next_node(node);
}

void Node::go_up_futher(Node *node)
{
	if (this->prev_node->get_length_from_start() != 0 && this->prev_node->get_length_from_start() > node->get_length_from_start())
		this->prev_node->go_up_futher(node);
	else
	{
		this->prev_node->next_node = node;
		node->next_node = this;
		node->prev_node = this->prev_node;
		this->prev_node = node;
	}
}

void Node::go_up()
{
	if (this->prev_node->get_length_from_start() > this->get_length_from_start())
	{
		this->prev_node->next_node = this->next_node;
		if (this->next_node != NULL)
			this->next_node->prev_node = this->prev_node;
		this->go_up_futher(this);
	}
}

void Node::remove_first_node()
{
	this->next_node = this->next_node->next_node;
	if (this->next_node != NULL)
		this->next_node->prev_node = this;
}

bool Node::is_Visited()
{
	return this->visited;
}

void Node::set_next_path(double length, Node *to_which_node)
{
	if (this->next_path != NULL)
		this->next_path->set_next_path(length, this, to_which_node);
	else
	{
		delete this->next_path;
		this->next_path = new Path(length, this, to_which_node);
	}
}

//getery setery
void Node::set_length_from_start(double length)
{
	this->length_from_start = length;
}

double Node::get_length_from_start()
{
	return this->length_from_start;
}

Path* Node::get_next_path()
{
	return this->next_path;
}
int Node::get_x()
{
	return this->x;
}

int Node::get_y()
{
	return this->y;
}

void Node::visit()
{
	this->visited = true;
}
void Node::unvisit()
{
	this->visited = false;
}

int Node::get_nr()
{
	return this->nr;
}