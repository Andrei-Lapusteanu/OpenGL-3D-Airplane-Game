#version 330

layout(location = 0) in vec2 texture_coord;

uniform sampler2D texture_1;

// Uniforms for light properties
uniform vec3 object_color;
uniform float alpha;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color = texture2D(texture_1, texture_coord);

	if(color.a < 0.5)
		discard;

	out_color = color;
    //out_color = vec4(object_color, alpha);
}