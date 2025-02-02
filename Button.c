#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define BLUE_LED_PIN 11
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13

#define TIME_DEBOUNCE 200  // Configurando o debounce para 200ms
#define TIME_LED_CYCLE 3000  // Tempo para alternar automaticamente os LEDs (3s)

#define BUTTON_PIN 5

volatile int button_state = 0;  // Estado atual do botão
volatile uint32_t last_press_time_BUTTON = 0;

// Função para alternar os LEDs automaticamente
int64_t cycle_leds(alarm_id_t id, void *user_data) {
    static bool button_pressed = false;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Se o botão não foi pressionado recentemente, alterne os LEDs automaticamente
    if (current_time - last_press_time_BUTTON >= TIME_LED_CYCLE) {
        button_state = (button_state + 1) % 4;
        if (button_state == 0) {
            gpio_put(BLUE_LED_PIN, true);
            gpio_put(RED_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, true);
        } else if (button_state == 1) {
            gpio_put(BLUE_LED_PIN, false);
        } else if (button_state == 2) {
            gpio_put(RED_LED_PIN, false);
        } else if (button_state == 3) {
            gpio_put(GREEN_LED_PIN, false);
        }
    }
    
    // Reagendar a próxima execução
    add_alarm_in_ms(TIME_LED_CYCLE, cycle_leds, NULL, false);
    return 0;
}

// Função de interrupção do botão
void button_isr_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_PIN && (current_time - last_press_time_BUTTON > TIME_DEBOUNCE)) {
        last_press_time_BUTTON = current_time;
        button_state = (button_state + 1) % 4;

        if (button_state == 0) {
            gpio_put(BLUE_LED_PIN, true);
            gpio_put(RED_LED_PIN, true);
            gpio_put(GREEN_LED_PIN, true);
        } else if (button_state == 1) {
            gpio_put(BLUE_LED_PIN, false);
        } else if (button_state == 2) {
            gpio_put(RED_LED_PIN, false);
        } else if (button_state == 3) {
            gpio_put(GREEN_LED_PIN, false);
        }
    }
}

int main() {
    stdio_init_all();

    // Inicializando os LEDs
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    // Inicializando o botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configura interrupção
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_isr_handler);

    // Agendar a primeira execução do alternador automático
    add_alarm_in_ms(TIME_LED_CYCLE, cycle_leds, NULL, false);

    while (true) {
        tight_loop_contents();
    }

    return 0;
}
