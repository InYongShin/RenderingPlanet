#version 410 core

const float pi = 3.141592f;

out vec4 outColor;

in vec2 texCoord;

uniform vec2 viewport;

uniform vec3 camPos;
uniform mat4 lookAt;
uniform mat4 proj;

uniform vec3 lightPos;
uniform vec3 lightCol;

uniform float volumeRadius;
uniform vec3 volumeCenter;
uniform float oceanRadius;

uniform float rayStep;
uniform int maxStep;

uniform float lightStep;
uniform int maxLightStep;

uniform float absorption;
uniform float lightAbsorptionToSun;

uniform sampler3D cloudTex;

uniform float zNear;
uniform float zFar;
uniform sampler2D depthTex;

float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * zNear * zFar) / (zFar + zNear - z * (zFar - zNear));
}

float sampleDensity(vec3 p)
{
    vec3 pTexCoord = (p + vec3(volumeRadius)) / (2.0 * volumeRadius);
    return texture(cloudTex, pTexCoord).r;
}

float lightMarch(vec3 rd, vec3 p)
{
    vec3 toLight = normalize(lightPos - p);
    
    float totalDensity = 0;
    for(int i=0; i<maxLightStep; ++i){
        p += toLight * lightStep;
        totalDensity += max(0, sampleDensity(p) * lightStep);
    }

    // float cosTheta = dot(rd, toLight);
    // float phase = HGPhase(g, -cosTheta);

    // float transmittance = 2 * exp(-totalDensity * lightAbsorptionToSun) * (1-exp(-2*totalDensity * lightAbsorptionToSun)) * phase;
    float transmittance = exp(-totalDensity * lightAbsorptionToSun);

    float darknessThreshold = 0.1;
    return darknessThreshold + transmittance * (1-darknessThreshold); 
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

    vec2 raySphereInfo = raySphere(volumeCenter, volumeRadius, ro, rd);
    float distToSphere = raySphereInfo.x;
    float distInsideSphere = raySphereInfo.y;
    float depth = texture(depthTex, texCoord).r;
    float linearDepth = linearizeDepth(depth) * rayLength;

    float distToOcean = raySphere(volumeCenter, oceanRadius, ro, rd).x;
    float distToSurface = min(distToOcean, linearDepth);

    distInsideSphere = min(distInsideSphere, distToSurface - distToSphere);

    float transmittance = 1.0;
    float lightEnergy = 0.0;

    if (distInsideSphere > 0){
        float stepLength = distInsideSphere / maxStep;
        float totalStepLength = distToSphere;
        for(int i=0; i<maxStep; ++i){
            vec3 p = ro + totalStepLength * rd;

            float density = sampleDensity(p);

            if (density>0.01){
                // float lightTransmittance = lightMarch(rd, p);
                // vec3 toLight = normalize(lightPos - p);
                // float cosTheta = dot(rd, toLight);
                // float phase = HGPhase(g, -cosTheta);
                transmittance *= exp(-density * stepLength * absorption);
                // transmittance *= 2*(1 - exp(-2*density * rayStep));
                // lightEnergy += density * stepLength * transmittance * lightTransmittance;
                lightEnergy += density * stepLength * transmittance;

                if (transmittance < 0.01) break;
            }
            totalStepLength += stepLength;
        }
    }

    vec4 col = vec4(0.0);
    vec3 cloudCol = lightEnergy * lightCol; // light color = vec3(1)
    col.rgb = transmittance + cloudCol;
    col.a = lightEnergy;

    outColor = col;
}