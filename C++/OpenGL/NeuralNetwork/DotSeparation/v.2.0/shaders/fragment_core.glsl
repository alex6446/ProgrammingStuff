#version 440

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D texture0;

layout(std430, binding = 0) buffer FLOWERS {
    float flowers[];
};

uniform vec2 resolution;

void main () {

	vec4 bg_color = texture(texture0, vs_texcoord);
	fs_color = bg_color;

	vec3 green_color = vec3(0.0196f, 0.6745, 0.447);
	vec3 blue_color = vec3(0.18f, 0.4353f, 0.8196f);

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
}