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

int getIndex (int x, int y) {
	return  x * int(gridsize.y) + y;
}

vec3 getColor (int index) {
	if (regions[index] < 0.5f) return vec3(0.18f, 0.4353f, 0.8196f);
	else return vec3(0.0196f, 0.6745, 0.447);
}

void main () {
	//vec2 st = gl_FragCoord.xy/vec2(640.f, 480.f);
	vec3 green_color = vec3(0.0196f, 0.6745, 0.447);
	vec3 blue_color = vec3(0.18f, 0.4353f, 0.8196f);

	vec3 bg_color = blue_color;

	int bg_cord_x = int(gl_FragCoord.x / step.x);
	int bg_cord_y = int((resolution.y - gl_FragCoord.y) / step.y);
	int index = getIndex(bg_cord_x, bg_cord_y);

	bg_color = getColor(index);
	
	float dist_up = (resolution.y - gl_FragCoord.y) - bg_cord_y * step.y;
	float dist_down = step.y - dist_up;
	float dist_left = gl_FragCoord.x - bg_cord_x * step.x;
	float dist_right = step.x - dist_left;

	/* float dist_upleft = length(vec2(dist_up, dist_left));
	float dist_upright = length(vec2(dist_up, dist_right));
	float dist_downleft = length(vec2(dist_down, dist_left));
	float dist_downright = length(vec2(dist_down, dist_right));
 */
	vec3 blend_color = vec3(0.f);

	if (bg_cord_x - 1 >= 0) blend_color += getColor(getIndex(bg_cord_x - 1, bg_cord_y)) * (1.f - dist_left / step.x);
	if (bg_cord_x + 1 < int(gridsize.x)) blend_color += getColor(getIndex(bg_cord_x + 1, bg_cord_y)) * (1.f - dist_right / step.x);
	if (bg_cord_y - 1 >= 0) blend_color += getColor(getIndex(bg_cord_x, bg_cord_y - 1)) * (1.f - dist_up / step.y);
	if (bg_cord_y + 1 < int(gridsize.y)) blend_color += getColor(getIndex(bg_cord_x, bg_cord_y + 1)) * (1.f - dist_down / step.y);
	
	/* float divider = length(step);
	float divider_upleft = divider;
	float divider_upright = divider;
	float divider_downleft = divider;
	float divider_downright = divider;

	float glob_tan = step.y / step.x;

	if (dist_up / dist_left < glob_tan) {
		divider_upleft = step.x * dist_upleft / dist_left;
	} else if (dist_up / dist_left > glob_tan) {
		divider_upleft = step.y * dist_upleft / dist_up;
	}

	if (dist_up / dist_right < glob_tan) {
		divider_upright = step.x * dist_upright / dist_right;
	} else if (dist_up / dist_right > glob_tan) {
		divider_upright = step.y * dist_upright / dist_up;
	}

	if (dist_down / dist_left < glob_tan) {
		divider_downleft = step.x * dist_downleft / dist_left;
	} else if (dist_down / dist_left < glob_tan) {
		divider_downleft = step.y * dist_downleft / dist_down;
	}

	if (dist_down / dist_right < glob_tan) {
		divider_downright = step.x * dist_downright / dist_right;
	} else if (dist_down / dist_right > glob_tan) {
		divider_downright = step.y * dist_downright / dist_down;
	}
 */
	//if (bg_cord_x - 1 >= 0 && bg_cord_y - 1 >= 0) 
	//	blend_color += getColor(getIndex(bg_cord_x - 1, bg_cord_y - 1)) * (1.f - dist_upleft / divider_upleft);
	//if (bg_cord_x + 1 < int(gridsize.x) && bg_cord_y - 1 >= 0) 
	//	blend_color += getColor(getIndex(bg_cord_x + 1, bg_cord_y - 1)) * (1.f - dist_upright / divider_upright);
	//if (bg_cord_y + 1 < int(gridsize.y) && bg_cord_x - 1 >= 0) 
	//	blend_color += getColor(getIndex(bg_cord_x - 1, bg_cord_y + 1)) * (1.f - dist_downleft / divider_downleft);
	//if (bg_cord_y + 1 < int(gridsize.y) && bg_cord_x + 1 < int(gridsize.x)) 
	//	blend_color += getColor(getIndex(bg_cord_x + 1, bg_cord_y + 1)) * (1.f - dist_downright / divider_downright);

	bg_color += blend_color;
	bg_color *= 0.25f;

	fs_color = vec4(bg_color, 1.f);

	float distance;
	for (int i = 0; i < flowers.length(); i+=4) {
		distance = length(vec2(gl_FragCoord.x, resolution.y - gl_FragCoord.y) - vec2(flowers[i], flowers[i+1]));
		if (distance < 12.f) {
			if (flowers[i+2] == 0)
				fs_color = vec4(blue_color, 1.f);  
			else
				fs_color = vec4(green_color, 1.f);  
			if (distance > 8.f)
				fs_color *= vec4(bg_color, 1.f); + vec4(vec3(0.2f), 1.f);

		}
	}

	if (regions[0] == 0.5f)
		fs_color = vec4(0.f);
}