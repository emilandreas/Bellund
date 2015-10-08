extern "C" {
#include "CAN_driver.h"
#include "spi_driver.h"
#include "MCP_driver.h"
}
#include <avr/io.h>
#include <stdio.h>
//#include "servo.h"

#include <Servo.h>


Servo myServo;

void servo_init(){
  myServo.attach(A4);
}
int servo_set(int8_t pos){
  //Map from % to angle in degrees
  int angle = map(pos, -100, 100,150 ,50);
  myServo.write(angle);
  return angle;
}

// create a FILE structure to reference our UART output function

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup() {
  servo_init();
  //Start can

  // Start the UART
  Serial.begin(9600) ;

  // fill in the UART file descriptor with pointer to writer.
  fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

  // The uart is the standard output device STDOUT.
  stdout = &uartout;
  CAN_init();
}

void loop() {
  
    //printf("Hello \n\r");
    Message m;
    m.id = 1;
    m.data[0] = 'l';
    m.data[1] = 'e';
    m.data[2] = 't';
    m.data[3] = '\0';
    m.length = 4;

    CAN_transmit(&m);
    //printf("message: %s \n\r", m.data);
  
  Message answer;
  if (!CAN_receive(&answer)) {
    int8_t x = answer.data[0];
    int8_t y = answer.data[1];  
    printf("X: %i Y: %i \n\r", x, y);
  }
  servo_set(answer.data[0]);
  
  Serial.print(answer.data[0]);
  printf("Angle: %i \r\n", servo_set(answer.data[0]));
  delay(10);
}
