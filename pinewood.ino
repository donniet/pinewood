#include <Adafruit_NeoPixel.h>
#include <Logging.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif


#define PIXEL_PIN 4
#define NUM_LEDS_PER_SIDE 11
#define MS_PER_FRAME 20

uint32_t colors[255];

const char message_hello[] = 
  "           "
  "###########"
  "    ##     "
  "    ##     "
  "###########"
  "           "
  "###########"
  "##  ##   ##"
  "##  ##   ##"
  "##  ##   ##"
  "           "
  "###########"
  "##         "
  "##         "
  "##         "
  "           "
  "###########"
  "##         "
  "##         "
  "##         "
  "           "
  "###########"
  "##       ##"
  "##       ##"
  "###########"
  "           "
  ;

const char message_checkerboard[] =
  " ##  ##  ##"
  " ##  ##  ##"
  "#  ##  ##  "
  "#  ##  ##  "
  " ##  ##  ##"
  " ##  ##  ##"
  "#  ##  ##  "
  "#  ##  ##  "
  " ##  ##  ##"
  " ##  ##  ##"
  "#  ##  ##  "
  "#  ##  ##  "
  " ##  ##  ##"
  " ##  ##  ##"
  "#  ##  ##  "
  "#  ##  ##  "
;

const char message[] = 
  "%%       $$"
  "  %%    $$ "
  "    %% $$  "
  "     $#%   "
  "   $$  %%  "
  " $$     %% "
  "$$       %%"
  "$$       %%"
  "  $$    %% "
  "    $$ %%  "
  "     %#$   "
  "   %%  $$  "
  " %%     $$ "
  "%%       $$"
 ;

const char message_winner[] = 
  "###########"
  " ##        "
  " ##        "
  "###########"
  "           "
  "##       ##"
  "###########"
  "##       ##"
  "           "
  "###########"
  "      ###  "
  "   ###     "
  "###########"
  "           "
  "###########"
  "      ###  "
  "   ###     "
  "###########"
  "           "
  "###########"
  "##  ##   ##"
  "##  ##   ##"
  "##  ##   ##"
  "           "
  "###########"
  "  ####   ##"
  " ## ##   ##"
  "##  #######"
  "           "
;

const char message_pinewood[] =
  "           "
  "###########"
  "    ##$$$##"
  "    ##$$$##"
  "    #######"
  "           "
  "##       ##"
  "###########"
  "##       ##"
  "           "
  "###########"
  "      ###  "
  "   ###     "
  "###########"
  "           "
  "###########"
  "##  ##   ##"
  "##  ##   ##"
  "##  ##   ##"
  "           "
  "###########"
  " ##        "
  " ##        "
  "###########"
  "           "
  "###########"
  "##$$$$$$$##"
  "##$$$$$$$##"
  "###########"
  "           "
  "###########"
  "##$$$$$$$##"
  "##$$$$$$$##"
  "###########"
  "           "
  "###########"
  "##$$$$$$$##"
  "##$$$$$$$##"
  "  #######  "
  "           "
  "           "
  ;

const unsigned long message_length = sizeof(message) / sizeof(char) / NUM_LEDS_PER_SIDE;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS_PER_SIDE * 2 + 1, PIXEL_PIN);

void setup() {
  Log.Init(LOGLEVEL, 38400L);
  Log.Info(CR"******************************************"CR);
  Log.Info("My favorite output stuff in future :-)"CR);
  Log.Info("******************************************"CR);
  
  colors['#'] = 0xFFFFFF;
  colors[' '] = 0x000000;
  colors['$'] = 0xFFF000;
  colors['%'] = 0x000FFF;
  // put your setup code here, to run once:
  pixels.begin();
  pixels.setBrightness(30);

  for (int i = 0; i < NUM_LEDS_PER_SIDE * 2 + 1; i++) {
    pixels.setPixelColor(i, 0x000000);
  }
}

unsigned int current = 0;

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long frame = (current++) % message_length;
  unsigned long back_frame = message_length - frame;

  unsigned long start = frame * NUM_LEDS_PER_SIDE;
  unsigned long back_start = back_frame * NUM_LEDS_PER_SIDE;

  
  float p = sin(2.0 * PI * float(frame) / float(message_length));
  
  uint32_t status = (uint32_t(float(0xFF) * p * p)) << 8;
  pixels.setPixelColor(2 * NUM_LEDS_PER_SIDE, status);

  for(unsigned long i = 0; i < NUM_LEDS_PER_SIDE; i++) {
    char front_char = message[start + i];
    pixels.setPixelColor(i, colors[front_char]);
//    pixels.setPixelColor(2 * NUM_LEDS_PER_SIDE  - i - 1, colors[front_char]);
    pixels.setPixelColor(2 * NUM_LEDS_PER_SIDE - i - 1, colors[message[back_start + i]]);
  } 

  pixels.show();
  delay(MS_PER_FRAME);
}
