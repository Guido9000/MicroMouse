set(SOURCES 
    src/driver.cpp
    src/main.cpp
    src/morse.cpp
    src/motor.cpp
    src/sonar.cpp
    )

idf_component_register(SRCS ${SOURCES}
                    PRIV_REQUIRES spi_flash
                    INCLUDE_DIRS . inc
                    REQUIRES freertos esp_common esp_timer driver)
                    
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)
