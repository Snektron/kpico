uniform sampler2D uTexture;

varying vec2 vTexCoords;

void main()
{
        gl_FragColor = vec4(texture2D(uTexture, vTexCoords).xyz, 1);
}
