#include "pneumatic_task.h"


int rotation_flag[2]    = {0,0};
int rotation_ok[2]      = {0,0};
int current_task        = NULL_TASK;
int command_flag        = NULL_TASK;

Cylinder rodless(rodless_pin,rodless_drv);
rodless.set_Direct(ROD_SET);
Cylinder eject_left(eject_left_pin,normal_drv);
eject_left.set_Direct(EJECT_SET);
Cylinder eject_right(eject_right_pin,normal_drv);
eject_right.set_Direct(EJECT_SET);
Cylinder grabber(grabber_pin,normal_drv);
grabber.set_Direct(GRABBER_GRAB);
Cylinder arm(arm_pin,normal_drv);
arm.set_Direct(ARM_REACH);

//ThreadController controll = ThreadController();

//Thread communication=Thread();
//Thread actuators=Thread();

//Below define callback functions
// Can be considered as two while loop

void communication_rx(int num)
{
    int avail;
    while(1)
    {
        avail = Wire.available();
        if(avail<=0)
            break;
        else if(avail = 3)
            command_flag = Wire.read();
        else if(avail = 2)
            rotation_flag[0] = Wire.read();
        else
            rotation_flag[1] = Wire.read();
    }
}

void communication_tx()
{
    Wire.write(current_task);
    Wire.write(rotation_ok[0]);
    Wire.write(rotation_ok[1]);
}

void actuators()
{
    
}
//Callback function defined
// Arduino Will be a slave device in I2C Communication
void communication_Init()
{
    Wire.setClock(CLOCK_FRQ);
    Wire.begin(DEVICE_ID); 
    Wire.onReceive(communication_rx);
    Wire.onRequest(communication_tx);
}
//Definition Of communication init
void setup()
{
    sensors_Init();
    TIM_IRQ_Init();
    //Below are left blank for init communication

    //communication init end
    Ms
    delay(2000);
}

void loop()
{
    switch(command_flag)
    {
        case TASK1:
        case TASK2:
        case TASK3:
            grab_task(command_flag);
            break;
        case RESET_TASK:
            reset();
            break;
        case EJECT_TASK:
            eject();
            break;
        case NULL_TASK:
            break;
    }
}