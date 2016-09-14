#include <cc1101.h>


#include <alloca.h>
#define CSN_PIN   14
#define MISO_PIN    16
#define GDO0_PIN     24
#define LED_PIN 13
static CC1101 cc1101;
char *cmd1="cmd1";
char *cmd2="cmd2";
char *cmd3="cmd3";
int send_count;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  cc1101.begin(CSN_PIN,MISO_PIN,GDO0_PIN);
  cc1101.writeDefaultSetting();
  if(cc1101.selftest()) Serial.println("cc1101 connect success");
  else Serial.println("cc1101 connect failure");
}
void handle_uart()
{
  int val;
  val= Serial.read();
  Serial.println(val);
  val=val-48;
  switch(val)
  {
    case 0:
      //digitalWrite(LED_PIN,HIGH);
      cc1101.write_string((unsigned char*)cmd1,4);
       Serial.println(cmd1);
      break;
    case 1:
      //digitalWrite(LED_PIN,LOW);
       cc1101.write_string((unsigned char*)cmd2,4);
        Serial.println(cmd2);
      break;
    case 2:
      Serial.print("hello world");
      break;
    default:
      break;  
  }
} 
void loop() {
  // static unsigned char * text=NULL;
  // static int length=0;
  //   if(Serial.available())
  //   {
  //     if(text) free(text);
  //     length=Serial.available();
  //     text=(unsigned char*)malloc(length);
  //     for(int i=0;i<length;++i) text[i]=Serial.read();
  //   }
  int i;
     delay(1000);
     cc1101.write_string((unsigned char*)"quanwei",7);
     unsigned char buffer[50]={0};
      Serial.print("Send cmd:  ");
      Serial.println(send_count++);
      i=i+1;
  //  int length=cc1101.read_string(buffer,50);
  int length=0;
    buffer[length]='\0';
    if(length){
      Serial.println((char*)buffer);
      
    }
}
