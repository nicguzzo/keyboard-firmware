#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define N_COLS 6
#define N_ROWS 5
#define KEY_DELAY 5
#define USI_DATA        USIDR
#define USI_STATUS      USISR
#define USI_CONTROL     USICR
#define USI_ADDRESS     0x8

#define NONE        0
#define ACK_PR_RX     1
#define BYTE_RX       2
#define ACK_PR_TX     3
#define PR_ACK_TX     4
#define BYTE_TX       5

#define DDR_USI             DDRB
#define PORT_USI            PORTB
#define PIN_USI             PINB
#define PORT_USI_SDA        PORTB5
#define PORT_USI_SCL        PORTB7

volatile uint8_t COMM_STATUS = NONE;

volatile uint8_t keys[6]={11,12,13,14,15,16};
volatile uint8_t i=0,col;

void USI_init(void) {
  // 2-wire mode; Hold SCL on start and overflow; ext. clock
  USI_CONTROL |= (1<<USIWM1) | (1<<USICS1);
  USI_STATUS = 0xf0;  // write 1 to clear flags, clear counter
  DDR_USI  &= ~(1<<PORT_USI_SDA);
  PORT_USI &= ~(1<<PORT_USI_SDA);
  DDR_USI  |=  (1<<PORT_USI_SCL);
  PORT_USI |=  (1<<PORT_USI_SCL);
  // startcondition interrupt enable
  USI_CONTROL |= (1<<USISIE);
}

int main(void) {
  
  DDRD |= _BV(PORTD6); //test led
  PORTD &= ~_BV(PORTD6);
  
  //port B as outputs  
  DDRB |= _BV(PORTB0);
  DDRB |= _BV(PORTB1);
  DDRB |= _BV(PORTB2);
  DDRB |= _BV(PORTB3);
  DDRB |= _BV(PORTB4);
  DDRB |= _BV(PORTB6);
  PORTB |= _BV(PORTB0);
  PORTB |= _BV(PORTB1);
  PORTB |= _BV(PORTB2);
  PORTB |= _BV(PORTB3);
  PORTB |= _BV(PORTB4);
  PORTB |= _BV(PORTB6);

  //set port d as inputs
  DDRD &= ~_BV(PORTD0);
  DDRD &= ~_BV(PORTD1);
  DDRD &= ~_BV(PORTD2);
  DDRD &= ~_BV(PORTD3);
  DDRD &= ~_BV(PORTD4);
  //enable internal pull-ups on port d pins
  PORTD |= _BV(PORTD0);
  PORTD |= _BV(PORTD1);
  PORTD |= _BV(PORTD2);
  PORTD |= _BV(PORTD3);
  PORTD |= _BV(PORTD4);
  _delay_ms(500);
  USI_init();
  sei();
  
  for(;;) { 
    PORTD |= _BV(PORTD6);
    _delay_ms(50);
    PORTD &= ~_BV(PORTD6);
    _delay_ms(50);
  }

}

ISR(USI_START_vect) {
  //uint8_t tmpUSI_STATUS;
  //tmpUSI_STATUS = USI_STATUS;
  COMM_STATUS = NONE;
  // Wait for SCL to go low to ensure the "Start Condition" has completed.
  // otherwise the counter will count the transition
  while ( (PIN_USI & (1<<PORT_USI_SCL)) );
  USI_STATUS = 0xf0; // write 1 to clear flags; clear counter
  // enable USI interrupt on overflow; SCL goes low on overflow
  USI_CONTROL |= (1<<USIOIE) | (1<<USIWM0);
}


ISR(USI_OVERFLOW_vect) {
  uint8_t BUF_USI_DATA = USI_DATA;
  switch(COMM_STATUS) {
  case NONE:
    if (((BUF_USI_DATA & 0xfe) >> 1) != USI_ADDRESS) {  // if not receiving my address
      // disable USI interrupt on overflow; disable SCL low on overflow
      USI_CONTROL &= ~((1<<USIOIE) | (1<<USIWM0));
    }
    else { // else address is mine
      DDR_USI  |=  (1<<PORT_USI_SDA);
      USI_STATUS = 0x0e;  // reload counter for ACK, (SCL) high and back low
      if (BUF_USI_DATA & 0x01) COMM_STATUS = ACK_PR_TX; else COMM_STATUS = ACK_PR_RX;
    }
    break;
  case ACK_PR_RX:
    DDR_USI  &= ~(1<<PORT_USI_SDA);
    COMM_STATUS = BYTE_RX;
    break;
  case BYTE_RX:
    /* Save received byte here! ... = USI_DATA*/
    DDR_USI  |=  (1<<PORT_USI_SDA);
    USI_STATUS = 0x0e;  // reload counter for ACK, (SCL) high and back low
    COMM_STATUS = ACK_PR_RX;
    break;
  case ACK_PR_TX:
    /* Put first byte to transmit in buffer here! USI_DATA = ... */

    PORTB &= ~_BV(PORTB0);
    _delay_ms(KEY_DELAY);
    keys[0]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB0);

    PORTB &= ~_BV(PORTB1);
    _delay_ms(KEY_DELAY);
    keys[1]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB1);

    PORTB &= ~_BV(PORTB2);
    _delay_ms(KEY_DELAY);
    keys[2]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB2);

    PORTB &= ~_BV(PORTB3);
    _delay_ms(KEY_DELAY);
    keys[3]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB3);

    PORTB &= ~_BV(PORTB4);
    _delay_ms(KEY_DELAY);
    keys[4]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB4);

    PORTB &= ~_BV(PORTB6);
    _delay_ms(KEY_DELAY);
    keys[5]=(~PIND)&0x1f;
    PORTB |= _BV(PORTB6);
    i=0;
    USI_DATA =keys[i];    
    PORT_USI |=  (1<<PORT_USI_SDA); // transparent for shifting data out
    COMM_STATUS = BYTE_TX;
    i++;
    break;
  case PR_ACK_TX:
    if(BUF_USI_DATA & 0x01) {
      COMM_STATUS = NONE; // no ACK from master --> no more bytes to send
    }
    else {
      /* Put next byte to transmit in buffer here! USI_DATA = ... */      
      USI_DATA =keys[i];      
      PORT_USI |=  (1<<PORT_USI_SDA); // transparent for shifting data out
      DDR_USI  |=  (1<<PORT_USI_SDA);
      COMM_STATUS = BYTE_TX;
      if(i<6)
        i++;
    }
    break;
  case BYTE_TX:
    DDR_USI  &= ~(1<<PORT_USI_SDA);
    PORT_USI &= ~(1<<PORT_USI_SDA);
    USI_STATUS = 0x0e;  // reload counter for ACK, (SCL) high and back low
    COMM_STATUS = PR_ACK_TX;
    break;
  }
  USI_STATUS |= (1<<USIOIF); // clear overflowinterruptflag, this also releases SCL
}