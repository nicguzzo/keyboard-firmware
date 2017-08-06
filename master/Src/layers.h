#ifndef _H_LAYERS
#define _H_LAYERS
#include "keyboard.h"

#define MAX_LAYERS 8
#define MAX_KEYS 30
#define DISABLED_KEY -1

typedef struct{
  uint16_t keys[MAX_KEYS];
}layer_t;

typedef struct {
  uint8_t current_layer_l;
  uint8_t current_layer_r;
  uint8_t command_mode;
  uint8_t layer_key;
}layer_state_t;

void init_layers();

void send_event(uint16_t code,uint8_t press);

enum {
  NEXT_LAYER=0x1000,
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

extern layer_state_t layer_state;
extern layer_t layers_left[MAX_LAYERS];
extern layer_t layers_right[MAX_LAYERS];

#endif