#include <stdio.h>
#include "pico/stdlib.h"

#define BLUE_LED_PIN 11
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13

#define TIME_DEBOUNCE 200  // Configurando o debounce para 200ms

#define BUTTON_PIN 5

volatile int button_state = 0;  // Estado atual do Botão
volatile uint32_t last_press_time_BUTTON = 0;

// Função de interrupção do botão
void button_isr_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Verifica se o botão foi pressionado e se o tempo de debounce passou
    if (gpio == BUTTON_PIN && (current_time - last_press_time_BUTTON > TIME_DEBOUNCE)) {
        last_press_time_BUTTON = current_time;  // Atualiza o tempo do último pressionamento

        // Alterna entre os LEDs conforme o estado atual
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

        // Atualiza o estado do botão, alternando entre 0, 1, 2, 3
        button_state = (button_state + 1) % 4; 
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

    // Loop principal (pode ser usado para fazer outras tarefas ou debug)
    while (true) {
        // Para não consumir a CPU excessivamente
        tight_loop_contents();
    }

    return 0;
}
