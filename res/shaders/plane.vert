#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 Projection, View;
void main() {
    gl_Position  = Projection * View * 
        vec4(aPos.xyz, 1.0f);
}
