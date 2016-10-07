#include<xc.h>
#include<p18f4585.h>
#include <delays.h>

#pragma config OSC = IRCIO67    // Internal Oscillator
#pragma config WDT = OFF        //Watchdog Off
#pragma config MCLRE = ON       //Master Reset Enabled
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#define _XTAL_FREQ 4000000

void shortdelay(void);
void longdelay (void);
void command(int instruction);
void ready(void);
void display(int dato);

void main(void){
    OSCCON=0x60;
    ADCON1=0x0F;
    CVRCONbits.CVREN=0;
    CMCON=0x07;
///PORTA--> D0->D7
    PORTB=0x00;
    LATB=0x00;
    TRISB=0x00;
//RC0-->RS
//RC1-->RW
//RC2-->E
    PORTE=0x00;
    LATE=0x00;
    TRISE=0x00;
    PORTEbits.RE0=0;
    longdelay();
    command(0x38);
    longdelay();
    command(0x0F);
    ready();
    command(0x01);
    ready();
    command(0x82);
    display(0x41);
    command(0x84);
    display(0x43);
}
void display(int dato){
    PORTB=dato;
    PORTEbits.RE0=1;
    PORTEbits.RE1=0;
    PORTEbits.RE2=1;
    shortdelay();
    PORTEbits.RE2=0;
}
void ready(void){
    TRISB=0xFF;
    PORTEbits.RE0=0;
    PORTEbits.RE1=1;
  loop:  PORTEbits.RE2=1;
    shortdelay();
    PORTEbits.RE2=0;
    if(PORTBbits.RB7==1){
    goto loop; }
    TRISB=0x00;
}
void longdelay(void) {
     __delay_ms(125);
     __delay_ms(125);
}

void shortdelay(){
    __delay_ms(1);
}

void command(int instruction ){
    PORTB=instruction;
    PORTEbits.RE0=0;
    PORTEbits.RE1=0;
    PORTEbits.RE2=1;
    shortdelay();
    PORTEbits.RE2=0;
}
