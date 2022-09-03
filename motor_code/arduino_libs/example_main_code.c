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

void A0(void)
{
    if (millis() - A_Task_Tmr > (A_TASK_RATE * 1000))
    {
        A_Task_Tmr = millis();
        (*A_Task_Ptr)();        //calls next A Task, thus actual A Task rate is dependent on no. of A Tasks
    }
    
    Base_State_Ptr = &B0;
}

void B0(void)
{
    if (millis() - B_Task_Tmr > (B_TASK_RATE * 1000))
    {
        A_Task_Tmr = millis();
        (*B_Task_Ptr)();
    }

    Base_State_Ptr = &A0;
}