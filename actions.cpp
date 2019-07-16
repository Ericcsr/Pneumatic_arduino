#include "pneumatic_task.h"

//Cylinders are externed in header file.
//Each cylinder was declared in pneumatic.task
extern int active_sensors[5];
extern bool  sensor_array[5];
extern Cylinder rodless,eject_left,eject_right,grabber,arm;
extern int rotation_flag[2];
extern int rotation_ok[2];

bool eject()
{
    eject_left.move(EJECT); //Release the cylinder to eject
    eject_right.move(EJECT);
    delay(300);
    eject_left.move(EJECT_RESET);
    eject_right.move(EJECT_RESET);
    if(eject_left.get_status()==1 && eject_right.get_status()==1)
        return true;
    else
    {
        return false;
    }
}

bool reset()
{
    eject_left.move(EJECT_RESET);
    eject_right.move(EJECT_RESET);
    grabber.move(GRABBER_RELEASE);
    arm.move(ARM_RETRACT)；
    while(sensor_array[0]==0 && counter<=500)
    {
        rodless.move(ROD_RESET);
    }
    rodless.move(ROD_STOP);
    set_activeSensor(SENSOR1);
}


//TASK1 is Grab First and Second Row of Ammo Boxes under the resource Island
//TASK2 is Grab A single box of Ammo on the resource Island
//TASK3 is Grab Continous 4 Boxes of Ammo Boxes on the resource Island
bool grab_task(int flag)
{
     if(flag == TASK2 || flag == TASK3)
    {
        arm.move(ARM_REACH);
        delay(500);
    }
    while(1)
    {
    if(command_flag==RESET_TASK)
    {
        reset();
        break;
    }
    rotation_ok[0] = 1;
    while(!rotation_flag[0]); //Wait until stm32 finish rotation the claw
    grabber.move(GRABBER_GRAB);
    delay(500); //Wait until grab is finished
    rotation_ok[1] = 1;
    while(!rotation_flag[1]);
    grabber.move(GRABBER_RELEASE);
    eject();
    delay(500);
    box_counter++;
    switch(task)
    {
        case TASK1: //Only wait for reach specific target
            while(sensor_array[box_counter])
            {
                if(box_counter<=2)
                    rodless.move(ROD_SET);
                else
                {
                    rodless.move(ROD_RESET);
                    delay(500);
                    if(box_counter==3)
                        arm.move(ARM_REACH);
                }
            }
            rodless.move(ROD_STOP);
            break;
        case TASK2:
            break;
        case TASK3:
            while(sensor_array[box_counter])
            {
                rodless.move(ROD_SET);
            }
            rodless.move(ROD_STOP);
            break;
    }
    if((task==TASK1 && counter>=5)||(task==TASK2)||(task==TASK3 && box_counter>=3))
    {
        arm.move(ARM_RETRACT);
        break;
    }
    }
    return reset();
}
