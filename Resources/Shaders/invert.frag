uniform sampler2D texture;
uniform float Time;
uniform float deltaTime;
float blinkTimes;


void main()
{
    blinkTimes = Time*8.0;
    float aux = ((deltaTime/Time)*blinkTimes);

    float x = step(mod(aux,2.0), 1.0);
    //if (blink) {
        vec4 originalColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
        gl_FragColor = vec4(vec3(1.0-x,1.0-x,1.0-x) +(-1.0+2.0*x)*originalColor.rgb, originalColor.a);
    //}
    //else gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;
}
