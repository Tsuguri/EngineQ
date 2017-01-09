#version 330 core

#include "../Common/Matrices.shh"
#include "../Common/Light.shh"

layout(location = 0) out
vec4 FragColor;

in VS_DATA
{
vec2 textureCoords;
}
IN;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpecular;

uniform sampler2D ssaoTexture;

mat4 invView = inverse(matrices.view);
mat4 invProjection = inverse(matrices.projection);

uniform bool useSSAO;
uniform bool usePCF;
uniform bool useRays;

float DirectionalShadowCalculations(Light light, sampler2D shadowMap, vec3 normal, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;
	
	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	    
	float currentDepth = projCoords.z;
	float bias = max(0.05f * (1.0f - dot(normal, -light.direction)), 0.005f) * 0.1f;
		
	float shadow = 0.0f;
	if (usePCF)
	{
		const float samples = 8.0f;
		vec2 offset = 8.0f / textureSize(shadowMap, 0); //(1.0f + (length(position)/30.0f))/ 25.0f;
		vec2 pcfStep = 2.0f * offset / samples;

		for (float x = -offset.x; x < offset.x; x += pcfStep.x)
		{
			for (float y = -offset.y; y < offset.y; y += pcfStep.y)
			{
				float closestDepth = texture(shadowMap, projCoords.xy + vec2(x, y)).r;
				shadow += (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
			}
		}
		shadow *= 1.0f / (samples * samples);
	}
	else
	{
		float closestDepth = texture(shadowMap, projCoords.xy).r;
		shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
	}
	
	return (projCoords.z <= 1.0f ? 1.0f : 0.0f) * shadow;
}

float PointShadowCalculations(Light light, samplerCube shadowMap, vec3 normal, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;

	vec3 fragToLight = position - light.position;

	float currentDepth = length(fragToLight);
	float bias = max(0.05f * (1.0f - dot(normal, -light.direction)), 0.005f);

	float shadow = 0.0f;
	if (usePCF)
	{
		const float samples = 4.0f;
		float offset = (1.0f + (currentDepth / light.farPlane)) / 25.0f;
		float pcfStep = 2.0f * offset / samples;

		for (float x = -offset; x < offset; x += pcfStep)
		{
			for (float y = -offset; y < offset; y += pcfStep)
			{
				for (float z = -offset; z < offset; z += pcfStep)
				{
					float closestDepth = texture(shadowMap, fragToLight + vec3(x, y, z)).r;
					shadow += (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
				}
			}
		}
		shadow *= 1.0f / (samples * samples * samples);
	}
	else
	{
		float closestDepth = texture(shadowMap, fragToLight).r;
		shadow = (currentDepth - bias > closestDepth) ? 1.0f : 0.0f;
	}

	return shadow;
}

float IsPointInShadow(Light light, sampler2D shadowMap, vec3 position)
{
	if (!light.castsShadows)
		return 0.0f;

	vec4 fragPosLightSpace = light.lightMatrix * vec4(position, 1.0);
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
    
	float currentDepth = projCoords.z;
	const float bias = 0.0005f;

	float projDepth = texture(shadowMap, projCoords.xy).r;
	float shadow = (currentDepth - bias > projDepth) ? 1.0f : 0.0f;
	
	return ((projCoords.z <= 1.0f) ? 1.0f : 0.0f) * shadow;
}

float SamplePoint(Light light, sampler2D shadowMap, vec3 cameraPosition, float cameraFragmentDistance)
{
	const float samples = 32.0f;

	const float minDistance = 0.0f;
	float maxDistance = cameraFragmentDistance;

	float step = (maxDistance - minDistance) / samples;

	vec4 rayPoint = invProjection * vec4(2.0f * IN.textureCoords - 1.0f, 1.0f, 1.0f);
	rayPoint.xyz /= rayPoint.w;
	vec3 direction = normalize(mat3(invView) * rayPoint.xyz);
		
	float shadow = 0.0f;
	for (float currentZ = minDistance; currentZ < maxDistance; currentZ += step)
	{
		vec3 newWorldSpacePosition = cameraPosition + direction * currentZ;

		shadow += IsPointInShadow(light, shadowMap, newWorldSpacePosition);
	}

	return shadow / samples;
}

float CalculateAttenuation(float constantAttenuation, float linearAttenuation, float quadraticAttenuation, float distance)
{
	return (1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance));
}




/*
vec3 projectOnPlane(in vec3 p, in vec3 pc, in vec3 pn)
{
	float distance = dot(pn, p - pc);
	return p - distance * pn;
}
int sideOfPlane(in vec3 p, in vec3 pc, in vec3 pn)
{
	if (dot(p - pc, pn) >= 0.0)
		return 1;
	else
		return 0;
}
vec3 linePlaneIntersect(in vec3 lp, in vec3 lv, in vec3 pc, in vec3 pn)
{
	return lp + lv * (dot(pn, pc - lp) / dot(pn, lv));
}
*/

void AreaRectLight(Light light, vec3 worldSpacePosition, vec3 worldSpaceNormal, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular)
{
	/*
    vec3 viewSpacePosition = (matrices.view * vec4(worldSpacePosition, 1.0f)).xyz;
    vec3 viewSpaceNormal = mat3(transpose(invView)) * worldSpaceNormal;

    vec3 lightPosition = (matrices.view * vec4(light.position, 1.0f)).xyz;
    vec3 lightDirection = (matrices.view * vec4(light.direction, 0.0f)).xyz;

    vec3 right = normalize(vec3(matrices.view * vec4(light.right, 0.0f)));
    vec3 pnormal = normalize(lightDirection);
    vec3 up = normalize(cross(right, pnormal));


    //width and height of the area light:
    float width = 0.5;
    float height = 1.0;

    //project onto plane and calculate direction from center to the projection.
    vec3 projection = projectOnPlane(viewSpacePosition, lightPosition, pnormal); // projection in plane
    vec3 dir = projection - lightPosition;

    //calculate distance from area:
    vec2 diagonal = vec2(dot(dir, right), dot(dir, up));
    vec2 nearest2D = vec2(clamp(diagonal.x, -width, width), clamp(diagonal.y, -height, height));
    vec3 nearestPointInside = lightPosition + (right * nearest2D.x + up * nearest2D.y);

    float dist = distance(viewSpacePosition, nearestPointInside); //real distance to area rectangle

    vec3 L = normalize(nearestPointInside - viewSpacePosition);
    float attenuation = CalculateAttenuation(1.0f, 0.7f, 1.8f, dist);

    float nDotL = dot(pnormal, -L);

    if (nDotL > 0.0 && sideOfPlane(viewSpacePosition, lightPosition, pnormal) == 1) //looking at the plane
    {
        //shoot a ray to calculate specular:
        vec3 R = reflect(normalize(-viewSpacePosition), viewSpaceNormal);
        vec3 E = linePlaneIntersect(viewSpacePosition, R, lightPosition, pnormal);

        float specAngle = dot(R, pnormal);
        if (specAngle > 0.0)
        {
			const float shininess = 1.0f;

            vec3 dirSpec = E - lightPosition;
            vec2 dirSpec2D = vec2(dot(dirSpec, right), dot(dirSpec, up));
            vec2 nearestSpec2D = vec2(clamp(dirSpec2D.x, -width, width), clamp(dirSpec2D.y, -height, height));
            float specFactor = 1.0 - clamp(length(nearestSpec2D - dirSpec2D) * shininess, 0.0, 1.0);
            specular += light.specular * attenuation * specFactor * specAngle;
        }
        diffuse += light.diffuse * attenuation * nDotL;
    }
   
    ambient += light.ambient * attenuation;
	*/







	/*
    vec3 lightPosition = light.position;
    vec3 lightDirection = light.direction;

    vec3 right = normalize(light.right);
    vec3 lightNormal = normalize(lightDirection);
    vec3 up = normalize(cross(right, lightNormal));

    vec3 cameraPosition = invView[3].xyz;



    //width and height of the area light:
    float halfWidth = 0.5f;
    float halfHeight = 1.0f;

    //project onto plane and calculate direction from center to the projection.
    vec3 projection = projectOnPlane(worldSpacePosition, lightPosition, lightNormal); // projection in plane
    vec3 dir = projection - lightPosition;

    //calculate distance from area:
    vec2 diagonal = vec2(dot(dir, right), dot(dir, up));
    vec2 nearest2D = vec2(clamp(diagonal.x, -halfWidth, halfWidth), clamp(diagonal.y, -halfHeight, halfHeight));
    vec3 nearestPointInside = lightPosition + (right * nearest2D.x + up * nearest2D.y);

    float dist = distance(worldSpacePosition, nearestPointInside); //real distance to area rectangle

    float attenuation = CalculateAttenuation(1.0f, 0.7f, 1.8f, dist);

    float nDotL = dot(lightNormal, normalize(worldSpacePosition - nearestPointInside));

    if (nDotL > 0.0 && sideOfPlane(worldSpacePosition, lightPosition, lightNormal) == 1) //looking at the plane
    {
        //shoot a ray to calculate specular:
        vec3 R = reflect(normalize(cameraPosition - worldSpacePosition), worldSpaceNormal);
        vec3 E = linePlaneIntersect(worldSpacePosition, R, lightPosition, lightNormal);

        float specAngle = dot(R, lightNormal);
        if (specAngle > 0.0)
        {
            const float shininess = 2.0f;

            vec3 dirSpec = E - lightPosition;
            vec2 dirSpec2D = vec2(dot(dirSpec, right), dot(dirSpec, up));
            vec2 nearestSpec2D = vec2(clamp(dirSpec2D.x, -halfWidth, halfWidth), clamp(dirSpec2D.y, -halfHeight, halfHeight));
            float specFactor = 1.0 - clamp(length(nearestSpec2D - dirSpec2D) * shininess, 0.0, 1.0);
            specular += light.specular * attenuation * specFactor * specAngle;
        }
    	diffuse += light.diffuse * attenuation * nDotL;
    }
   
    ambient += light.ambient * attenuation;
	*/













	const float halfWidth = 0.25f;
	const float halfHeight = 0.5f;


	// Cast ray
	vec3 viewPosition = invView[3].xyz;
	vec3 viewDirection = normalize(worldSpacePosition - viewPosition);


	// Reflect ray from surface
	vec3 reflectedDirection = reflect(viewDirection, worldSpaceNormal);


	// Calculate ray intersection with light surface
	vec3 lightNormal = normalize(light.direction);
	vec3 lightRight = normalize(light.right);
	vec3 lightUp = normalize(cross(lightRight, lightNormal));



	/*
	var dot = Vector3.DotProduct(ray.Direction, plane.Normal);

	if (dot < Eps)
	{
		distance = 0.0f;
		return false;
	}
			
	distance = Vector3.DotProduct((plane.Point - ray.Origin), plane.Normal) / dot;
	return true;
	*/


	// Project ray onto plane
	float d = dot(reflectedDirection, lightNormal);
	float lightPlaneDistance = dot((light.position - worldSpacePosition), lightNormal) / d;

	vec3 lightPlanePoint = worldSpacePosition + reflectedDirection * lightPlaneDistance;
	vec3 lightPlanePointNorm = lightPlanePoint - light.position;

	vec2 components = vec2(dot(lightPlanePointNorm, lightRight), dot(lightPlanePointNorm, lightUp));
	components = vec2(clamp(components.x, -halfWidth, halfWidth), clamp(components.y, -halfHeight, halfHeight));
		
	vec3 nearestPointInside = light.position + components.x * lightRight + components.y * lightUp;
		
    
	// Light sees point
	float nDotL = dot(lightNormal, normalize(worldSpacePosition - nearestPointInside));
	if (nDotL > 0.0f)
	{
		// Diffuse
		vec3 v0 = normalize(light.position - halfWidth * lightRight + halfHeight * lightUp - worldSpacePosition);
		vec3 v1 = normalize(light.position + halfWidth * lightRight + halfHeight * lightUp - worldSpacePosition);
		vec3 v2 = normalize(light.position + halfWidth * lightRight - halfHeight * lightUp - worldSpacePosition);
		vec3 v3 = normalize(light.position - halfWidth * lightRight - halfHeight * lightUp - worldSpacePosition);
		
		vec3 lightVec = vec3(0.0f);
		lightVec += acos(dot(v0, v1)) * normalize(cross(v0, v1));
		lightVec += acos(dot(v1, v2)) * normalize(cross(v1, v2));
		lightVec += acos(dot(v2, v3)) * normalize(cross(v2, v3));
		lightVec += acos(dot(v3, v0)) * normalize(cross(v3, v0));

		float diffuseFactor = max(dot(lightVec, -worldSpaceNormal), 0.0f) / (2.0f * 3.14159265f);
		diffuse += diffuseFactor * light.diffuse * 3.0f;


		// Specular
		// Points in the right direction
		if (d < 0.0f)
		{
			float lightDistance = distance(worldSpacePosition, nearestPointInside);
			float distanceOutside = distance(lightPlanePoint, nearestPointInside);
		
			const float MaxDist = 0.1f;
			float specularFade = exp(-(distanceOutside * distanceOutside) / (lightDistance * lightDistance) * (1.0f / MaxDist));
		//	float specularFade = MaxDist / (distanceOutside * distanceOutside / lightDistance / lightDistance + MaxDist); 
		//	if (specularFade < 0.1f)
		//		specularFade = 0.0f;

			float attenuation = CalculateAttenuation(1.0f, 0.7f, 1.8f, lightDistance);
		
			specular = light.specular * 5 * specularFade * attenuation;		
		}
	}












	ambient = light.ambient;
}



void main()
{
	// Extract information from G-Buffer
	vec3 color = texture(gColorSpecular, IN.textureCoords).rgb;
	float materialSpecular = texture(gColorSpecular, IN.textureCoords).a;

	// World space G-Buffer
	//	vec3 worldSpacePosition = texture(gPosition, IN.textureCoords).xyz;
	//	vec3 viewSpacePosition = (matrices.view * vec4(worldSpacePosition, 1.0f)).xyz;
	//	
	//	vec3 worldSpaceNormal = normalize(texture(gNormal, IN.textureCoords).xyz);
	//	vec3 viewSpaceNormal = normalize(mat3(transpose(invView)) * worldSpaceNormal);
	
	// View space G-Buffer
	vec3 viewSpacePosition = texture(gPosition, IN.textureCoords).xyz;
	vec3 worldSpacePosition = (invView * vec4(viewSpacePosition, 1.0f)).xyz;
	
	vec3 viewSpaceNormal = normalize(texture(gNormal, IN.textureCoords).xyz);
	vec3 worldSpaceNormal = normalize(mat3(transpose(matrices.view)) * viewSpaceNormal);

	float ambientOcclusion = 1.0f;
	if (useSSAO)
	{
		ambientOcclusion = texture(ssaoTexture, IN.textureCoords).r;
	}

	// Camera data
	vec3 cameraPosition = invView[3].xyz;
	vec3 viewDir = cameraPosition - worldSpacePosition;
	float viewDirLength = length(viewDir);
	viewDir /= viewDirLength;


	// TODO
	const vec3 materialAmbient = vec3(1.0f);
	const float materialShininess = 32;


	// Lighting
	// All calculations in world space
	vec3 result = vec3(0.0f);
	for (int i = 0; i < lightCount; ++i)
	{
		Light light = lights[i];


		vec3 ambient = vec3(0.0f);
		vec3 diffuse = vec3(0.0f);
		vec3 specular = vec3(0.0f);
	
		AreaRectLight(light, worldSpacePosition, worldSpaceNormal, ambient, diffuse, specular);



		/*
		vec3 lightDir;
		float strength = 1.0f;

		if (light.type == 0)
		{
			lightDir = normalize(-light.direction);
		}
		else
		{
			lightDir = light.position - worldSpacePosition;
			float lightDirLengthInv = 1.0f / length(lightDir);

			strength = 3.0f * lightDirLengthInv;
			lightDir *= lightDirLengthInv;
		}


		// Ambient
		vec3 ambient = light.ambient * materialAmbient;


		// Diffuse
		float lightMultiplier = max(dot(worldSpaceNormal, lightDir), 0.0f);
		vec3 diffuse = lightMultiplier * light.diffuse;


		// Specular
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(worldSpaceNormal, halfwayDir), 0.0), materialShininess);
		vec3 specular = light.specular * spec * materialSpecular;
		*/

		// Shadows
		float shadow = 1.0f;
		float raysShadow = 1.0f;
	
		/*	
		// Directional lights
		if (light.type == 0)
		{
			if (i == 0)
				shadow = DirectionalShadowCalculations(light, lights_q_0_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 1)
				shadow = DirectionalShadowCalculations(light, lights_q_1_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 2)
				shadow = DirectionalShadowCalculations(light, lights_q_2_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 3)
				shadow = DirectionalShadowCalculations(light, lights_q_3_q_DirectionalShadowMap, worldSpaceNormal, worldSpacePosition);

			if (useRays)
			{
				if (i == 0)
					raysShadow = SamplePoint(light, lights_q_0_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 1)
					raysShadow = SamplePoint(light, lights_q_1_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 2)
					raysShadow = SamplePoint(light, lights_q_2_q_DirectionalShadowMap, cameraPosition, viewDirLength);
				else if (i == 3)
					raysShadow = SamplePoint(light, lights_q_3_q_DirectionalShadowMap, cameraPosition, viewDirLength);
			}
		}
		// Point lights
		else if (light.type == 1)
		{
			if (i == 0)
				shadow = PointShadowCalculations(light, lights_q_0_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 1)
				shadow = PointShadowCalculations(light, lights_q_1_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 2)
				shadow = PointShadowCalculations(light, lights_q_2_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
			else if (i == 3)
				shadow = PointShadowCalculations(light, lights_q_3_q_PointShadowMap, worldSpaceNormal, worldSpacePosition);
		}
		*/

	//	shadow = 1.0f - shadow;
	//	float raysMultiplier = 1.0f; //viewSpacePosition.z * viewSpacePosition.z;
	//	raysShadow = (1.0f - raysShadow * raysMultiplier);
		
		result += (ambient + shadow * (diffuse + specular)) * color * raysShadow * ambientOcclusion;
	}

	FragColor = vec4(result, 1.0f);
}