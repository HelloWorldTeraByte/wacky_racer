#include <stdio.h>
#include "usb_serial.h"
#include "pio.h"
#include "sys.h"
#include "pacer.h"
#include "delay.h"


#define PACER_RATE 1000
#define LED_FLASH_RATE 2

static usb_serial_cfg_t usb_serial_cfg =
{
    .read_timeout_us = 1,
    .write_timeout_us = 1,
};

static usb_serial_t *stream;


static void
prompt_command (void)
{
    usb_serial_puts (stream, "> ");
}


static void
process_command (void)
{
    char buffer[80];
    char *str;
    
    str = usb_serial_gets (stream, buffer, sizeof (buffer));
    if (! str)
        return;

    // usb_serial (stream, "<<<%s>>>\n", str);
    
    switch (str[0])
    {
    case '0':
        pio_output_set (LED1_PIO, 0);
        break;
        
    case '1':
        pio_output_set (LED1_PIO, 1);
        break;

    case 'h':
        usb_serial_puts (stream, "Hello world!\n");
        break;

    default:
       break;
    }

    prompt_command ();
}


int main (void)
{
    usb_cdc_t usb_cdc;
    int flash_ticks = 0;
    int i;

    pio_config_set (LED1_PIO, PIO_OUTPUT_LOW);                
    pio_config_set (LED2_PIO, PIO_OUTPUT_LOW);                

    stream = usb_serial_init (&usb_serial_cfg, "");

    for (i = 0; i < 100; i++)
    {
        usb_serial_puts (stream, "Hello world\n");
        delay_ms (100);
    }

    prompt_command ();
    
    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();

	flash_ticks++;
	if (flash_ticks >= PACER_RATE / (LED_FLASH_RATE * 2))
	{
	    flash_ticks = 0;

	    pio_output_toggle (LED2_PIO);

            process_command ();
	}
    }
}
