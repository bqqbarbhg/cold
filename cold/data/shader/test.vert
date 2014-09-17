uniform mat4 WVP;

varying vec4 color;

void main() {
	gl_Position = WVP * gl_Vertex;
	color = gl_Color;
}