// LCD_ili9488.c
// Driver LCD 3.5" 320x480 on ILI9488 chip
// based on: http://www.lcdwiki.com/
// Created: Aug 26, 2020
//       Author: Alex Shamilich

// Шрифты делаются программой
// MikroElektronika GLCD Font Creator 1.2.0.0
// MikroElektronika 2011 http://www.mikroe.com
//=======================================================================================

//#include "stm32f10x_conf.h"
#include "main.h"

#include "LCD_ili9488.h"
#include "string.h"

TLCD9488_DEV LCD9488_DEV;

uint16_t LCD9488_Point_Color = 0x0000;
uint16_t LCD9488_Back_Color  = 0xFFFF;
uint16_t LCD9488_DeviceCode;
//=======================================================================================
void LCD9488_Init_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LCD9488_DC_RS_GPIO_Port, 		LCD9488_DC_RS_Pin, 	GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD9488_CS_GPIO_Port, 		LCD9488_CS_Pin, 	GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD9488_RST_GPIO_Port, 		LCD9488_RST_Pin, 	GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD9488_LED_GPIO_Port, 		LCD9488_LED_Pin, 	GPIO_PIN_RESET);

//	/*Configure GPIO pin : PtPin */
//	GPIO_InitStruct.Pin = LD2_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD9488_DC_RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD9488_DC_RS_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD9488_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD9488_CS_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD9488_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD9488_RST_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LCD9488_LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LCD9488_LED_GPIO_Port, &GPIO_InitStruct);
}
//=======================================================================================
void LCD9488_Init(void)
{
	MX_SPI2_Init();
	HAL_Delay(100);
	LCD9488_Init_GPIO();

	LCD9488_LED_SET;//Включить подсветку

	HAL_Delay(100);
 	LCD9488_RESET();
 	HAL_Delay(100);

	LCD9488_Transport_WR_REG(0XF7);
	LCD9488_Transport_WR_DATA(0xA9);
	LCD9488_Transport_WR_DATA(0x51);
	LCD9488_Transport_WR_DATA(0x2C);
	LCD9488_Transport_WR_DATA(0x82);
	LCD9488_Transport_WR_REG(0xC0);
	LCD9488_Transport_WR_DATA(0x11);
	LCD9488_Transport_WR_DATA(0x09);
	LCD9488_Transport_WR_REG(0xC1);
	LCD9488_Transport_WR_DATA(0x41);
	LCD9488_Transport_WR_REG(0XC5);
	LCD9488_Transport_WR_DATA(0x00);
	LCD9488_Transport_WR_DATA(0x0A);
	LCD9488_Transport_WR_DATA(0x80);
	LCD9488_Transport_WR_REG(0xB1);
	LCD9488_Transport_WR_DATA(0xB0);
	LCD9488_Transport_WR_DATA(0x11);
	LCD9488_Transport_WR_REG(0xB4);
	LCD9488_Transport_WR_DATA(0x02);
	LCD9488_Transport_WR_REG(0xB6);
	LCD9488_Transport_WR_DATA(0x02);
	LCD9488_Transport_WR_DATA(0x42);
	LCD9488_Transport_WR_REG(0xB7);
	LCD9488_Transport_WR_DATA(0xc6);
	LCD9488_Transport_WR_REG(0xBE);
	LCD9488_Transport_WR_DATA(0x00);
	LCD9488_Transport_WR_DATA(0x04);
	LCD9488_Transport_WR_REG(0xE9);
	LCD9488_Transport_WR_DATA(0x00);
	LCD9488_Transport_WR_REG(0x36);
	LCD9488_Transport_WR_DATA((1<<3)|(0<<7)|(1<<6)|(1<<5));
	LCD9488_Transport_WR_REG(0x3A);
	LCD9488_Transport_WR_DATA(0x66);
	LCD9488_Transport_WR_REG(0xE0);
	LCD9488_Transport_WR_DATA(0x00);
	LCD9488_Transport_WR_DATA(0x07);
	LCD9488_Transport_WR_DATA(0x10);
	LCD9488_Transport_WR_DATA(0x09);
	LCD9488_Transport_WR_DATA(0x17);
	LCD9488_Transport_WR_DATA(0x0B);
	LCD9488_Transport_WR_DATA(0x41);
	LCD9488_Transport_WR_DATA(0x89);
	LCD9488_Transport_WR_DATA(0x4B);
	LCD9488_Transport_WR_DATA(0x0A);
	LCD9488_Transport_WR_DATA(0x0C);
	LCD9488_Transport_WR_DATA(0x0E);
	LCD9488_Transport_WR_DATA(0x18);
	LCD9488_Transport_WR_DATA(0x1B);
	LCD9488_Transport_WR_DATA(0x0F);
	LCD9488_Transport_WR_REG(0XE1);
	LCD9488_Transport_WR_DATA(0x00);
	LCD9488_Transport_WR_DATA(0x17);
	LCD9488_Transport_WR_DATA(0x1A);
	LCD9488_Transport_WR_DATA(0x04);
	LCD9488_Transport_WR_DATA(0x0E);
	LCD9488_Transport_WR_DATA(0x06);
	LCD9488_Transport_WR_DATA(0x2F);
	LCD9488_Transport_WR_DATA(0x45);
	LCD9488_Transport_WR_DATA(0x43);
	LCD9488_Transport_WR_DATA(0x02);
	LCD9488_Transport_WR_DATA(0x0A);
	LCD9488_Transport_WR_DATA(0x09);
	LCD9488_Transport_WR_DATA(0x32);
	LCD9488_Transport_WR_DATA(0x36);
	LCD9488_Transport_WR_DATA(0x0F);
	LCD9488_Transport_WR_REG(0x11);
	HAL_Delay(120);
	LCD9488_Transport_WR_REG(0x29);

	LCD9488_GUI_SetOrientation(USE_HORIZONTAL);
	LCD9488_GUI_Clear(WHITE);

}
//=======================================================================================
void LCD9488_Transport_SPI_WriteByte(uint8_t Byte)
{
	while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
		LCD_SPI.Instance->DR = Byte;
}
//=======================================================================================
void LCD9488_Transport_WR_REG(uint8_t data)
{
   LCD9488_CS_CLR;
   LCD9488_RS_CLR;
   LCD9488_Transport_SPI_WriteByte(data);
   HAL_SPI_Transmit(&LCD_SPI, &data, 1, 10);
   LCD9488_CS_SET;
}
//=======================================================================================
void LCD9488_Transport_WR_DATA(uint8_t data)
{
   LCD9488_CS_CLR;
   LCD9488_RS_SET;
   LCD9488_Transport_SPI_WriteByte(data);
   LCD9488_CS_SET;
}
//=======================================================================================
void LCD9488_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD9488_Transport_WR_REG(LCD_Reg);
	LCD9488_Transport_WR_DATA(LCD_RegValue);
}
//=======================================================================================
void LCD9488_WriteRAM_Prepare(void)
{
	LCD9488_Transport_WR_REG(LCD9488_DEV.WramCmd);
}
//=======================================================================================
void LCD9488_WriteData_16Bit(uint16_t Data)
{
	uint8_t r = (Data>>8)&0xF8; 	// RED Color
	uint8_t g = (Data>>3)&0xFC; 	// Green Color
	uint8_t b = Data<<3; 			// Blue Color

	LCD9488_CS_CLR;
	LCD9488_RS_SET;
	while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
		LCD_SPI.Instance->DR = r;

	while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
		LCD_SPI.Instance->DR = g;

	while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
		LCD_SPI.Instance->DR = b;

	while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );

	LCD9488_CS_SET;
}
//=======================================================================================
void LCD9488_GUI_Draw_Point(uint16_t x,uint16_t y)
{
	LCD9488_GUI_SetCursor(x,y);
	LCD9488_WriteData_16Bit(LCD9488_Point_Color);
}
//=======================================================================================
void LCD9488_GUI_Clear(uint16_t Color)
{
	LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);
	LCD9488_CS_CLR;
	LCD9488_RS_SET;
	uint32_t cnt = LCD9488_DEV.Height * LCD9488_DEV.Width;
	uint8_t r = (Color>>8)&0xF8; 	// RED Color
	uint8_t g = (Color>>3)&0xFC; 	// Green Color
	uint8_t b = Color<<3; 			// Blue Color

	while (cnt)
	{
		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = r;//RED

		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = g;//GREEN

		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = b;//BLUE

		cnt--;
	}
	LCD9488_CS_SET;
}

//=======================================================================================
void LCD9488_RESET(void)
{
	LCD9488_RST_CLR;
	HAL_Delay(100);
	LCD9488_RST_SET;
	HAL_Delay(50);
}
//=======================================================================================
void LCD9488_GUI_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{
	LCD9488_Transport_WR_REG(LCD9488_DEV.SetXcmd);
	LCD9488_Transport_WR_DATA(xStar>>8);
	LCD9488_Transport_WR_DATA(0x00FF&xStar);
	LCD9488_Transport_WR_DATA(xEnd>>8);
	LCD9488_Transport_WR_DATA(0x00FF&xEnd);

	LCD9488_Transport_WR_REG(LCD9488_DEV.SetYcmd);
	LCD9488_Transport_WR_DATA(yStar>>8);
	LCD9488_Transport_WR_DATA(0x00FF&yStar);
	LCD9488_Transport_WR_DATA(yEnd>>8);
	LCD9488_Transport_WR_DATA(0x00FF&yEnd);

	LCD9488_WriteRAM_Prepare();
}
//=======================================================================================
void LCD9488_GUI_SetOrientation(uint8_t direction)
{
			LCD9488_DEV.SetXcmd=0x2A;
			LCD9488_DEV.SetYcmd=0x2B;
			LCD9488_DEV.WramCmd=0x2C;
	switch(direction){
		case 0:										// 0 degree
			LCD9488_DEV.Width=LCD_W;
			LCD9488_DEV.Height=LCD_H;
			LCD9488_WriteReg(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:										// 90 degree
			LCD9488_DEV.Width=LCD_H;
			LCD9488_DEV.Height=LCD_W;
			LCD9488_WriteReg(0x36,(1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:										// 180 degree
			LCD9488_DEV.Width=LCD_W;
			LCD9488_DEV.Height=LCD_H;
			LCD9488_WriteReg(0x36,(1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:										// 270 degree
			LCD9488_DEV.Width=LCD_H;
			LCD9488_DEV.Height=LCD_W;
			LCD9488_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		default:break;
	}
}
//=======================================================================================
void LCD9488_GUI_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD9488_GUI_SetWindows(Xpos,Ypos,Xpos,Ypos);										// Окно размером в 1 точку
}

//=======================================================================================
void LCD9488_GUI_Draw_PointColor(uint16_t x,uint16_t y,uint16_t color)
{
	LCD9488_GUI_SetCursor(x,y);
	LCD9488_WriteData_16Bit(color);
}
//=======================================================================================
void LCD9488_GUI_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{
	uint16_t width  = ex - sx + 1;
	uint16_t height = ey - sy + 1;
	uint32_t cnt = height * width;
	uint8_t r = (color>>8)&0xF8; 	// RED Color
	uint8_t g = (color>>3)&0xFC; 	// Green Color
	uint8_t b = color<<3; 			// Blue Color

	LCD9488_GUI_SetWindows(sx,sy,ex,ey);

	LCD9488_CS_CLR;
	LCD9488_RS_SET;
	while (cnt)
	{
		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = r;//RED

		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = g;//GREEN

		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
			LCD_SPI.Instance->DR = b;//BLUE

//		while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );

		cnt--;
	}
	LCD9488_CS_SET;
	LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);
}
//=======================================================================================
void LCD9488_GUI_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	delta_x=x2-x1;
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1;
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )
	{
		LCD9488_GUI_Draw_Point(uRow,uCol);
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
//=======================================================================================
void LCD9488_GUI_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD9488_GUI_Draw_Line(x1,y1,x2,y1);
	LCD9488_GUI_Draw_Line(x1,y1,x1,y2);
	LCD9488_GUI_Draw_Line(x1,y2,x2,y2);
	LCD9488_GUI_Draw_Line(x2,y1,x2,y2);
}
//=======================================================================================
void LCD9488_GUI_Fill_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD9488_GUI_Fill(x1,y1,x2,y2,LCD9488_Point_Color);
}
//=======================================================================================
void LCD9488_GUI_INT_Circle8(int xc, int yc, int x, int y, uint16_t c)
{
	LCD9488_GUI_Draw_PointColor(xc + x, yc + y, c);
	LCD9488_GUI_Draw_PointColor(xc - x, yc + y, c);
	LCD9488_GUI_Draw_PointColor(xc + x, yc - y, c);
	LCD9488_GUI_Draw_PointColor(xc - x, yc - y, c);
	LCD9488_GUI_Draw_PointColor(xc + y, yc + x, c);
	LCD9488_GUI_Draw_PointColor(xc - y, yc + x, c);
	LCD9488_GUI_Draw_PointColor(xc + y, yc - x, c);
	LCD9488_GUI_Draw_PointColor(xc - y, yc - x, c);
}
//=======================================================================================
void LCD9488_GUI_Draw_Circle(int xc, int yc,uint16_t c,int r, int fill)
{
	int x = 0;
	int y = r;
	int yi;
	int d = 3 - 2 * r;

	if (fill)
	{
		while (x <= y)
		{
			for (yi = x; yi <= y; yi++)
				LCD9488_GUI_INT_Circle8(xc, yc, x, yi, c);

			if (d < 0)
			{
				d = d + 4 * x + 6;
			}
			else
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
	else
	{
		while (x <= y)
		{
			LCD9488_GUI_INT_Circle8(xc, yc, x, y, c);
			if (d < 0)
			{
				d = d + 4 * x + 6;
			}
			else
			{
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}
//=======================================================================================
void LCD9488_GUI_Draw_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD9488_GUI_Draw_Line(x0,y0,x1,y1);
	LCD9488_GUI_Draw_Line(x1,y1,x2,y2);
	LCD9488_GUI_Draw_Line(x2,y2,x0,y0);
}
//=======================================================================================
static void LCD9488_GUI_INT_swap(uint16_t *a, uint16_t *b)
{
	uint16_t tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
//=======================================================================================
void LCD9488_GUI_Fill_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	uint16_t a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1)
	{
    LCD9488_GUI_INT_swap(&y0,&y1);
		LCD9488_GUI_INT_swap(&x0,&x1);
 	}
 	if (y1 > y2)
	{
    LCD9488_GUI_INT_swap(&y2,&y1);
		LCD9488_GUI_INT_swap(&x2,&x1);
 	}
  if (y0 > y1)
	{
    LCD9488_GUI_INT_swap(&y0,&y1);
		LCD9488_GUI_INT_swap(&x0,&x1);
  }
	if(y0 == y2)
	{
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		LCD9488_GUI_Fill(a,y0,b,y0,LCD9488_Point_Color);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;

	if(y1 == y2)
	{
		last = y1;
	}
  else
	{
		last = y1-1;
	}
	for(y=y0; y<=last; y++)
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			LCD9488_GUI_INT_swap(&a,&b);
		}
		LCD9488_GUI_Fill(a,y,b,y,LCD9488_Point_Color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++)
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			LCD9488_GUI_INT_swap(&a,&b);
		}
		LCD9488_GUI_Fill(a,y,b,y,LCD9488_Point_Color);
	}
}
//=======================================================================================
void LCD9488_GUI_SetFont(unsigned char* AFont, uint16_t AFontColor, uint16_t ABackgroundColor) // Установить параметры для выбранного шрифта
{
	LCD9488_CurrentFont = AFont;														// Указатель на массив с данными шрифта
	LCD9488_Point_Color = AFontColor;													// Цвет пикселей рисования
	LCD9488_Back_Color  = ABackgroundColor;												// Цвет фона

	// Прочитать параметры шрифта
	LCD9488_CurrentFont_FirstChar		= LCD9488_CurrentFont[0];          				// Первый символ в наборе
	LCD9488_CurrentFont_LastChar		= LCD9488_CurrentFont[1];          				// Последний символ в наборе
	LCD9488_CurrentFont_Offset			= LCD9488_CurrentFont[2];          				// Число байтов на 1 символ в массиве шрифта
	LCD9488_CurrentFont_PixHoriz 		= LCD9488_CurrentFont[3];           			// Размер символов по горизонтали
	LCD9488_CurrentFont_PixVert 		= LCD9488_CurrentFont[4];                   	// Размер символов по вертикали
	LCD9488_CurrentFont_BytesPerLine	= LCD9488_CurrentFont[5];                   	// Число байт на 1 горизонтальную линию в символе
}
//=======================================================================================
void LCD9488_GUI_GotoXY(uint16_t x1, uint16_t y1)										// Установить координаты начала для печати символа или строки
{
	char_x = x1;
	char_y = y1;
}
//=======================================================================================
void LCD9488_GUI_Draw_Char(uint16_t fc, uint16_t bc, uint8_t c, ADrawType Overlying)
{
    unsigned int b;
    unsigned char* CurCharBitmap;														// начало данных для текущего символа в массиве шрифта
    unsigned char z, cur_width;

    if ((c < LCD9488_CurrentFont_FirstChar) || (c > LCD9488_CurrentFont_LastChar))
    {
    	return;  																		// работаем только с символами, которые есть в шрифте
    }

	c = c - LCD9488_CurrentFont_FirstChar; 												// сдвигаем до 1го символа в наборе (см ASCII таблицу)

    if (char_x + LCD9488_CurrentFont_PixHoriz > LCD9488_DEV.Width)
     {
         char_x = 0;
         char_y = char_y + LCD9488_CurrentFont_PixVert;
         if (char_y >= (LCD9488_DEV.Height - LCD9488_CurrentFont_PixVert) )
         {
             char_y = 0;
         }
     }

    CurCharBitmap = &LCD9488_CurrentFont[((c) * LCD9488_CurrentFont_Offset) + 6]; 		// начало массива текущего символа (с = номер символа; offset = сколько байтов на символ в шрифте; 6 = первые 6 байт во всем массиве - заголовок с параметрами шрифта)

    cur_width = CurCharBitmap[0];                          								// ширина текущего символа - в начале каждого символа первый байт - его ширина

    if (Overlying == DRAW_OVERLYING)													// Если режим наложения - рисуем только значащие точки символа поверх того что уже нарисовано (медленно)
    {
        for (uint8_t cur_y = 0; cur_y < LCD9488_CurrentFont_PixVert; cur_y++)			// перебор по вертикали
        {
           for (uint8_t cur_x = 0; cur_x < LCD9488_CurrentFont_PixHoriz; cur_x++)		// перебор по горизонтали
           {
               z =  CurCharBitmap[LCD9488_CurrentFont_BytesPerLine * cur_x + ((cur_y & 0xF8) >> 3) + 1];

               b = 1 << (cur_y & 0x07);

               if (( z & b ) == 0x00) 													// фон, там где нет точки изображения символа
               {

               }
               else																		// точка изображения символа
               {
            	   LCD9488_Point_Color = fc;											// устанавливаем цвет точки
            	   LCD9488_GUI_Draw_Point(char_x + cur_x, char_y + cur_y);				// Рисуем точку по координатам
               }


           }
       }
       LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);

    }
    if (Overlying == DRAW_NO_OVERLYING)													// Если НЕ режим наложения - рисуем символ цветом fc на фоне bc
    {
    	uint8_t red, green, blue;														// цветовые компопнеты точки

        LCD9488_GUI_SetWindows(char_x, char_y, char_x + LCD9488_CurrentFont_PixHoriz - 1, char_y + LCD9488_CurrentFont_PixVert);

        for (uint8_t cur_y = 0; cur_y < LCD9488_CurrentFont_PixVert; cur_y++)			// перебор по вертикали
        {
           for (uint8_t cur_x = 0; cur_x < LCD9488_CurrentFont_PixHoriz; cur_x++)		// перебор по горизонтали
           {
               z =  CurCharBitmap[LCD9488_CurrentFont_BytesPerLine * cur_x + ((cur_y & 0xF8) >> 3)+1];
               b = 1 << (cur_y & 0x07);

               if (( z & b ) == 0x00) 													// фон, там где нет точки изображения символа
               {
            	   red		= (bc>>8)&0xF8;
            	   green 	= (bc>>3)&0xFC;
            	   blue	= bc<<3;
               }
               else																		// точка изображения символа
               {
                  	red		= (fc>>8)&0xF8;
                  	green 	= (fc>>3)&0xFC;
                  	blue	= fc<<3;
               }
               // Пишет компонеты цветов для текущей точик в символе
               LCD9488_CS_CLR;
               LCD9488_RS_SET;
               while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
               	   LCD_SPI.Instance->DR = red;
               while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
               	   LCD_SPI.Instance->DR = green;
               while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );
               	   LCD_SPI.Instance->DR = blue;
               while ( !( LCD_SPI.Instance->SR & SPI_SR_TXE ) );

               LCD9488_CS_SET;
           }
       }
       LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);
    }

    // Сдвигаем позицию (char_x, char_y) для печати следующего символа
    if ((cur_width + 2) < LCD9488_CurrentFont_PixHoriz)
    {
        char_x = char_x + cur_width + 2;
    }
    else
    {
    	char_x = char_x + LCD9488_CurrentFont_PixHoriz;
    }
}
//=======================================================================================
void LCD9488_GUI_Draw_String(uint16_t x,uint16_t y,uint8_t size,uint8_t *p, ADrawType Overlying)
{
	if(x>(LCD9488_DEV.Width-1)||y>(LCD9488_DEV.Height-1))
		return;

	LCD9488_GUI_GotoXY(x, y);
    while((*p <= LCD9488_CurrentFont_LastChar)&&(*p >= LCD9488_CurrentFont_FirstChar))
    {
		if(char_x > (LCD9488_DEV.Width-1) || char_y >(LCD9488_DEV.Height-1))
			return;

		LCD9488_GUI_Draw_Char(LCD9488_Point_Color,LCD9488_Back_Color,*p, Overlying);
        p++;
    }
}
//=======================================================================================
void LCD9488_GUI_Draw_StringColor(uint16_t x, uint16_t y, char* str, unsigned char* font, uint16_t fontcolor, uint16_t bgcolor, ADrawType Overlying)
{
	uint16_t x0 = x;

  	LCD9488_GUI_SetFont(font, fontcolor, bgcolor);
  	LCD9488_GUI_GotoXY(x, y);
    while(*str != 0)
    {
		if( x > (LCD9488_DEV.Width - LCD9488_CurrentFont_PixHoriz/2) || y > (LCD9488_DEV.Height - LCD9488_CurrentFont_PixVert) )
			return;

		if(*str == 0x0D)															// конец строки, перевод на новую строку
        {
            y = y + LCD9488_CurrentFont_PixVert;
			x = x0;
            str++;
        }
        else
		{
        	LCD9488_GUI_Draw_Char(LCD9488_Point_Color,LCD9488_Back_Color,*str, Overlying);
		}
		str++;
    }
}
//=======================================================================================
void LCD9488_GUI_Draw_StringCenter(uint16_t x, uint16_t y, char* str, unsigned char* font, uint16_t fontcolor, uint16_t bgcolor, ADrawType Overlying)
{
	LCD9488_GUI_SetFont(font, fontcolor, bgcolor);
	uint16_t len=strlen((const char *)str);
	uint16_t x1=(x - len*(LCD9488_CurrentFont_PixHoriz))/2;
	LCD9488_GUI_Draw_StringColor(x1, y, str, font, fontcolor, bgcolor, Overlying);
}
//=======================================================================================
uint32_t LCD9488_GUI_INT_mypow(uint8_t m,uint8_t n)										// get the nth power of m (internal call)
{
	uint32_t result=1;
	while(n--)result*=m;
	return result;
}
//=======================================================================================
/*****************************************************************************
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
                y:the bebinning y coordinate of the number
								num:the number(0~4294967295)
								len:the length of the display number
								size:the size of display number
******************************************************************************/
void LCD9488_GUI_Draw_Number(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size, ADrawType Overlying)
{
	// Переделать все по другому
//	uint8_t t,temp;
//	uint8_t enshow=0;
//	for(t=0;t<len;t++)
//	{
//		temp=(num/LCD9488_GUI_INT_mypow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
////				LCD9488_GUI_Draw_Char(x+(size/2)*t,y,LCD9488_Point_Color,LCD9488_Back_Color,' ',size,0);
//				LCD9488_GUI_Draw_Char(x+(size/2)*t,y,LCD9488_Point_Color,LCD9488_Back_Color,' ', Overlying);
//				continue;
//			}else enshow=1;
//
//		}
//	 	//LCD9488_GUI_Draw_Char(x+(size/2)*t,y,LCD9488_Point_Color,LCD9488_Back_Color,temp+'0',size,0);
//		LCD9488_GUI_Draw_Char(x+(size/2)*t,y,LCD9488_Point_Color,LCD9488_Back_Color,temp+'0', Overlying);
//	}
}
//=======================================================================================
/*****************************************************************************
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
                y:the bebinning y coordinate of the BMP image
								p:the start address of image array
******************************************************************************/
void LCD9488_GUI_Draw_BMP16(uint16_t x,uint16_t y,const char *p)						// Display a 16-bit BMP image
{
//  	int i;
//	unsigned char picH,picL;
//	LCD9488_GUI_SetWindows(x,y,x+40-1,y+40-1);
//    for(i = 0; i < 40*40 ;i++)
//	{
//	 	picL = *(p+i*2);
//		picH = *(p+i*2+1);
//		LCD9488_WriteData_16Bit(picH<<8|picL);
//	}
//	LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);

  	int i;
	unsigned char picH,picL;
	LCD9488_GUI_SetWindows(x,y,x+100-1,y+100-1);
    for(i = 0; i < 100*100 ;i++)
	{
	 	picL = *(p+i*2);
		picH = *(p+i*2+1);
		LCD9488_WriteData_16Bit(picH<<8|picL);
	}
	LCD9488_GUI_SetWindows(0,0,LCD9488_DEV.Width-1,LCD9488_DEV.Height-1);

}
//=======================================================================================
