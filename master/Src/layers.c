#include "layers.h"

void readFlash(void);

layers_t layers;

void sendkey(uint8_t side,uint8_t code,uint8_t press);
void process_commands(uint8_t side,uint8_t code,uint8_t press);

void init_layers(){
  //int i,j;
  uint8_t *layers_8=(uint8_t *)&layers;
  readFlash();
  if(layers_8[0]==0xff){
    layers.state.command_mode=0;
    layers.state.curr[LEFT]=1;
    layers.state.curr[RIGHT]=1;
    layers.state.layer_key=27;
  }

  //disable all keys by default
  /*for(i=0;i<MAX_LAYERS;i++){
    for(j=0;j<MAX_KEYS;j++){
      layers.side[0][i].keys[j]=DISABLED_KEY;      
      layers.side[1][i].keys[j]=DISABLED_KEY;
    }
  }*/
  keyboard_setModifiers(0);
}
static uint8_t modifier=0;

uint8_t is_modifier(uint8_t side,uint8_t code,uint8_t l,uint8_t press){
  uint8_t mod=1;

  if(code==layers.side[side][l].lshift){
    if(press)
      modifier|=KEY_MOD_LSHIFT;
    else
      modifier&=~KEY_MOD_LSHIFT;
  }else if(code==layers.side[side][l].rshift){
    if(press)
      modifier|=KEY_MOD_RSHIFT;
    else
      modifier&=~KEY_MOD_RSHIFT;
  }else if(code==layers.side[side][l].lctrl){
    if(press)
      modifier|=KEY_MOD_LCTRL;
    else
      modifier&=~KEY_MOD_LCTRL;
  }else if(code==layers.side[side][l].rctrl){
    if(press)
      modifier|=KEY_MOD_RCTRL;
    else
      modifier&=~KEY_MOD_RCTRL;
  }else if(code==layers.side[side][l].lalt){
    if(press)
      modifier|=KEY_MOD_LALT;
    else
      modifier&=~KEY_MOD_LALT;
  }else if(code==layers.side[side][l].ralt){
    if(press)
      modifier|=KEY_MOD_RALT;
    else
      modifier&=~KEY_MOD_RALT;
  }else if(code==layers.side[side][l].lmeta){
    if(press)
      modifier|=KEY_MOD_LMETA;
    else
      modifier&=~KEY_MOD_LMETA;
  }else if(code==layers.side[side][l].rmeta){
    if(press)
      modifier|=KEY_MOD_RMETA;
    else
      modifier&=~KEY_MOD_RMETA;
  }else{
    mod=0;    
  }

  return mod;
}

void send_event(uint8_t side,uint8_t code,uint8_t press){  
  Log("press: %d key: %d code: %#02x\n\r",press,code,layers.side[side][layers.state.curr[side]].keys[code]);
  if(layers.state.command_mode){
    if(code==layers.state.layer_key){
      layers.state.command_mode=0; //go back to normal    
      Log("leaving command mode\r\n");
    }else{      
      process_commands(side,code,press);
    }
  }else{
    if(code==layers.state.layer_key){
      Log("entering command mode\r\n");
      layers.state.command_mode=1; // go to command mode
    }else{
      sendkey(side,code,press);           
    }
  }
}
void sendkey(uint8_t side,uint8_t code,uint8_t press){
  if(is_modifier(side,code,layers.state.curr[side],press)){
    keyboard_setModifiers(modifier);
    if(press){
      keyboard_pressScanCode(0);
    }else{
      keyboard_releaseScanCode(0);
    }
  }else{
    if(layers.side[side][layers.state.curr[side]].keys[code]!= DISABLED_KEY){
      if(press){
        keyboard_pressScanCode(layers.side[side][layers.state.curr[side]].keys[code]);
      }else{
        keyboard_releaseScanCode(layers.side[side][layers.state.curr[side]].keys[code]);
      }    
    }
  }
}
void process_commands(uint8_t side,uint8_t code,uint8_t press){
  switch(layers.side[side][0].keys[code]){
    case NEXT_LAYER: //increments both layers
    if(layers.state.curr[RIGHT]<MAX_LAYERS-1){
      layers.state.curr[RIGHT]++;
    }
    if(layers.state.curr[LEFT]<MAX_LAYERS-1){
      layers.state.curr[LEFT]++;
    }
    break;
    case PREV_LAYER: //decremnts both layers
    if(layers.state.curr[RIGHT]>0){
      layers.state.curr[RIGHT]--;
    }
    if(layers.state.curr[LEFT]>0){
      layers.state.curr[LEFT]--;
    }
    break;
    //..
    //TODO: implement all commands
    //
    default:
      sendkey(side,code,press);
  }
}
