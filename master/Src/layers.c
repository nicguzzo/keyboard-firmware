#include "layers.h"


layer_state_t layer_state;
layer_t layers_left[8];
layer_t layers_right[8];

void init_layers(){

  //layer[0] //commands layers

  layers_left[0].keys[0]=NEXT_LAYER;
  layers_left[0].keys[1]=PREV_LAYER;
  // TODO: map all commands...
  // ... // 

  //layer[1] // user layer 1

  layers_left[1].keys[0]=KEY_ENTER;
  layers_left[1].keys[1]=KEY_SPACE;

  // TODO: map all keycodes...
  // ... // 

}