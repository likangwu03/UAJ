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

		play_Triangle,
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
		key_R,
		key_X,

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
		float proportion; //width/height
	};
	static ControlsTextureInfo Controls[CONTROLS_NUM]{
		{"XBOX_KEYS",3,2,1},
		{"XBOX_KEYS",3,3,1},
		{"XBOX_KEYS",3,4,1},
		{"XBOX_KEYS",3,5,1},
		{"XBOX_KEYS",21,5,1},
		{"XBOX_KEYS",21,6,1},

		{"PLAYSTATION_KEYS",3,2,1},
		{"PLAYSTATION_KEYS",3,3,1},
		{"PLAYSTATION_KEYS",3,4,1},
		{"PLAYSTATION_KEYS",3,5,1},
		{"PLAYSTATION_KEYS",21,5,1},
		{"PLAYSTATION_KEYS",21,6,1},

		{"KEYBOARD_KEYS",0,4,1},
		{"KEYBOARD_KEYS",4,2,1},
		{"KEYBOARD_KEYS",1,5,1},
		{"KEYBOARD_KEYS",5,4,1},
		{"KEYBOARD_KEYS",2,2,1},
		{"KEYBOARD_KEYS",1,4,1},
		{"KEYBOARD_KEYS",7,4,1},
		
		{"KEYBOARD_KEYS",2,0,1},
		{"KEYBOARD_KEYS",3,0,1},

		{"KEYBOARD_KEYS_2",2,2,2},
		{"KEYBOARD_KEYS_2",3,1,2},
		{"KEYBOARD_KEYS_2",1,0,2},
	};
}
