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
  layer_t layer[MAX_LAYERS];
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
  uint8_t current_layer;
  uint8_t mode; //0 =normal 1= cmd
  uint8_t cmd_key;  
}layers_t;

void init_layers();

void send_event(uint8_t code,uint8_t press);
void is_mouse(uint8_t code);

enum {
  NEXT_LAYER=0,
  PREV_LAYER,
  NEXT_LAYER_R,
  PREV_LAYER_R,
  NEXT_LAYER_L,
  PREV_LAYER_L,
  LAYER_1,
  LAYER_2,
  LAYER_3,
  LAYER_4,
  LAYER_5,
  LAYER_6,
  LAYER_7,
  LAYER_8,
  LAYER_1_L,
  LAYER_2_L,
  LAYER_3_L,
  LAYER_4_L,
  LAYER_5_L,
  LAYER_6_L,
  LAYER_7_L,
  LAYER_8_L,
  LAYER_1_H,
  LAYER_2_H,
  LAYER_3_H,
  LAYER_4_H,
  LAYER_5_H,
  LAYER_6_H,
  LAYER_7_H,
  LAYER_8_H
};

extern layers_t layers;


#endif
