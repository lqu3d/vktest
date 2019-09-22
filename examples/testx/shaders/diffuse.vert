
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;
layout(location = 0) out vec4 ocolor;

layout(std140, binding = 0) uniform bufferVal{
	mat4 mvp;
}myBuffVals;

void main(){
	ocolor = color;
	gl_Position = myBuffVals.mvp * pos;
}
