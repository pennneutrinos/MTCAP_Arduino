/*
 Programs thresholds on MTCA Plus
 ...assuming you have the correct chunks of vector board
 */
 
// Thresholds in Volts
float thresh_h = 4.5;
float thresh_m = 4.5;
float thresh_l = 4.92;

// Arduino pins to use
int dac_clk = 13;
int dac_sel = 11;
int dac_l = 12;
int dac_m = 10;
int dac_h = 9;

const int clk_delay = 50;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(dac_clk, OUTPUT);
  pinMode(dac_sel, OUTPUT);
  pinMode(dac_l, OUTPUT);
  pinMode(dac_m, OUTPUT);
  pinMode(dac_h, OUTPUT);
  digitalWrite(dac_sel, HIGH);
}
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(dac_sel, LOW);
  digitalWrite(dac_clk, HIGH);

  unsigned int l = (thresh_l + 5)*(4095/10);;
  unsigned int m = (thresh_m + 5)*(4095/10);;
  unsigned int h = (thresh_h + 5)*(4095/10);;

  // First 4 bits are unused
  for(int i=0; i < 4; i++) {
    digitalWrite(dac_l, (l>>i) & 1);
    digitalWrite(dac_l, LOW);  
    digitalWrite(dac_m, LOW); 
    digitalWrite(dac_h, LOW); 
    digitalWrite(dac_clk, LOW);
    delay(50);
    digitalWrite(dac_clk, HIGH);
    delay(50);
  }
  
  for(int i = 11;i>=0;i--)
  {
    digitalWrite(dac_l, (l>>i) & 1); 
    digitalWrite(dac_m, (m>>i) & 1); 
    digitalWrite(dac_h, (h>>i) & 1); 
    delay(20);
    printf("%u\n", (l>>i) & 1);
    digitalWrite(dac_clk, LOW);
    delay(clk_delay);
    digitalWrite(dac_clk, HIGH);
    delay(clk_delay);
  }
  digitalWrite(dac_sel,HIGH);
  while(1) {
    delay(3600);
  }
    
}
