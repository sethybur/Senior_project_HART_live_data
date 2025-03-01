#include <Wire.h> //I2C library
const uint8_t I2C_myAddress = 0b0000100; //7bit number identifing this device on the I2C Bus
const uint8_t I2C_controllerAddress = 0b0000001; //7bit number identifing where data should be sent to
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
  I2C_buffer[1024] = "";
  Wire.begin(I2C_myAddress);
  Wire.onReceive(I2C_interupt);

    // initiate serial protocol
  Serial.begin(9600);

  randomSeed(I2C_myAddress);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  //simulating sending data
  String num = String(random(10), DEC);
  String mesage = "sensor id: " + String(I2C_myAddress) + ":\t" + num;
  // I2C_send(mesage.c_str());
  I2C_send("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccdddddddddddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiijjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkklllllllllllllllllllllllllllllllmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnooooooooooooooooooooooooooooooopppppppppppppppppppppppppppppppqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrssssssssssssssssssssssssssssssstttttttttttttttttttttttttttttttuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz1111111111111111111111111111111222222222222222222222222222222233333333333333333333333333333334444444444444444444444444444444555555555555555555555555555555566666666666666666666666666666667777777777777777777777777777777");

  //handle I2C comands
  if(I2C_recievedFlag) I2C_recieve();
}

/*  sends data to I2C data controller
    takes in a string
    functions like println() but to controller
    */
void I2C_send(char message[]) {
  int index = 0;
  int bytes_sent = 0;
  do {
    Wire.beginTransmission(I2C_controllerAddress); //reserves the bus for transmitting

    // sends my address so reader knows where this is coming from.
    Wire.write(I2C_myAddress);
    bytes_sent++;

    // send the mesage in 32 byte chunks
    do {
      Wire.write(message[index]);
      
      index++;
      bytes_sent++;
    } while(message[index-1] != 0 && bytes_sent < 32);

    Wire.endTransmission(); //unreserves the bus
    delay(10);
    bytes_sent = 0;
  } while(message[index-1] != 0);
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