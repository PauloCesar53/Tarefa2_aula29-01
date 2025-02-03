#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/bootrom.h"
#include "hardware/clocks.h" 
#include "hardware/pll.h"    

//definiçao gpio para os 3 LEDs
#define LED_G_PIN 11 
#define LED_B_PIN 12
#define LED_R_PIN 13

//definição de variáveis que guardarão o estadoatual de cada lED
bool led_on_1 = true;// para LED gpio 11 que inicialmente será ligado 
bool led_on_2 = false;
bool led_on_3 = false;

//função callback que será chamada repetidamente pelo temporizador 
bool repeating_timer_callback(struct repeating_timer *t) {
  if (led_on_1)//para primeira chamda será verdadeiro 
  {
    led_on_1 = !led_on_1;//muda valor logíco para false 
    gpio_put(LED_G_PIN, led_on_1);//desliga LED gpio 11
    gpio_put(LED_B_PIN, true);//liga led Gpio 12
    gpio_put(LED_R_PIN, led_on_1);//garante que LED gpio 13 esta desligado 
    led_on_2 = !led_on_2;//muda valor logíco para verdadeiro (importante pra entra no segundo if da próxima chamada)
  }
  else if (led_on_2)
  {
    led_on_2 = !led_on_2;//muda valor logíco para false 
    gpio_put(LED_G_PIN, led_on_2);//garante que LED gpio 11 esta desligado 
    gpio_put(LED_B_PIN, led_on_2);//desliga LED gpio 12
    gpio_put(LED_R_PIN, true);//liga led Gpio 12
    led_on_3 = !led_on_3;//muda valor logíco para verdadeiro (importante pra entra no segundo if da próxima chamada)
  }
  else if (led_on_3)
  {
    led_on_3 = !led_on_3;//muda valor logíco para false 
    gpio_put(LED_G_PIN, true);//liga led Gpio 11
    gpio_put(LED_B_PIN, led_on_3);//garante que LED gpio 11 esta desligado 
    gpio_put(LED_R_PIN, led_on_3);//desliga LED gpio 12
    led_on_1 = !led_on_1;//muda valor logíco para verdadeiro (importante pra entra no segundo if da próxima chamada)
  }
    // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
    return true;
}
int main()
{
  // inicializa o sdk
  stdio_init_all();
  // configurando LED (verde na BitDogLab e vermelho no wokwi)
  gpio_init(LED_G_PIN);//inicia o pino 
  gpio_set_dir(LED_G_PIN, GPIO_OUT);//configura como saída 
  gpio_put(LED_G_PIN, true);// liga o primeiro para iniciar o ciclo de repetição 

// configurando LED (azul na BitDogLab e amarelo no wokwi)
  gpio_init(LED_B_PIN);//inicia o pino 
  gpio_set_dir(LED_B_PIN, GPIO_OUT);//configura como saída
  
//configurando LED (vermelhho na BitDogLab e verde no wokwi)
  gpio_init(LED_R_PIN);//inicia o pino
  gpio_set_dir(LED_R_PIN, GPIO_OUT);//configura como saída

  // Declaração de uma estrutura de temporizador de repetição.
  // Esta estrutura armazenará informações sobre o temporizador configurado.
  struct repeating_timer timer;
  // Configura o temporizador para chamar a função de callback a cada 3 segundos.
  add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

  while (true)
  {
    
  }
  return 0;
}
