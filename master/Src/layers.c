#include "layers.h"
#include "mouse.h"
void readFlash(void);

layers_t layers;
int8_t incx=0;
int8_t incy=0;
void sendkey(uint8_t code,uint8_t press);
void process_commands(uint8_t code,uint8_t press);

void init_layers(){
  uint16_t i,j;
  //disable all keys by default
  for(i=0;i<MAX_LAYERS;i++){
    for(j=0;j<MAX_KEYS;j++){
      layers.layer[i].keys[j]=DISABLED_KEY;
    }
  }

  readFlash();
  layers.mode=0;
  layers.current_layer=1;

  keyboard_setModifiers(0);
}
static uint8_t modifier=0;

void is_mouse(uint8_t code,uint8_t press)
{

  static int8_t incu=1;
  static int8_t incd=1;
  static int8_t incl=1;
  static int8_t incr=1;

  //TODO: make MAX_INC a variable with conf settings??
  #define MAX_INC 60

  if(layers.mode){

    if(press){
      if(code==layers.mu){
        if(incu<MAX_INC)
          //incu++;
          incu*=2;
        incy=-incu;
      }
      if(code==layers.md){
        if(incd<MAX_INC)
          //incd++;
          incd*=2;
        incy=incd;
      }
      if(code==layers.ml){
        if(incl<MAX_INC)
          //incl++;
          incl*=2;
        incx=-incl;
      }
      if(code==layers.mr){
        if(incr<MAX_INC)
          //incr++;
          incr*=2;
        incx=incr;
      }
    }else{
      if(code==layers.mu){
        incu=1;
      }
      if(code==layers.md){
        incd=1;
      }
      if(code==layers.ml){
        incl=1;
      }
      if(code==layers.mr){
        incr=1;
      }
    }

  }
}

uint8_t is_modifier(uint8_t code,uint8_t press){
  uint8_t mod=1;

  if(code==layers.lshift){
    if(press)
      modifier|=KEY_MOD_LSHIFT;
    else
      modifier&=~KEY_MOD_LSHIFT;
  }else if(code==layers.rshift){
    if(press)
      modifier|=KEY_MOD_RSHIFT;
    else
      modifier&=~KEY_MOD_RSHIFT;
  }else if(code==layers.lctrl){
    if(press)
      modifier|=KEY_MOD_LCTRL;
    else
      modifier&=~KEY_MOD_LCTRL;
  }else if(code==layers.rctrl){
    if(press)
      modifier|=KEY_MOD_RCTRL;
    else
      modifier&=~KEY_MOD_RCTRL;
  }else if(code==layers.lalt){
    if(press)
      modifier|=KEY_MOD_LALT;
    else
      modifier&=~KEY_MOD_LALT;
  }else if(code==layers.ralt){
    if(press)
      modifier|=KEY_MOD_RALT;
    else
      modifier&=~KEY_MOD_RALT;
  }else if(code==layers.lmeta){
    if(press)
      modifier|=KEY_MOD_LMETA;
    else
      modifier&=~KEY_MOD_LMETA;
  }else if(code==layers.rmeta){
    if(press)
      modifier|=KEY_MOD_RMETA;
    else
      modifier&=~KEY_MOD_RMETA;
  }else{
    mod=0;
  }

  return mod;
}

void send_event(uint8_t code,uint8_t press){

  if(layers.mode){//command mode, layer 0
    if(code==layers.cmd_key){
      layers.mode=0; //go back to normal
      Log1("leaving command mode\r\n");
    }else{
      process_commands(code,press);
    }
  }else{
    if(code==layers.cmd_key){
      Log1("entering command mode\r\n");
      layers.mode=1; // go to command mode
    }else{
      sendkey(code,press);
    }
  }
}
void sendkey(uint8_t code,uint8_t press){

  //is_mouse(code,press);
  Log1("press: %d key: %d code: %#02x current_layer %d\n\r",
    press,
    code,
    layers.layer[layers.current_layer].keys[code],
    layers.current_layer
  );
  if(is_modifier(code,press)){
    keyboard_setModifiers(modifier);
    if(press){
      keyboard_pressScanCode(0);
    }else{
      keyboard_releaseScanCode(0);
    }
  }else{
    if(layers.layer[layers.current_layer].keys[code]!= DISABLED_KEY){
      if(press){
        keyboard_pressScanCode(layers.layer[layers.current_layer].keys[code]);
      }else{
        keyboard_releaseScanCode(layers.layer[layers.current_layer].keys[code]);
      }
    }
  }
}
void process_commands(uint8_t code,uint8_t press){
  uint8_t curr_l;
  switch(layers.layer[0].keys[code]){
    case NEXT_LAYER:

    break;
    case PREV_LAYER:

    break;
    //..
    //TODO: implement all commands
    //
    default:
      curr_l=layers.current_layer;
      layers.current_layer=0;
      sendkey(code,press);
      layers.current_layer=curr_l;
  }
}
