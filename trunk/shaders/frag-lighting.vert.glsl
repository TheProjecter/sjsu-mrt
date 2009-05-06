varying vec3 normal, light_dir, half_vector;
varying vec4 diffuse, ambient;

void main()
{
    normal = normalize(gl_NormalMatrix * gl_Normal);
    light_dir = normalize(vec3(gl_LightSource[0].position));
    half_vector = normalize(gl_LightSource[0].halfVector.xyz);

    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
    ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;

    gl_Position = ftransform();
}

