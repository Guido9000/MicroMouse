#pragma once

#include <iostream>
#include <string>
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "config.h"
#include "log.h"

struct SensorReading
{
    float frontal, left, right;
};

class Sensor
{ 
    public:
        explicit Sensor(std::string name)
            : p_name(std::move(name))   // move: cannibalize an existing "useless" object's resources 
        {}
        void setQueue(QueueHandle_t queue, TaskHandle_t masterHandle) {
            sensorQueue_  = queue;
            masterHandle_ = masterHandle;
        }

        virtual ~Sensor() = default;

        virtual bool theresWall() const = 0;
        virtual float read() const = 0;
    
    protected:  // can be called from this class and derived classes
        std::string p_name;
        QueueHandle_t sensorQueue_  = NULL;
        TaskHandle_t  masterHandle_ = NULL;
        void sendReading(float value) {
            xQueueSend(sensorQueue_, &value, 0);    // Don't touch the queue, directly use the function
            xTaskNotifyGive(masterHandle_);
        }


};


// Ultrasonic Sensor
class UsSensor : public Sensor
{ 
    public:
        explicit UsSensor(int OUTPIN, int INPIN, std::string name)
            : Sensor(std::move(name)), p_trigPin(OUTPIN), p_echoPin(INPIN)
        {
            if(ussensor_setup()){std::cout << name << " ultrasound sensor  is online" << std::endl;}
        }

        bool theresWall() const override;
        float read() const override;

    private:
        int p_trigPin;
        int p_echoPin;

        volatile int64_t echo_start_time_ = 0;
        volatile int64_t echo_end_time_   = 0;

        TaskHandle_t USsensorTaskHandle_ = NULL;

        bool ussensor_setup();
        static void sUSSensorTask(void* instance);
        void sonarTask(void* instance);
        static void IRAM_ATTR echo_isr(void* instance);

};


class IRSensor : public Sensor
{ 
    public:
        explicit IRSensor(adc_channel_t adc_channel, std::string name)
            : Sensor(std::move(name)), p_adc_channel(adc_channel)
        {
            if(irsensor_setup()){std::cout << name << " IR sensor is online" << std::endl;}
        }

        bool theresWall() const override;
        float read() const override;

    private:
        static adc_oneshot_unit_handle_t adc1_handle;
        static bool adc_initialized;
        adc_channel_t p_adc_channel;

        bool irsensor_setup();
        void irTask(void* instance);
};