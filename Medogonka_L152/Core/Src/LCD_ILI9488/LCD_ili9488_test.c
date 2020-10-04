#include "main.h"


#include "LCD_ili9488_pic.h"


//======================================================================================
uint16_t ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};
//======================================================================================

void main_test(void)
{
//	DrawTestPage("main_test");
//	LCD9488_GUI_Draw_StringCenter(0,30,RED,BLUE,"String 1",16,1);
//	LCD9488_GUI_Draw_StringCenter(0,60,RED,BLUE,"String 2",16,1);
//	LCD9488_GUI_Draw_StringCenter(0,90,GREEN,BLUE,"3.5\" ILI9488 320X480",16,1);
//	LCD9488_GUI_Draw_StringCenter(0,120,BLUE,BLUE,"xiaoFeng@QDtech 2018-08-06",16,1);
//	HAL_Delay(1500);
//	HAL_Delay(1500);

	LCD9488_GUI_Draw_StringColor(200, 50, "START", (unsigned char*)Arial20x23_RUS, GREEN, BLUE, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 10, "Small_6: 1234567890", (unsigned char*)Small_6, GREEN, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 20, "Small_7: 1234567890", (unsigned char*)Small_7, GREEN, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 35, "Arial_9: 1234567890", (unsigned char*)Arial_9, GREEN, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 50, "Arial12x12: 1234567890", (unsigned char*)Arial12x12, RED, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 70, "Arial24x23: 1234567890", (unsigned char*)Arial24x23, RED, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 100, "Arial28x28: 123457890", (unsigned char*)Arial28x28, RED, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 140, "Rubik11x16: 1234567890", (unsigned char*)Rubik11x16, RED, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 170, "Unispace21x42: 1234567", (unsigned char*)Unispace21x42, MAROON, BLUE, DRAW_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 230, "194 rpm", (unsigned char*)OpenSansExtrabold31_42x46, RED, CYAN, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_StringColor(200, 230, "194 rpm", (unsigned char*)Unispace32x48_Digits, RED, CYAN, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_StringColor(320, 230, "8458", (unsigned char*)OpenSansExtrabold48_38x48_Digits, RED, CYAN, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_StringColor(10, 280, "BPMono7x13: 012@jIWgMA (www.alex-ismagilov.com)", (unsigned char*)BPMono7x13, RED, CYAN, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_BMP16(379, 0, gImage_bee1);


//    LCD9488_GUI_Clear(LIGHTGREEN);
//    LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,20,BLUE);
//    LCD9488_GUI_Fill(0,LCD9488_DEV.Height-20,LCD9488_DEV.Width,LCD9488_DEV.Height,BLUE);
//    LCD9488_Point_Color=WHITE;
//    LCD9488_GUI_Draw_StringCenter(0,2,WHITE,BLUE,"LCD 3.5' ILI9488",12,1);
//    LCD9488_GUI_Draw_StringCenter(0,LCD9488_DEV.Height-18,WHITE,BLUE,"Alex Shamilich1",16,1);
//    LCD9488_GUI_Draw_StringCenter(uint16_t x, uint16_t y, char* str, unsigned char* font, uint16_t fontcolor, uint16_t bgcolor)
//    LCD9488_GUI_Draw_StringCenter(50, 20, "@123456789ABCDEFGHIJKLMNOPQRSTUXYZ", (unsigned char*)Arial_9, YELLOW, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(50, 50, "@123456789ABCDEFGHIJKLMNOPQRSTUXYZ", (unsigned char*)Arial12x12, YELLOW, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(50, 100, "@MW{}56789ABCDEFGHIJKLMNOPQRSTUXYZ", (unsigned char*)Arial28x28, YELLOW, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(50, 150, "@123456789ABCDEFGHIJKLMNOPQRSTUXYZ", (unsigned char*)Small_6, YELLOW, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(50, 200, "@MW{}567", (unsigned char*)Neu42x35, YELLOW, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(200, 50, "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_'", (unsigned char*)Arial20x23_RUS, GREEN, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(200, 50, "START I HUJNQ", (unsigned char*)Arial20x23_RUS, GREEN, BLUE, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(10, 130, "Neu42x35: 123456", (unsigned char*)Neu42x35, RED, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(10, 170, "Unispace21x42: 1234567", (unsigned char*)Unispace21x42, MAROON, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(20, 220, "0123456789", (unsigned char*)Unispace26x39, PURPLE, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(10, 130, "0123456789", (unsigned char*)Digital7Mono32x48, RED, CYAN, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringColor(10, 230, "01234AlexM", (unsigned char*)LCD55Mono37x48, RED, CYAN, DRAW_NO_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(20, 20, "555", (unsigned char*)Unispace26x39, GREEN, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(50, 80, "189rpm", (unsigned char*)Unispace21x42, RED, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(20, 160, "1234", (unsigned char*)Small_6, YELLOW, BLUE, DRAW_OVERLYING);
//    LCD9488_GUI_Draw_StringCenter(20, 180, "8", (unsigned char*)Neu42x35, YELLOW, BLUE, DRAW_NO_OVERLYING);

}

//======================================================================================
// @name       :void DrawTestPage(uint8_t *str)
// @date       :2018-08-09
// @function   :Drawing test interface
// @parameters :str:the start address of the Chinese and English strings
// @retvalue   :None
void DrawTestPage(char *str)
{
//	LCD9488_GUI_Clear(WHITE);
//	LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,20,BLUE);
//	LCD9488_GUI_Fill(0,LCD9488_DEV.Height-20,LCD9488_DEV.Width,LCD9488_DEV.Height,BLUE);
//	LCD9488_Point_Color=WHITE;
//	LCD9488_GUI_Draw_StringCenter(0,2,WHITE,BLUE,str,16,1);
//	LCD9488_GUI_Draw_StringCenter(0,LCD9488_DEV.Height-18,WHITE,BLUE,"http://www.lcdwiki.com",16,1);

	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}
//======================================================================================
// @name       :void Test_Color(void)
// @date       :2018-08-09
// @function   :Color fill test(white,black,red,green,blue)
// @parameters :None
// @retvalue   :None
void Test_Color(void)
{
//	//DrawTestPage("DrawTestPage");
//	LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,LCD9488_DEV.Height,WHITE);
//	LCD9488_GUI_Draw_StringColor(20,30,BLUE,YELLOW,"BL Test",16,1);HAL_Delay(800);
//	LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,LCD9488_DEV.Height,RED);
//	LCD9488_GUI_Draw_StringColor(20,30,BLUE,YELLOW,"RED ",16,1);HAL_Delay(800);
//	LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,LCD9488_DEV.Height,GREEN);
//	LCD9488_GUI_Draw_StringColor(20,30,BLUE,YELLOW,"GREEN ",16,1);HAL_Delay(800);
//	LCD9488_GUI_Fill(0,0,LCD9488_DEV.Width,LCD9488_DEV.Height,BLUE);
//	LCD9488_GUI_Draw_StringColor(20,30,RED,YELLOW,"BLUE ",16,1);HAL_Delay(800);
}
//======================================================================================
// @name       :void Test_FillRec(void)
// @date       :2018-08-09
// @function   :Rectangular display and fill test
//								Display red,green,blue,yellow,pink rectangular boxes in turn,
//								1500 milliseconds later,
//								Fill the rectangle in red,green,blue,yellow and pink in turn
// @parameters :None
// @retvalue   :None
void Test_FillRec(void)
{
//	uint8_t i=0;
//	DrawTestPage("Test_FillRec");
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for (i=0; i<5; i++)
//	{
//		LCD9488_Point_Color=ColorTab[i];
//		LCD9488_GUI_Draw_Rectangle(LCD9488_DEV.Width/2-80+(i*15),LCD9488_DEV.Height/2-80+(i*15),LCD9488_DEV.Width/2-80+(i*15)+60,LCD9488_DEV.Height/2-80+(i*15)+60);
//	}
//	HAL_Delay(1500);
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for (i=0; i<5; i++)
//	{
//		LCD9488_Point_Color=ColorTab[i];
//		LCD9488_GUI_Fill_Rectangle(LCD9488_DEV.Width/2-80+(i*15),LCD9488_DEV.Height/2-80+(i*15),LCD9488_DEV.Width/2-80+(i*15)+60,LCD9488_DEV.Height/2-80+(i*15)+60);
//	}
//	HAL_Delay(1500);
}
//======================================================================================
// @name       :void Test_Circle(void)
// @date       :2018-08-09
// @function   :circular display and fill test
//								Display red,green,blue,yellow,pink circular boxes in turn,
//								1500 milliseconds later,
//								Fill the circular in red,green,blue,yellow and pink in turn
// @parameters :None
// @retvalue   :None
void Test_Circle(void)
{
//	uint8_t i=0;
//	DrawTestPage("Test_Circle");
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for (i=0; i<5; i++)
//		LCD9488_GUI_Draw_Circle(LCD9488_DEV.Width/2-80+(i*25),LCD9488_DEV.Height/2-50+(i*25),ColorTab[i],30,0);
//	HAL_Delay(1500);
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for (i=0; i<5; i++)
//	  	LCD9488_GUI_Draw_Circle(LCD9488_DEV.Width/2-80+(i*25),LCD9488_DEV.Height/2-50+(i*25),ColorTab[i],30,1);
//	HAL_Delay(1500);
}
//======================================================================================
// @name       :void English_Font_test(void)
// @date       :2018-08-09
// @function   :English display test
// @parameters :None
// @retvalue   :None
void English_Font_test(void)
{
//	DrawTestPage("English_Font_test");
//	LCD9488_GUI_Draw_StringColor(10,30,BLUE,YELLOW,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",12,0);
//	LCD9488_GUI_Draw_StringColor(10,45,BLUE,YELLOW,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",12,1);
//	LCD9488_GUI_Draw_StringColor(10,60,BLUE,YELLOW,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",12,0);
//	LCD9488_GUI_Draw_StringColor(10,80,BLUE,YELLOW,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",16,0);
//	LCD9488_GUI_Draw_StringColor(10,100,BLUE,YELLOW,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",16,1);
//	LCD9488_GUI_Draw_StringColor(10,120,BLUE,YELLOW,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",16,0);
//	HAL_Delay(1200);
}
//======================================================================================
// @name       :void Test_Triangle(void)
// @date       :2018-08-09
// @function   :triangle display and fill test
//								Display red,green,blue,yellow,pink triangle boxes in turn,
//								1500 milliseconds later,
//								Fill the triangle in red,green,blue,yellow and pink in turn
// @parameters :None
// @retvalue   :None
void Test_Triangle(void)
{
//	uint8_t i=0;
//	DrawTestPage("Test_Triangle");
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for(i=0;i<5;i++)
//	{
//		LCD9488_Point_Color=ColorTab[i];
//		LCD9488_GUI_Draw_Triangel(LCD9488_DEV.Width/2-80+(i*20),LCD9488_DEV.Height/2-20+(i*15),LCD9488_DEV.Width/2-50-1+(i*20),LCD9488_DEV.Height/2-20-52-1+(i*15),LCD9488_DEV.Width/2-20-1+(i*20),LCD9488_DEV.Height/2-20+(i*15));
//	}
//	HAL_Delay(1500);
//	LCD9488_GUI_Fill(0,20,LCD9488_DEV.Width,LCD9488_DEV.Height-20,WHITE);
//	for(i=0;i<5;i++)
//	{
//		LCD9488_Point_Color=ColorTab[i];
//		LCD9488_GUI_Fill_Triangel(LCD9488_DEV.Width/2-80+(i*20),LCD9488_DEV.Height/2-20+(i*15),LCD9488_DEV.Width/2-50-1+(i*20),LCD9488_DEV.Height/2-20-52-1+(i*15),LCD9488_DEV.Width/2-20-1+(i*20),LCD9488_DEV.Height/2-20+(i*15));
//	}
//	HAL_Delay(1500);
}
//======================================================================================
// @name       :void Pic_test(void)
// @date       :2018-08-09
// @function   :picture display test
// @parameters :None
// @retvalue   :None
void Pic_test(void)
{
//	DrawTestPage("Pic_test");
//	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
//	LCD9488_GUI_Draw_BMP16(30,30,gImage_qq);
//	LCD9488_GUI_Draw_StringColor(30+12,75,BLUE,YELLOW,"QQ",16,1);
//	LCD9488_GUI_Draw_BMP16(90,30,gImage_qq);
//	LCD9488_GUI_Draw_StringColor(90+12,75,BLUE,YELLOW,"QQ",16,1);
//	LCD9488_GUI_Draw_BMP16(150,30,gImage_qq);
//	LCD9488_GUI_Draw_StringColor(150+12,75,BLUE,YELLOW,"QQ",16,1);
//	HAL_Delay(1200);
}
//======================================================================================
// @name       :void Rotate_Test(void)
// @date       :2018-08-09
// @function   :rotate test
// @parameters :None
// @retvalue   :None
void Rotate_Test(void)
{
//	uint8_t i=0;
//	char *Direction[4]={"Rotation:0","Rotation:90","Rotation:180","Rotation:270"};
//
//	for(i=0;i<4;i++)
//	{
//	LCD9488_GUI_SetOrientation(i);
//	DrawTestPage("Rotate_Test");
//	LCD9488_GUI_Draw_StringColor(20,30,BLUE,YELLOW,Direction[i],16,1);
//	LCD9488_GUI_Draw_BMP16(30,50,gImage_qq);
//	HAL_Delay(1000);HAL_Delay(1000);
//	}
//	LCD9488_GUI_SetOrientation(USE_HORIZONTAL);
}
//======================================================================================




