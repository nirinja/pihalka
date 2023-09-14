#include <Nextion.h>

#define STEPPIN 12 //step
#define DIRPIN 11 //direction
#define ENAPIN 10 //eable motor

int Speed = 100;
int StepNo = 1;

int stepCount = 0;
bool spinningDirection = true;

NexButton b0 = NexButton(0, 1, "b0");
NexButton b1 = NexButton(0, 2, "b1");
NexButton b2 = NexButton(0, 3, "b2");
NexButton b3 = NexButton(0, 4, "b3");

NexTouch *nex_listen_list[] = {
  &b0,
  &b1,
  &b2,
  &b3,
  NULL
};

bool stop = false;
void b0PopCallback(void *ptr) {
  stop = true;
}

void b1PopCallback(void *ptr) {
  Speed = 500;
  StepNo = 10000;
  digitalWrite(ENAPIN, LOW);
}

void b2PopCallback(void *ptr) {
  Speed = 250;
  StepNo = 15000;
  digitalWrite(ENAPIN, LOW);
}

void b3PopCallback(void *ptr) {
  Speed = 100;
  StepNo = 20000;
  digitalWrite(ENAPIN, LOW);
}

void setup() {
  Serial.begin(9600);
  nexInit();
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
  b2.attachPop(b2PopCallback, &b2);
  b3.attachPop(b3PopCallback, &b3);

  pinMode(STEPPIN, OUTPUT); // Corrected to use STEPPIN
  pinMode(DIRPIN, OUTPUT);  // Corrected to use DIRPIN
  pinMode(ENAPIN, OUTPUT);

  digitalWrite(DIRPIN, LOW);  // low je spinningDirection  true
  digitalWrite(ENAPIN, HIGH);
}

void loop() {
  nexLoop(nex_listen_list);

  if(StepNo != 0 || Speed != 0 ){
    digitalWrite(STEPPIN, HIGH);  // Corrected to use STEPPIN
    delayMicroseconds(Speed);
    digitalWrite(STEPPIN, LOW);  // Corrected to use STEPPIN
    delayMicroseconds(Speed);
    stepCount++;

    if (stepCount == StepNo) {
      spinningDirection = !spinningDirection;
      digitalWrite(DIRPIN, spinningDirection ? LOW : HIGH);  // Corrected to use DIRPIN
      stepCount = 0;
    } 
    if (stepCount == 0 && spinningDirection ==  false && stop ){
        Speed = 0;
        StepNo = 0;
        digitalWrite(ENAPIN, HIGH);
        stop = false;
    } 
  }
}