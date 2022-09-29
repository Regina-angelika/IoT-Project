/*////////////////////////////////////////////////////////////////////////////////
 * Arduino code to display scrolling characters on 4 or more 7x8 LED matrix.    *
 * The no: of matrices can be increased with a small change in code.            *
 * Comments are given in each statement for editing.                            *
 * Circuit designed and program modified by Soumit Das,B.Tech AEIE,RCCIIT Kol   *
 * Contact : soumitdas99@gmail.com                                              *
/*////////////////////////////////////////////////////////////////////////////////

char msg[] ="HELLO WORLD";//Change the text here.
int scrollspeed=35;//Set the scroll speed ( lower=faster)

int x;
int y;

//Columns
int clockPin1 = 5; //Arduino pin connected to Clock Pin 11 of 74HC595
int latchPin1 = 4; //Arduino pin connected to Latch Pin 12 of 74HC595
int dataPin1 = 6;  //Arduino pin connected to Data Pin 14 of 74HC595

//Rows
int clockPin2 = 2; //Arduino pin connected to Clock Pin 11 of 74HC595
int latchPin2 = 7; //Arduino pin connected to Latch Pin 12 of 74HC595
int dataPin2 = 3;  //Arduino pin connected to Data Pin 14 of 74HC595

//BITMAP
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 6 is # of LED matrices
byte bitmap[8][7]; 

int numZones = sizeof(bitmap) / 8; // One Zone refers to one 8 x 8 Matrix ( Group of 8 columns)
int maxZoneIndex = numZones-1;
int numCols = numZones * 8;

//FONT DEFENITION
byte alphabets[][5] = {
 {0,0,0,0,0},                       // spatie      ASCII 32
 {0,0,253,0,0},                     // uitroepteken  ASCII 33
 {0,96,0,96,0},                      // "           ASCII 34
 {20,127,20,127,20},                // #           ASCII 35
 {36,42,127,42,18},                    // $           ASCII 36
 {17,2,4,8,17},                        // %           ASCII 37
 {54,73,85,34,5},                      // &           ASCII 38
 {0,0,104,112,0},                      // '           ASCII 39
 {28,34,65},                           // (           ASCII 40
 {65,34,28},                           // )           ASCII 41
 {20,8,62,8,20},                       // *           ASCII 42
 {8,8,62,8,8},                         // +           ASCII 43
 {0,0,5,6,0},                          // ,           ASCII 44
 {8,8,8,8,8},                          // -           ASCII 45
 {0,0,1,0,0},                          // .           ASCII 46
 {1,2,4,8,16},                         // /           ASCII 47
 {62,69,73,81,62},                     // 0           ASCII 48
 {0,33,127,1,0},                       // 1           ASCII 49
 {33,67,69,73,49},                     // 2           ASCII 50
 {66,65,81,105,70},                    // 3           ASCII 51
 {12,20,36,127,4},                     // 4           ASCII 52
 {113,81,81,81,78},                    // 5           ASCII 53
 {30,41,73,73,6},                      // 6           ASCII 54
 {64,64,79,80,96},                     // 7           ASCII 55
 {54,73,73,73,54},                     // 8           ASCII 56
 {48,73,73,74,60},                     // 9           ASCII 57 
 {0,0,54,54,0},                        // :           ASCII 58
 {0,0,53,54,0},                        // ;           ASCII 59
 {0,8,20,34,65},                       // <           ASCII 60
 {20,20,20,20,20},                     // =           ASCII 61
 {0,65,34,20,8},                       // >           ASCII 62
 {32,64,69,72,48},                     // ?           ASCII 63
 {38,73,77,65,62},                     // @           ASCII 64
 {31,36,68,36,31},                     // A           ASCII 65
 {127,73,73,73,54},                    // B           ASCII 66
 {62,65,65,65,34},                     // C           ASCII 67
 {127,65,65,34,28},                    // D           ASCII 68
 {127,73,73,65,65},                    // E           ASCII 69
 {127,72,72,72,64},                    // F           ASCII 70
 {62,65,65,69,38},                     // G           ASCII 71
 {127,8,8,8,127},                      // H           ASCII 72
 {0,65,127,65,0},                      // I           ASCII 73
 {2,1,1,1,126},                        // J           ASCII 74
 {127,8,20,34,65},                     // K           ASCII 75
 {127,1,1,1,1},                        // L           ASCII 76
 {127,32,16,32,127},                   // M           ASCII 77
 {127,32,16,8,127},                    // N           ASCII 78
 {62,65,65,65,62},                     // O           ASCII 79
 {127,72,72,72,48},                    // P           ASCII 80
 {62,65,69,66,61},                     // Q           ASCII 81
 {127,72,76,74,49},                    // R           ASCII 82
 {50,73,73,73,38},                     // S           ASCII 83
 {64,64,127,64,64},                    // T           ASCII 84
 {126,1,1,1,126},                      // U           ASCII 85
 {124,2,1,2,124},                      // V           ASCII 86
 {126,1,6,1,126},                      // W           ASCII 87
 {99,20,8,20,99},                      // X           ASCII 88
 {96,16,15,16,96},                     // Y           ASCII 89
 {67,69,73,81,97},                     // Z           ASCII 90
 {0,127,65,65,0},                      // [           ASCII 91
 {0,0,0,0,0},                          // \           ASCII 92
 {0,65,65,127,0},                      // ]           ASCII 93
 {16,32,64,32,16},                     // ^           ASCII 94
 {1,1,1,1,1},                          // _           ASCII 95
 {0,64,32,16,0},                       // `           ASCII 96
 {2,21,21,21,15},                      // a           ASCII 97
 {127,5,9,9,6},                        // b           ASCII 98
 {14,17,17,17,2},                      // c           ASCII 99
 {6,9,9,5,127},                        // d           ASCII 100
 {14,21,21,21,12},                     // e           ASCII 101
 {8,63,72,64,32},                      // f           ASCII 102
 {24,37,37,37,62},                     // g           ASCII 103
 {127,8,16,16,15},                     // h           ASCII 104
 {0,0,47,0,0},                         // i           ASCII 105
 {2,1,17,94,0},                        // j           ASCII 106
 {127,4,10,17,0},                      // k           ASCII 107
 {0,65,127,1,0},                       // l           ASCII 108
 {31,16,12,16,31},                     // m           ASCII 109
 {31,8,16,16,15},                      // n           ASCII 110
 {14,17,17,17,14},                     // o           ASCII 111
 {31,20,20,20,8},                      // p           ASCII 112
 {8,20,20,12,31},                      // q           ASCII 113
 {31,8,16,16,8},                       // r           ASCII 114
 {2,21,21,21,9},                       // s           ASCII 115
 {16,126,17,1,2},                      // t           ASCII 116
 {30,1,1,2,31},                        // u           ASCII 117
 {28,2,1,2,28},                        // v           ASCII 118
 {30,1,6,1,30},                        // w           ASCII 119
 {17,10,4,10,17},                      // x           ASCII 120
 {24,5,5,5,30},                        // y           ASCII 121
 {17,19,21,25,17},                     // z           ASCII 122
 {0,0,8,54,65},                        // {           ASCII 123
 {0,0,127,0,0},                        // |           ASCII 124
 {65,54,8,0,0},                        // }           ASCII 125/Z
};

void setup() {
 pinMode(latchPin1, OUTPUT);
 pinMode(clockPin1, OUTPUT);
 pinMode(dataPin1, OUTPUT);

 pinMode(latchPin2, OUTPUT);
 pinMode(clockPin2, OUTPUT);
 pinMode(dataPin2, OUTPUT);
 
 //Clear bitmap
 for (int row = 0; row < 8; row++) {
   for (int zone = 0; zone <= maxZoneIndex; zone++) {
     bitmap[row][zone] = 0; 
   }
 }
}

//FUNCTIONS
// Displays bitmap array in the matrix
void RefreshDisplay()
{
 for (int row = 0; row < 8; row++) {
   int rowbit = 1 << row;
   digitalWrite(latchPin2, LOW);//Hold latchPin LOW for transmitting data
   shiftOut(dataPin2, clockPin2, MSBFIRST, rowbit);   //Transmit data

   //Start sending column bytes
   digitalWrite(latchPin1, LOW);//Hold latchPin LOW for transmitting data

   //Shift out to each matrix
   for (int zone = maxZoneIndex; zone >= 0; zone--) 
   {
     shiftOut(dataPin1, clockPin1, MSBFIRST, bitmap[row][zone]);
   }

   //flip both latches at once to eliminate flicker
   digitalWrite(latchPin1, HIGH);//Return the latch pin 1 high to signal chip
   digitalWrite(latchPin2, HIGH);//Return the latch pin 2 high to signal chip

   //Wait
   delayMicroseconds(300);
 }
}

// Converts row and colum to bitmap bit and turn it off/on
void Plot(int col, int row, bool isOn)
{
 int zone = col / 8;
 int colBitIndex = x % 8;
 byte colBit = 1 << colBitIndex;
 if (isOn)
   bitmap[row][zone] =  bitmap[y][zone] | colBit;
 else
   bitmap[row][zone] =  bitmap[y][zone] & (~colBit);
}
// Plot each character of the message one column at a time, updated the display, shift bitmap left.
void XProcess()
{
 for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
 {
   int alphabetIndex = msg[charIndex] - ' ';
   if (alphabetIndex < 0) alphabetIndex=0;
   
   //Draw one character of the message
   // Each character is 5 columns wide, loop two more times to create 2 pixel space betwen characters (FOR ME ITS 1 EXTRA)
   for (int col = 0; col < 6; col++)
   {
     for (int row = 0; row < 8; row++)
     {
       // Set the pixel to what the alphabet say for columns 0 thru 4, but always leave columns 5 and 6 blank.
       bool isOn = 0; 
       if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
       Plot( numCols-1, row, isOn); //Draw on the rightmost column, the shift loop below will scroll it leftward.
     }
     for (int refreshCount=0; refreshCount < scrollspeed; refreshCount++)
       RefreshDisplay();
     //Shift the bitmap one column to left
     for (int row=0; row<8; row++)
     {
       for (int zone=0; zone < numZones; zone++)
       {
         //This right shift would show as a left scroll on display because leftmost column is represented by least significant bit of the byte.
         bitmap[row][zone] = bitmap[row][zone] >> 1;
         // Shift over lowest bit from the next zone as highest bit of this zone.
         if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7, bitRead(bitmap[row][zone+1],0));
       }
     }
   }
 }
}
void loop() {
 XProcess();
}
