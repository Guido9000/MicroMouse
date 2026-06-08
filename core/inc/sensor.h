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
    float frontal = -1.0f;
    float left    = -1.0f;
    float right   = -1.0f;

    bool isValid() const {
        return frontal != -1.0f && left != -1.0f && right != -1.0f;
    }

    void print() const {
        std::cout << "F: " << frontal 
                  << " L: " << left 
                  << " R: " << right << std::endl;
    }
};

class Sensor
{ 
    public:
        explicit Sensor(std::string name)
            : p_name(std::move(name))   // move: cannibalize an existing "useless" object's resources 
        {}
        void setQueue(QueueHandle_t queue, TaskHandle_t masterHandle) {
            Queue_              = queue;
            masterHandle_       = masterHandle;
        }
        void setTaskHandle(TaskHandle_t myhandle) {
            classTaskHandle_    = myhandle;
        }

        virtual         ~Sensor();
        virtual bool    theresWall() const  = 0;
        virtual float   read() const        = 0;
    
    protected:  // can be called from this class and derived classes
        std::string p_name;
        QueueHandle_t Queue_            = NULL;
        TaskHandle_t  masterHandle_     = NULL;     // Handle of the father
        TaskHandle_t  classTaskHandle_  = NULL;     // Handle of the class

        void sendReading(float value) {
            xQueueSend(Queue_, &value, 0);    // it doesn't touch the queue, directly use the function
            xTaskNotifyGive(masterHandle_);   // Notify the master
        }
};


// Ultrasonic Sensor
class UsSensor : public Sensor
{ 
    public:
        explicit UsSensor(int OUTPIN, int INPIN, std::string name)
            : Sensor(std::move(name)), p_trigPin(OUTPIN), p_echoPin(INPIN)
        { }

        static void sUSSensorTask(void* instance);
        bool        ussensor_setup();
        bool        theresWall() const override;
        float       read() const override;

    private:
        int p_trigPin;
        int p_echoPin;

        volatile int64_t echo_start_time_ = 0;
        volatile int64_t echo_end_time_   = 0;
       
        void                    sonarTask();
        static void IRAM_ATTR   echo_isr(void* instance);
};


// InfraRed Sensor
class IRSensor : public Sensor
{ 
    public:
        explicit IRSensor(adc_channel_t adc_channel, std::string name)
            : Sensor(std::move(name)), p_adc_channel(adc_channel)
        { }

        static void sIRSensorTask(void* instance);
        bool        irsensor_setup();
        bool        theresWall() const override;
        float       read() const override;

    private:
        static adc_oneshot_unit_handle_t    adc1_handle;
        static SemaphoreHandle_t            adcMutex_;     // Avoid double access to adc1_handle
        static bool                         adc_initialized;
        adc_channel_t                       p_adc_channel;
        
        void irTask();
};