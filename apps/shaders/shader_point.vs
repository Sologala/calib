#version 330 core
 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aIntensity;
 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
out vec3 ourColor;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    float height = smoothstep(-10.0, 10.0, aPos.z);
    ourColor = vec3(height, 0.5f, 0.5f);
}
