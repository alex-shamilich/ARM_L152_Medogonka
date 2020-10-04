#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

// Функции отображения на экране

#include "Motor.h"

void Display_Test(uint16_t pos_x, uint16_t pos_y);												// Для тестов
void Display_SystemVoltage(uint16_t pos_x, uint16_t pos_y);										// Показать напряжение питания процессора
void Display_MotorDirection(uint16_t pos_x, uint16_t pos_y, TMotorDirection AMotorDirection);	// Показать направление вращения мотора



#endif /* INC_DISPLAY_H_ */