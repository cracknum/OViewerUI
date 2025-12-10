#version 440 core

out vec4 fragColor;
void main()
{
    fragColor = vec4(
        clamp((gl_Position[0] + 1.0f), 0.0f, 1.0f), 
        clamp((gl_Position[1] + 1.0f), 0.0f, 1.0f),
        clamp((gl_Position[2] + 1.0f), 0.0f, 1.0f),
         1.0f
    );
}