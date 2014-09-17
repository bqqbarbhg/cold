#include "map.h"

namespace cold {

Map::Map(int w, int h, int d)
	: width(w), height(h), depth(d)
{
	data = new unsigned char[w * h * d * Block::size];
	memset(data, 0, w * h * d * Block::size);
}
Map::~Map() {
	delete data;
}
Block *Map::get_block(int x, int y, int z) {
	return reinterpret_cast<Block*>(data + x + y * width + z * width * height);
}
const Block *Map::get_block_const(int x, int y, int z) const {
	return reinterpret_cast<const Block*>(data + x + y * width + z * width * height);
}

void Map::push_update(Block *b) {
	update_queue.push(b);
}

void Map::update_block(Block *b) {
}

bool Map::next_update() {
	if (!update_queue.size())
		return false;
	update_block(update_queue.front());
	update_queue.pop();
	return true;
}

}