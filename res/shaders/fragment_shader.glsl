#version 400 core

out vec4 out_Colour;

in vec3 reflectedVector;
in vec3 refractedVector;
in vec3 pass_normal;
in vec2 pass_textureCoordinates;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 lightDirection_cameraspace;
in vec3 normal_cameraspace;

uniform sampler2D textureSampler;
uniform samplerCube enviroMap;

uniform vec3 lightPos;
uniform int mode;

const vec3 lightColor = vec3(1.0,1.0,1.0);
const float lightPower = 50.0;
const vec3 materialSpecularColor = vec3(0.3,0.3,0.3);

void main()
{
	if (mode >= 1 && mode <= 2) {
		/* Material properties */
		vec3 materialDiffuseColor = texture(textureSampler, pass_textureCoordinates).rgb;
		vec3 materialAmbientColor = vec3(0.3,0.3,0.3) * materialDiffuseColor;

		/* Normal of the computed fragment, in camera space */
		/* Direction of the light (from the fragment to the light) */
		vec3 n = normalize(normal_cameraspace);
		vec3 l = normalize(lightDirection_cameraspace);
		float cosTheta = clamp(dot(n, l), 0.0, 1.0);

		if (mode == 1)
			out_Colour = vec4(materialDiffuseColor * lightColor * cosTheta + materialAmbientColor, 1.0);
		else if (mode == 2) {
			vec3 eye = normalize(EyeDirection_cameraspace);
			vec3 reflection = (-l) - 2.0 * dot(n, (-l)) * n;
			float cosAlpha = clamp(dot(eye, reflection), 0.0, 1.0);

			/* Distance to the light */
			float distance = length(lightPos - Position_worldspace);
			out_Colour = vec4(vec3(
				materialAmbientColor +
				materialDiffuseColor * lightColor * lightPower * cosTheta / (distance*distance) +
				materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5.0) / (distance*distance)
			), 1.0);
		}
	}  else if (mode >= 3 && mode <= 4) {
		if (mode == 3) {
			vec4 reflectedColour = texture(enviroMap, reflectedVector);
			out_Colour = mix(out_Colour, reflectedColour, 1.0);
		} else if (mode == 4) {
			vec4 reflectedColour = texture(enviroMap, reflectedVector);
			vec4 refractedColour = texture(enviroMap, refractedVector);
			vec4 enviroColour = mix(reflectedColour, refractedColour, 0.5);
			out_Colour = mix(out_Colour, enviroColour, 0.8);
		}
	} else if (mode == 5) { //normal
		out_Colour = vec4(pass_normal, 1.0);
	} else if (mode == 6) { //grey
		float grey = (pass_normal.x + pass_normal.y+ pass_normal.z) / 3.0;
		vec3 g = vec3(grey, grey, grey);
		out_Colour = vec4(g, 1.0);
	}
}