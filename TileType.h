#ifndef TILETYPE_H
#define TILETYPE_H

enum class TileType {
    Empty,  // Default walkable tile
    Wall,   // Needs 2 hits to be destroyed
    Mine //,   // Destroys tank on contact
    // Tank,   // Tile occupied by a tank (can be handled dynamically)
    // Spawn1, // Initial position of player 1's tank
    // Spawn2  // Initial position of player 2's tank
};

#endif // TILETYPE_H