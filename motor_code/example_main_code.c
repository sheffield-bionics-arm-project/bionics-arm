/*
  example_main_code.c - Example Main Code file for Bionics Arduino code.
  Utilizes state machines for running background tasks at fixed sample rates,
    allowing different rates for different tasks.
  Created by David Wilkinson (Sheffield Bionics) 03-09-2022.
  Released into the public domain.
*/

#include "Arduino.h"

#define A_TASK_RATE 10; //10ms task rate
#define B_TASK_RATE 20; //20ms task rate


// State Machine func prototypes
//-------------------------------
// Base states
void A0(void);
void B0(void);

//A branch states - run at A_TASK_RATE
void A1(void);
void A2(void);

//B branch states - run at B_TASK_RATE
void B1(void);
void B2(void);

// State pointer declarations
void (*Base_State_Ptr)(void);
void (*A_Task_Ptr)(void);
void (*B_Task_Ptr)(void);

// State machine timer vars
unsigned long A_Task_Tmr = 0;
unsigned long B_Task_Tmr = 0;

// Task state machine init
Base_State_Ptr = &A0;
A_Task_Ptr = &A1;
B_Task_Ptr = &B1;


//=================================================================================
//	STATE-MACHINE SEQ/SYNC FOR BACKGROUND TASKS
//=================================================================================
/* ---- Explanation ----
    Base States: A0, B0, ... (additional can be added)
        Each branch task type (A/B/C...) can have a different task rate assigned to it
        Then each branch state (A1, A2, B1, B2...) will be called sequentially and periodically
        at this task rate.
        Example:
            A1 --(10ms passed)--> A2 --(10ms passed)--> A1 etc...
        As the Base State Pointer is moved after executing a task, the execution order is as follows:
            Base_State_Ptr = &A0
                EXECUTE A1
                    -> Base_State_Ptr = &B0
                EXECUTE B1
                    -> Base_State_Ptr = &A0
                EXECUTE A2
                    -> Base_State_Ptr = &B0
                EXECUTE B2
                    -> Base_State_Ptr = &A0
                EXECUTE A1
                    -> Base_State_Ptr = &B0 
                ... repeats ad infinitum

        The actual task rate for each child task (A1, A2 etc.) thus will depend on the number of tasks in the branch.
        This is because only ONE branch state will be executed at the rate specified by A_TASK_RATE.
            Thus, having (for example) two A tasks (A1, A2) and an A_TASK_RATE of 10 means it takes 20ms to fully
            loop through ALL A tasks as there is 10ms between each A task call.

        Additional task types (C, D...) can be added with ease to allow different task rates.
            Simply move the Base_State_Ptr of the last base state (B0 by default) to &C0 (for example)
            and follow the same code structure as A and B tasks follow.

        The advantage of this structure is that not all tasks are required to run on every loop of Arduino code.
            For example, reading EMG signals does not need to occur on EVERY loop, but as these functions ARE
            time-critical and must be called on a FIXED sample rate (which cannot be guaranteed when calling in void loop())
            then putting them in the below state machine structure will ensure a more consistent sample rate.
        
        Algorithms such as digital filters and controllers need to be executed at a consistent rate, as these algorithms
            are dependent on sampling frequency. 

        The below structure simplifies the assertion of sampling frequency
            by utilizing millis() to check the time between task execution.
*/


void A0(void)
{
    if (millis() - A_Task_Tmr >= (A_TASK_RATE))
    {
        A_Task_Tmr = millis();  // update time of current A task execution
        (*A_Task_Ptr)();        // calls next A Task
    }
    
    Base_State_Ptr = &B0;
}

void B0(void)
{
    if (millis() - B_Task_Tmr >= (B_TASK_RATE))
    {
        A_Task_Tmr = millis();  // update time of current B task execution
        (*B_Task_Ptr)();        // calls next B task
    }

    Base_State_Ptr = &A0;
}


// ---- A Tasks (executed every "A_TASK_RATE"-milliseconds) ----
void A1(void)
{
    // example function calls for A tasks

    // moveMotors();

    A_Task_Ptr = &A2;
}


void A2(void)
{
    // example function calls for A tasks

    // lockArmPosition();
    //other fast-rate functions

    A_Task_Ptr = &A1;
}


// ---- B Tasks (executed at B_TASK_RATE period, in ms) ----
void B1(void)
{
    // example function calls for B tasks

    // readEmgSignals();
    // processEmgReading();

    B_Task_Ptr = &B2;
}

void B2(void)
{
    // example function calls for B tasks
    
    // monitorBatteryHealth();

    B_Task_Ptr = &B1;
}




// ---- MAIN ARDUINO CODE ----


void setup()
{
    // one-time device init code below...

}

void loop()
{
    (*Base_State_Ptr)();    // move to a Base state (A0, B0 etc.)

}