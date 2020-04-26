#version 440
in vec3 vs_position;
in vec3 vs_color;

out vec4 fs_color;

layout(std430, binding = 0) buffer FLOWERS {
    float flowers[];
};

uniform vec2 step;
uniform vec2 resolution;

const int rsize = 1000;
uniform float regions[rsize];


uniform vec2 gridsize;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

void main () {
	//vec2 st = gl_FragCoord.xy/vec2(640.f, 480.f);
	vec3 green_color = vec3(0.0196f, 0.6745, 0.447);
	vec3 blue_color = vec3(0.18f, 0.4353f, 0.8196f);

	vec4 bg_color = vec4(blue_color, 1.f);
	vec2 bg_cord;
	bg_cord.x = gl_FragCoord.x / step.x;
	bg_cord.y = (resolution.y - gl_FragCoord.y) / step.y;
	//float index = bg_cord.y * gridsize.x + bg_cord.x;
	highp int index = int(int(bg_cord.x) * int(gridsize.y) + int(bg_cord.y));
	

	if (regions[index] < 0.5f)
		bg_color = vec4(blue_color, 1.f);
	else
		bg_color = vec4(green_color, 1.f);

	fs_color = bg_color;

	float distance;
	for (int i = 0; i < flowers.length(); i+=4) {
		distance = length(vec2(gl_FragCoord.x, resolution.y - gl_FragCoord.y) - vec2(flowers[i], flowers[i+1]));
		if (distance < 12.f) {
			if (flowers[i+2] == 0)
				fs_color = vec4(blue_color, 1.f);  
			else
				fs_color = vec4(green_color, 1.f);  
			if (distance > 8.f)
				fs_color *= bg_color + vec4(vec3(0.2f), 1.f);

		}
	}

	if (regions[0] == 0.5f)
		fs_color = vec4(0.f);
}