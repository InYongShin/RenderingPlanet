#version 410 core

const float pi = 3.141592f;

out vec4 outColor;

in vec2 texCoord;

uniform vec2 viewport;

uniform vec3 camPos;
uniform mat4 lookAt;
uniform mat4 proj;

uniform vec3 lightPos;
uniform vec3 dirToSun;

uniform float oceanRadius;
uniform float atmosphereRadius;
uniform vec3 atmosphereCenter;

uniform float densityFalloff;
uniform int numInScatteringPoints;
uniform int numOpticalDepthPoints;

uniform vec3 scatteringCoefficients;

uniform float zNear;
uniform float zFar;
uniform sampler2D depthTex;

float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
}

vec2 raySphere(vec3 center, float radius, vec3 ro, vec3 rd)
{
    vec3 offset = ro - center;
    float a = 1;
    float b = 2 * dot(offset, rd);
    float c = dot(offset, offset) - radius * radius;
    float d = b * b - 4 * a * c;

    if (d > 0)
    {
        float s = sqrt(d);
        float dstToSphereNear = max(0, (-b - s) / (2 * a));
        float dstToSphereFar = (-b + s) / (2 * a);

        if (dstToSphereFar >= 0)
        {
            return vec2(dstToSphereNear, dstToSphereFar - dstToSphereNear);
        }
    }

    return vec2(100000000.0, 0.0);
}

float densityAtPoint(vec3 densitySamplePoint)
{
    float heightAboveSurface = length(densitySamplePoint - atmosphereCenter) - oceanRadius;
    float height01 = heightAboveSurface / (atmosphereRadius - oceanRadius);
    float localDensity = exp(-height01 * densityFalloff) * (1.0 - height01);
    return localDensity;
}

float opticalDepth(vec3 ro, vec3 rd, float rl)
{
    vec3 densitySamplePoint = ro;
    float stepSize = rl / (numOpticalDepthPoints - 1);
    float opticalDepth = 0.0;
    for (int i=0; i<numOpticalDepthPoints; ++i)
    {
        float localDensity = densityAtPoint(densitySamplePoint);
        opticalDepth += localDensity * stepSize;
        densitySamplePoint += rd * stepSize;
    }
    return opticalDepth;
}

vec3 calculateLight(vec3 ro, vec3 rd, float rl)
{
    vec3 inScatterPoint = ro;
    float stepSize = rl / (numInScatteringPoints - 1);
    vec3 inScatteredLight = vec3(0.0);

    for (int i=0; i<numInScatteringPoints; ++i)
    {
        float sunRayLength = raySphere(atmosphereCenter, atmosphereRadius, inScatterPoint, dirToSun).y;
        float sunRayOpticalDepth = opticalDepth(inScatterPoint, dirToSun, sunRayLength);
        float viewRayOpticalDepth = opticalDepth(inScatterPoint, -rd, stepSize * i);
        vec3 transmittance = exp(-(sunRayOpticalDepth + viewRayOpticalDepth) * scatteringCoefficients);
        float localDensity = densityAtPoint(inScatterPoint);

        inScatteredLight += localDensity * transmittance * scatteringCoefficients * stepSize;
        inScatterPoint += rd * stepSize;
    }

    return inScatteredLight;
}

void main()
{
    float x = (2.0 * gl_FragCoord.x - viewport.x) / viewport.x;
    float y = (2.0 * gl_FragCoord.y - viewport.y) / viewport.y;

    vec4 rayClip = vec4(x, y, -1.0, 1.0);
    vec4 rayView = inverse(proj) * rayClip;
    rayView = vec4(rayView.xy, -1.0, 0.0);
    vec3 rayWorld = (inverse(lookAt) * rayView).xyz;
    float rayLength = length(rayWorld);
    rayWorld = normalize(rayWorld);

    vec3 rd = rayWorld;
    vec3 ro = camPos;

    float depth = texture(depthTex, texCoord).r;
    float linearDepth = linearizeDepth(depth) * rayLength;

    float distToOcean = raySphere(atmosphereCenter, oceanRadius, ro, rd).x;
    float distToSurface = min(distToOcean, linearDepth);

    vec2 rayAtmosphereInfo = raySphere(atmosphereCenter, atmosphereRadius, ro, rd);
    float distToAtmosphere = rayAtmosphereInfo.x;
    float distInsideAtmosphere = min(rayAtmosphereInfo.y, distToSurface - distToAtmosphere);

    if (distInsideAtmosphere > 0)
    {
        const float epsilon = 0.000001;
        vec3 pointInAtmosphere = ro + rd * (distToAtmosphere + epsilon);
        vec3 light = calculateLight(pointInAtmosphere, rd, distInsideAtmosphere - epsilon * 2.0);
        outColor = vec4(light, length(light));
    }
    else
    {
        discard;
    }
}