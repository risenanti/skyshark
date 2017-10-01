// Radio min/max values for each stick for my radio (worked out at beginning of article)
#define RC_THR_MIN   1070
#define RC_YAW_MIN   1068
#define RC_YAW_MAX   1915
#define RC_PIT_MIN   1077
#define RC_PIT_MAX   1915
#define RC_ROL_MIN   1090
#define RC_ROL_MAX   1913

// Motor numbers definitions
#define MOTOR_FL   0    // Front left    
#define MOTOR_FR   1    // Front right
#define MOTOR_BL   2    // back left
#define MOTOR_BR   3    // back right

// Arduino map function
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double constrain(double x, double a, double b) {
    if(x < a) {
        return a;
    }
    else if(b < x) {
        return b;
    }
    else
        return x;
}


#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))