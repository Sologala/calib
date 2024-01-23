#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
layout (location = 0) in vec3 aColor;

uniform mat4 pvm;
out vec4 oAxisColor; // 向片段着色器输出一个颜色

void main()
{
    gl_Position = pvm * vec4(aPos, 1.0);
    oAxisColor = vec4(aColor, 1.0); // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}
