#include <cc1101.h>
#include <SPI.h>
#include <alloca.h>
#include <math.h>
const int csn=53;
const int miso=50;
const int gdo0=48;

void CC1101::begin()
{
	SPI.begin();
    pinMode(csn,OUTPUT);
    pinMode(miso,INPUT);
    pinMode(gdo0,INPUT);
}
void CC1101::writeDefaultSetting()
{
	write_command_by_addr(CCxxx0_FSCTRL1,rfSettings.FSCTRL1);
    write_command_by_addr(CCxxx0_FSCTRL0,rfSettings.FSCTRL0);
    write_command_by_addr(CCxxx0_FREQ2,rfSettings.FREQ2);
    write_command_by_addr(CCxxx0_FREQ1,rfSettings.FREQ1);
    write_command_by_addr(CCxxx0_FREQ0,rfSettings.FREQ0);
    write_command_by_addr(CCxxx0_MDMCFG4,rfSettings.MDMCFG4);
    write_command_by_addr(CCxxx0_MDMCFG3,rfSettings.MDMCFG3);
    write_command_by_addr(CCxxx0_MDMCFG2,rfSettings.MDMCFG2);
    write_command_by_addr(CCxxx0_MDMCFG1,rfSettings.MDMCFG4);
    write_command_by_addr(CCxxx0_MDMCFG0,rfSettings.MDMCFG4);
    write_command_by_addr(CCxxx0_CHANNR,rfSettings.CHANNR);
    write_command_by_addr(CCxxx0_DEVIATN,rfSettings.DEVIATN);
    write_command_by_addr(CCxxx0_FREND1,rfSettings.FREND1);
    write_command_by_addr(CCxxx0_FREND0,rfSettings.FREND0);
    write_command_by_addr(CCxxx0_MCSM0,rfSettings.MCSM0);
    write_command_by_addr(CCxxx0_FOCCFG,rfSettings.FOCCFG);
    write_command_by_addr(CCxxx0_BSCFG,rfSettings.BSCFG);
    write_command_by_addr(CCxxx0_AGCCTRL2,rfSettings.AGCCTRL2);
    write_command_by_addr(CCxxx0_AGCCTRL1,rfSettings.AGCCTRL1);
    write_command_by_addr(CCxxx0_AGCCTRL0,rfSettings.AGCCTRL0);
    write_command_by_addr(CCxxx0_FSCAL3,rfSettings.FSCAL3);
    write_command_by_addr(CCxxx0_FSCAL2,rfSettings.FSCAL2);
    write_command_by_addr(CCxxx0_FSCAL1,rfSettings.FSCAL1);
    write_command_by_addr(CCxxx0_FSCAL0,rfSettings.FSCAL0);
    write_command_by_addr(CCxxx0_FSTEST,rfSettings.FSTEST);
    write_command_by_addr(CCxxx0_TEST2,rfSettings.TEST2);
    write_command_by_addr(CCxxx0_TEST1,rfSettings.TEST1);
    write_command_by_addr(CCxxx0_TEST0,rfSettings.TEST0);
    write_command_by_addr(CCxxx0_IOCFG2,rfSettings.IOCFG2);
    write_command_by_addr(CCxxx0_IOCFG0,rfSettings.IOCFG0);
    write_command_by_addr(CCxxx0_PKTCTRL1,rfSettings.PKTCTRL1);
    write_command_by_addr(CCxxx0_PKTCTRL0,rfSettings.PKTCTRL0);
    write_command_by_addr(CCxxx0_ADDR,rfSettings.ADDR);
    write_command_by_addr(CCxxx0_PKTLEN,rfSettings.PKTLEN);
    Serial.print("addr is :");
    Serial.println(readreg_by_addr(0x09),HEX);
    Serial.print("version :");
    Serial.println(readstatus_by_addr(0x31),HEX);
}
bool CC1101::selftest()
{
	return readstatus_by_addr(0x31)==0x14;
}
void CC1101::write_string(unsigned char* text,int size)
{
    write_command_by_addr(CCxxx0_TXFIFO,size);
    write_command_by_addr(CCxxx0_TXFIFO,text,size);
    write_mode(0x35);
    delay(5);
    while(digitalRead(gdo0));
    write_mode(CCxxx0_SFTX);    
}

int CC1101::read_string(unsigned char *buffer,int length)
{
    write_mode(0x34); //receive mode
    if(readstatus_by_addr(CCxxx0_RXBYTES)&0x7f)
    {
        int size=readreg_by_addr(CCxxx0_RXFIFO);
        size=min(size,length);
        unsigned char state[2];
        readreg_by_addr(CCxxx0_RXFIFO,buffer,size);
        readreg_by_addr(CCxxx0_RXFIFO,state,2);
        write_mode(CCxxx0_SFRX);
        if(state[1]&0x80)
            return size;
    }
    return 0;
}
unsigned char CC1101::readreg_by_addr(unsigned char addr)
{
    addr|=0x80;
    digitalWrite(csn, LOW);
    while(digitalRead(miso));
    SPI.transfer(addr);
    unsigned char value=SPI.transfer(0);
    digitalWrite(csn, HIGH);
    return value;
}
unsigned char CC1101::readstatus_by_addr(unsigned char addr)
{
    addr|=0xc0;
    digitalWrite(csn, LOW);
    while(digitalRead(miso));
    SPI.transfer(addr);
    unsigned char value=SPI.transfer(0);
    digitalWrite(csn, HIGH);
    return value;
}
void CC1101::readreg_by_addr(unsigned addr,unsigned char* buffer,int size)
{
    addr|=0xc0;    
    digitalWrite(csn, 0);
    while(digitalRead(miso));
    SPI.transfer(addr);
    for(int i=0;i<size;++i)
        buffer[i]=SPI.transfer(0);
    digitalWrite(csn, HIGH);
}
void CC1101::write_command_by_addr(unsigned char addr,unsigned data)
{
	digitalWrite(csn,LOW);
	while(digitalRead(miso));
	SPI.transfer(addr);
	SPI.transfer(data);
	digitalWrite(csn, HIGH);
}
void CC1101::write_command_by_addr(unsigned char addr,unsigned char * buffer,int size)
{
    addr=addr|0x40;
    digitalWrite(csn,LOW);
    while(digitalRead(miso));
    SPI.transfer(addr);
    for(int i=0;i<size;++i)
        SPI.transfer(buffer[i]);
    digitalWrite(csn, HIGH);
}

void CC1101::write_mode(unsigned char mode)
{
    digitalWrite(csn, LOW);
    while(digitalRead(miso));
    SPI.transfer(mode);
    digitalWrite(csn, HIGH);
}