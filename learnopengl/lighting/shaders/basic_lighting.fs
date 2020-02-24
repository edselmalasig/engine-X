#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient color and light intensity multiplier.
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
		// Get the unit vector from the VAP nml vertex attrib
    vec3 norm = normalize(Normal);

		// vector inside normalize function will start from the
		// face of the polygon pointing towards the position of the light source
		// light dir is the unit vector of this. it is normalized so
		// the diffuse is not harshly shaded
    vec3 lightDir = normalize(lightPos - FragPos);
		// vector projection diffuse must have the max angle data that makes our 3d
		// object have a sense of depth not just dimensions that is shaded
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

		FragColor = vec4(result, 1.0);
		//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
