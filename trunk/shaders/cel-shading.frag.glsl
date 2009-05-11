varying vec3 normal, light_dir;

void main()
{
    float intensity;
    vec3 n;

    n = normalize(normal);
    intensity = max(dot(light_dir ,n), 0.0); 

    if (intensity > 0.98)
        gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);
    else if (intensity > 0.5)
        gl_FragColor = vec4(0.4, 0.4, 0.8, 1.0);    
    else if (intensity > 0.25)
        gl_FragColor = vec4(0.2, 0.2, 0.4, 1.0);
    else
        gl_FragColor = vec4(0.1, 0.1, 0.1, 1.0);
}

