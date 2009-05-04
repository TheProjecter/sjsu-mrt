void main()
{
    gl_FragColor.r = 1 - gl_Color.r;
    gl_FragColor.g = 1 - gl_Color.g;
    gl_FragColor.b = 1 - gl_Color.b;
    gl_FragColor.a = gl_Color.a;
} 
