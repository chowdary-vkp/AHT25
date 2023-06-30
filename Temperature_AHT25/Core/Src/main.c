/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define AHT25_ADDR 0x38
#define AHT25_MEASURE_CMD 0xAC
#define REG_TEMP 0x00

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

//static const uint8_t AHT25_ADDR = 0x38 << 1;
//static const uint8_t REG_TEMP = 0xE1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

//	HAL_StatusTypeDef ret;
//	uint8_t buf[12];
//	int16_t val;
//	float temp_c;

  /* USER CODE END 1 */
	  uint8_t buf[12];
	  int16_t temperature;
	  float temp_c;

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  while (1)
//  {
//
//    // Tell TMP102 that we want to read from the temperature register
//    buf[0] = REG_TEMP;
//    ret = HAL_I2C_Master_Transmit(&hi2c1, AHT25_ADDR, buf, 1, HAL_MAX_DELAY);
//    HAL_Delay(500);
//    if ( ret != HAL_OK ) {
//      strcpy((char*)buf, "Error Tx\r\n");
//    } else {
//
//      // Read 2 bytes from the temperature register
//      ret = HAL_I2C_Master_Receive(&hi2c1, AHT25_ADDR, buf, 2, HAL_MAX_DELAY);
//      if ( ret != HAL_OK ) {
//        strcpy((char*)buf, "Error Rx\r\n");
//      } else {
//
//        //Combine the bytes
//        val = ((int16_t)buf[0] << 4) | (buf[1] >> 4);
//
//        // Convert to 2's complement, since temperature can be negative
//        if ( val > 0x7FF ) {
//          val |= 0xF000;
//        }
//
//        // Convert to float temperature value (Celsius)
//        temp_c = val * 0.0625;
//
//        // Convert temperature to decimal format
//        temp_c *= 100;
//        sprintf((char*)buf,
//              "%u.%u C\r\n",
//              ((unsigned int)temp_c / 100),
//              ((unsigned int)temp_c % 100));
//      }
//    }
//
//    // Send out buffer (temperature or error message)
//    HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
//
//    // Wait
//    HAL_Delay(500);
//
//    /* USER CODE END WHILE */
//
//    /* USER CODE BEGIN 3 */
//  }
  /* USER CODE END 3 */
//  while (1)
//    {
//      buf[0] = ;
//      if (HAL_I2C_Master_Transmit(&hi2c1, AHT25_ADDR, buf, 1, 100) != HAL_OK)
//      {
//        strcpy((char*)buf, "Error Tx\r\n");
//
//        //strcpy((char*)buf, "Error Rx\r\n");
//      }
//      else
//      {
//        HAL_Delay(80);  // Wait for measurement completion (adjust delay if needed)
//
//        if (HAL_I2C_Master_Receive(&hi2c1, AHT25_ADDR, buf, 6, HAL_MAX_DELAY) != HAL_OK)
//        {
//          strcpy((char*)buf, "Error Rx\r\n");
//        }
//        else
//        {
//          temperature = ((int16_t)buf[2] << 8) | buf[3];
//
//          if (temperature > 0x7FF)
//          {
//            temperature = temperature | 0xF000;
//          }
//
//          temp_c = temperature * 0.1;
//
//          char temp_str[20];
//          sprintf(temp_str, "%.2f C\r\n", temp_c);
//          HAL_UART_Transmit(&huart2, (uint8_t*)temp_str, strlen(temp_str), HAL_MAX_DELAY);
//        }
//      }
//      HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
//      HAL_Delay(500);
//    }

  while (1)
  {
    buf[0] = AHT25_MEASURE_CMD;

    if (HAL_I2C_Master_Transmit(&hi2c1, AHT25_ADDR, buf, 1, HAL_MAX_DELAY) != HAL_OK)
    {
      Error_Handler();
    }

    HAL_Delay(80);  // Wait for measurement completion (adjust delay if needed)

    if (HAL_I2C_Master_Receive(&hi2c1, AHT25_ADDR, buf, 6, HAL_MAX_DELAY) != HAL_OK)
    {
      Error_Handler();
    }

    temperature = ((int16_t)buf[2] << 8) | buf[3];

    if (temperature > 0x7FF)
    {
      temperature = temperature | 0xF000;
    }

    temp_c = temperature * 0.1;

    char temp_str[20];
    sprintf(temp_str, "%.2f C\r\n", temp_c);
    HAL_UART_Transmit(&huart2, (uint8_t*)temp_str, strlen(temp_str), HAL_MAX_DELAY);

    HAL_Delay(500);
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
