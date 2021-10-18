#include "Node.hpp"
#include "def.h"

void Node::set_parent (class Node *parent) {
	if (this->parent) {
		Error ("Node already has parent");
		return ;
	}
	this->parent = parent;
	parent->childs.push_back (this);
}