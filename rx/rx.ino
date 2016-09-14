#include <cc1101.h>

#include <alloca.h>
#define CSN_PIN   10
#define MISO_PIN    12
#define GDO0_PIN     9
#define LED_PIN 13
static CC1101 cc1101;
char *cmd1="cmd1";
char *cmd2="cmd2";
char *cmd3="cmd3";
int rev_count;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  cc1101.init_io(CSN_PIN,MISO_PIN,GDO0_PIN);
  cc1101.begin();
  cc1101.writeDefaultSetting();
  if(cc1101.selftest()) Serial.println("cc1101 connect success");
  else Serial.println("cc1101 connect failure");
  rev_count=0;
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
      digitalWrite(LED_PIN,HIGH);
      cc1101.write_string((unsigned char*)cmd1,sizeof(cmd1));
       Serial.println(cmd1);
      break;
    case 1:
      digitalWrite(LED_PIN,LOW);
       cc1101.write_string((unsigned char*)cmd2,sizeof(cmd2));
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
    
     delay(1000);
   //  cc1101.write_string((unsigned char*)"quanwei",7);
     unsigned char buffer[50]={0};
    int length=cc1101.read_string(buffer,50);
    buffer[length]='\0';
     if(length){
      Serial.println((char*)buffer);
      Serial.println(rev_count++);
    }
    
}

