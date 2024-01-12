#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color; // Color uniform

void main()
{
    vec4 texColor = texture(u_Texture, TexCoord);

    // Blend the color if it is set
    FragColor = texColor * (u_Color != vec4(0.0) ? u_Color : vec4(1.0));
}