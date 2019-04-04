#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 in_color;

out vec4 vColor;

void main() {
    gl_Position = position;
    vColor = in_color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 vColor;

uniform vec4 u_Color;

void main() {
    color = vColor;
}