// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: lcd.c
//            Biblioteca de manipulação do LCD
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------


#include "lcd.h"
#include <pic18f4520.h>
#include "bits.h"
#include "io.h"
#include "atraso.h"

#define L0 0x80
#define L1 0xC0
#define L2 0x90
#define L3 0xD0

#define EN PIN_E1
#define RS PIN_E2



void lcd_wr(unsigned char val) {
    LPORT = val;
}

void lcd_cmd(unsigned char val) {
    LENA = 1;
    lcd_wr(val);
    LDAT = 0;
    atraso_ms(3);
    LENA = 0;
    atraso_ms(3);
    LENA = 1;
}

void lcd_dat(unsigned char val) {
    LENA = 1;
    lcd_wr(val);
    LDAT = 1;
    atraso_ms(3);
    LENA = 0;
    atraso_ms(3);
    LENA = 1;
}

void lcd_init(void) {
    LENA = 0;
    LDAT = 0;
    atraso_ms(20);
    LENA = 1;

    lcd_cmd(L_CFG);
    atraso_ms(5);
    lcd_cmd(L_CFG);
    atraso_ms(1);
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_OFF);
    lcd_cmd(L_ON); //liga
    lcd_cmd(L_CLR); //limpa
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L1);
}

void Delay40us(void)
{
	unsigned char i;
	for(i=0; i < 25; i++); //valor aproximado
}

void Delay2ms(void)
{
	unsigned char i;
	for(i=0; i < 50; i++)
	{
		Delay40us();
	}
}



void lcdCommand(unsigned char cmd)
{
    unsigned char old_D;
    old_D = PORTD;
    
    //garantir compatibilidade
    TRISD = 0x00;
    
	digitalWrite(RS, LOW);	//comando
	PORTD = cmd;

    digitalWrite(EN, HIGH);   //Pulso no Enable
	digitalWrite(EN, LOW);

    
    PORTD= old_D;
    
    if((cmd == 0x02)||(cmd == 0x01)){
       Delay2ms();   
    }else{
	   Delay40us();
    }
    
    
}

void lcdData(unsigned char valor)
{
    //garantir compatibilidade
    unsigned char old_D;
    old_D = PORTD;
    
    TRISD = 0x00;
	digitalWrite(RS, HIGH);	//comando

	PORTD = valor;
	
    digitalWrite(EN, HIGH);   //Pulso no Enable
	digitalWrite(EN, LOW);
    
    PORTD= old_D;
    
	Delay40us();
    
}
 

void lcdInit(void){
	// configurações de direção dos terminais
    pinMode(RS, OUTPUT);
    pinMode(EN, OUTPUT);
	TRISD = 0x00;		//dados

    // garante inicialização do LCD (+-10ms)
	Delay2ms(); Delay2ms();	Delay2ms();	Delay2ms();	Delay2ms();
    //precisa enviar 4x pra garantir 8 bits
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    Delay2ms();	Delay2ms();
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    Delay2ms();
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    lcdCommand(0x06);	//modo incremental
    
    //habilitar o cursor, trocar 0x0C por 0x0F;
    lcdCommand(0x0C);	//display e cursor on, com blink
    lcdCommand(0x01);	//limpar display
}
void lcdPosition(unsigned char linha, unsigned char coluna){
    char comando = 0;
    
    if(linha == 0) comando = L0 + coluna;
    if(linha == 1) comando = L1 + coluna;
    if(linha == 2) comando = L2 + coluna;
    if(linha == 3) comando = L3 + coluna;
    
    lcdCommand(comando);
}