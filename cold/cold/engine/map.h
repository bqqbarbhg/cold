#ifndef _COLD_ENGINE_MAP_H
#define _COLD_ENGINE_MAP_H

#include <cold/engine/block.h>
#include <queue>

namespace cold {

class Map {
public:
	Map(int w, int h, int d);
	~Map();
	
	Block *get_block(int x, int y, int z);
	const Block *get_block_const(int x, int y, int z) const;
	void push_update(Block *b);
	bool next_update();
	void update_block(Block *b);

	const int width, height, depth;
private:
	unsigned char* data;
	std::queue<Block*> update_queue;
};

}
#endif