#version 400 core

layout(vertices = 1) out;

//PatchSize = PATCH_SIZE in context
in vec3 position_TCS_in[];

// TCS's Output
out patch vec3 position_TES_in[4];

uniform float tessLevelOuter0;

void main() {
	// 设置isoline的细分等级
	gl_TessLevelOuter[0] = tessLevelOuter0;
	gl_TessLevelOuter[1] = 1;
	// 顶点位置赋值
	position_TES_in[0] = position_TCS_in[0];
	position_TES_in[1] = position_TCS_in[0] + vec3(0.0, 1.0, 0.0);
	position_TES_in[2] = position_TCS_in[1] + vec3(0.0, 1.0, 0.0);
	position_TES_in[3] = position_TCS_in[1];
}
	