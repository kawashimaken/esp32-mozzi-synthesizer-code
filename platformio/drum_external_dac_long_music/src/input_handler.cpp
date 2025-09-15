#include "input_handler.h"
#include "driver/gpio.h"

void input_init() {
 // Basic initialization performed in setup()
}

void input_task_init() {
 set_pinmode();
}

void input_update() {
 // Input processing handled within sequence setup functions
}

void set_pinmode() {
 pinMode(cross_button_up, INPUT);
 pinMode(cross_button_down, INPUT);
 pinMode(cross_button_left, INPUT);
 pinMode(cross_button_right, INPUT);
 pinMode(button_confirm, INPUT);
 pinMode(button_cancel, INPUT);
 pinMode(clock_out, OUTPUT);
 pinMode(run_stop, INPUT_PULLUP);
 
 gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLDOWN_ONLY);
 gpio_set_pull_mode(GPIO_NUM_23, GPIO_PULLDOWN_ONLY);
 gpio_set_pull_mode(GPIO_NUM_19, GPIO_PULLDOWN_ONLY);
 gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLDOWN_ONLY);
 gpio_set_pull_mode(GPIO_NUM_16, GPIO_PULLDOWN_ONLY);
 gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLDOWN_ONLY);
}