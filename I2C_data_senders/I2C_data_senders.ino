#include <Wire.h> //I2C library
const int I2C_myAddress = 0b1000000; //7bit number identifing this device on the I2C Bus
const int I2C_controllerAddress = 0b0000001; //7bit number identifing where data should be sent to
bool I2C_recievedFlag;
char I2C_buffer[1024];

// function headers
void I2C_send(char message[]);
void I2C_recieve();
void I2C_interupt(int number_of_bytes);

void setup() {
  // put your setup code here, to run once:
  
  // initeate I2C protocol 
  I2C_recievedFlag = false;
  char I2C_buffer[1024] = "";
  Wire.begin(I2C_myAddress);
  Wire.onReceive(I2C_interupt);

  randomSeed(I2C_myAddress);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100); //add delay

  //simulating sending data
  delay(1000);
  String num = String(random(10), DEC);
  String mesage = "sensor id: " + String(I2C_myAddress) + ":\t" + num;
  I2C_send(mesage.c_str());

  //handle I2C comands
  if(I2C_recievedFlag) I2C_recieve();
}

/*  sends data to I2C data controller
    takes in a string
    functions like println() but to controller
    */
void I2C_send(char message[]) {
  Wire.beginTransmission(I2C_controllerAddress); //reserves the bus for transmitting
  Wire.write(message); //writes the bytes to the bus
  Wire.endTransmission(); //unreserves the bus
}

/*  reads the I2C_buffer string 
    you can use this to signal what ever you want
    */
void I2C_recieve() {
  /*  read buffer do stuff
      example:
      if(I2C_buffer == "comand1") {runComand1Function()}
      */
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