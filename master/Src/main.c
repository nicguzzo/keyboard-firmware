/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usb/usb_device.h"
#include "usb/usbd_cdc_if.h"
//#include "usb/USBSerial.h"

/* USER CODE BEGIN Includes */
//#include <stm32_hal_legacy.h>
#include "../bluepill_utils/utils.h"
#include "keyboard.h"
#include "mouse.h"
#include "layers.h"
#include <stdio.h>
#include <stdarg.h>

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define I2C_ADDRESS (0x8<<1)
#define USE_I2C
#define TEST
//#define STLINK

uint8_t keys[20];
uint8_t data[10];
char  tmp[128];
uint8_t endline[2];

HAL_StatusTypeDef ret;
/*const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};*/
void init_keyboard();

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM2_Init(void);
                                    
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void set_rgb(int r,int g,int b){
  TIM2->CCR1=b;
  TIM2->CCR2=g;
  TIM2->CCR3=r;
}

#if defined(STLINK)
#define Log printf
#else
void Log(const char* fmt, ...)
{
  va_list va;    
  va_start(va, fmt);
  vsnprintf(tmp, 127, fmt, va);      
  va_end(va);
  HAL_UART_Transmit(&huart1,(uint8_t*)tmp,strlen(tmp),500);
}
#endif
#define flashAddress 0x8000000
uint32_t saveAddress =flashAddress+(1024*64); // last page

uint8_t *layers_8=(uint8_t *)&layers;
uint16_t *layers_16=(uint16_t *)&layers;
uint32_t mSize=sizeof(layers_t);
uint32_t mSize_16=sizeof(layers_t)>>1;

void show_hal_error(char *msg,HAL_StatusTypeDef stat){
  switch(stat){
    case HAL_OK:      Log("%s Hal status HAL_OK\r\n",msg);      break;
    case HAL_ERROR:   Log("%s Hal status HAL_ERROR\r\n",msg);   break;
    case HAL_BUSY:    Log("%s Hal status HAL_BUSY\r\n",msg);    break;
    case HAL_TIMEOUT: Log("%s Hal status HAL_TIMEOUT\r\n",msg); break;
  }
}

void writeFlash(void)
{
  uint32_t i,j;
  uint32_t PageError; 
  HAL_StatusTypeDef stat;

  FLASH_EraseInitTypeDef einfo;
  einfo.TypeErase=FLASH_TYPEERASE_PAGES;
  einfo.Banks=FLASH_BANK_1;
  einfo.PageAddress =saveAddress;
  einfo.NbPages=1;
  set_rgb(65535,0,0);
  stat=HAL_FLASH_Unlock();
  if(stat!=HAL_OK){
    show_hal_error("HAL_FLASH_Unlock",stat);
  }
  stat=HAL_FLASHEx_Erase(&einfo,&PageError);
  if(stat!=HAL_OK){
    show_hal_error("HAL_FLASHEx_Erase",stat);
  }
  if(PageError == 0xFFFFFFFF){
    Log("erase ok.\r\n");
  }else{
    Log("erase failed at dir %#x.\r\n",PageError);
  }
  for(i=0,j=0; i<mSize_16; i++,j+=2){
    stat=HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,saveAddress+j,layers_16[i]);
    if(stat!=HAL_OK){
      show_hal_error("HAL_FLASH_Program",stat);
    }
    (i%2)?set_rgb(65535,0,0): set_rgb(0,0,65535);
  }
  stat=HAL_FLASH_Lock();
  if(stat!=HAL_OK){
    show_hal_error("HAL_FLASH_Lock",stat);
  }
  set_rgb(0,65535,0);
}

void readFlash(void)
{
  uint32_t i;
  Log("Reading conf from flash.\r\n");
  uint8_t* saved=(uint8_t*)saveAddress;
  for(i=0; i<mSize; i++){
    layers_8[i] = saved[i];
    //Log("%#02x  %#02x \r\n",layers_8[i],saved[i]);
  }
  Log("done.\r\n");
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  GPIO_PinState keys_master[30];
  int keys_slave[30];
  int i,j,k,kk;
  endline[0]='\n';
  endline[1]='\r';
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  init_vector_table();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  reenumerate_usb();

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  
  //MX_USB_DEVICE_Init();
  MX_USART1_UART_Init();
  //MX_I2C2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  

  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
  set_rgb(0,0,0);
   

  //jsmn_init(&parser);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */  
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
  init_keyboard();
  init_mouse();
  
  beginSerialHID(&keyboard.device,&mouse.device);
  
  
#ifdef USE_I2C
  MX_I2C2_Init();
  while((ret=HAL_I2C_IsDeviceReady(&hi2c2, I2C_ADDRESS,5,500))!=HAL_OK){
    //Log("ret1 0x%x\n\r",ret);
    show_hal_error("HAL_I2C_IsDeviceReady",ret);
    
    HAL_I2C_DeInit(&hi2c2);
    set_rgb(65535,0,0);
    HAL_Delay(200);
    set_rgb(0,65535,0);        
    HAL_Delay(200);
    set_rgb(0,0,65535);    
    HAL_Delay(200);

    MX_I2C2_Init();
    set_rgb(65535,0,0);
    HAL_Delay(200);
    set_rgb(0,65535,0);        
    HAL_Delay(200);
    set_rgb(0,0,65535);    
    HAL_Delay(200);
  }
#endif
  Log("conf size: %d bytes\r\n",mSize);
  
  init_layers();
  set_rgb(0,65535,0);
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    check_bootloader();
    //read master matrix
    for(i=5;i>=0;i--){
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3<<i,0);
      HAL_Delay(2);
      for(j=4;j>=0;j--){
        k=!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3<<j);
        kk=(4-j)*6+i;
        
        //if(mouse){
          //mouse
        //}else{
          if(k==1 && keys_master[kk]==0){                    
            send_event(RIGHT,kk,1);
          }
          if(k==0 && keys_master[kk]==1){          
            send_event(RIGHT,kk,0);
          }
        //}

        keys_master[kk]=k;
      }  
      HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3<<i,1);    
    }
#ifdef USE_I2C
    //read from slave via i2c
    data[0]=0x0;
    ret=HAL_I2C_Master_Transmit (&hi2c2, I2C_ADDRESS, data, 1,(uint32_t)500);
    if(HAL_OK!=ret){
      show_hal_error("HAL_I2C_Master_Transmit",ret);
      //Log("ret2 0x%x\n\r",ret);      
    }else{
    
      ret=HAL_I2C_Master_Receive (&hi2c2, I2C_ADDRESS, keys, 6,(uint32_t)500);
      if(HAL_OK!=ret){
        show_hal_error("HAL_I2C_Master_Receive",ret);
        //Log("ret3 0x%x\n\r",ret);        
      }else{
        for(i=0;i<6;i++){
          for(j=0;j<5;j++){
            
            k=((keys[i]>>j) & 0x1);
            kk=(j*6+i);
            if(k==1 && keys_slave[kk]==0){              
              send_event(LEFT,kk,1);
            }
            if(k==0 && keys_slave[kk]==1){              
              send_event(LEFT,kk,0);
            }
            keys_slave[kk]=k;
          }  
          //if(i==0 && (keys[i] & 0x1) ){
            //keyboard_write(0x8);
            //test_kb();
            //data[0]='h';
            //data[1]='i';
            //CDC_Transmit_FS(data,2);
            //Log(tmp,"rand_max%d\n\r",RAND_MAX);            
          //}
          //Log(tmp,"%d ",keys[i]);          
          //HAL_UART_Transmit(&huart1,(uint8_t*)bit_rep[keys[i] >> 4],4,500);
          //HAL_UART_Transmit(&huart1,(uint8_t*)bit_rep[keys[i] & 0x0F],4,500);
          //HAL_UART_Transmit(&huart1,endline,2,500);
        }  
      }
    }
#endif
    //set_rgb(rand()>>16,rand()>>16,rand()>>16);
    keyboard_sendReport();
    //key debounce
    HAL_Delay(5);
  }
  /* USER CODE END 3 */

}

void USBSerial_Rx_Handler(uint8_t *data, uint16_t len){
  Log("cmd: \r\n");
  HAL_UART_Transmit(&huart1,data,len,500);
  Log("\r\n");
  char dd[20];
  int i,j,l,k,s;
  uint8_t code;
  if(len>=4 && data[0]=='s' && data[1]=='a'&& data[2]=='v'&& data[3]=='e'){
    Log("layers size: %d\n\r",sizeof(layers));
    Log("writing conf to flash...\r\n");
    writeFlash();
    Log("done.\r\n");
  }
  // r1
  if(len>=6 && (data[0]=='r'||data[0]=='l')){    
    if(data[0]=='r'){      
      s=RIGHT;
    }
    if(data[0]=='l'){
      s=LEFT;
    }
    dd[0]=data[1];    
    dd[1]='\0';
    l=atoi(dd); //layer
    dd[0]=data[2];
    dd[1]=data[3];
    dd[2]='\0';
    k=atoi(dd); //key    
    Log(" side: %c layer: %d key: %d ",data[0],l,k);
    if(k>=0 && k <MAX_KEYS){

      switch(data[4])
      {
        case 'c':
          {
            dd[0]=data[5];
            dd[1]=data[6];
            dd[2]='\0';
            code=strtoul(dd, NULL, 16) & 0xff;
            Log("code: %#02x\r\n",code);  
            layers.side[s][l].keys[k]=code;
          }
          break;
        case 'p':
          {
            dd[0]=data[5];
            dd[1]=data[6];
            if(data[5]=='M'){
              switch(data[6]){
                case 'U':
                  layers.side[s][l].mu=k;
                break;
                case 'D':
                  layers.side[s][l].md=k;
                break;
                case 'L':
                  layers.side[s][l].ml=k;
                break;
                case 'R':
                  layers.side[s][l].mr=k;
                break;

              }
            }
            /*if(len>=11){
              dd[0]=data[5];
              dd[1]=data[6];
              dd[2]=data[7];
              dd[3]='\0';
              px=atoi(dd);
              dd[0]=data[8];
              dd[1]=data[9];
              dd[2]=data[10];
              dd[3]='\0';
              py=atoi(dd);
              Log("px %d py %d\r\n",px,py);

            }*/
          }
          break;
        case 'm':
          {
            for(j=0,i=5;i<len && j<20;j++,i++){
              dd[j]=data[i];
            }
            dd[j]='\0';
            Log("modif: %s\r\n",dd);
            layers.side[s][l].keys[k]=DISABLED_KEY;
            if(strcmp(dd,"LSHIFT")==0){
              layers.side[s][l].lshift=k;
            }
            if(strcmp(dd,"RSHIFT")==0){
              layers.side[s][l].rshift=k;
            }
            if(strcmp(dd,"LCTRL")==0){
              layers.side[s][l].lctrl=k;
            }
            if(strcmp(dd,"RCTRL")==0){
              layers.side[s][l].rctrl=k;
            }
            if(strcmp(dd,"LALT")==0){
              layers.side[s][l].lalt=k;
            }
            if(strcmp(dd,"RALTL")==0){
              layers.side[s][l].ralt=k;
            }
            if(strcmp(dd,"LMETA")==0){
              layers.side[s][l].lmeta=k;
            }
            if(strcmp(dd,"RMETA")==0){
              layers.side[s][l].rmeta=k;
            }

            if(strcmp(dd,"CMD")==0){
              layers.state.cmd_key=k;
              layers.state.cmd_key_side=s;
            }
          }
          break;
      }
    }
  }
}

/** System Clock Configuration
*/

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 
                           PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim2);

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  //while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
