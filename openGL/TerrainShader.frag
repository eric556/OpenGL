#version 330 core
out vec4 color;

in vec3 pos;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 white = vec3(1.0f,1.0f,1.0f);
	vec3 green = vec3(0.2f,0.8f,0.2f);
	vec3 grey = vec3(0.4f,0.4f,0.4f);
	vec3 blue = vec3(0.18f,0.71f,0.96f);

	 // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 0.9f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
        
    vec3 finalLightCalc = (ambient + diffuse + specular);

	if(pos.y > 400){
		color = vec4(white * finalLightCalc,1.0f);
	} else if( pos.y <= 400 && pos.y > 200){
		color = vec4(grey * finalLightCalc,1.0f);
	}else if ( pos.y <= 200 && pos.y > 50){
		color = vec4(green * finalLightCalc,1.0f);
	}else{
		color = vec4(blue * finalLightCalc,1.0f);
	}

	//vec3 posNormalized = normalize(pos)
	//color = vec4(pos.x/255,pos.y/255, pos.z/255,1.0f);
	
}