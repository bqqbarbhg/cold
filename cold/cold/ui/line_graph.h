#ifndef _COLD_UI_LINE_GRAPH_H
#define _COLD_UI_LINE_GRAPH_H

#include <cold/ui/control.h>
#include <cold/render/vertex_buffer.h>
#include <cold/render/index_buffer.h>
#include <cold/util/unique_array.h>
#include <cold/resource/handle.h>
#include <cold/render/font.h>
#include <glm/glm.hpp>

namespace cold { namespace ui {

class LineGraph : public Control {
public:
	LineGraph(const Rectangle& bounds, const glm::vec4& color, Handle<Font> f, unsigned int segments, float width);
	virtual void draw(SpriteBatch& sb) const;
	void push(float val);
	float get_min() { return min; }
	float get_max() { return max; }
private:
	void update_graph();
	unsigned int index;
	unsigned int segments;
	static const unsigned int segm_stride, vert_stride;
	float width;
	float min, max;
	float minlen, maxlen;
	unsigned int first;
	char minbuf[40], maxbuf[40];
	UniqueArray<float> vertex_data, value_data;
	IndexBuffer index_buffer;
	Handle<Font> font;
};

} }

#endif