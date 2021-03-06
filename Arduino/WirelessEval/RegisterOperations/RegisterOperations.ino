// ************************************************************
// Takes a 16-bit register address and a 16-bit register value 
// and writes the address to value
int regRead(int addr) {
  /* Write register address */
  byte addrAry[2];
  byte ntx;  // Number of transmitted bytes
  byte nrx;  // Number of received bytes
  byte regVals[2]; // The two bytes of read out data

  addrAry[0] = (addr & 0x00FF);
  addrAry[1] = (addr >> 8) & 0x00FF; 

  Wire.beginTransmission(i2cAddr); // transmit to device via I2C
  ntx = Wire.write(addrAry, 2);        // sends two bytes
  Wire.endTransmission();
  if (ntx != 2) {
    Serial.println("*** Error: regRead - could not write register address" );
    return -1;
  }

  /* Receive Register Contents */
  Wire.requestFrom(i2cAddr, 2);    // request 2 bytes from slave device #8

  nrx = 0;
  while (Wire.available()) { // slave may send less than requested
    nrx = nrx + 1;
    int c = Wire.read(); // receive a byte as character
    if (nrx < 3) {
      regVals[nrx-1] = c;
    }
  }
  
  if (nrx < 2) {
    Serial.println("*** Error: regRead - could not read register value" );
    return -1;
  } else {
    return regVals[1] | (regVals[0] << 8);
  }
}

