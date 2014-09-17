#ifndef _COLD_ENGINE_QUADTREE_H
#define _COLD_ENGINE_QUADTREE_H

#include <set>
#include <cold/engine/bounding_box.h>

namespace cold {

class Scene;
class QuadTree {
	class Node {
		BoundingBox bounds;
	};
	const Scene& scene;
};

}

#endif