#include <FAB_LED.h>
#include <string.h>

// Declare the LED protocol and the port
ws2812b<D,6>  strip;

// How many pixels to control
const uint8_t numPixels = 4;

// How bright the LEDs will be (max 255)
const uint8_t maxBrightness = 16;

// The pixel array to display
grb  pixels[numPixels] = {};

using namespace std; 
////////////////////////////////////////////////////////////////////////////////
// Sets the array to specified color
////////////////////////////////////////////////////////////////////////////////
void FillPixels(char r, char g, char b)
{
  for(int i = 0; i < numPixels; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}

////////////////////////////////////////////////////////////////////////////////
// This method is automatically called once when the board boots.
////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  // Turn off the LEDs
  Serial.println("start;");
  //strip.clear(2 * numPixels);
  FillPixels(255,0,0);
  strip.sendPixels(numPixels, pixels); 
  
  noInterrupts();           // disable all interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 20000;            // compare match register 8MHz/8/100Hz

  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 >> CS10); //prescaler = 8
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();
}

String s;
int timer = 0;
int oldtimer = 0;
////////////////////////////////////////////////////////////////////////////////
/// @brief This method is automatically called repeatedly after setup() has run.
/// It is the main loop.
////////////////////////////////////////////////////////////////////////////////
void loop()
{
  if (Serial.available() > 0)
  {
    s = Serial.readString();
    Serial.println(s);
  }

  if(timer != oldtimer)
  {
    if(s[0]-48 < 6) scene(s[0]-48);
    
    strip.sendPixels(numPixels, pixels); 
    oldtimer = timer;
  }
}

void scene(char scene_number)
{
    switch(scene_number)
    {
      case 1:
        scene_lauflicht();
        Serial.println("1;");
      break;
      case 2:
        scene_rainbow();
        Serial.println("2;");
      break;
      case 3:
        scene_loading();
        Serial.println("3;");
      break;
      case 4:
        scene_white();
        Serial.println("4;");
      break;
      default:
        scene_off();
        Serial.println("off;");
      break;  
    }  
}

void scene_lauflicht()
{
  static char counter = 1;
  static char llpos = 0;
  
  if(counter != 20)
  {
    counter++;
  }
  else
  {
      counter = 1;
      FillPixels(0,0,0);
      Set_pixel(llpos,0,0,255);
      if(llpos == 3)
      {
        llpos = 0;
      }
      else
      {
        llpos++;  
      }
  }
}

void scene_loading()
{
  static char counter = 1;
  static char llpos = 0;
  char c = 0;
  
  if(counter != 25)
  {
    counter++;
  }
  else
  {
      counter = 1;
      FillPixels(0,0,0);
      
      for(c = 0 ; c != llpos+1; c++)
      {
        Set_pixel(c,0,0,255);
      }
      
      if(llpos == 3) llpos = 0;
      else llpos++;
      
  }
}

void scene_rainbow()
{
  //Just look at this
    //https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/HSV-RGB-comparison.svg/451px-HSV-RGB-comparison.svg.png
    
    static int Counter = 0;   //=degrees
    static char rgbArr[3];
    
    if(Counter <= 60)
    { 
        rgbArr[0] = 240;                    //(R)GB, 240 as max
        rgbArr[1] = rgbArr[1] + 4;          //R(G)B, 60 * 4 = 240
        rgbArr[2] = 0;                      //RG(B), 0 as min
    }
    if((Counter > 60) && (Counter <= 120))
    {
        rgbArr[0] = rgbArr[0] - 4;
        rgbArr[1] = 240;
    }
    if((Counter > 120) && (Counter <= 180))
    {
        rgbArr[0] = 0;
        rgbArr[2] = rgbArr[2] + 4;
    }
    if((Counter > 180) && (Counter <= 240))
    {
        rgbArr[1] = rgbArr[1] - 4;
        rgbArr[2] = 240;
    }
    if((Counter > 240) && (Counter <= 300))
    {
        rgbArr[0] = rgbArr[0] + 4;
        rgbArr[1] = 0;
    }
    if((Counter > 300) && (Counter <= 360))
    {
        rgbArr[0] = 240;
        rgbArr[2] = rgbArr[2] - 4;;
    }
    if(Counter == 360) //Max limit reached
    {
      Counter = 0;     //restart Counter at 0
    } 
    else
    {
      Counter++;       //increase Counter
    }

    FillPixels(rgbArr[0],rgbArr[1],rgbArr[2]);
    /*
    Serial.print(Counter);
    Serial.print(", ");
    */
}

void scene_white()
{
  FillPixels(240,240,240);
}
void scene_off()
{
  FillPixels(0,0,0);
}

void Set_pixel(int pos,char r,char g,char b)
{
    pixels[pos].r = r;
    pixels[pos].g = g;
    pixels[pos].b = b;
}

void Send_newPixel()
{
  strip.sendPixels(numPixels, pixels);
}

void clearPixels(void)
{
  for(int i = 0; i != numPixels; i++)
  {
    pixels[i].r = 0;
    pixels[i].g = 0;
    pixels[i].b = 0;
  }
}

ISR(TIMER1_COMPA_vect)
{
  //digitalWrite(13, digitalRead(13) ^ 1); // LED ein und aus
  
  timer++;
}
