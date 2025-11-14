#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "morse.h"

const std::map< char, std::string > ascii_to_morse =
{
{'A',".-"},
{'B',"-..."},
{'C',"-.-."},
{'D',"-.."},
{'E',"."},
{'F',"..-."},
{'G',"--."},
{'H',"...."},
{'I',".."},
{'J',".---"},
{'K',"-.-"},
{'L',".-.."},
{'M',"--"},
{'N',"-."},
{'O',"---"},
{'P',".--."},
{'Q',"--.-"},
{'R',".-."},
{'S',"..."},
{'T',"-"},
{'U',"..-"},
{'V',"...-"},
{'W',".--"},
{'X',"-..-"},
{'Y',"-.--"},
{'Z',"--.."},
{'0',"-----"},
{'1',".----"},
{'2',"..---"},
{'3',"...--"},
{'4',"....-"},
{'5',"....."},
{'6',"-...."},
{'7',"--..."},
{'8',"---.."},
{'9',"----."},
{'.',".-.-.-"},
{',',"--..--"},
{'?',"..--.."},
{'=',"-...-"},
};


void MorseLed::on(int ms) const{
    gpio_set_level((gpio_num_t)gpio_, 1);
    vTaskDelay(pdMS_TO_TICKS(ms));
    off(100);
}

void MorseLed::off(int ms) const{
    gpio_set_level((gpio_num_t)gpio_, 0);
    vTaskDelay(pdMS_TO_TICKS(ms));
}

void convert_to_morse(const std::string& msg, int led_gate){
    std::string msg_morse;

    for (int i = 0; i < msg.length(); i++)
    {
        
        msg_morse += ascii_to_morse.at(msg[i]);
        if(i != msg.length())
        {
            msg_morse += ' ';
        }

    }
    //std::cout << msg_morse << std::endl;
    blink_led(msg_morse, led_gate);

}

void blink_led(const std::string& msg_morse, int led_gate){
    MorseLed led(led_gate);

    for (int i = 0; i < msg_morse.length(); i++){
        if(msg_morse[i] == '.') {led.dot();}
        else if(msg_morse[i] == '-') {led.dash();}
        else if(msg_morse[i] == ' ') {led.space();}
    }
}
