#ifndef _H_LAYERS
#define _H_LAYERS
#include "keyboard.h"

#define MAX_LAYERS 8
#define MAX_KEYS 64
#define DISABLED_KEY 0xff
#define LEFT 0
#define RIGHT 1
typedef struct{
  uint8_t keys[MAX_KEYS];  
}layer_t;

typedef struct{
  
  uint8_t lctrl; //modifiers are fixed for all layers
  uint8_t lshift;
  uint8_t lalt;
  uint8_t lmeta;
  uint8_t rctrl;
  uint8_t rshift;
  uint8_t ralt;
  uint8_t rmeta;
  uint8_t mu; //mouse
  uint8_t md;
  uint8_t ml;
  uint8_t mr;
  uint8_t mb1;
  uint8_t mb2;
  uint8_t mb3;
  uint8_t mb4;
  uint8_t mb5;
  uint8_t current_layer;
  uint8_t mode; //0 =normal 1= cmd
  uint8_t cmd_key;
  //uint8_t padding;// padding for 2 byte aligned structure   
  layer_t layer[MAX_LAYERS];
}layers_t;

void init_layers();

void send_event(uint8_t code,uint8_t press);
uint8_t is_mouse(uint8_t code,uint8_t press);

enum {
  NEXT_LAYER=0,
  PREV_LAYER,
  
};

extern int8_t incx;
extern int8_t incy;
extern layers_t layers;


#endif
