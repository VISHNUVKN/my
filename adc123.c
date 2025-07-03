#include<reg52.h>
sbit rd=P1^0;
sbit wr=P1^1;
sbit intr=P1^2;
sbit cs=P1^3;

sbit rs=P3^4;
sbit rw=P3^5;
sbit en=P3^6;

void delay(int c);
void init(void);
void cmd(char ch);
void dat(char cha);
void adc_conv();

void main(){
	int i,k=0;
	unsigned char adc_dat;
	unsigned int adc_val;
	char dig[]={'0','.','0','0','0','0','v'};
	char new_dig[]={'0','.','0','0','0','0','v'};
	init();
	while(1){
		adc_conv();
		adc_dat=P2;
		adc_val=adc_dat*196;
		for(i=5;i>=0;i--){
			if(i==1)
				continue;
			new_dig[i]=(adc_val%10)+0X30;
			adc_val/=10;
		}
		for(i=0;i<7;i++){
			if(new_dig[i]!=dig[i]){
				k++;
				break;
			}
		}
		if(k){
			cmd(0x01);
			for(i=0;i<7;i++){
				dat(new_dig[i]);
				dig[i]=new_dig[i];
			}
		}
		k=0;
	}
}
void delay(int c){
	int i;
	for(i=0;i<c;i++);
}
void init(){
	cmd(0x38);
	cmd(0x0C);
	cmd(0x01);
	cmd(0x80);
}
void cmd(char ch){
	P0=ch;
	rs=0;
	rw=0;
	en=1;
	delay(100);
	en=0;
	delay(100);
}
void dat(char cha){
	P0=cha;
	rs=1;
	rw=0;
	en=1;
	delay(100);
	en=0;
	delay(100);
}
void adc_conv(){
	cs=0;
	wr=0;
	delay(100);
	wr=1;
	rd=1;
	while(intr);
	rd=0;
}


	
	