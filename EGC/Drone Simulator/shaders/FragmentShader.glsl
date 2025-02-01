#version 330

// Input
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

// 2D Noise Function (based on Morgan McGuire)
float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // smooth interpolation
    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

float make_it_smoother(float edge0, float edge1, float value) {
    value = clamp((value - edge0) / (edge1 - edge0), 0.0, 1.0);
    return value * value * (3.0 - 2.0 * value);
}


void main() {
    vec3 color1 = frag_color;
	vec3 color2 = vec3(0.364, 0.533, 0.239);

    float noiseValue = noise(frag_position.xz * 0.1);
    float mixFactor = make_it_smoother(0.3, 0.7, noiseValue);
    vec3 result_color = mix(color1, color2, mixFactor);

    out_color = vec4(result_color, 1.0);
    out_normal = vec4(normalize(frag_normal), 1.0);
    out_texture = vec3(frag_texture, 1.0);
}
