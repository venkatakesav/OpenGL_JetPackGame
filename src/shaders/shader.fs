#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform int jet_main;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    float center = distance(TexCoord, vec2(0.5, 0.5));
    if(texColor.a < 0.1)
        if(jet_main == 0){
            discard;
        }
        else{
            texColor = mix(vec4(1.0, 0.7, 0.0, 1.0), texColor, smoothstep(0.4, 0.6, center));
        }
    FragColor = texColor;
}