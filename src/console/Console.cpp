#include "Console.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
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

bool	Console::listen_command () {
	std::string	command;

	std::cout << " command: ";
	std::getline (std::cin, command);
	std::vector<std::string>	words = split (command, ' ');

	if (words.size () == 0) {
		return true;
	}
	if (0 == words[0].compare ("continue") || 0 == words[0].compare ("c")) {
		return false;
	} else if (0 == words[0].compare ("quit")) {
		exit (0);
	} else if (0 == words[0].compare ("skeleton") || 0 == words[0].compare ("sk")) {
		auto sk_help = []() {
			std::cout << "usage: skeleton show" << std::endl;
			std::cout << "usage: skeleton new_frame <start_time>" << std::endl;
			std::cout << "usage: skeleton new_child" << std::endl;
			std::cout << "usage: skeleton save" << std::endl;
			std::cout << "usage: skeleton select [<name>]" << std::endl;
			std::cout << "usage: skeleton new <name> [<clone_name>]" << std::endl;
			std::cout << "usage: skeleton node <index>" << std::endl;
			std::cout << "usage: skeleton frame <index>" << std::endl;
			std::cout << "usage: skeleton set self_origin <x> <y> <z>" << std::endl;
			std::cout << "usage: skeleton set parent_origin <x> <y> <z>" << std::endl;
			std::cout << "usage: skeleton set scale <x> <y> <z>" << std::endl;
			std::cout << "usage: skeleton set rot <x> <y> <z>" << std::endl;
			std::cout << "usage: skeleton clear frames" << std::endl;
		};

		if (words.size () <= 1) {
			sk_help ();
			return true;
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
				for (size_t index = 0; index < node->rot_frames.size (); index += 1) {
					struct RotationFrame	&frame = node->rot_frames[index];

					std::cout << "  " << frame.time << " " << frame.axis << " " << frame.angle << ((int) index == _frame_index ? " <--" : "") << std::endl;
				}
			}
		} else if (0 == words[1].compare ("new_frame") || 0 == words[1].compare ("newfr")) {
			if (words.size () <= 2) {
				std::cout << "usage: skeleton new_frame <start_time>" << std::endl;
				return true;
			}
			float	start_time = std::strtof (words[2].c_str(), nullptr);
			if (_node_index >= 0) {
				std::vector<RotationFrame>	&frames = skeleton._nodes[_node_index].rot_frames;
				frames.push_back ({ start_time, ftm::vec3 (1, 0, 0), 0.f });
				_frame_index = frames.size () - 1;
				std::sort (frames.begin (), frames.end (), [](const RotationFrame &left, const RotationFrame &right) { return left.time < right.time; });
				for (size_t index = 0; index < frames.size (); index += 1) {
					if (frames[index].time == start_time) {
						_frame_index = index;
						break ;
					}
				}
				skeleton.RecalcAnimationDuration ();
			} else {
				Error ("no node selected");
			}
		} else if (0 == words[1].compare ("new_child") || 0 == words[1].compare ("newch")) {
			if (_node_index >= 0) {
				class Node	&parent = skeleton._nodes[_node_index];

				skeleton._nodes.push_back (Node (parent.model));
				skeleton._nodes.back ().parent_index = _node_index;
				parent.childs.push_back (skeleton._nodes.size () - 1);
				_node_index = skeleton._nodes.size () - 1;
				_frame_index = -1;
			} else if (skeleton._nodes.size () == 0) {
				skeleton._nodes.push_back (Node (model));
				_node_index = skeleton._nodes.size () - 1;
				_frame_index = -1;
			} else {
				Error ("no parent selected");
			}
		} else if (0 == words[1].compare ("new")) {
			if (words.size () <= 2) {
				std::cout << "usage: skeleton new <name> [<clone_name>]" << std::endl;
				return true;
			}
			if (words.size () == 4) {
				skeleton = Skeleton (create_nodedata (model, words[3]));
				skeleton._name = words[2];
			} else {
				skeleton._nodes.clear ();
				skeleton._nodes.push_back (Node (model));
			}
			_node_index = 0;
			_frame_index = -1;
		} else if (0 == words[1].compare ("save") || 0 == words[1].compare ("s")) {
			NodeSerializer	serializer;

			for (size_t index = 0; hardskeletons[index].name; index += 1) {
				if (0 != skeleton._name.compare (hardskeletons[index].name)) {
					serializer.serialize_nodedata (create_nodedata (0, hardskeletons[index].name));
				}
			}
			serializer.serialize_nodes (skeleton._nodes, skeleton._name);
			serializer.serialize_translations(skeleton._translation_frames, skeleton._name);
			std::fstream	file("src/skeleton/HardSkeleton_serialized2.cpp", file.out | file.trunc);
			if (!file.is_open ()) {
				Error ("cannot open file for serialized data. Outputing to stdout");
				std::cout << serializer.finalize () << std::endl;
			} else {
				file << serializer.finalize () << std::endl;
				std::cout << "saved" << std::endl;
			}
		} else if (0 == words[1].compare ("select") || 0 == words[1].compare ("sel")) {
			if (words.size () <= 2) {
				std::cout << "skeleton list:" << std::endl;
				for (size_t index = 0; hardskeletons[index].name; index += 1) {
					std::cout << "  " << hardskeletons[index].name << std::endl;
				}
			} else {
				bool found = false;
				size_t index = 0;

				for (; hardskeletons[index].name; index += 1) {
					if (0 == words[2].compare (hardskeletons[index].name)) {
						found = true;
						break ;
					}
				}
				if (found) {
					skeleton = Skeleton (create_nodedata (model, hardskeletons[index].name));
				} else {
					Error ("skeleton '%s' not found", words[2].c_str ());
				}
			}
		} else if (0 == words[1].compare ("node") || 0 == words[1].compare ("n")) {
			if (words.size () <= 2) {
				std::cout << "usage: skeleton node <index>" << std::endl;
				return true;
			}
			int index = std::strtol (words[2].c_str(), nullptr, 10);
			if (index < 0) {
				_node_index = -1;
			} else {
				_node_index = index % skeleton._nodes.size ();
			}
			_frame_index = -1;
		} else if (0 == words[1].compare ("frame") || 0 == words[1].compare ("f")) {
			if (_node_index < 0) {
				Error ("no node selected");
				return true;
			}
			if (words.size () <= 2) {
				std::cout << "usage: skeleton frame <index>" << std::endl;
				return true;
			}
			int index = std::strtol (words[2].c_str(), nullptr, 10);
			if (index < 0) {
				_frame_index = -1;
			} else {
				if (_is_rotation_frame) {
					_frame_index = index % skeleton._nodes[_node_index].rot_frames.size ();
				} else {
					_frame_index = index % skeleton._translation_frames.size ();
				}
			}
		} else if (0 == words[1].compare ("set")) {
			if (words.size () <= 2 + 3) {
				std::cout << "usage: skeleton set self_origin <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set parent_origin <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set scale <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set rot <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set rotaxis <axis_x> <axis_y> <axis_z> <angle>" << std::endl;
				return true;
			}
			if (0 == words[2].compare ("self_origin")) {
				ftm::vec3	value (std::strtof (words[3].c_str(), nullptr), std::strtof (words[4].c_str(), nullptr), std::strtof (words[5].c_str(), nullptr));

				if (_node_index >= 0) {
					skeleton._nodes[_node_index].self_origin = value;
				} else {
					Error ("no node selected");
				}
			} else if (0 == words[2].compare ("parent_origin")) {
				ftm::vec3	value (std::strtof (words[3].c_str(), nullptr), std::strtof (words[4].c_str(), nullptr), std::strtof (words[5].c_str(), nullptr));

				if (_node_index >= 0) {
					skeleton._nodes[_node_index].parent_origin = value;
				} else {
					Error ("no node selected");
				}
			} else if (0 == words[2].compare ("scale")) {
				ftm::vec3	value (std::strtof (words[3].c_str(), nullptr), std::strtof (words[4].c_str(), nullptr), std::strtof (words[5].c_str(), nullptr));

				if (_node_index >= 0) {
					skeleton._nodes[_node_index].scale = value;
				} else {
					Error ("no node selected");
				}
			} else if (0 == words[2].compare ("rot")) {
				float angle_x = ftm::radians (std::strtof (words[3].c_str(), nullptr));
				float angle_y = ftm::radians (std::strtof (words[4].c_str(), nullptr));
				float angle_z = ftm::radians (std::strtof (words[5].c_str(), nullptr));

				if (_node_index >= 0 && _frame_index >= 0) {
					struct RotationFrame	&frame = skeleton._nodes[_node_index].rot_frames[_frame_index];
					ftm::quat	quat;

					quat = ftm::angleAxis (angle_x, ftm::vec3 (0, 1, 0)) * ftm::angleAxis (angle_y, ftm::vec3 (1, 0, 0)) * ftm::angleAxis (angle_z, ftm::vec3 (0, 0, 1));
					frame.axis = ftm::axis (quat);
					frame.angle = ftm::angle (quat);
				} else {
					Error ("no node or frame selected");
				}
			} else if (0 == words[2].compare ("rotaxis")) {
				float axis_x = std::strtof (words[3].c_str(), nullptr);
				float axis_y = std::strtof (words[4].c_str(), nullptr);
				float axis_z = std::strtof (words[5].c_str(), nullptr);
				float angle = std::strtof (words[6].c_str(), nullptr);

				if (_node_index >= 0 && _frame_index >= 0) {
					RotationFrame	&frame = skeleton._nodes[_node_index].rot_frames[_frame_index];
					frame.axis = ftm::vec3 (axis_x, axis_y, axis_z);
					frame.angle = angle;
				} else {
					Error ("no node or frame selected");
				}
			} else {
				std::cout << "usage: skeleton set self_origin <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set parent_origin <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set scale <x> <y> <z>" << std::endl;
				std::cout << "usage: skeleton set rot <x> <y> <z>" << std::endl;
				return true;
			}
		} else if (0 == words[1].compare ("clear")) {
			if (words.size () <= 2) {
				std::cout << "usage: skeleton clear frames" << std::endl;
				return true;
			}
			if (0 == words[2].compare ("frames")) {
				_frame_index = -1;
				for (auto &node : skeleton._nodes) {
					node.rot_frames.clear ();
				}
			}
		} else {
			Error ("unknown '%s' skeleton's command", words[1].c_str ());
			sk_help ();
		}
	} else if (0 == words[0].compare ("new_transl") || 0 == words[0].compare ("newtf")) {
		if (words.size () <= 1) {
			std::cout << "usage: newtf <start_time>" << std::endl;
			return true;
		}
		float	start_time = std::strtof (words[1].c_str(), nullptr);
		std::vector<TranslationFrame>	&frames = skeleton._translation_frames;
		frames.push_back ({ start_time, ftm::vec3 (0, 0, 0)});
		_frame_index = frames.size () - 1;
		std::sort (frames.begin (), frames.end (), [](const TranslationFrame &left, const TranslationFrame &right) { return left.time < right.time; });
		for (size_t index = 0; index < frames.size (); index += 1) {
			if (frames[index].time == start_time) {
				_frame_index = index;
				break ;
			}
		}
		skeleton.RecalcAnimationDuration ();
	}
	else {
		std::cout << "Unknown command." << std::endl;
	}
	return true;
}

void	Console::update (struct Input &input, float delta) {
	if (input.select_node) {
		if (_node_index + input.select_node >= 0) {
			_node_index += input.select_node;
			_node_index %= skeleton._nodes.size ();
			Debug ("node index: %d", _node_index);
			_frame_index = -1;
		} else {
			_node_index = -1;
		}
	}
	if (input.select_frame && _node_index >= 0) {
		if (_is_rotation_frame != input.is_rotation_frame) {
			_frame_index = -1;
			_is_rotation_frame = input.is_rotation_frame;
			if (input.is_rotation_frame)
				Debug("Rotation mode applied");
			else
				Debug("Translation mode applied");
		}
		if (_frame_index + input.select_frame >= 0) {
			_frame_index += input.select_frame;
			if (skeleton._nodes[_node_index].rot_frames.size () && _is_rotation_frame) {
				_frame_index %= skeleton._nodes[_node_index].rot_frames.size ();
			}
			else if (skeleton._translation_frames.size() && !_is_rotation_frame) {
				_frame_index %= skeleton._translation_frames.size();
			}
			else {
				_frame_index = -1;
			}
			Debug ("frame index: %d", _frame_index);
		} else {
			_frame_index = -1;
		}
	}
	if (_node_index >= 0 && _node_index < (int) skeleton._nodes.size ()) {
		skeleton.HighlightNode (_node_index);
		skeleton.ChangeNodeSize(_node_index, input.scale_delta);
		skeleton.ChangeNodeColor(_node_index, input.color_delta);
		if (_frame_index >= 0 && input.is_rotation_frame) {
			skeleton.RotateNodeFrame(_node_index, _frame_index, input.rotate_euler);
		}
		if (_frame_index >= 0 && !input.is_rotation_frame) {
			skeleton.TranslateFrame(_frame_index, input.translate);
		}
		static bool old_is_parent_origin = input.is_parent_origin;
		if (old_is_parent_origin != input.is_parent_origin) {
			if (input.is_parent_origin) {
				std::cout << "self origin: " << skeleton._nodes[_node_index].self_origin << std::endl;
				std::cout << "switched to parent origin" << std::endl;
				std::cout << "parent origin: " << skeleton._nodes[_node_index].parent_origin << std::endl;
			} else {
				std::cout << "parent origin: " << skeleton._nodes[_node_index].parent_origin << std::endl;
				std::cout << "switched to self origin" << std::endl;
				std::cout << "self origin: " << skeleton._nodes[_node_index].self_origin << std::endl;
			}
			old_is_parent_origin = input.is_parent_origin;
		}
		if (input.is_parent_origin) {
			skeleton._nodes[_node_index].parent_origin += input.origin_delta * 0.1f;
		} else {
			skeleton._nodes[_node_index].self_origin += input.origin_delta * 0.1f;
		}
	} else {
		skeleton.HighlightNode (-1);
	}
	if (!input.animate) {
		skeleton.Animate(delta);
	} else {
		if (_node_index >= 0 && _frame_index >= 0) {
			if (_is_rotation_frame) {
				skeleton.SetAnimationTime (skeleton._nodes[_node_index].rot_frames[_frame_index].time);
			}
			else {
				skeleton.SetAnimationTime(skeleton._translation_frames[_frame_index].time);
			}
			skeleton.Animate(0);
		}
	}
}
