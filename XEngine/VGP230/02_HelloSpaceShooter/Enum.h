#pragma once

enum EntityType : int
{
	ET_ALL = -1,				// 1111 1111
	ET_NONE = 0,				// 0000 0000
	ET_SHIP = 1 << 0,			// 0000 0001 Value 1 pushed over to the 0 index (bit)
	ET_BULLET_PLAYER = 1 << 1,	// 0000 0010 Value 1 pushed over to the 1 index (bit)
	ET_BULLET_ENEMY = 1 << 2,	// 0000 0100 Value 1 pushed over to the 2 index (bit)
	ET_ENEMY = 1 << 3,			// 0000 1000 Value 1 pushed over to the 3 index (bit)
};

enum class State
{
	Start,
	RunGame,
	End,
};

// enum => ET_NONE
// enum class => State::Start

// int val = ET_ALL; OK
// int val = State::Start; NOT OK
// int val = (int)State:Start; OK