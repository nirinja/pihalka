#include <NexButton.h>
#include <NexTouch.h>

#define STEPPIN 13
#define DIRPIN 11
#define ENAPIN 10

int val = 0;

NexButton b0 = NexButton(0, 2, "b0");
NexButton b1 = NexButton(0, 3, "b1");

NexTouch *nex_listen_list[] = {
    &b0,
    &b1,
    NULL
};

void b0PopCallback(void *ptr) {
    digitalWrite(ENAPIN, LOW);
    val = 1;
}

void b1PopCallback(void *ptr) {
    digitalWrite(ENAPIN, LOW);
    val = 0;
}

void setup() {
    pinMode(STEPPIN, OUTPUT);
    pinMode(DIRPIN, OUTPUT);
    pinMode(ENAPIN, OUTPUT);
    pinMode(9, OUTPUT); // Assuming this is the pin you want to use for motor control
}

void loop() {
    val = digitalRead(9);

    if (val == 1) {
        forward(2500);
        reverse(2500);
    }
}

void forward(int steps) {
    int i;
    digitalWrite(ENAPIN, LOW);
    digitalWrite(DIRPIN, HIGH);
    for (i = 0; i < steps; i++) {
        digitalWrite(STEPPIN, !digitalRead(STEPPIN));
        delayMicroseconds(500);
    }
    digitalWrite(ENAPIN, HIGH);
}

void reverse(int steps) {
    int i;
    digitalWrite(ENAPIN, LOW);
    digitalWrite(DIRPIN, LOW);
    for (i = 0; i < steps; i++) {
        digitalWrite(STEPPIN, !digitalRead(STEPPIN));
        delayMicroseconds(500);
    }
    digitalWrite(ENAPIN, HIGH);
}