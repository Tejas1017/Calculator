#include <LPC21xx.H>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(unsigned int band){
	int a[]={15,60,30,15,15};
	unsigned int PCLK =a[VPBDIV]*1000000;
	unsigned int result=0;
	result=PCLK/(16*band);
	PINSEL0 |=0X05;
	U0LCR=0X85;
	U0DLL=result& 0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=0X03;
}	

void uart0_tx(unsigned char data){
	U0THR=data;
	while(THRE==0);
}
unsigned char uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}
void uarto_tx_string(char *ptr){
 	while(*ptr){
		uart0_tx(*ptr);
		ptr++;
	}
}
void uart0_rx_string(char *ptr,unsigned int max_bytes){
	unsigned int i;
	for(i=0;i<max_bytes;i++){
		while(RDR==0);
		ptr[i]=U0RBR;
		uart0_tx(ptr[i]);
		if(ptr[i]=='\r')
			break;

	}
	ptr[i]='\0';
}
#include <stdio.h>
void uart0_tx_int(int num){
	char buff[10];
	sprintf(buff,"%d",num);
	uarto_tx_string(buff);
}
