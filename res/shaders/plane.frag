#version 330 core
layout (location = 0) out vec4 outColor;
in vec3 nearPoint, farPoint;

float far = 100.0f;
float near = 0.1f;


in mat4 Model;
in mat4 View;
in mat4 Projection;

float depth(vec3 pos){

	vec4 clip_space_pos = 
            Projection * View * Model * vec4(pos.xyz, 1.0);

	return (clip_space_pos.z / clip_space_pos.w);
}

float getLinearDepth(vec3 pos){
	vec4 clip_space_pos = 
            Projection * View * vec4(pos.xyz, 1.0);

	float clip_space_depth = 
            (clip_space_pos.z/ clip_space_pos.w) * 
            2.0f - 1.0f;

	float linear_depth = (2.0f * near * far) / 
            (far + near - clip_space_depth * (far - near));
	return linear_depth / far;
}

vec4 grid(vec3 frag_pos_3d, float scale, float size){
	vec2 coord = frag_pos_3d.xz * scale;
	vec2 derivative = fwidth(coord);
	vec2 grid = abs(fract(coord - 0.5f) - 0.5f) / derivative;
	float line = min(grid.x, grid.y);
	float min_z = min(derivative.y, 1);
	vec4 color;
	float min_x = min(derivative.x, 1);
	if (min(line, size) == size){
		color = vec4(0.03f, 0.03f, 0.03f, 0.8f);
	} else {
		color = vec4(0.2f, 0.2f, 0.2f, 0.8f);
	}

	/* z axis */
	if ( frag_pos_3d.x > -0.1f * min_x && 
			frag_pos_3d.x  < 0.1f * min_x ){
		color.x = 0.0f;
		color.y = 0.0f;
		color.z = 1.0f;
	}

	/* x axis */
	if ( frag_pos_3d.z > -0.1f * min_z && 
			frag_pos_3d.z  < 0.1f * min_z ){
		color.x = 1.0f;
		color.y = 0.0f;
		color.z = 0.0f;
	}

	return color;
}

void main() {
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);

    gl_FragDepth = depth(fragPos3D);

    float linearDepth = getLinearDepth(fragPos3D);
    float fading = max(0, (0.5f - linearDepth));
    
    outColor = ( grid(fragPos3D, 1, 1.0f) + grid(fragPos3D, 10, 0.5f)) * float(t>0);
}
