#include "pico/stdlib.h"
#include "pico/double.h"
#include <stdlib.h>

const uint BUTTON_1_PIN = 10U;
const uint BUTTON_2_PIN = 11U;
const uint BUTTON_3_PIN = 12U;

const uint LED_1_PIN = 19U;
const uint LED_2_PIN = 20U;
const uint LED_3_PIN = 21U;

const uint BUZZER_PIN = 14U;
const uint BI_LED_PIN = PICO_DEFAULT_LED_PIN;

const uint ON = 1U;
const uint OFF = 0U;

int current_led = 0;

void boot_blink()
{
    gpio_put(BI_LED_PIN, ON);
    gpio_put(BUZZER_PIN, ON);
    sleep_ms(50);
    gpio_put(BI_LED_PIN, OFF);
    gpio_put(BUZZER_PIN, OFF);
}

void buzz_correct ()
{
    gpio_put(BUZZER_PIN, ON);
    sleep_ms(150);
    gpio_put(BUZZER_PIN, OFF);
}

void buzz_error ()
{
    sleep_ms(50);
    gpio_put(BUZZER_PIN, OFF);
    sleep_ms(50);
    gpio_put(BUZZER_PIN, ON);
    sleep_ms(50);
    gpio_put(BUZZER_PIN, OFF);
}

void setup_item(const uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void setup()
{
    setup_item(BUTTON_1_PIN);
    setup_item(BUTTON_2_PIN);
    setup_item(BUTTON_3_PIN);
    
    setup_item(LED_1_PIN);
    setup_item(LED_2_PIN);
    setup_item(LED_3_PIN);
    
    setup_item(BUZZER_PIN);
    setup_item(BI_LED_PIN);
}

int random_led()
{
    return (rand() % 3);
}

int game_start()
{
    int light = LED_1_PIN + random_led();

    if (current_led != 0)
        gpio_put(current_led, OFF);

    current_led = light;
    gpio_put(light, ON);
}

int game_win()
{
    buzz_correct();
    game_start();
}

int main() 
{
    setup();
    boot_blink();

    game_start();

    while (true)
    {
        if (gpio_get(BUTTON_1_PIN) && gpio_get(LED_1_PIN))
            game_win();

        if (gpio_get(BUTTON_2_PIN) && gpio_get(LED_2_PIN))
            game_win();

        if (gpio_get(BUTTON_3_PIN) && gpio_get(LED_3_PIN))
            game_win();
    }
}
