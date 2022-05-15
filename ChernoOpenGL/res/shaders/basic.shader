#shader vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 v_uv;

void main()
{
   gl_Position = position;
   v_uv = uv;
}

#shader fragment

#version 330 core

in vec2 v_uv;

out vec4 color;

uniform vec4 uColor;
uniform sampler2D uTex;

void main()
{
	color = texture(uTex, v_uv);
}