int cycle;
int i;
int j;
int k;
int l;
int val_X;
int val_Y;
int Frame_Sync = 2;
int Digital_Input = 4;
int Clock = 3;
int Digital_Output = 5;
int Frame_Sync_val = LOW;
int Digital_Input_X = 0;
int Digital_Input_Y = 0;
int Digital_Input_X_Binary[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Digital_Input_Y_Binary[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Digital_Output_X_Binary[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Digital_Output_Y_Binary[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Clock_val = LOW;
int Digital_Output_val = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(Frame_Sync, OUTPUT);
  pinMode(Digital_Input, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Digital_Output, INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  for(cycle = 0; cycle < 100; cycle ++){
    Digital_Input_X = 65536 - cycle/100.0 * 65536;
    Digital_Input_Y = cycle/100.0 * 65536;
    for(l = 0; l < 16; l ++){
      if ( pow(2, 15-l) < Digital_Input_X && Digital_Input_X < pow(2, 16-l) ){
        Digital_Input_X_Binary[l] = 1;
        Digital_Input_X = Digital_Input_X - pow(2, 15-l);
      }
      else{ Digital_Input_X_Binary[l] = 0; }
     if ( pow(2, 15-l) < Digital_Input_Y && Digital_Input_Y < pow(2, 16-l)){
        Digital_Input_Y_Binary[l] = 1;
        Digital_Input_Y = Digital_Input_Y - pow(2, 15-l);
      }
      else{ Digital_Input_Y_Binary[l] = 0; }
    }
  
    for(i = 0; i <2; i ++){
      Frame_Sync_val = 1 - Frame_Sync_val;
      digitalWrite(Frame_Sync, Frame_Sync_val);
      for(j=0; j<2; j++){
        for(k = 0; k < 32; k ++){
          if(Clock_val == 0 && j == 0){
            digitalWrite(Digital_Input, Digital_Input_X_Binary[k/2]);
          }
          else if(Clock_val ==0 && j ==1){
            digitalWrite(Digital_Input, Digital_Input_Y_Binary[k/2]);
          }
          if(Clock_val == 1 && j ==0){
            Digital_Output_X_Binary[k/2] = digitalRead(Digital_Output);
          }
          else if (Clock_val == 1 && j == 1){
            Digital_Output_Y_Binary[k/2] = digitalRead(Digital_Output);
          }
          Clock_val = 1 - Clock_val;
          digitalWrite(Clock, Clock_val);
          delay(3);
        }
      }
      if(i == 1){
        val_X = 0;
        val_Y = 0;
        for(l = 0; l < 16; l++ ){val_X = val_X + pow(2, 15-l) * Digital_Output_X_Binary[l] ;}
        for(l = 0; l < 16; l++){val_Y = val_Y + pow(2, 15-l) * Digital_Output_Y_Binary[l] ;}

    
        Serial.print("X output: ");
        Serial.println(val_X);
        Serial.print("Y output: ");
        Serial.println(val_Y);
    }
  }
}
}
