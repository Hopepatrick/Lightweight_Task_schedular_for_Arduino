/*
Make your own lightweight non-blocking RTOS for Arduino
Author: Patrick NDAYIKUNDA
Date: 17/08/2023

*/

void task1(void){
  Serial.println("I'm running as task 1");
}

void task2(void){
  Serial.println("I'm running as task 2");
}

void task3(void){
  Serial.println("I'm running as task 3");
}

typedef struct Scheduler{
void (*run) (void);
unsigned long current_time;
unsigned long prev_time;
uint32_t delay_time;
};

static Scheduler sched[] = {
{task1,0,0,500},
{task2,0,0,1000},
{task3,0,0,2000},
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < sizeof(sched)/ sizeof(sched[0]); i++){
    sched[i].current_time = millis();
  }
  for(int i=0;i<sizeof(sched)/ sizeof(sched[0]);i++){
    if(sched[i].current_time - sched[i].prev_time>=sched[i].delay_time){
      sched[i].prev_time = sched[i].current_time;
      sched[i].run();
    }

  }

}
