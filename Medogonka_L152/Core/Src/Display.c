// Функции отображения на экране

#include "main.h"


char str[18];																			// Для печати строк через sprintf

//======================================================================================
void Display_Test(uint16_t pos_x, uint16_t pos_y)										// Для тестов
{
//	sprintf(str, "%04.3f", ADC_State.Speed_value_volts);
//	LCD9488_GUI_Draw_StringColor(10, 230, str, (unsigned char*)LCD55Mono37x48, RED, CYAN, DRAW_NO_OVERLYING);

	sprintf(str, "%02d", Speed_value_percent);
//	LCD9488_GUI_Draw_StringColor(200, 230, str, (unsigned char*)Digital7Mono32x48, RED, CYAN, DRAW_NO_OVERLYING);
	LCD9488_GUI_Draw_StringColor(200, 230, str, (unsigned char*)Unispace32x48_Digits, RED, CYAN, DRAW_NO_OVERLYING);


}
//======================================================================================
void Display_SystemVoltage(uint16_t pos_x, uint16_t pos_y)								// Показать напряжение питания процессора
{
	unsigned char* Font = (unsigned char*)Arial_9;

	sprintf(str, "Vcc = %3.2fv", ADC_State.ADC_Ref_Voltage);
	LCD9488_GUI_Draw_StringColor(pos_x, pos_y, str, Font, RED, CYAN, DRAW_NO_OVERLYING);

	sprintf(str, "Tmp = %+2dC", (int)ADC_State.CPU_Temperature);
	LCD9488_GUI_Draw_StringColor(pos_x, pos_y + 10, str, Font, RED, CYAN, DRAW_NO_OVERLYING);

}
//======================================================================================
void Display_MotorDirection(uint16_t pos_x, uint16_t pos_y, TMotorDirection AMotorDirection) // Показать направление вращения мотора
{
	unsigned char* Font = (unsigned char*)Arial28x28;
	switch (AMotorDirection)
	{
		case MD_STOP:
			LCD9488_GUI_Draw_StringColor(pos_x, pos_y, " STOP  ", Font, RED, LIGHTBLUE, DRAW_NO_OVERLYING);
			break;
		case MD_FWD:
			LCD9488_GUI_Draw_StringColor(pos_x, pos_y, "FORWARD", Font, RED, LIGHTBLUE, DRAW_NO_OVERLYING);
			break;
		case MD_REV:
			LCD9488_GUI_Draw_StringColor(pos_x, pos_y, "REVERSE", Font, RED, LIGHTBLUE, DRAW_NO_OVERLYING);
			break;
	}
}
//======================================================================================
void Display_MotorSpeed(uint16_t pos_x, uint16_t pos_y, uint16_t ASpeed) 					// Показать скорость вращения мотора
{
	unsigned char* Font = (unsigned char*)Unispace32x48_Digits;

	sprintf(str, "%04d", (uint16_t)ASpeed);
	LCD9488_GUI_Draw_StringColor(pos_x, pos_y, str, Font, BLUE, WHITE, DRAW_NO_OVERLYING);
}
//======================================================================================
void Display_Temperature(uint16_t pos_x, uint16_t pos_y, double ATemp) 						// Показать температуру
{
	unsigned char* Font = (unsigned char*)Arial28x28;

	sprintf(str, "Temp = %+2.1f C", ATemp );
	LCD9488_GUI_Draw_StringColor(pos_x, pos_y, str, Font, BLUE, WHITE, DRAW_NO_OVERLYING);
}
//======================================================================================


