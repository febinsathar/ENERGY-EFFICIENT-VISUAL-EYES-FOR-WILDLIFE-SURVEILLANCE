#include<18f4550.h>

#fuses HSPLL, NOWDT, NOPROTECT, NOLVP, NODEBUG, USBDIV, 

PLL5, CPUDIV1, VREGEN

#use delay(clock=28800000)

#define pir3 PIN_D7

#define pir2 PIN_D6

#define pir1 PIN_D5

#define led1 PIN_A0

#define led2 PIN_A1

#define led3 PIN_A4

#define servo PIN_C2

#define sdo PIN_C7

#define sdi PIN_B0

unsigned char i=0,k=0,j=0,tempii;

unsigned int16 a=0;

unsigned char f1=00;

void pic_rpi()//communicate with rpi

{

 output_low(sdo);

 for(k=0;k<10;++k)

 {

 output_low(led1);

 output_low(led2);

 delay_ms(100);

 output_high(led1);

 output_high(led2);

 delay_ms(100);

 }

 while(1)

 {

 if(input(sdi)==0)

 break;

 }

 output_high(sdo);

 for(k=0;k<10;++k)

 {

 output_low(led1);

 output_low(led2);

 delay_ms(100);

 output_high(led1);

 output_high(led2);

 delay_ms(100);

 }

}

void readpir() //to read PIR outputs

{

 if(input(pir1))

 { 

 output_low(led1);

 i+=3;

 }

 else

 output_high(led1);

 if(input(pir2))

 {

 output_low(led2);

 i+=6;

 } 

 else

 output_high(led2);

 if(input(pir3))

 {

 output_low(led3);

 i+=12;

 }

 else

 output_high(led3);

}

void turnservo(int16 b) //rotates the servo through angle b

{

 b=10*b+450;

 for(f1=0;f1<=50;f1++)

 {

 output_high(servo);

 delay_us(b);

 output_low(servo);

 delay_us(20000-b);

 }

}

void findangle() // use status of PIR outputs to find the 

angle to which the camera is to be turned

{

 switch(i)

 {

 case 3: a=0;

 break;

 

 case 9: a=45;

 break;

 

 case 18: a=135;

 break;

 

 case 12: a=180;

 break;

 case 6:

 case 21:

 case 15: a=90;

 break;

 }

 turnservo(a);

 pic_rpi();

 turnservo(a);

 //code to avoid multiple photos 

 tempii=i;

 while(1)

 {

 i=0;

 readpir();

 if(i!=tempii)

 break;

 

}

 i=0; }

void main() {

 unsigned char tempi=0;

 output_high(led1);

 output_high(led2);

 output_high(led3); 

 i=0;

 turnservo(90);

 //handshake between rpi and pic

 delay_ms(10000);

 output_high(sdo);

 while(1)

 

{

 if(input(sdi)==0)

 break;

 

}

 output_low(sdo);

 while(1)

 

{

 if(input(sdi)==1)

 break;

 

}

 output_high(sdo);

 //for testing

 for (j=0;j<10;++j)

 

{

 output_low(led1);

 output_low(led2);

 output_low(led3);

 delay_ms(100);

 output_high(led1);

 output_high(led2);

 output_high(led3); 

 delay_ms(100);

 

}

 //handshake completed

 output_high(led1);

 output_high(led2);

 output_high(led3);

 while(1)

 {

 if(input(pir1)||(input(pir2))||(input(pir3)))

 {

 i=0;

 readpir();

 delay_ms(300);

 tempi=i;

 i=0;

 readpir();

 if(tempi==i)

 findangle();

 else

 continue;

 }

 else

 {

 output_high(led1);

 output_high(led2);

 output_high(led3); 

 }

 }

 while(1)

 {

 output_low(led3);

 delay_ms(100);

 output_high(led3);

 delay_ms(100);

 }

}
