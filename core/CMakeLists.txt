file(GLOB_RECURSE SOURCES "src/*.cpp")

idf_component_register(
    SRCS ${SOURCES}
    PRIV_REQUIRES spi_flash
    INCLUDE_DIRS . inc src/hal src/nav
    REQUIRES freertos esp_common esp_timer driver
    PRIV_REQUIRES esp_adc
)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)
