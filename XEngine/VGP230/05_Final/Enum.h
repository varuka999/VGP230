#pragma once

enum UnitState : int
{
    UNIT_STATE_INACTIVE = 0,
    UNIT_STATE_MOVING,
    UNIT_STATE_WINDUP,
    UNIT_STATE_ATTACKING,
};

enum WallState : int
{
    WALL_STATE_INACTIVE = 0,
    WALL_STATE_INTACT,
    WALL_STATE_DESTROYED,
};

enum UnitEnum : int
{
    INVALID = 0,
    INFANTRY = 1, // Resource cost of unit is equal to its enum value (strange compromise for now)
    FARMER = 3,
    ARCHER = 5,
    SHIELD = 10,
    RAM = 50,
};