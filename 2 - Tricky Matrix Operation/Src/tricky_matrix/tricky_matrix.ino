/*
 * Project Name: Tricky Matrix Problem
 * 
 * Task:
 * 1. Generate a mirror image equivalent of a matrix represented by uint16_t and
 *    uint64_t datatypes each.
 * 2. For the same two datatypes generate a counter clock-wise rotated matrix.
 */

/*
 * --- Utility function used for debugging ---
 * Print a uint64_t in hex format.
 */
 void printHex64(uint64_t val);
 
/*
 * Core functions for the task given
 */
// Return mirror image of uint16_t
uint16_t mirror16(uint16_t num);

// Return mirror image of uint64_t
uint64_t mirror64(uint64_t num);

// Return counter clockwise rotated image of uint16_t
uint16_t rotate16(uint16_t num);

// Return counter clockwise rotated image of uint64_t
uint64_t rotate64(uint64_t num);

void setup() {
  uint16_t x = 0x124f;
  uint64_t y = 0xfe010101010101fe;

  /* Initialize Serial comm */
  Serial.begin(9600);
  
  Serial.println("--------- Mirror image ---------");
  Serial.print("x = 0x");
  Serial.println(x, HEX);
  Serial.print("mirror16(x) = 0x");
  Serial.println(mirror16(x), HEX);
  
  Serial.print("y = 0x");
  printHex64(y);
  Serial.print("mirror64(y) = 0x");
  printHex64(mirror64(y));
  
  Serial.println("--------- Anti-clock wise rotation ---------");
  Serial.print("x = 0x");
  Serial.println(x, HEX);
  Serial.print("rotate16(x) = 0x");
  Serial.println(rotate16(x), HEX);
  
  Serial.print("y = 0x");
  printHex64(y);
  Serial.print("rotate64(y) = 0x");
  printHex64(rotate64(y));

  Serial.println("\n--------------------***--------------------\n");
}

void loop() {
}

uint16_t mirror16(uint16_t num) {
    uint16_t nBits = 3; // Nibble bits 0 - 3
    uint16_t nibble, reverse_nibble, ret_val = 0;

    // For each nibble do... reverse its bit sequence.
    // There are 4 nibbles in a uint16_t integer.
    for(uint16_t i = 0; i < 4; ++i) {

      // Extract each nibble one-by-one starting from right most nibble of num.
      nibble = (num >> (i * 4)) & 0x000f;
      
      // Rearrange the bits of the currrent nibble in reverse order.
      reverse_nibble = nibble;
      nibble >>= 1;
      nBits = 3; // Reset bit count of a nibble
      while(nibble)
      {
        reverse_nibble <<= 1;
        reverse_nibble |= nibble & 0x1;
        nibble >>= 1;
        nBits--;
      }
      reverse_nibble <<= nBits;
      
      ret_val |= (reverse_nibble & 0x000f) << (i * 4);
    
    }// end for
    
    return ret_val; 
}

uint64_t mirror64(uint64_t num) {
    uint64_t nBits = 7; // Bits 0 - 7 of each byte
    uint64_t _byte, reverse_byte, ret_val = 0;

    // For each byte do... reverse its bit sequence.
    // There are 8 bytes in a uint64_t integer.
    for(uint16_t i = 0; i < 8; ++i) {

      // Extract each byte one-by-one starting from right most byte of num.
      _byte = (num >> (i * 8)) & 0x00ff;
      
      // Rearrange the bits of the currrent byte in reverse order.
      reverse_byte = _byte;
      _byte >>= 1;
      nBits = 7; // Reset bit count of a byte
      while(_byte)
      {
        reverse_byte <<= 1;
        reverse_byte |= _byte & 0x1;
        _byte >>= 1;
        nBits--;
      }
      reverse_byte <<= nBits;
      
      ret_val |= (reverse_byte & 0x00ff) << (i * 8);
    
    }// end for
    
    return ret_val; 
}

uint16_t rotate16(uint16_t num) {
  uint16_t nibble, bit_pos_mask = 0x01, ret_val = 0;

  // For each nibble do... reverse its bit sequence.
  // There are 4 nibbles in a uint16_t integer.
  for(uint16_t i = 0; i < 4; ++i) {

    // Extract each nibble one-by-one starting from right most nibble of num.
    nibble = (num >> (i * 4)) & 0x000f;

    // Setting the 0th, 1th, 2th, 3th bit of each nibble happens here.
    for(int i = 3; i >= 0; --i) {
      if(nibble & (1 << i)) {
        ret_val |= bit_pos_mask << ((3 - i) * 4); // Set bit
      }
      else {
        ret_val &= ~(bit_pos_mask << ((3 - i) * 4)); // Clear bit
      }
    }

    bit_pos_mask <<= 1; 
  
  }// end for
    
  return ret_val; 
}

uint64_t rotate64(uint64_t num) {
  uint64_t _byte, bit_pos_mask = 0x01, ret_val = 0;

  // For each byte do... reverse its bit sequence.
  // There are 8 bytes in a uint64_t integer.
  for(uint16_t i = 0; i < 8; ++i) {

    // Extract each byte one-by-one starting from right most byte of num.
    _byte = (num >> (i * 8)) & 0x00ff;

    // Setting the 0th, 1th, 2th, 3th bit of each byte happens here.
    for(int i = 7; i >= 0; --i) {
      if(_byte & (1 << i)) {
        ret_val |= bit_pos_mask << ((7 - i) * 8); // Set bit
      }
      else {
        ret_val &= ~(bit_pos_mask << ((7 - i) * 8)); // Clear bit
      }
    }

    bit_pos_mask <<= 1; 
  
  }// end for
    
  return ret_val;  
}

void printHex64(uint64_t val) {
  uint8_t *ptr;
  char __str[15] = "";

  // Since endianness of the ATMega328p is little-endian,
  // each byte has to printed starting from the last byte address.
  for(int16_t i = 7; i >= 0; i--) {
    ptr = ((uint8_t*)&val + i);
    sprintf(__str, "%02x", *ptr);
    Serial.print(__str);
  }
  Serial.println();
}

