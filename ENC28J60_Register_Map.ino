/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: October 7, 2018
  Outputs: Displays power-on-reset values of all ENC28J60 registers 
		   from BANK0, BANK1, BANK2 and BANK3 on serial terminal */

#include <SPI.h>

#define CS 10
#define MOSI 11
#define MISO 12
#define SCK 13

void setup() 
{
  Serial.begin(9600);
  SPI.begin();                               
  pinMode(CS, OUTPUT);                                  //  Setting CSN pin as output.
  pinMode(MOSI, OUTPUT);                                //  Setting MOSI pin as output.
  pinMode(MISO, INPUT);                                 //  Setting MISO pin as input.
  pinMode(SCK, OUTPUT);                                 //  Setting SCK pin as output.
  digitalWrite(CS, HIGH);                               //  Setting CS = 1 to make SPI idle.
  delay(2000);
}

void loop() 
{              
  for (byte j = 0; j <= 3; j++)
  {
    writeReg(0x40 | 0x1F, j);
    Serial.print("BANK: ");
    Serial.println(j);
    for (byte k = 0; k <= 0x19; k++)
    {
      Serial.print(k, HEX);
      Serial.print("h: ");
      Serial.print(readReg(k), HEX);
      Serial.print(", ");
    }
    Serial.println("\r\n");
  }
  while(1);
}

void writeReg(byte ADDR, byte CONTENT)
{
  digitalWrite(CS, LOW);                               // Setting CS = 0 to make SPI active.
  SPI.transfer(ADDR);                                  // Address of register where content is to be written.
  SPI.transfer(CONTENT);                               // Actual content that is to be written.
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
}

byte readReg(byte ADDR)
{
  byte regVal;
  digitalWrite(CS, LOW);                               // Setting CS = 0 to make SPI active.
  SPI.transfer(ADDR);                                  // Address of register from where content is to be read.    
  regVal = SPI.transfer(0x00);                   
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
  return regVal;
}
