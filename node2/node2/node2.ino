extern "C" {
#include "CAN_driver.h"
#include "spi_driver.h"
#include "MCP_driver.h"
}
#include <avr/io.h>
#include <stdio.h>

// create a FILE structure to reference our UART output function

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup() {
  //Start can

  // Start the UART
  Serial.begin(9600) ;

  // fill in the UART file descriptor with pointer to writer.
  fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

  // The uart is the standard output device STDOUT.
  stdout = &uartout;

  printf("%02x", CAN_init());
}

void loop() {
  /*
    printf("Hello \n\r");
    Message m;
    m.id = 1;
    m.data[0] = 'l';
    m.data[1] = 'e';
    m.data[2] = 'i';
    m.data[3] = '\0';
    m.length = 4;

    CAN_transmit(&m);
    printf("message: %s \n\r", m.data);
  */
  Message answer;
  if (!CAN_receive(&answer)) {
    printf("answer: %s \n\r", answer.data);
  }
  //Serial.print(answer.data[0]);
  delay(1000);
}
