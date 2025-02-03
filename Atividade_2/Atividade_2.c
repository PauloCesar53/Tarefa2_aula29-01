
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// definiçao gpio para os 3 LEDs e botão
#define LED_G_PIN 11
#define LED_B_PIN 12
#define LED_R_PIN 13
#define BUTTON_PIN 5 // Define o pino GPIO 5 para ler o estado do botão.

uint PINO_LED = 11;            // auxiliar para entrar na função de callback e desligar inicialmente pino 11
bool led_active = false;       // Indica se o LED está atualmente aceso (para evitar múltiplas ativações).

// Função de callback para desligar o LED após o tempo programado, que irá se repetir 3 vezes
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    if (PINO_LED != 13)
    {
        // Desliga o LED configurando o pino LED_PIN para nível baixo.
        gpio_put(PINO_LED, false);
        PINO_LED++;//incrementa para pino 12
        // Retorna  para indicar que o alarme  deve se repetir a cada 3 segundos
        return 3000 * 1000;
    }
    else
    {
        gpio_put(PINO_LED, false);//entra no Pino 13
        led_active = false;//indica que os pinos estão todos desligados 
        PINO_LED = 11;//iguala a 11 para repetir o processo 
        return 0; // Retorna 0 para indicar que o alarme  não deve se repetir.
    }
}

int main()
{
    // Inicializa sdk
    stdio_init_all();

    // Configuração  do LED gpio11
    gpio_init(LED_G_PIN);              // iniciando pino
    gpio_set_dir(LED_G_PIN, GPIO_OUT); // definindo como saída

    // Configuração  do LED gpio12
    gpio_init(LED_B_PIN);              // iniciando pino
    gpio_set_dir(LED_B_PIN, GPIO_OUT); // definindo como saída

    // Configuração  do LED gpio13
    gpio_init(LED_R_PIN);              // iniciando pino
    gpio_set_dir(LED_R_PIN, GPIO_OUT); // definindo como saída

    // Configura o pino BUTTON_PIN (5) como entrada digital.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o resistor pull-up interno para o pino do botão.

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true)
    {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && !led_active)
        {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);
            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0)
            {
                // Liga o LEDs configurando o pinos para nível alto.
                gpio_put(LED_G_PIN, true);
                gpio_put(LED_B_PIN, true);
                gpio_put(LED_R_PIN, true);

                // Define 'led_active' como true para indicar que o LED está aceso.
                led_active = true;
                // Agenda um alarme para desligar o primeiro LED após 3 segundos (3000 ms).
                // A função 'turn_off_callback' será chamada após esse tempo.
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }  
        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        // Isso evita que o loop seja executado muito rapidamente e consuma recursos desnecessários.
        sleep_ms(10);
    }
    return 0;
}
