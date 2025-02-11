#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "splash.h"
#include "touch.h"

#define true 1
#define false 0

unsigned char already_started=false;
/* SDL_Event event; */
unsigned char running = false;
unsigned char DoNotSend;

char hostname;
unsigned short port;

extern unsigned char DoNotSend;

int main(int argc, char *argv[])
{
  if (argc<3)
    {
      printf("\nplatoterm <host> <port>\n");
      printf("e.g. irata.online 8005\n");
      return(1);
    }
  else
    {
      strcpy(hostname,argv[1]);
      port=atoi(argv[2]);
    }
  
  screen_init();
  touch_init();
  DoNotSend=1;
  ShowPLATO((padByte *)splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  DoNotSend=0;
  
  running = true;

  while (running)
    {
      keyboard_main();
      io_main();
      screen_main();
      touch_main();
    }
�
  io_done();
  touch_done();
  screen_done();

  return(0);
}
