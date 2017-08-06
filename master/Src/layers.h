#ifndef _H_LAYERS
#define _H_LAYERS
#include "keyboard.h"

typedef struct{
  uint16_t keys[30];
}layer_t;

typedef struct {
  uint8_t current_layer_l;
  uint8_t current_layer_r;
}layer_state_t;

void init_layers();


enum {
  NEXT_LAYER=0x1000,
  PREV_LAYER,
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

extern layer_state_t layer_state;
extern layer_t layers_left[8];
extern layer_t layers_right[8];

#endif