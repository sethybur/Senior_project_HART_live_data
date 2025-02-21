#include <Wire.h> //I2C library
const uint8_t I2C_myAddress = 0b0000001; //7bit number identifing this device on the I2C Bus
bool I2C_recievedFlag;
const int bufferSize = 1024;
char I2C_buffer[32];
char I2C_buffer_1[bufferSize];
char I2C_buffer_2[bufferSize];
char I2C_buffer_4[bufferSize];
char I2C_buffer_3[bufferSize];
const uint8_t device1 = 0b0000010;
const uint8_t device2 = 0b0000100;
const uint8_t device3 = 0b0001000;

int miss;

unsigned long start_time;
unsigned long end_time;


// function headers
void I2C_recieve();
void I2C_interupt(int number_of_bytes);
void radioSend(char message[]);

void setup() {
  // put your setup code here, to run once:
  
  // set up buffers
  for (int i = 0; i < 32; i++) I2C_buffer[i] = 0;
  I2C_buffer_1[bufferSize] = "";
  I2C_buffer_2[bufferSize] = "";
  I2C_buffer_3[bufferSize] = "";
  I2C_buffer_4[bufferSize] = "";

  // initiate serial protocol
  Serial.begin(9600);

  // initeate I2C protocol 
  I2C_recievedFlag = false;
  Wire.begin(I2C_myAddress);
  Wire.onReceive(I2C_interupt);
  miss = 0;

  radioSend("starting");
}

void loop() {
  // put your main code here, to run repeatedly:

  //handle I2C comands
  if(I2C_recievedFlag) I2C_recieve();
  if(miss > 0){
    Serial.print("miss ");
    Serial.println(miss);
  }
}

/*  reads the I2C_buffer string
    sends the string to the radio if not empty
    */
void I2C_recieve() {
    
    // select buffer
    char *buffer;
    uint8_t device = I2C_buffer[0];
    if (device = device1) buffer = I2C_buffer_1;
    if (device = device2) buffer = I2C_buffer_2;
    if (device = device3) buffer = I2C_buffer_3;
      Serial.println(I2C_buffer);
      int i = 0;
      while (buffer[i] != 0) i++;
      Serial.println(i, DEC);
      int j = 1;
      while (I2C_buffer[j] != 0 && j < 32) {
        buffer[i] = I2C_buffer[j];
        i++;
        j++;
      }


    // //get to blank character
    // int i = 0;
    
    // 
   
    // for (int j = 1; i < 32; i++){
    //   buffer[i] = I2C_buffer[j];
    //   i++;
    //   // if mesage is over send to radio and clear buffer
    //   if (I2C_buffer[j] == 0){
    //     if (buffer != "") {
    //       radioSend(I2C_buffer);
    //       int i = 0;
    //       while (buffer[i] != 0) {
    //         buffer[i] = 0;
    //         i++;
    //       } 
    //     }
    //     break;
    //   }
    // }

      // Serial.println(buffer);
      // i = 0;
      // while (buffer[i] != 0 && i < bufferSize) {
      //   buffer[i] = 0;
      //   i++;
      // }


  for (int i = 0; i < 32; i++) I2C_buffer[i] = 0;
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