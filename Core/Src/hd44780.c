
/**
  ******************************************************************************
  * @file           : hd44780.c
  * @brief          : Functions for controlling HD44780 LCD in 4-bit mode
  ******************************************************************************
  */

#include "hd44780.h"

/**
  * @brief Enable LCD by toggling E pin
  * @retval None
  */
void lcd_enable(void){
    HAL_GPIO_WritePin(GPIOB, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOB, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

/**
  * @brief Set data on LCD pins D4-D7
  * @retval None
  */
void lcd_set_data(uint8_t half_data){
    HAL_GPIO_WritePin(GPIOB, D4_PIN, (half_data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, D5_PIN, (half_data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, D6_PIN, (half_data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, D7_PIN, (half_data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    lcd_enable();
}

/**
  * @brief Send data byte to HD44780: rs=0 command, rs=1 character
  * @retval None
  */
void lcd_send_data(uint8_t byte, uint8_t rs){
    HAL_GPIO_WritePin(GPIOB, RS_PIN, rs);
    lcd_set_data(byte >> 4);      // old 4 bytes
    lcd_set_data(byte & 0x0F);    // new 4 bytes
}

/**
  * @brief Initialize HD44780 LCD in 4-bit mode
  * @retval None
  */
void lcd_init(void){
    HAL_Delay(50);   // >40ms delay after power on

    HAL_GPIO_WritePin(GPIOB, RS_PIN, GPIO_PIN_RESET);

    // change to 8-bit mode 
    lcd_set_data(0x03); //send first half byte of 0x33 command
    HAL_Delay(5);

    lcd_set_data(0x03); //send 2nd half byte of 0x33 command
    HAL_Delay(1);

    //cahnge to 4-bit mode 
    lcd_set_data(0x03); //send first half byte of 0x32 command
    HAL_Delay(1);

    lcd_set_data(0x02); //send 2nd half byte of 0x32 command, now we are in 4-bit mode
    HAL_Delay(1);

    // sending whole commands in 4-bit mode
    lcd_send_data(0x28, 0); // 4-bit, 2 lines, 5x8 font
    lcd_send_data(0x0C, 0); // display on, cursor off, blink off
    lcd_send_data(0x06, 0); // entry mode, increment cursor, move display off
    lcd_send_data(0x01, 0); // clear screen
    HAL_Delay(5);
}


/**
  * @brief Print string on LCD
  * @retval None
  */
void lcd_print(char *str){
    while(*str){
        lcd_send_data(*str++, 1);
        HAL_Delay(1);
    }
}
