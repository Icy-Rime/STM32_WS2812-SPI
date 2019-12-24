#include "WS2812.h"

const RGBColor_TypeDef RED      = {255,0,0};
const RGBColor_TypeDef GREEN    = {0,255,0};
const RGBColor_TypeDef BLUE     = {0,0,255};
const RGBColor_TypeDef SKY      = {0,255,255};
const RGBColor_TypeDef MAGENTA  = {255,0,220};
const RGBColor_TypeDef YELLOW   = {127,216,0};
const RGBColor_TypeDef ORANGE   = {127,106,0};
const RGBColor_TypeDef BLACK    = {0,0,0};
const RGBColor_TypeDef WHITE    = {255,255,255};

u8 pixelBuffer[ Pixel_S1_NUM ][24];

void WS2812_Configuration()
{
    
    GPIO_InitTypeDef    GPIOInitStructure;
    SPI_InitTypeDef     SPIInitStructure;
    DMA_InitTypeDef     DMAInitStructure;
            
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
        
    GPIOInitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIOInitStructure);
    
    SPIInitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPIInitStructure.SPI_Mode = SPI_Mode_Master;
    SPIInitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPIInitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPIInitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPIInitStructure.SPI_NSS = SPI_NSS_Soft;
    SPIInitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPIInitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPIInitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2,&SPIInitStructure);
    
    SPI_Cmd(SPI2,ENABLE);
    
    SPI_CalculateCRC(SPI2,DISABLE);
    
    SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE);
    
    
    DMA_DeInit(DMA1_Channel5);
    DMAInitStructure.DMA_PeripheralBaseAddr      = (u32) &(SPI2 -> DR);
    DMAInitStructure.DMA_MemoryBaseAddr          = (u32) &(*pixelBuffer);
    DMAInitStructure.DMA_DIR                     = DMA_DIR_PeripheralDST;        //PeripheralBaseAddr为目标地址,即从pixelBuffer到SPI1 -> DR
    DMAInitStructure.DMA_BufferSize              = ( Pixel_S1_NUM  )*24;
    DMAInitStructure.DMA_PeripheralInc           = DMA_PeripheralInc_Disable;
    DMAInitStructure.DMA_MemoryInc               = DMA_MemoryInc_Enable;
    DMAInitStructure.DMA_PeripheralDataSize      = DMA_PeripheralDataSize_Byte;
    DMAInitStructure.DMA_MemoryDataSize          = DMA_MemoryDataSize_Byte;
    DMAInitStructure.DMA_Mode                    = DMA_Mode_Normal;
    DMAInitStructure.DMA_Priority                = DMA_Priority_High;
    DMAInitStructure.DMA_M2M                     = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMAInitStructure);
    
    
    Delay_ms(1);
    RGB_BLACK(Pixel_S1_NUM  );
    Delay_ms(1);
       
}


void RGB_SetColor(unsigned char LedId, RGBColor_TypeDef Color)
{
    
    u8 i;
    if( LedId > ( Pixel_S1_NUM ) ) return; //to avoid overflow
  
    for(i=0;i<=7;i++)    pixelBuffer[LedId][i]= ( (Color.G & (1 << (7 -i)) )? (CODE1):CODE0 );
    for(i=8;i<=15;i++)   pixelBuffer[LedId][i]= ( (Color.R & (1 << (15-i)) )? (CODE1):CODE0 );
    for(i=16;i<=23;i++)  pixelBuffer[LedId][i]= ( (Color.B & (1 << (23-i)) )? (CODE1):CODE0 );

    
}

void rgb_SendArray(void)
{
    DMA_Cmd(DMA1_Channel5, DISABLE );
    DMA_ClearFlag(DMA1_FLAG_TC5);
    DMA_SetCurrDataCounter(DMA1_Channel5,( Pixel_S1_NUM ) * 24 );
    DMA_Cmd(DMA1_Channel5, ENABLE);
}



/* Basic Color Effects -------------------------------------------------------*/
/**
  * @brief  Configure the whole serial RGB pixels to red.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_RED(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)  
    RGB_SetColor(i,RED);
  
  rgb_SendArray();
}

/**
  * @brief  Configure the whole serial RGB pixels to green.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_GREEN(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,GREEN);
  
  rgb_SendArray();
}

/**
  * @brief  Configure the whole serial RGB pixels to blue.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_BLUE(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,BLUE);
  
  rgb_SendArray();
}

/**
  * @brief  Configure the whole serial RGB pixels to yellow.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_YELLOW(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,YELLOW);
  
  rgb_SendArray();
}

/**
  * @brief  Configure the whole serial RGB pixels to magenta.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_MAGENTA(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,MAGENTA);
  
  rgb_SendArray();
}


/**
  * @brief  Configure the whole serial RGB pixels to black/all-off.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_BLACK(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,BLACK);
  
  rgb_SendArray();
}

/**
  * @brief  Configure the whole serial RGB pixels to white.
  * @param  Pixel_LEN: the account of RGB pixels in serial
  * @retval None
  */
void RGB_WHITE(u16 Pixel_LEN)
{
  u8 i;
  for(i=0;i<Pixel_LEN;i++)
    RGB_SetColor(i,WHITE);
  
  rgb_SendArray();
}

/* Complicated Color Effects -------------------------------------------------*/
RGBColor_TypeDef Colourful_Wheel(u8 WheelPos)
{
  WheelPos = 255 - WheelPos;
  RGBColor_TypeDef color;
  if(WheelPos < 85) 
  {
    color.R = 255 - WheelPos * 3;
    color.G = 0;
    color.B = WheelPos * 3;
  return color;
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    color.R = 0;
    color.G = WheelPos * 3;
    color.B = 255 - WheelPos * 3;
  return color;
  }
  
  WheelPos -= 170;
  color.R = WheelPos * 3; 
  color.G = 255 - WheelPos * 3;
  color.B = 0;
  
  return color;  
}

void rainbowCycle(u8 Pixel_LEN)  
{
  u16 i, j=0;
  for( j=0; j<1023; j++)  // 1 cycles of all colors on wheel
  { 
    for( i=0; i < Pixel_LEN; i++)  
      RGB_SetColor(i,Colourful_Wheel(((i * 256 / Pixel_LEN) + j)&255));
    
    rgb_SendArray();
    Delay_ms(20);
  }
}

