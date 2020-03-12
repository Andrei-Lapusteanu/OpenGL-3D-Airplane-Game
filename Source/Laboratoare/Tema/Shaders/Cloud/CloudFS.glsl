#version 330

layout(location = 0) out vec4 out_color;

uniform vec3 object_color;

void main()
{
    out_color = vec4(object_color, 0.2);
}


