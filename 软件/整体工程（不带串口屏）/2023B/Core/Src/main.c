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
#include "dac.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "math.h"
#include "arm_math.h"
#include "ADS8688.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//定义判断状态标志位
#define open_flag 0
#define c_flag 1
#define r_flag 2

//定义连接负载板电容
#define add_C 1.9

//定义基础开路震荡频率
#define basic_freq 132e3

//乘积和振荡频率的一次函数关系
#define freq_slope -0.465
#define freq_intercept 60.803

//线缆等效电容线密度
#define line_density_slope 46.167
#define line_density_intercept 18.992

//定义分压测量电阻的串联已知电阻
#define Rs 20.5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int time[3];
int i = 0;
int flag = 1;

//定义第一次测量电路频率
double freq = 0;
//定义第一次测量的乘积=线长*振荡频率
double sum = 0;
//定义第一次测量线长
double length = 0;
//定义第一次测量电缆的电容值
double C = 0;

//定义接入负载后的振荡频率
double connect_freq = 0;

double R_vol = 0;
//负载类型判断
int type = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//判断负载类型
int judge_type(float connect_freq);

//第一次计算电缆长度
void calculate_length();

//第二次计算
void recalculate();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
//	__HAL_TIM_SET_COUNTER(&htim1,0);

	if(i==0)
	{
		time[i] = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);
		i++;
	}
	else if(i==1)
	{
		time[i] = HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_3);
		i++;
	}
	else
	{
		return;
	}

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_USART1_UART_Init();
  MX_DAC_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  //初始化ADS8688
  ADS8688_Init_Mult();

  //初始化定时器一些参数
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
  __HAL_TIM_SET_COUNTER(&htim1,0);

  //初始化继电器
  HAL_GPIO_WritePin(Relays_GPIO_Port, Relays_Pin, RESET);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //适当延时，使输入捕获频率测量完毕
  HAL_Delay(1000);
  //计算第一次的参数：freq,C,length
  calculate_length();

  HAL_Delay(1000);

  //进行第二次计算
  recalculate();
  //进行负载判断
  type = judge_type(connect_freq);

  if(type == c_flag)
  {
	  //计算连接后的乘积
	  double sum_connect = (-0.4052)*connect_freq/1000+60.846;
	  //计算连接后的等效电缆长度
	  double length_connect = sum_connect/(connect_freq/1000);
	  //根据电缆电容线密度，由等效长度算出等效电容大小
	  double C_connect = length_connect*line_density_slope+line_density_intercept;
	  //算出来的C不对，需要拟合得出正确的结果
	  double real_c = 2.0755*(C_connect-C-add_C)+8.7644;
	  printf("newC=%f\r\n",real_c);
  }
  else if(type == r_flag)
  {
	 //写后续切换继电器操作
  	 HAL_GPIO_WritePin(Relays_GPIO_Port, Relays_Pin, SET);
  	 HAL_Delay(100);

  	 //分压法测电阻阻值，用8688采集电压更准确
  	 R_vol = get_vol(1);
	 printf("R_vol=%f\r\n",R_vol);

 	 double R = (R_vol*Rs)/(5-R_vol);
 	 printf("R=%f\r\n",R);
  }
  else
  {
	  //开路，什么也不操作
  }

    while (1)
  {



  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int judge_type(float connect_freq)
{
	//如果不震荡了，那就是接入了电阻
	if(connect_freq == 0)
	{
		return r_flag;
	}
	//如果频率和开路的基本频率基本一样，那么就是开路，这个容忍度是40kHz
	else if((basic_freq-connect_freq)<40e3)
	{
		return open_flag;
	}
	//否则就是电容接入
	else
	{
		return c_flag;
	}
}


void calculate_length()
{
	//第一次计算，算出振荡频率、线长和等效电容
	time[2]=time[1]-time[0];
	printf("%d\r\n",time[2]);
	freq= (84*1000000)/time[2];
	printf("freq=%f k\r\n",freq/1000);
	sum = freq_slope*freq/1000+freq_intercept;
	length = sum/(freq/1000);
	printf("length=%f\r\n",length);
	C = length*46.167+18.992;
	printf("C=%f\r\n",C);
}

void recalculate()
{
	//第二次计算，考虑到可能不震荡从而触发不了输入捕获，先把两个time置零
	time[1] = time[0] = 0;
	i = 0;
	__HAL_TIM_SET_COUNTER(&htim1,0);
	HAL_Delay(1000);
	time[2]=time[1]-time[0];

	//如果算出来是0，那说明没有触发输入捕获，这样就说明没有震荡，接入了电阻
	if(time[2] == 0)
	{
		connect_freq = 0;
		printf("电阻");
	}
	//触发了输入捕获就是开路或者接入电容，可以算出来振荡频率
	else
	{
		connect_freq= (84*1000000)/time[2];
	}
}

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
    while (1) {
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
