#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sonar.h"
 
bool Sonar::sonar_setup()
{
    // Turn on the sensor
    //Echo
    gpio_reset_pin((gpio_num_t)p_echoPin);
    gpio_set_direction((gpio_num_t)p_echoPin, GPIO_MODE_INPUT);
    //Trig
    gpio_reset_pin((gpio_num_t)p_trigPin);
    gpio_set_direction((gpio_num_t)p_trigPin, GPIO_MODE_OUTPUT);

    gpio_set_level((gpio_num_t)p_trigPin, 0);

    return true;
}


bool Sonar::theresWall()
{
    if(read() < MAX_WALL_DIST){return true;}
    else{return false;}
}


float Sonar::read()
{
    int64_t start = 0;
    int64_t end = 0;

    // Delay to clean the area
    gpio_set_level((gpio_num_t)p_trigPin, 0);
    esp_rom_delay_us(4);
    // Send the signal to trigger pin
    gpio_set_level((gpio_num_t)p_trigPin, 1);
    esp_rom_delay_us(10);
    gpio_set_level((gpio_num_t)p_trigPin, 0);

    // 2. Aspetta che Echo salga
    while (gpio_get_level((gpio_num_t)p_echoPin) == 0) { } //interrupt
    if(gpio_get_level((gpio_num_t)p_echoPin) == 1)
    {
        start = esp_timer_get_time();
    }

    // 3. Aspetta che Echo torni basso
    while (gpio_get_level((gpio_num_t)p_echoPin) == 1) 
    {

    }
    if(gpio_get_level((gpio_num_t)p_echoPin) == 0)
    {
        end = esp_timer_get_time();
    }

    // Calculate time of fly of the signal and convert in cm (0.017~1/58)
    int64_t duration = end - start;
    int64_t distance = duration / 58;
    
    return distance;

}