#version 410 core

out vec4 outColor;

in vec2 texCoord;

uniform vec2 viewport;

uniform vec3 camPos;
uniform mat4 lookAt;
uniform mat4 proj;

uniform float oceanRadius;
uniform vec3 oceanCenter;

uniform vec3 colA;
uniform vec3 colB;

uniform float depthMultiplier;
uniform float alphaMultiplier;

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

    vec2 raySphereInfo = raySphere(oceanCenter, oceanRadius, ro, rd);
    float distToSphere = raySphereInfo.x;
    float distInsideSphere = raySphereInfo.y;
    float depth = texture(depthTex, texCoord).r;
    float linearDepth = linearizeDepth(depth) * rayLength;
    float oceanViewDepth = min(distInsideSphere, linearDepth - distToSphere);

    vec4 col = vec4(0.0);
    if (oceanViewDepth > 0)
    {
        float opticalDepth01 = 1.0 - exp(-oceanViewDepth * depthMultiplier);
        col.a = 1.0 - exp(-oceanViewDepth * alphaMultiplier);
        col.rgb = mix(colA, colB, opticalDepth01);
    }
    else
    {
        discard;
    }

    outColor = col;
}