#ifndef _EXIO_PCF8574_H_

#define _EXIO_PCF8574_H_
#include "main.h"

#define EXIO_I2C_HANDLER hi2c2

#define PCF8574_DEV_ADDR 0x40

/* @brief 测试PCF8574设备连接情况
 * @param 无
 * @retv  测试结果，HAL_OK或者HAL_ERROR
 */
inline HAL_StatusTypeDef EXIO8574devCheck(void)
{
    return HAL_I2C_IsDeviceReady(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,5,0xff);
}

/* @brief 读取PCF8574设备全部IO口输入
 * @param 无
 * @retv  8位IO口情况
 */
uint8_t EXIO8574ReadPorts(void)
{
    uint8_t cache;
    HAL_I2C_Master_Receive(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    return cache;
}

/* @brief 设置PCF8574设备全部IO口输出
 * @param 8位IO口状态
 * @retv  无
 */
inline void EXIO8574WritePorts(uint8_t writeData)
{
    HAL_I2C_Master_Transmit(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&writeData,1,0xff);
}

/* @brief 读取PCF8574设备指定引脚状态
 * @param 指定引脚号
 * @retv  引脚状态
 */
uint8_t EXIO8574ReadPin(uint8_t PinN)
{
    uint8_t cache;
    HAL_I2C_Master_Receive(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    if(cache&(1<<PinN))
        return 1;
    return 0;
}

/* @brief 设置PCF8574设备指定引脚状态
 * @param 指定引脚号
 * @param 引脚状态
 * @retv  无
 */
void EXIO8574WritePin(uint8_t PinN,uint8_t PinStatus)
{
    uint8_t cache;
    HAL_I2C_Master_Receive(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    if(PinStatus == 0) 
        cache &= ~(1<<PinN);
    else
        cache |= (1<<PinN);
    
    HAL_I2C_Master_Transmit(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    
}

/* @brief 翻转PCF8574设备指定引脚状态
 * @param 指定引脚号
 * @retv  引脚状态
 */
uint8_t EXIO8574TogglePin(uint8_t PinN)
{
    uint8_t cache;
    HAL_I2C_Master_Receive(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    cache ^= (1<<PinN);
    
    HAL_I2C_Master_Transmit(&EXIO_I2C_HANDLER,PCF8574_DEV_ADDR,&cache,1,0xff);
    return cache;
    
}

#endif
