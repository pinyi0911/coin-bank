#include <BluetoothSerial.h>
#include <Servo.h>  //匯入函式庫
#include "pitches.h" 
Servo myservo;  // 建立伺服馬達控制
BluetoothSerial BT;

const int servoPin = 18;  //用常態變數設定pin腳位，與之前define方式差不多
int pos = 0;

  
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BT.begin("rita");//請改名
  myservo.attach(servoPin);  // 將伺服馬達連接的GPIO pin連接伺服物件
  Serial.begin(115200);//序列阜連線速率(鮑率)
  pinMode(25,OUTPUT);
  pinMode(33,OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
  while (BT.available()) {
    //讀取藍芽資料
     String BTdata=BT.readString();
     
    //顯示在序列視窗
    Serial.println(BTdata);

  if(BTdata=="3333"){  //密碼正確

    digitalWrite(25,HIGH);
    digitalWrite(33,LOW);
    for(pos = 0; pos <180; pos++){ // 一度一度由 0 度旋轉到 180 度
        myservo.write(pos); //Servo設定角度
        Serial.println(pos);
        delay(30);
       
      }
      
    }
    else {    //密碼錯誤
      
      digitalWrite(33,HIGH);
      digitalWrite(25,LOW);
      }

   if(BTdata=="a"){ //上鎖
    
    
        myservo.write(0); //Servo設定角度
        Serial.println(pos);
        delay(30);
        digitalWrite(33,LOW);
        digitalWrite(25,LOW);
      
    }
    if(BTdata=="r"){ //重新輸入
    
        digitalWrite(33,LOW);
        digitalWrite(25,LOW);
      
    }
  }    



}
