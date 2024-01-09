#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    // Define the size of the checkered pattern (adjust as needed)
    float checkSize = 8.0;

    // Calculate the checkered pattern based on UV coordinates
    ivec2 checkeredCoord = ivec2(TexCoord * checkSize);
    int checker = (checkeredCoord.x + checkeredCoord.y) % 2;

    // Assign colors based on the checkered pattern
    vec3 color1 = vec3(1.0, 1.0, 1.0);  // Color for the first square
    vec3 color2 = vec3(0.0, 0.0, 0.0);  // Color for the second square

    vec3 finalColor = mix(color1, color2, float(checker));

    // Set alpha to 1.0 (fully opaque)
    FragColor = vec4(finalColor, 1.0);
}