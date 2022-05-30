#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 Projection, View;
out vec3 nearPoint, farPoint;

vec3 unprojectPoint(vec2 vec, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(vec.xy, z, 1.0);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}


void main() {
    nearPoint = unprojectPoint(aPos.xy, 0.f, View, Projection);
    farPoint = unprojectPoint(aPos.xy, 1.f, View, Projection);
    gl_Position  = vec4(aPos.xyz, 1.0f);
}
