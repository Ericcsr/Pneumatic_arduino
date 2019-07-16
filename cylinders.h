#ifndef __CYLINDERS__
#define __CYLINDERS__
#include "Arduino.h"


// Cylinders are defined in a OOP way
// Cylinder is the base class
// each cylinder with different functions are child classes

class Cylinder
{
    public:
        Cylinder(int Pin[2],void (*drv_func)(int,int[]));
        void set_Direct(bool dir);
        int get_status();
        void move(int dir); 
    private:
        int pin[2] = {NULL_PIN,NULL_PIN};
        int status;
        int direction;
        void (*Driver)(int,int[]);
};

void rodless_drv (int dir,int pin[]);
void normal_drv  (int dir,int pin[]);
#endif 