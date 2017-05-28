#include "Path.h"

Path::Path()
{
	this->end = NULL;
	this->length = NULL;
	this->next_path = NULL;
}

Path::Path(double length, Node *begin, Node *end)
{
	this->length = length;
	this->end = end;
	this->next_path = NULL;
}

Path::~Path()
{
	delete this->next_path;	
}

void Path::set_next_path(double length, Node *begin, Node *end)
{
	Path *p = new Path(length, begin, end);
	p->next_path = this->next_path;
	this->next_path = p;
}

Path* Path::get_next_path()
{
	return this->next_path;
}

double Path::get_length()
{
	return this->length;
}
bool Path::check_if_already_is_path(Node *end)
{
	if (this == NULL)
		return false;

	if ( this->end == end)
		return true;

	Path *p = this->next_path;
	while (p != NULL)
	{
		if ( p->end == end)
			return true;
		p = p->next_path;
	}
	return false;
}
Node* Path::get_end()
{
	return this->end;
}