uniform sampler2D texture;
uniform float time;
uniform vec2 posF;
uniform vec2 posS;

void main()
{
    vec4 originalColor = texture2D(texture, gl_TexCoord[0].xy) * gl_Color;

    gl_FragColor = (
//            vec3 ( 
//            (sin
//                     (distance(posF, posS+gl_FragCoord.xy)*0.2)
//                         *originalColor.rgba*0.7
//                 )
                (originalColor.rgba*0.8) 
                + 0.2*(originalColor.rgba*float(sin(time*distance(posF, posS)/10.0)) )*originalColor.a 
            )
//             )
              ;  
}
