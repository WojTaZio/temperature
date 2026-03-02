
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : hd44780.h
  * @brief          : Header for hd44780.c file.
  *                   This files contains macros and function prototypes for HD44780 LCD control.
  ******************************************************************************
 */ 

#ifndef HD44780_H
#define HD44780_H

#include "stm32f4xx_hal.h"

// Define LCD pins
#define E_PIN    GPIO_PIN_6
#define RS_PIN   GPIO_PIN_7
#define D4_PIN   GPIO_PIN_5
#define D5_PIN   GPIO_PIN_4
#define D6_PIN   GPIO_PIN_3
#define D7_PIN   GPIO_PIN_15




// Function prototypes
void lcd_enable(void);
void lcd_set_data(uint8_t half_data);
void lcd_send_data(uint8_t byte, uint8_t rs);
void lcd_init(void);
void lcd_print(char *str);

#endif
