#include "shader.h"
#include <glm/ext.hpp>
#include <cold/render/impl/gl.h>
#include <cold/platform/io.h>
#include <cold/platform/os.h>
#include <cold/util/assert.h>
#include <cold/render/texture.h>
#include <cold/resource/load_info.h>
#include <cold/resource/resource.h>
#include <cold/resource/resource_loader.h>
#include <cold/render/impl/debug.h>

namespace cold {

Shader Shader::Uninitialized = Shader(0, 0, 0);

Shader::Shader()
{
	gl_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	gl_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	gl_program = glCreateProgram();
}
Shader::Shader(const Shader& s)
	: gl_program(0)
	, gl_vertex_shader(0)
	, gl_fragment_shader(0)
{
	COLD_DEBUG_ASSERT(&s == &Uninitialized);
}
Shader::Shader(Shader&& s)
	: gl_program(s.gl_program)
	, gl_vertex_shader(s.gl_vertex_shader)
	, gl_fragment_shader(s.gl_fragment_shader)
{
	s.gl_program = s.gl_vertex_shader = s.gl_fragment_shader = 0;
}
Shader::Shader(unsigned int p, unsigned int v, unsigned int f)
	: gl_program(p), gl_vertex_shader(v), gl_fragment_shader(f)
{
}

void Shader::operator=(Shader&& s) {
	COLD_DEBUG_ASSERT(gl_vertex_shader == 0 && gl_fragment_shader == 0 && gl_program == 0);
	gl_vertex_shader = s.gl_vertex_shader;
	gl_fragment_shader = s.gl_fragment_shader;
	gl_program = s.gl_program;
	s.gl_vertex_shader = 0;
	s.gl_fragment_shader = 0;
	s.gl_program = 0;
}

Shader::~Shader() {
	if (gl_program) {
		if (gl_vertex_shader) glDetachShader(gl_program, gl_vertex_shader);
		if (gl_fragment_shader) glDetachShader(gl_program, gl_fragment_shader);
		glDeleteProgram(gl_program);
	}
	if (gl_vertex_shader) glDeleteShader(gl_vertex_shader);
	if (gl_fragment_shader) glDeleteShader(gl_fragment_shader);
}
void Shader::shader_compile(unsigned int shader, const std::string& src) {
	const GLchar *str = src.c_str();
	const GLint len = src.size();
	glShaderSource(shader, 1, &str, &len);
	glCompileShader(shader);
	glAttachShader(gl_program, shader);
}
void Shader::compile_file(const char* vert, const char* frag) {
	compile(
		read_file_string(vert),
		read_file_string(frag));
}
void Shader::compile(const std::string& vert, const std::string& frag) { COLD_RENDER_DEBUG
	COLD_DEBUG_ASSERT(gl_vertex_shader != 0 && gl_fragment_shader != 0 && gl_program != 0);
	shader_compile(gl_vertex_shader, vert); COLD_RENDER_CHECK
	shader_compile(gl_fragment_shader, frag); COLD_RENDER_CHECK
	glLinkProgram(gl_program); COLD_RENDER_CHECK

#if defined(_DEBUG) && 0
/*
	int size;
	char text[256];

	glGetInfoLogARB(gl_program, 256, &size, text);
	if (*text) {
		os::message_box("Shader compiler error", text, os::MBOX_ERROR);
	}
	*/
#endif
}
void Shader::apply() {
	COLD_DEBUG_ASSERT(gl_vertex_shader != 0 && gl_fragment_shader != 0 && gl_program != 0);
	glUseProgram(gl_program);
	for (std::map<std::string, Uniform>::iterator it = uniforms.begin(); it != uniforms.end(); ++it) {
		if (it->second.dirty) {
			if (it->second.loc == -2) {
				it->second.loc = glGetUniformLocation(gl_program, it->first.c_str());
			}
			it->second.apply();
		}
	}
}
void Shader::apply_const() const {
	COLD_DEBUG_ASSERT(gl_vertex_shader != 0 && gl_fragment_shader != 0 && gl_program != 0);
#ifdef _DEBUG
	for (std::map<std::string, Uniform>::const_iterator it = uniforms.cbegin(); it != uniforms.cend(); ++it) {
		COLD_ASSERT(!it->second.dirty);
	}
#endif
	glUseProgram(gl_program);
}

Shader::Uniform::Uniform()
	: type(NONE), loc(-2)
{
}

int Shader::get_uniform_count() const {
	int i;
	glGetProgramiv(gl_program, GL_ACTIVE_UNIFORMS, &i);
	return i;
}
std::string Shader::get_uniform_name(int index) const {
	char buffer[64];
	int len;
	GLint di;
	GLenum de;
	glGetActiveAttrib(gl_program, index, sizeof(buffer), &len, &di, &de, buffer);
	return std::string(buffer, len);
}

Shader::Uniform& Shader::Uniform::operator=(const Texture& w) {
	COLD_DEBUG_ASSERT(w.gl_texture != 0);
	cast_set<unsigned int>(TEXTURE) = w.gl_texture;
	return *this;
}

template <typename T>
T& Shader::Uniform::cast(Shader::Uniform::Type t) {
	COLD_ASSERT(type == t);
	return *reinterpret_cast<T*>(data);
}
template <typename T>
const T& Shader::Uniform::cast_const(Shader::Uniform::Type t) const {
	COLD_ASSERT(type == t);
	return *reinterpret_cast<const T*>(data);
}
template <typename T>
T& Shader::Uniform::cast_set(Shader::Uniform::Type t) {
	COLD_ASSERT(type == t || type == NONE);
	type = t;
	dirty = true;
	return *reinterpret_cast<T*>(data);
}

template <typename T>
inline T& Shader::Uniform::get() {
	return *reinterpret_cast<T*>(data);
}

void Shader::Uniform::apply() {
	switch (type) {
	case FLOAT:
		glUniform1f(loc, get<float>());
		break;
	case VEC2:
		glUniform2fv(loc, 1, glm::value_ptr(get<glm::vec2>()));
		break;
	case VEC3:
		glUniform3fv(loc, 1, glm::value_ptr(get<glm::vec3>()));
		break;
	case VEC4:
		glUniform4fv(loc, 1, glm::value_ptr(get<glm::vec4>()));
		break;
	case MAT4:
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(get<glm::mat4>()));
		break;
	case TEXTURE:
		glBindTexture(GL_TEXTURE_2D, get<unsigned int>());
		glUniform1i(loc, 0);
		break;
	}
}

template <>
Resource<Shader>* Resource<Shader>::load(const ResourceLoadInfo& info) {
	std::string v, f;
	if (!info.get_arg("vert", v)) return nullptr;
	if (!info.get_arg("frag", f)) return nullptr;
	Shader s;
	s.compile(
		ResourceLoader::get()->load_string(v),
		ResourceLoader::get()->load_string(f));
	return new Resource<Shader>(std::move(s));
}

#define M(t) \
	template t& Shader::Uniform::cast<t>(Shader::Uniform::Type w); \
	template const t& Shader::Uniform::cast_const<t>(Shader::Uniform::Type w) const; \
	template t& Shader::Uniform::cast_set<t>(Shader::Uniform::Type w);

M(float)
M(glm::vec2)
M(glm::vec3)
M(glm::vec4)
M(glm::mat4)
M(unsigned int)

}