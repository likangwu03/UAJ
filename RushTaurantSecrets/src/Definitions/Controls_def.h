#pragma once
#include <cstdint>
#include <vector>
#include <string>
using namespace std;
namespace _ecs {
	enum ControlsType {
		xbox_X,
		xbox_A,
		xbox_Y,
		xbox_B,
		xbox_LS,
		xbox_RS,

		play_Triangule,
		play_Circle,
		play_Cross,
		play_Rectangle,
		play_LS,
		play_RS,

		key_Q,
		key_E,
		key_Z,
		key_V,
		key_C,

		key_LEFT,
		key_RIGHT,

		key_SPACE,
		key_ENTER,
		key_ESC,
		
		CONTROLS_NUM
	};
	struct ControlsTextureInfo {
		string textureName;
		int col;
		int fil;
	};
	static ControlsTextureInfo Controls[CONTROLS_NUM]{
		{"XBOX_KEYS",3,2},
		{"XBOX_KEYS",3,3},
		{"XBOX_KEYS",3,4},
		{"XBOX_KEYS",3,5},
		{"XBOX_KEYS",21,5},
		{"XBOX_KEYS",21,6},

		{"PLAYSTATION_KEYS",3,2},
		{"PLAYSTATION_KEYS",3,3},
		{"PLAYSTATION_KEYS",3,4},
		{"PLAYSTATION_KEYS",3,5},
		{"PLAYSTATION_KEYS",21,5},
		{"PLAYSTATION_KEYS",21,6},

		{"KEYBOARD_KEYS",0,4},
		{"KEYBOARD_KEYS",4,2},
		{"KEYBOARD_KEYS",1,5},
		{"KEYBOARD_KEYS",5,4},
		{"KEYBOARD_KEYS",2,2},
		
		{"KEYBOARD_KEYS",2,0},
		{"KEYBOARD_KEYS",3,0},

		{"KEYBOARD_KEYS_2",2,2},
		{"KEYBOARD_KEYS_2",3,1},
		{"KEYBOARD_KEYS_2",1,0},
	};
}
