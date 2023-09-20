#include <Nextion.h>

#define STEPPIN 12 //step (PUL+)
#define DIRPIN 11 //direction (DIR+)
#define ENAPIN 10 //eable motor (ENA+)

int BtnSpeed = 100; //se spremeni ko se gumb pritisne
int BtnStepNo = 1;

int Speed = 0; //ko se dokoča cikel se mu value od BtnSpeed nastima
int StepNo = 0;

int stepCount = 0; //steje stepe
bool spinningDirection = true; //pove v katero smer se vrti

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

//gumbi
void b0PopCallback(void *ptr) {
  BtnSpeed = 0;
  BtnStepNo = 0;
}

void b1PopCallback(void *ptr) {
  BtnSpeed = 90;
  BtnStepNo = 8000;
  digitalWrite(ENAPIN, LOW);
}

void b2PopCallback(void *ptr) {
  BtnSpeed = 50;
  BtnStepNo = 11000;
  digitalWrite(ENAPIN, LOW);
}

void b3PopCallback(void *ptr) {
  BtnSpeed = 23;
  BtnStepNo = 13500;
  digitalWrite(ENAPIN, LOW);
}

void setup() {
  Serial.begin(9600);
  nexInit();
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
  b2.attachPop(b2PopCallback, &b2);
  b3.attachPop(b3PopCallback, &b3);

  pinMode(STEPPIN, OUTPUT);
  pinMode(DIRPIN, OUTPUT); 
  pinMode(ENAPIN, OUTPUT);

  digitalWrite(DIRPIN, LOW);  // low => spinningDirection = true
  digitalWrite(ENAPIN, HIGH); //High => onemogočen motor- se ne premika
}

void loop() {
  nexLoop(nex_listen_list); //posluša ce se btn pritisne

  if (stepCount == 0 && spinningDirection){ //po končanem ciklu se spremeni speed
    Speed = BtnSpeed;
    StepNo = BtnStepNo;
  }

  if(Speed != 0 && StepNo != 0 ){
    digitalWrite(STEPPIN, HIGH); 
    delayMicroseconds(Speed);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(Speed);
    stepCount++;

    if (stepCount == StepNo) { //spremeni smer vrtenja
      spinningDirection = !spinningDirection;
      digitalWrite(DIRPIN, spinningDirection ? LOW : HIGH);
      stepCount = 0;
    } 
  }else{ //ustavi motor
    digitalWrite(ENAPIN, HIGH);
  }
}