#include "pneumatic_task.h"

extern int current_task;
extern int rotation_ok[2];

void sensor_Init()
{
    for(int i=22;i<27;i++)
        pinMode(i,INPUT);
}

void TIM_IRQ_Init()
{
    MsTimer2::set(UPDATE_FRQ,sensors_update);
    MsTimer2::start();
}

void TIM_Stop()
{
    MsTimer2::stop();
}

//Update all active sensors; when a sensor is triggered deactivate it
//After the actions are taken sensor can be activated.
void sensor_update(int size)
{
    for(int i=0;i<size;i++)
    {
        if(active_sensors[i]=ACTIVATE)
        {
            sensor_array[i] = !digitalRead(active_sensors[i]+SHIFTER-1);
            if(sensor_array[i]==1) //Sensor is triggered
                active_sensors[i] = DEACTIVATE;
        }
    }
    TIM_Stop();
    Wire.write(current_task);
    Wire.write(rotation_ok[0]);
    Wire.write(rotation_ok[1]);
    MsTimer2::start();
}

//set active sensors when external functions need to
void set_activeSensor(int sensor)
{
    active_sensors[sensor-SHIFTER-1] = ACTIVATE+sensor-SHIFTER-1;
}