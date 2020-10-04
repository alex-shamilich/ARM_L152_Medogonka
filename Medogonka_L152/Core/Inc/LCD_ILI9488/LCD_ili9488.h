// LCD_ili9488.h
// Driver LCD 3.5" 320x480 on ILI9488 chip
// based on: http://www.lcdwiki.com/
// Created: Aug 26, 2020
//       Author: Alex Shamilich

#ifndef INC_LCD_ILI9488_LCD_ILI9488_H_
#define INC_LCD_ILI9488_LCD_ILI9488_H_

#include "stdlib.h"
#include "stdint.h"

#include "spi.h"

#include "LCD_ili9488_fonts.h"

#define LCD_SPI         		hspi2													// Дескриптор SPI интерфейса

// Пины для управления LCD
// Подсветка
#define LCD9488_LED_Pin 		GPIO_PIN_3
#define LCD9488_LED_GPIO_Port 	GPIOC
#define LCD9488_LED_SET 		HAL_GPIO_WritePin(LCD9488_LED_GPIO_Port, 	LCD9488_LED_Pin, GPIO_PIN_SET)
#define LCD9488_LED_CLR 		HAL_GPIO_WritePin(LCD9488_LED_GPIO_Port, 	LCD9488_LED_Pin, GPIO_PIN_RESET)
#define LCD9488_LED_INV 		HAL_GPIO_TogglePin(LCD9488_LED_GPIO_Port, 	LCD9488_LED_Pin)

// DC-RS (Команды или данные)
#define LCD9488_DC_RS_Pin 		GPIO_PIN_0
#define LCD9488_DC_RS_GPIO_Port GPIOC
#define LCD9488_RS_SET 			HAL_GPIO_WritePin(LCD9488_DC_RS_GPIO_Port, 	LCD9488_DC_RS_Pin, GPIO_PIN_SET)
#define LCD9488_RS_CLR 			HAL_GPIO_WritePin(LCD9488_DC_RS_GPIO_Port, 	LCD9488_DC_RS_Pin, GPIO_PIN_RESET)
#define LCD9488_RS_INV 			HAL_GPIO_TogglePin(LCD9488_DC_RS_GPIO_Port, LCD9488_DC_RS_Pin)

// Chip Select
#define LCD9488_CS_Pin 			GPIO_PIN_2
#define LCD9488_CS_GPIO_Port 	GPIOC
#define LCD9488_CS_SET 			HAL_GPIO_WritePin(LCD9488_CS_GPIO_Port, 	LCD9488_CS_Pin, GPIO_PIN_SET)
#define LCD9488_CS_CLR 			HAL_GPIO_WritePin(LCD9488_CS_GPIO_Port, 	LCD9488_CS_Pin, GPIO_PIN_RESET)
#define LCD9488_CS_INV 			HAL_GPIO_TogglePin(LCD9488_CS_GPIO_Port, 	LCD9488_CS_Pin)

// Reset
#define LCD9488_RST_Pin 		GPIO_PIN_1
#define LCD9488_RST_GPIO_Port 	GPIOC
#define LCD9488_RST_SET 		HAL_GPIO_WritePin(LCD9488_RST_GPIO_Port, 	LCD9488_RST_Pin, GPIO_PIN_SET)
#define LCD9488_RST_CLR 		HAL_GPIO_WritePin(LCD9488_RST_GPIO_Port, 	LCD9488_RST_Pin, GPIO_PIN_RESET)
#define LCD9488_RST_INV 		HAL_GPIO_TogglePin(LCD9488_RST_GPIO_Port,	LCD9488_RST_Pin)

//LCD
typedef struct
{
	uint16_t Width;																		// Ширина
	uint16_t Height;																	// Высота
	uint16_t ID;																		// Идентификатор
	uint8_t  Dir;																		// Ориентация
	uint16_t WramCmd;																	//
	uint16_t SetXcmd;																	//
	uint16_t SetYcmd;																	//
}TLCD9488_DEV;

extern TLCD9488_DEV LCD9488_DEV;

typedef enum enumADrawType
{
		DRAW_NO_OVERLYING=0,															// Рисовать с использованием фона (для шрифтов)
		DRAW_OVERLYING=1																// Рисовать с без использования фона (для шрифтов), поверх уже существующего изображения
} ADrawType;

#define USE_HORIZONTAL  	 0 															// Ориентация,  0-0град, 1-90град, 2-180град, 3-270град

#define LCD_W 320
#define LCD_H 480
#define LCD_PIXEL_COUNT		LCD_W * LCD_H

unsigned int 	char_x;
unsigned int 	char_y;

unsigned char* 	LCD9488_CurrentFont;													// Указатель на массив битов шрифта
uint8_t 		LCD9488_CurrentFont_FirstChar;       									// Первый символ в наборе
uint8_t 		LCD9488_CurrentFont_LastChar;											// Последний символ в наборе
uint8_t 		LCD9488_CurrentFont_Offset;												// Число байтов на 1 символ в массиве шрифта
uint8_t 		LCD9488_CurrentFont_PixHoriz;											// Размер символов по горизонтали
uint8_t 		LCD9488_CurrentFont_PixVert;						                   	// Размер символов по вертикали
uint8_t 		LCD9488_CurrentFont_BytesPerLine;					                   	// Число байт на 1 горизонтальную линию в символе
extern uint16_t LCD9488_Point_Color;													// Цвет рисования
extern uint16_t LCD9488_Back_Color;														// Цвет фона


//Заранее определенные цвета
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define GRAY  		0X8430
#define DARKBLUE    0X01CF
#define LIGHTBLUE   0X7D7C
#define GRAYBLUE    0X5458
#define LIGHTGREEN  0X841F
#define LIGHTGRAY   0XEF5B
#define LGRAYBLUE   0XA651
#define LBBLUE      0X2B12

#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DGREEN      0x03E0      /*   0, 128,   0 */
#define DCYAN       0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LGRAY       0xC618      /* 192, 192, 192 */
#define DGRAY       0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
//#define CYAN        0x07FF      /*   0, 255, 255 */
#define CYAN        0x7FFF
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define BROWN 		0XBC40
#define BRRED 		0XFC07

unsigned int 	char_x;																	// Горизонтальная позиция при печати символов и строк
unsigned int 	char_y;																	// Вертикальная позиция при печати символов и строк

void LCD9488_Init(void);
void LCD9488_Init_GPIO(void);
void LCD9488_RESET(void);

void LCD9488_Transport_SPI_WriteByte(uint8_t Byte);
void LCD9488_Transport_WR_REG(uint8_t data);
void LCD9488_Transport_WR_DATA(uint8_t data);
void LCD9488_Transport_WriteData_16Bit(uint16_t Data);

void LCD9488_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD9488_WriteRAM_Prepare(void);

void LCD9488_GUI_Clear(uint16_t Color);
void LCD9488_GUI_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd);
void LCD9488_GUI_SetOrientation(uint8_t direction );
void LCD9488_GUI_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD9488_GUI_SetFont(unsigned char* AFont, uint16_t AFontColor, uint16_t ABackgroundColor);
void LCD9488_GUI_GotoXY(uint16_t x1, uint16_t y1);
void LCD9488_GUI_Draw_Point(uint16_t x,uint16_t y);//����
void LCD9488_GUI_Draw_PointColor(uint16_t x,uint16_t y,uint16_t color);
void LCD9488_GUI_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD9488_GUI_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD9488_GUI_Draw_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD9488_GUI_Draw_Circle(int xc, int yc,uint16_t c,int r, int fill);
void LCD9488_GUI_Draw_BMP16(uint16_t x,uint16_t y,const char *p); // картинка 40x40
void LCD9488_GUI_Draw_Char(uint16_t fc, uint16_t bc, uint8_t c, ADrawType Overlying);
void LCD9488_GUI_Draw_Number(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size, ADrawType Overlying);
void LCD9488_GUI_Draw_String(uint16_t x,uint16_t y,uint8_t size,uint8_t *p, ADrawType Overlying);
void LCD9488_GUI_Draw_StringColor(uint16_t x, uint16_t y, char* str, unsigned char* font, uint16_t fontcolor, uint16_t bgcolor, ADrawType Overlying);
void LCD9488_GUI_Draw_StringCenter(uint16_t x, uint16_t y, char* str, unsigned char* font, uint16_t fontcolor, uint16_t bgcolor, ADrawType Overlying);
void LCD9488_GUI_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);
void LCD9488_GUI_Fill_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD9488_GUI_Fill_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);


#endif /* INC_LCD_ILI9488_LCD_ILI9488_H_ */

//void LCD_DisplayOn(void);
//void LCD_DisplayOff(void);
//void LCD_SetParam(void);
//void LCD_WriteRAM(uint16_t RGB_Code);
//void LCD_Show2Num(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint8_t size,uint8_t mode);
//uint16_t LCD_ReadRAM(void);
//uint16_t LCD_BGR2RGB(uint16_t c);
//uint16_t LCD_ReadPoint(uint16_t x,uint16_t y);
//uint16_t LCD_RD_DATA(void);
//uint16_t LCD_ReadReg(uint8_t LCD_Reg);
//void Draw_Circle(uint16_t x0,uint16_t y0,uint16_t fc,uint8_t r);
