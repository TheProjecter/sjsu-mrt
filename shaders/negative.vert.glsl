void main()
{
    vec3 normal;
    vec3 light_dir;
    vec4 diffuse;
    float nl;

    normal = normalize(gl_NormalMatrix * gl_Normal);
    light_dir = normalize(vec3(gl_LightSource[0].position));
    nl = max(dot(normal, light_dir), 0.0);
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;

    gl_FrontColor = nl * diffuse;
    gl_Position = ftransform();
}
