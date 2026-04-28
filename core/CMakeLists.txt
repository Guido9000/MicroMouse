# set(SOURCES 
#     src/driver.cpp
#     src/main.cpp
#     src/morse.cpp
#     src/motor.cpp
#     src/sonar.cpp
#     src/tasks.cpp
#     )

# idf_component_register(SRCS ${SOURCES}
#                     PRIV_REQUIRES spi_flash
#                     INCLUDE_DIRS . inc
#                     INCLUDE_DIRS . src/hal
#                     REQUIRES freertos esp_common esp_timer driver)
                    
# target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)

# # target_include_directories(micromouse PRIVATE ../inc)
# # target_include_directories(micromouse PRIVATE ../src)
# # target_include_directories(micromouse PRIVATE ../src/hal)
# # target_include_directories(micromouse PRIVATE ../src/nav)

file(GLOB_RECURSE SOURCES "src/*.cpp")

idf_component_register(
    SRCS ${SOURCES}
    PRIV_REQUIRES spi_flash
    INCLUDE_DIRS . inc src/hal src/nav
    REQUIRES freertos esp_common esp_timer driver
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)
