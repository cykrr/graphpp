#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 Model, View, Projection, World;

void main() {
  FragPos = vec3(Model * vec4(aPos, 1.0f));
  Normal = vec3(Model * vec4(aNormal, 1.0f));

  gl_Position = Projection * View * Model *
      vec4(FragPos.xyz, 1.0f);
}
