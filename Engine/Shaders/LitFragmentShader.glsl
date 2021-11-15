#version 460 core

in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vPixelPos;

uniform sampler2D uTexture;

uniform vec3 uCameraPosition;
uniform vec3 uAmbientColor;
uniform vec3 uSunColor;

out vec4 FragColor;

const float PI = 3.14159265358979;

//Normal distribution
float D(float alpha, vec3 N, vec3 H)
{
    float numerator = pow(alpha, 2.0);

    float NdotH = max(dot(N, H), 0.0);
    float denominator = PI * pow(pow(NdotH, 2.0) * (pow(alpha, 2.0) - 1.0) + 1.0, 2.0);
    denominator = max(denominator, 0.000001);

    return numerator / denominator;
}

//Schlick-Beckmann Shadowing
float G1(float alpha, vec3 N, vec3 X)
{
    float numerator = max(dot(N, X), 0.0);

    float k = alpha / 2.0;
    float denominator = max(dot(N, X), 0.0) * (1.0 - k) + k;
    denominator = max(denominator, 0.000001);

    return numerator / denominator;
}

//Smith model
float G(float alpha, vec3 N, vec3 V, vec3 L)
{
    return G1(alpha, N, V) * G1(alpha, N, L);
}

vec3 Fresnel(vec3 F0, vec3 V, vec3 H)
{
    return F0 + (vec3(1.0) - F0) * pow(1 - max(dot(V, H), 0.0), 5.0);
}

void main()
{
    /*vec3 textureColor = texture(uTexture, vTexCoords).rgb;
    vec3 normal = normalize(vNormal);

    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0) - vPixelPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * uSunColor;

    FragColor = vec4(textureColor * (diffuse + uAmbientColor), 1.0);*/

    vec3 textureColor = vec3(0.0, 1.0, 0.0);
    vec3 normal = normalize(vNormal);
    vec3 ambient = uAmbientColor * textureColor;

    vec3 N = normal;

    //View dir
    vec3 V = normalize(uCameraPosition - vPixelPos);

    //Light dir
    vec3 L = normalize(vec3(0.6, 1.0, 1.0) - vPixelPos);
    //vec3 L = normalize(vec3(0.5, 1.0, 1.0));

    vec3 H = normalize(V + L);

    //Reflectivity
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, textureColor.rgb, 1.0);

    float metallic = 0.9f;

    vec3 Ks = Fresnel(F0, V, H);
    vec3 Kd = (vec3(1.0) - Ks) * (1.0 - metallic);

    vec3 lambert = (textureColor) / PI;

    //Roughness
    float alpha = 0.5;
    vec3 cookTorranceNumerator = D(alpha, N, H) * G(alpha, N, V, L) * Fresnel(F0, V, H);
    float cookTorranceDenominator = 4.0 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0);
    vec3 cookTorrance = cookTorranceNumerator / cookTorranceDenominator;

    vec3 BRDF = Kd * lambert + cookTorrance;
    vec3 outLight = vec3(0.0) + BRDF * uSunColor * max(dot(L, N), 0.0);

    FragColor = vec4(outLight + ambient, 1.0);
}
