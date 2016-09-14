#include <cc1101.h>
#include <alloca.h>

static CC1101 cc1101;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  cc1101.begin();
  cc1101.writeDefaultSetting();
  if(cc1101.selftest()) Serial.println("cc1101 connect success");
  else Serial.println("cc1101 connect failure");
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
     cc1101.write_string((unsigned char*)"quanwei",7);
     unsigned char buffer[50]={0};
    int length=cc1101.read_string(buffer,50);
    buffer[length]='\0';
    if(length){
      Serial.println((char*)buffer);
    }
}