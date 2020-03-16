#include <SPI.h>

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>


#define OLED_RESET 4



Adafruit_SSD1306 display(OLED_RESET);



#if (SSD1306_LCDHEIGHT != 64)


#error("Height incorrect, please fix Adafruit_SSD1306.h!");


#endif


int coin_pin = A3;



int target_amount = 500;


int balance_amount = 0;



int coin_value = 10;

int coin_inserted_state = HIGH;


void setup() {



  // put your setup code here, to run once:

   // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  // init done

   pinMode( coin_pin ,INPUT);

   Serial.begin(9600);

   updateDisplay();

  delay(2000);



}

void loop() {



  // put your main code here, to run repeatedly:



  // Serial.println(  digitalRead( coin_pin ));



  // delay(500);







     if( (digitalRead( coin_pin ) == LOW ) && coin_inserted_state == HIGH ){



        coin_inserted_state = LOW;



        balance_amount += coin_value;



        updateDisplay();



     }



     else if( (digitalRead( coin_pin ) == HIGH ) && coin_inserted_state == LOW ){



        coin_inserted_state = HIGH;



     }



}


void updateDisplay()

{


int remaining_amount = target_amount - balance_amount ;


    remaining_amount = (remaining_amount < 0)?0:remaining_amount;


  float  p = ((float)balance_amount / (float)target_amount) * 100.00;



  float bar = ((float)(display.width()-6) / 100) * p;


   // Clear the buffer.



  display.clearDisplay();



   // text display tests



  display.setTextSize(3);



  display.setCursor(0,0);



    display.setTextColor(WHITE);



  //display.setTextColor(BLACK, WHITE); // 'inverted' text

  display.println(balance_amount);

  display.setTextSize(1);

  display.setCursor(0,30);

    display.setTextColor(WHITE);

  //display.setTextColor(BLACK, WHITE); // 'inverted' text

  display.print("Remaining: ");

  display.print( remaining_amount );

  display.setCursor(100,55);

  display.setTextSize(1);

  display.setTextColor(BLACK, WHITE); // 'inverted' text

  display.print(" ");

  display.print(target_amount);

  display.drawRect(0, 40, display.width()-2, display.height()-52, WHITE);

  display.fillRect(2, 42, bar , display.height()-56, WHITE);

  display.display();

}
