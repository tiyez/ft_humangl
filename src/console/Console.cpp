
#include "Console.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "def.h"

// CAUTION!!! copy-pasted from https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
    	if (!item.empty()) {
	        *result++ = item;
    	}
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
// CAUTION!!!

void	Console::listen_command () {
	std::string	command;

	while (1) {
		std::cout << " command: ";
		std::getline (std::cin, command);
		std::vector<std::string>	words = split (command, ' ');

		if (words.size () == 0) {
			continue ;
		}
		if (0 == words[0].compare ("continue") || 0 == words[0].compare ("c")) {
			break ;
		} else if (0 == words[0].compare ("skeleton") || 0 == words[0].compare ("sk")) {
			if (words.size () <= 0) {
				std::cout << "usage: skeleton show" << std::endl;
				std::cout << "usage: skeleton new_frame <time>" << std::endl;
				continue ;
			}
			if (0 == words[1].compare ("show") || 0 == words[1].compare ("sh")) {
				std::cout << "Skeleton name: " << skeleton._name << std::endl;
				std::cout << "Nodes count: " << skeleton._nodes.size () << std::endl;
				if (_node_index >= 0) {
					class Node	*node = &skeleton._nodes[_node_index];

					std::cout << "translation: " << node->translation << std::endl;
					std::cout << "rotation: " << node->rotation << std::endl;
					std::cout << "scale: " << node->scale << std::endl;
					std::cout << "self_origin: " << node->self_origin << std::endl;
					std::cout << "parent_origin: " << node->parent_origin << std::endl;
					std::cout << "Frames: " << std::endl;
					for (auto &rot : node->rot_frames) {
						std::cout << "  " << rot.time << " " << rot.axis << " " << rot.angle << std::endl;
					}
				}
			} else if (0 == words[1].compare ("serialize") || 0 == words[1].compare ("ser")) {
				
			}
		}
	}
}

void	Console::update (struct Input &input, float delta) {
	if (input.select_node) {
		if (_node_index + input.select_node >= 0 && _node_index + input.select_node < (int) skeleton._nodes.size ()) {
			_node_index += input.select_node;
			Debug ("node index: %d", _node_index);
		} else {
			_node_index = -1;
		}
	}
	if (input.select_frame && _node_index >= 0) {
		if (_frame_index + input.select_frame >= 0 && _frame_index + input.select_frame < (int) skeleton._nodes[_node_index].rot_frames.size ()) {
			_frame_index += input.select_frame;
			Debug ("frame index: %d", _frame_index);
		}
	}
	if (_node_index >= 0 && _node_index < (int) skeleton._nodes.size ()) {
		skeleton.HighlightNode (_node_index);
		skeleton.ChangeNodeSize(_node_index, input.scale_delta);
		skeleton.ChangeNodeColor(_node_index, input.color_delta);
		if (_frame_index >= 0) {
			skeleton.RotateNodeFrame(_node_index, _frame_index, input.rotate_x, input.rotate_y);
		}
	}
	if (!input.animate) {
		skeleton.Animate(delta);
	} else {
		if (_node_index >= 0 && _frame_index >= 0) {
			skeleton.SetAnimationTime (skeleton._nodes[_node_index].rot_frames[_frame_index].time);
			skeleton.Animate(0);
		}
	}
}


