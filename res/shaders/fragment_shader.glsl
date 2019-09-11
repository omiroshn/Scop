#version 400 core

out vec4 out_Colour;

in vec2 pass_textureCoordinates;
in vec3 pass_normal;
in vec3 reflectedVector;
in vec3 refractedVector;

uniform sampler2D TextureSampler;
uniform samplerCube enviroMap;

// uniform vec3 lightPos;
// uniform vec3 cameraPos;

const vec3 lightDirection = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.3;

// in vec2 TexCoord;
// in vec3 Normal;
// in vec3 FragPos;
// in vec3 reflectedVector;

void main()
{
	// float brightness = max(dot(-lightDirection, normalize(pass_normal)), 0.0) + ambient;
	// out_Colour = texture(TextureSampler, pass_textureCoordinates) * brightness;
	out_Colour = texture(TextureSampler, pass_textureCoordinates);
	
	vec4 reflectedColour = texture(enviroMap, reflectedVector);
	// vec4 refractedColour = texture(enviroMap, refractedVector);
	// vec4 enviroColour = mix(reflectedColour, refractedColour, 0.5);

	// out_Colour = mix(out_Colour, enviroColour, 1.0);


	// vec4 texColor = texture(TextureSampler, TexCoord);
	
	// float ambientStrength = 0.2;
	// vec3 lightColor = vec3(1.0,1.0,1.0);
	// vec3 ambient = ambientStrength * lightColor;

	// vec3 norm = normalize(Normal);
	// vec3 lightDir = normalize(lightPos - FragPos);

	// vec3 viewDir = normalize(cameraPos - FragPos);
	// vec3 reflectDir = reflect(-lightDir, norm);

	// float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = diff * lightColor;

	// float specularStrength = 0.3;
	// float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	// vec3 specular = specularStrength * spec * lightColor;

	// vec3 result = (ambient + diffuse) * texColor.xyz;
	// color = vec4(result, 1.0);

	// vec4 reflectedColor = texture(enviroMap, reflectedVector);
	// color = mix(color, reflectedColor, 0.6);

	// // color = vec4(Normal, 1.0);

	// //grey
	// float grey = (Normal.x + Normal.y+ Normal.z) / 3.0;
	// vec3 g = vec3(grey, grey, grey);
	// // color = vec4(g, 1.0);
}
