#include <Wire.h> //I2C library
const int I2C_myAddress = 0b0000001; //7bit number identifing this device on the I2C Bus
bool I2C_recievedFlag;
char I2C_buffer[1024];

// function headers
void I2C_recieve();
void I2C_interupt(int number_of_bytes);
void radioSend(char message[]);

void setup() {
  // put your setup code here, to run once:
  
  // initeate I2C protocol 
  I2C_recievedFlag = false;
  char I2C_buffer[1024] = "";
  Wire.begin(I2C_myAddress);
  Wire.onReceive(I2C_interupt);

  // initiate serial protocol
  Serial.begin(9600);

  radioSend("starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); //add delay

  //handle I2C comands
  if(I2C_recievedFlag) I2C_recieve();
}

/*  reads the I2C_buffer string
    sends the string to the radio if not empty
    */
void I2C_recieve() {

  if (I2C_buffer != "") {
    radioSend(I2C_buffer);
    int i = 0;
    while (I2C_buffer[i] != '\0') {
      I2C_buffer[i] = '\0';
      i++;
    } 
  }
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