//Author: Nicolas Guzzo
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#define N_COLS 6
#define N_ROWS 5



int main (void)
{
  unsigned char keys[N_COLS][N_ROWS];
  int row,col;
  unsigned char col_pins[N_COLS];
  unsigned char row_pins[N_ROWS];

  memset(keys,0,sizeof(keys));  

  //port B as outputs
  DDRB |= _BV(DDB0);
  DDRB |= _BV(DDB1);
  DDRB |= _BV(DDB2);
  DDRB |= _BV(DDB3);
  DDRB |= _BV(DDB4);
  DDRB |= _BV(DDB6);

  //set port d as inputs
  DDRD &= ~_BV(PORTD0);
  DDRD &= ~_BV(PORTD1);
  DDRD &= ~_BV(PORTD2);
  DDRD &= ~_BV(PORTD3);
  DDRD &= ~_BV(PORTD4);
  //enable internal pull-ups on port d pins
  PORTD |= _BV(DDD1);
  PORTD |= _BV(DDD2);
  PORTD |= _BV(DDD3);
  PORTD |= _BV(DDD4);
  PORTD |= _BV(DDD5);
 
  col_pins[0]=PORTB0;
  col_pins[1]=PORTB1;
  col_pins[2]=PORTB2;
  col_pins[3]=PORTB3;
  col_pins[4]=PORTB4;
  col_pins[5]=PORTB6;

  row_pins[0]=PORTD0;
  row_pins[1]=PORTD1;
  row_pins[2]=PORTD2;
  row_pins[3]=PORTD3;
  row_pins[4]=PORTD4;

 while(1) {
  
  PORTB |= _BV(PORTB0);
  
  PORTB &= ~_BV(PORTB5);
  unsigned char k;
  for(col=0;col<6;col++){
    //set col low
    PORTB &= ~_BV(col_pins[col]);
    
    for(row=0;row<5;row++){
      k=PORTD& (0x1 << row );      
      if(keys[row][col]!=k){
        keys[row][col]=k;        
      }
    }
    PORTB |= _BV(col_pins[col]); 
    
  }
 }
}
