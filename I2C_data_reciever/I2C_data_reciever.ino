#include <Wire.h> //I2C library

// I2C variables
const int I2C_charBufferSize = 32; //make sure it is the same size as the Wire.h buffer
bool I2C_recievedFlag;
char I2C_buffer[I2C_charBufferSize];

// only thing that should need to be changed up here
const uint8_t I2C_myAddress = 0b0000001; //7bit number identifing this device on the I2C Bus

// string buffer variables
const int charBufferSize = 1024;
char charBuffer_1[charBufferSize];
char charBuffer_2[charBufferSize];
char charBuffer_3[charBufferSize];
const uint8_t device1 = 0b0000010;
const uint8_t device2 = 0b0000100;
const uint8_t device3 = 0b0001000;

// function headers
void I2C_recieve();
void I2C_interupt(int number_of_bytes);
void radioSend(char message[]);

void setup() {
  // put your setup code here, to run once:
  
  // set up buffers
  for (int i = 0; i < I2C_charBufferSize; i++) I2C_buffer[i] = 0;
  charBuffer_1[charBufferSize] = "";
  charBuffer_2[charBufferSize] = "";
  charBuffer_3[charBufferSize] = "";

  // initiate serial protocol
  Serial.begin(500000);

  // initeate I2C protocol 
  I2C_recievedFlag = false;
  Wire.begin(I2C_myAddress);
  Wire.onReceive(I2C_interupt);

  radioSend("starting");
}

void loop() {
  // put your main code here, to run repeatedly:

  //handle I2C comands
  if(I2C_recievedFlag) I2C_recieve();
}

/*  reads the I2C_buffer string
    sends the string to the radio if not empty
    */
void I2C_recieve() {
    // select buffer
    char *buffer;
    uint8_t device = I2C_buffer[0];
    if (device = device1) buffer = charBuffer_1;
    if (device = device2) buffer = charBuffer_2;
    if (device = device3) buffer = charBuffer_3;
    int i = 0;
    while (buffer[i] != 0) i++;
    int j = 1;
    while (j < I2C_charBufferSize && i < charBufferSize) {
      buffer[i] = I2C_buffer[j];
      i++;
      j++;
    } while ((I2C_buffer[j-1] != 0) && (j < I2C_charBufferSize) && (i < charBufferSize));
    
    if (I2C_buffer[j-1] == 0) {
      radioSend(buffer);
      i = 0;
      while (buffer[i] != 0 && i < charBufferSize) {
        buffer[i] = 0;
        i++;
      }
    }

  for (int i = 0; i < I2C_charBufferSize; i++) I2C_buffer[i] = 0;
  I2C_recievedFlag = false; //set flag to false
}

/*  handles an I2C interupt
    sets flag I2C_recieved_flag to true
    interprets incoming bytes as chars
    stores as string I2C_buffer 
    */
void I2C_interupt(int number_of_bytes) {
  for(int i = 0; i < number_of_bytes; i++)
  {
    I2C_buffer[i] = Wire.read();
  }
  I2C_recievedFlag = true; //set flag to true
}

/*  the code to send data over meshtastic
    for now it is a serial print
    */
void radioSend(char message[]){
  Serial.println(message);
}