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


float Sonar::read_distance()
{

    int uno = 0;
    int due = 0;
    int tre = 0;

    std::cout << "Leggo" << std::endl;
    // Delay to clean the area
    gpio_set_level((gpio_num_t)p_trigPin, 0);
    esp_rom_delay_us(4);
    // Send the signal
    gpio_set_level((gpio_num_t)p_trigPin, 1);
    uno = gpio_get_level((gpio_num_t)p_trigPin);

    esp_rom_delay_us(100);
    gpio_set_level((gpio_num_t)p_trigPin, 0);
    due = gpio_get_level((gpio_num_t)p_trigPin);

    //gpio_set_level((gpio_num_t)p_echoPin, 1);
    // 2. Aspetta che Echo salga
    tre = gpio_get_level((gpio_num_t)p_echoPin);
    while (gpio_get_level((gpio_num_t)p_echoPin) == 0) { } //interrupt
    int64_t start = esp_timer_get_time();
    std::cout << "Accendo: " << start << std::endl;
    uno = gpio_get_level((gpio_num_t)p_trigPin);
    int i = 0;
    // 3. Aspetta che Echo torni basso
    while (gpio_get_level((gpio_num_t)p_echoPin) == 1) 
    {
        /*i++; 
        if(i == 10000)
        {
            break;
        }*/
    }
    int64_t end = esp_timer_get_time();
    std::cout << "Preso: " << end << std::endl;

    // 4. Calcola durata (microsecondi)
    int64_t duration = end - start;

    // 5. Converte in cm
    float distance = duration / 58.0;
    
    std::cout << uno << " " << due << " " << tre <<std::endl;
    return distance;

}