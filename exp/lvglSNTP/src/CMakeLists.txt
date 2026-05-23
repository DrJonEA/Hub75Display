add_executable(${NAME}
        main.cpp
        Widgets.cpp
        WifiHelper.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
    hub75
    pico_stdlib
    pico_multicore
    pico_aon_timer
    pimoroni_i2c
    pico_graphics
    pico_vector
    hardware_pwm
	hardware_pio 
	hardware_adc 
	hardware_dma 
	pico_graphics 
	lvgl
	FreeRTOS-Kernel-Heap4 # FreeRTOS kernel and dynamic heap
	freertos_config #FREERTOS_PORT
	pico_cyw43_arch_lwip_sys_freertos
	pico_lwip_sntp
	LWIP_PORT
)

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 0)
pico_enable_stdio_uart(${NAME} 1)
target_compile_definitions(${NAME} PRIVATE
    PICO_DEFAULT_UART_RX_PIN=17
    PICO_DEFAULT_UART_TX_PIN=16
)
target_compile_definitions(${NAME} PRIVATE
    WIFI_SSID=\"$ENV{WIFI_SSID}\"
    WIFI_PASSWORD=\"$ENV{WIFI_PASSWORD}\"
)



# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})