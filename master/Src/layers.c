#include "layers.h"


layer_state_t layer_state;
layer_t layers_left[8];
layer_t layers_right[8];

void process_commands(uint16_t code);

void init_layers(){
  int i,j;
  layer_state.command_mode=0;
  layer_state.current_layer_r=1;
  layer_state.current_layer_l=1;
  layer_state.layer_key=2;

  //disable all keys by default
  for(i=0;i<MAX_LAYERS;i++){
    for(j=0;j<MAX_KEYS;j++){
      layers_left[i].keys[j]=DISABLED_KEY;
      layers_right[i].keys[j]=DISABLED_KEY;
    }
  }
  //layer[0] //commands layers

  layers_left[0].keys[0]=NEXT_LAYER;
  layers_left[0].keys[1]=PREV_LAYER;
  // TODO: map all commands...
  // ... // 

  //layer[1] // user layer 1

  layers_left[1].keys[0]=KEY_ENTER;
  layers_left[1].keys[1]=KEY_SPACE;
  layers_left[1].keys[3]=KEY_A;

  // TODO: map all keycodes...
  // ... // 

}

void send_event(uint16_t code,uint8_t press){
  if(layer_state.command_mode){
    if(code==layer_state.layer_key){
      layer_state.command_mode=0; //go back to normal      
    }else{
      if(code <30){
        process_commands(layers_right[0].keys[code]);
      }else{        
        process_commands(layers_left[0].keys[code]);        
      }
    }
  }else{
    if(code==layer_state.layer_key){
      layer_state.command_mode=1; // go to command mode
    }else{
      if(layers_right[layer_state.current_layer_r].keys[code]!= DISABLED_KEY){
        if(code <30){ // right
          if(press){
            keyboard_press(layers_right[layer_state.current_layer_r].keys[code]);
          }else{
            keyboard_release(layers_right[layer_state.current_layer_r].keys[code]);
          }    
        }else{ //left
          if(press){
            keyboard_press(layers_left[layer_state.current_layer_l].keys[code-30]);
          }else{
            keyboard_release(layers_left[layer_state.current_layer_l].keys[code-30]);
          }
        }
      }
    }
  }
}

void process_commands(uint16_t code){
  switch(code){
    case NEXT_LAYER: //increments both layers
      if(layer_state.current_layer_r<MAX_LAYERS-1){
        layer_state.current_layer_r++;
      }
      if(layer_state.current_layer_l<MAX_LAYERS-1){
        layer_state.current_layer_l++;
      }
    break;
    case PREV_LAYER: //decremnts both layers
      if(layer_state.current_layer_r>0){
        layer_state.current_layer_r--;
      }
      if(layer_state.current_layer_l>0){
        layer_state.current_layer_l--;
      }
    break;
    //..
    //TODO: implement all commands
    //
  }
}