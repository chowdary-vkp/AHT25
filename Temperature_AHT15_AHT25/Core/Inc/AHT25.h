/*
 * AHT25.h
 *
 *  Created on: Jun 17, 2023
 *      Author: dinesh
 */

#ifndef INC_AHT25_H_
#define INC_AHT25_H_

#include "main.h"

#define AHT25_device_address		(uint8_t)0x38
#define AHT25_initialization		(uint8_t)0b11100001
#define AHT25_measurement_trigger	(uint8_t)0xAC
#define AHT25_soft_reset			(uint8_t)0xBA
#define I2C_read					(uint8_t)0x01
#define I2C_write					(uint8_t)0x00


extern I2C_HandleTypeDef hi2c1;

extern float AHT25_relative_humidity, AHT25_temperature;
extern uint8_t measure_humidity;

extern void AHT25_init();
extern void AHT25_reset();
extern void AHT25_read_data();


#endif /* INC_AHT25_H_ */
