#define D0 PB0
#define D1 PB1
#define D2 PB2
#define D3 PB3
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
int table_index = 0;
int index=0;
uint8_t v_level;
byte SineWave[32]={8,9,10,11,12,13,14,15,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7};
void setup() {
DDRB |= 15;//set PB0, PB1, PB2, PB3 as output 
timer1_init();
}

void loop() {
  if(underworld_melody[index]==0){
    TIMSK1=0;
    PORTB=0;
  }
  else{
     set_freq();
  }
  int noteDuration=1000/underworld_tempo[index];
 delay(noteDuration);
 TIMSK1=0;
 PORTB=0;
 int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 index=(index+1)%((sizeof(underworld_tempo))/sizeof(int));

}
void timer1_init(){
 cli();        
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  TCCR1B &= ~(1<<WGM13); 
  TCCR1B |= (1 << WGM12);    // CTC mode
  TCCR1B |= (1<<CS10);       // no prescaler 
  TIMSK1 |= (1 << OCIE1A);   // enable timer compare interrupt

  sei();    
}
ISR(TIMER1_COMPA_vect){
  v_level = SineWave[table_index];
  PORTB = v_level;       
  table_index = (table_index+1)%32;
  
}
void set_freq(){
  cli();  
  TIMSK1 |= (1 << OCIE1A); 
  OCR1A = int((16000000/(32*underworld_melody[index]))-1);  //compare value
  sei(); 
}

/*void timer2_init(){
cli();//stop interrupts
//set timer2 interrupt every 128us
TCCR2A = 0;// set entire TCCR2A register to 0
TCCR2B = 0;// same for TCCR2B
TCNT2  = 0;//initialize counter value to 0
OCR2A = int(16000000*delays[index]/64); 
// turn on CTC mode
TCCR2A |= (1 << WGM21);
// Set CS22 bit for 64 prescaler
TCCR2B |= (1 << CS22);  
// enable timer compare interrupt
TIMSK2 |= (1 << OCIE2A);
sei();//allow interrupts
}
ISR(TIMER2_COMPA_vect){
index=(index+1)%(sizeof(delays));
timer1_init();
}
*/
