
#include "Console.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include "def.h"
#include "NodeSerializer.hpp"
#include "HardSkeleton.hpp"


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
			if (words.size () <= 1) {
				std::cout << "usage: skeleton show" << std::endl;
				std::cout << "usage: skeleton new_frame <start_time>" << std::endl;
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
			} else if (0 == words[1].compare ("new_frame") || 0 == words[1].compare ("newfr")) {
				if (words.size () <= 2) {
					std::cout << "usage: skeleton new_frame <start_time>" << std::endl;
					continue ;
				}
				float	start_time = std::strtof (words[2].c_str(), nullptr);
				if (_node_index >= 0) {
					skeleton._nodes[_node_index].rot_frames.push_back ({ start_time, glm::vec3 (1, 0, 0), 0.f });
					_frame_index = skeleton._nodes[_node_index].rot_frames.size () - 1;
					skeleton.RecalcAnimationDuration ();
				} else {
					Error ("no node selected");
				}
			} else if (0 == words[1].compare ("new_child") || 0 == words[1].compare ("newch")) {
				
			} else if (0 == words[1].compare ("save") || 0 == words[1].compare ("s")) {
				NodeSerializer	serializer;

				for (size_t index = 0; hardskeletons[index].name; index += 1) {
					if (0 != skeleton._name.compare (hardskeletons[index].name)) {
						serializer.serialize_nodedata (create_nodedata (0, hardskeletons[index].name));
					}
				}
				serializer.serialize_nodes (skeleton._nodes, skeleton._name);
				std::fstream	file("src/skeleton/HardSkeleton_serialized.cpp", file.out | file.trunc);
				if (!file.is_open ()) {
					Error ("cannot open file for serialized data. Outputing to stdout");
					std::cout << serializer.finalize () << std::endl;
				} else {
					file << serializer.finalize () << std::endl;
					std::cout << "saved" << std::endl;
				}
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


// 1. Torso movement
// 2. Add wings
// 3. Add jump, walk, idle, fly, wings protection

