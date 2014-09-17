#ifndef _COLD_RENDER_SHADER_H
#define _COLD_RENDER_SHADER_H

#include <glm/glm.hpp>
#include <string>
#include <map>

namespace cold {

class Texture;

// Class that holds a shader instance
// Non-copyable except from Shader::Uninitialized
class Shader {
public:
	Shader();
	Shader(const Shader&);
	Shader(Shader&& s);
	~Shader();
	void operator=(Shader&& s);

	// Shader program uniform variable
	struct Uniform {
	public:
		Uniform();
		// Type of an uniform
		enum Type {
			// None
			NONE,
			// float
			FLOAT,
			// glm::vec2
			VEC2,
			// glm::vec3
			VEC3,
			// glm::vec4
			VEC4,
			// glm::mat4
			MAT4,
			// const Texture&
			TEXTURE,
		};
#define _COLD_RENDER_SHADER_H_MACRO(t, s)	operator t&() { return cast<t>(s); } \
				operator const t&() const { return cast_const<t>(s); } \
				Uniform& operator=(const t& w) { cast_set<t>(s) = w; return *this; }
		_COLD_RENDER_SHADER_H_MACRO(float, FLOAT)
		_COLD_RENDER_SHADER_H_MACRO(glm::vec2, VEC2)
		_COLD_RENDER_SHADER_H_MACRO(glm::vec3, VEC3)
		_COLD_RENDER_SHADER_H_MACRO(glm::vec4, VEC4)
		_COLD_RENDER_SHADER_H_MACRO(glm::mat4, MAT4)
		Uniform& operator=(const Texture& w);
	private:
		friend class Shader;
		template <typename T>
		T& cast(Type t);
		template <typename T>
		const T& cast_const(Type t) const;
		template <typename T>
		T& cast_set(Type t);
		template <typename T>
		T& get();
		void apply();
#undef _COLD_RENDER_SHADER_H_MACRO
#define _COLD_RENDER_SHADER_H_MACRO(a, b) ((sizeof(a)>(b))?sizeof(a):(b))
		char data[
		_COLD_RENDER_SHADER_H_MACRO(	float,
		_COLD_RENDER_SHADER_H_MACRO(	glm::vec2,
		_COLD_RENDER_SHADER_H_MACRO(	glm::vec3,
		_COLD_RENDER_SHADER_H_MACRO(	glm::vec4,
		_COLD_RENDER_SHADER_H_MACRO(	glm::mat4,
		_COLD_RENDER_SHADER_H_MACRO(	unsigned int,
		sizeof(char)))))))
		];
	private:
		Type type;
		bool dirty;
		int loc;
	};

	// Compiles the shaders from two sources
	// vert_source: Source code to the vertex shader
	// frag_source: Source code to the fragment shader
	void compile(const std::string& vert_source, const std::string& frag_source);

	// Compiles the shaders from two files
	// vert_file: Filename to compile the vertex shader from
	// frag_file: Filename to compile the fragment shader from
	void compile_file(const char* vert_file, const char* frag_file);

	// Applies the shader to the current render state
	void apply();

	// Applies the shader to the current render state
	// Fails if some shader uniforms are changed
	void apply_const() const;
	
	// Returns the amount of uniform variables _used_ by the shaders
	int get_uniform_count() const;

	// Returns the name of the uniform variable at `index`
	// index: Index of the uniform to get
	std::string get_uniform_name(int index) const;

	// Uniforms used by the vertex and fragment shaders
	std::map<std::string, Uniform> uniforms;

	static Shader Uninitialized;

private:
	Shader& operator=(const Shader&);
	friend struct Uniform;
	Shader(unsigned int p, unsigned int v, unsigned int f);
	void shader_compile(unsigned int shader, const std::string& src);
	unsigned int gl_program, gl_vertex_shader, gl_fragment_shader;
};

}

#undef _COLD_RENDER_SHADER_H_MACRO
#endif