varying vec3 normal, light_dir, half_vector;
varying vec4 diffuse, ambient;

void main()
{
    vec4 color = ambient;
    vec3 n = normalize(normal);
    float nl = max(dot(n, light_dir), 0.0);

    if (nl > 0.0) {
        float nh = max(dot(n, normalize(half_vector)), 0.0);

        color += diffuse * nl;
        color += gl_FrontMaterial.specular * 
                 gl_LightSource[0].specular * 
                 pow(nh, gl_FrontMaterial.shininess);
    }

    gl_FragColor = color;
}

