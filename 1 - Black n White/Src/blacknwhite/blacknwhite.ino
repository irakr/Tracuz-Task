/* Analog pin number for color sensor.  */
#define COLOR_SENSOR_PIN  A0

/* Stores the count of the number of black and white bars in the barcode. */
int nWhite = 0, nBlack = 0;

/* Indicates whether a barcode operation has started or not.  */
bool startOp = false;

/* 
 * These variables indicate whether a white bar has been detected and
 * this information will help prevent duplicate readings of same color.
 * This is useful since we know that each color bars has a certain width
 * and the MCU may be too fast to detect same color a hundreds of time
 * while being in the area of that particular color. 
 */
bool inWhite = false, inBlack = false;

/*
 * Checks whether the color is black or white.
 * Returns 0 for black, 1 for white and -1 for any other color.
 */
int getColor(void) {
  int readVal = analogRead(COLOR_SENSOR_PIN);
  if(readVal == 0) // Black
    return 0;
  else if(readVal == 1023) // White
    return 1;
  else
    return -1;
    
}

void setup() {
  // Configure sensor pins
  pinMode(COLOR_SENSOR_PIN, INPUT);

  // Configure UART for printing output messages on the terminal.
  Serial.begin(9600);
}

void loop() {

  // Check the color.
  int val = getColor();
  
  // Start of each barcode operation if color detected is either white or black.
  if((val == 0) || (val == 1)) {
    while(true) {
      // If White detected and we were not in white bar recently.
      if((inWhite == false) && (val == 1)) {
        nWhite++;
        inWhite = true; // We are in white bar.
        inBlack = false; // We are out of black bar.
      }
      // If Black detected and we were not in white bar recently.
      else if((inBlack == false) && (val == 0)) {
        nBlack++;
        inBlack = true; // We are in black bar.
        inWhite = false; // We are out of white bar.
      }
      else if(val == -1) { // Neither black nor white detected (Termination condition).
    
        // Print the result and reset the count variables for next operation.
        char str[70];
        sprintf(str, "Number of Black bars = %d and white bars = %d",
                      nBlack, nWhite);
        Serial.println(str);
        nWhite = nBlack = 0;
        inWhite = inBlack = false;
        break;
      }

      // Keep reading color values.
      val = getColor();
    }
  }
  // else no barcode has been detected yet.
}
