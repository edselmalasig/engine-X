#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform int mode;
void main()
{
     if(mode == 0 || mode == 1){
          FragColor = vec4(objectColor, 1.0);
     }else{
         FragColor = vec4(objectColor * lightColor, 1.0);
     }
}
