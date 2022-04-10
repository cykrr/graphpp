#version 330 core
/* world coordinates (xyz)*/
layout (location = 0) in vec3 aPos; 

uniform mat4 Model, View, Projection;

void main() {
    gl_Position = Model * vec4(aPos.xyz, 1.0f);
}
