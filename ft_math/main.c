#include "ft_math.h"
#include <stdio.h>
int main()
{
    float x = 1.0f;
    t_vec4 v;
    v = vec4_init(x,x,x,12.0f);
    printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
    return 0;
}