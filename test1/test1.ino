byte keys[5][6];
int row,col;
void setup() {
  
  Serial.begin(9600);  
  Serial.print("KB test\n");
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH); 
  memset(keys,0,sizeof(keys));  
}

void loop() {
  int k;
  for(col=0;col<6;col++){
    digitalWrite(col+8, LOW);
    for(row=0;row<5;row++){      
      k=!digitalRead(row+2);
      if(keys[row][col]!=k){
        keys[row][col]=k;
        Serial.print("c: ");
        Serial.print(col);
        Serial.print(" r: ");
        Serial.print(row);
        Serial.print("\n");
      }
    }
    digitalWrite(col+8, HIGH);
  }
}
