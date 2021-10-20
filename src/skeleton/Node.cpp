#include "Node.hpp"
#include "def.h"

void Node::SetParent (class Node *parent) {
	if (this->parent) {
		Error ("Node already has parent");
		return ;
	}
	this->parent = parent;
	parent->childs.push_back (this);
}

void Node::SetRotationFrames(std::vector<RotationFrame> &&frames) {
	rot_frames = frames;
}
