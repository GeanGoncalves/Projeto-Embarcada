/* 
Nome: Gean Carlos Gonçalves Martins
Matrícula: 2020021262

Projeto final de Programação Embarcada (ECOP04), com o professor Otavio de Souza. 
Grill Elétrico*/ 

#include "config.h"
#include "pic18f4520.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "pwm.h"
#include "atraso.h"
#include "bits.h"

void inicio(void) {
    lcdInit();
    lcdPosition(1, 5);
    lcdData('G');
    lcdData('r');
    lcdData('i');
    lcdData('l');
    lcdData('l');
    
    lcdPosition(2, 4);
    lcdData('E');
    lcdData('l');
    lcdData('e');
    lcdData('t');
    lcdData('r');
    lcdData('i');
    lcdData('c');
    lcdData('o');
    atraso_ms(3500);
    lcd_cmd(L_CLR);
 
}

void impressao(void) {
    lcdInit();
    lcdPosition(0, 0);
    {
        lcdData('1');
        lcdData('-');
        lcdData('C');
        lcdData('a');
        lcdData('r');
        lcdData('n');
        lcdData('e');
        lcdData(' ');
        lcdData('d');
        lcdData('e');
        lcdData(' ');
        lcdData('P');
        lcdData('o');
        lcdData('r');
        lcdData('c');
        lcdData('o');
    }

    lcdPosition(1, 0);
    {
        lcdData('2');
        lcdData('-');
        lcdData('C');
        lcdData('a');
        lcdData('r');
        lcdData('n');
        lcdData('e');
        lcdData(' ');
        lcdData('d');
        lcdData('e');
        lcdData(' ');
        lcdData('B');
        lcdData('o');
        lcdData('i');
    }

    lcdPosition(2, 0);
    {
        lcdData('3');
        lcdData('-');
        lcdData('L');
        lcdData('i');
        lcdData('n');
        lcdData('g');
        lcdData('u');
        lcdData('i');
        lcdData('c');
        lcdData('a');
    }

    lcdPosition(3, 0);
    {
        lcdData('4');
        lcdData('-');
        lcdData('F');
        lcdData('r');
        lcdData('a');
        lcdData('n');
        lcdData('g');
        lcdData('o');

    }

}

void impressaoponto(void) {
    lcdInit();
    lcdPosition(0, 0);
    {
        lcdData('7');
        lcdData('-');
        lcdData('M');
        lcdData('a');
        lcdData('l');
        lcdData(' ');
        lcdData('p');
        lcdData('a');
        lcdData('s');
        lcdData('s');
        lcdData('a');
        lcdData('d');
        lcdData('a');
    }

    lcdPosition(1, 0);
    {
        lcdData('8');
        lcdData('-');
        lcdData('A');
        lcdData('o');
        lcdData(' ');
        lcdData('p');
        lcdData('o');
        lcdData('n');
        lcdData('t');
        lcdData('o');
    }
    lcdPosition(2, 0);
    {
        lcdData('9');
        lcdData('-');
        lcdData('B');
        lcdData('e');
        lcdData('m');
        lcdData(' ');
        lcdData('p');
        lcdData('a');
        lcdData('s');
        lcdData('s');
        lcdData('a');
        lcdData('d');
        lcdData('a');
    }
    
}

void main(void) {
    unsigned long int contipo = 0;
    unsigned long int contponto = 0;
    unsigned long int cont = 0; 
    unsigned int tecla = 16;
    unsigned int teclay = 16;
    unsigned char posicao, aux, i;
    unsigned char k, j;
        
    TRISD = 0X00; //Leds Desligados
    PORTD = 0X00; //Leds Desligados
    
    inicio();
    kpInit();
    impressao(); //IMPRESSAO DE QUAL CARNE
    for (;;) {
    
        kpDebounce();

        if (kpRead() != tecla) {
            tecla = kpRead();

            if (BitTst(tecla, 3)) { // carne porco (1)
                contipo = 10;
            }
            if (BitTst(tecla, 7)) { // carne boi (2)
                contipo = 7.5;
            }
            if (BitTst(tecla, 11)) { // linguiça (3) 
                contipo = 8;
            }
            if (BitTst(tecla, 2)) { //frango (4)
                contipo = 9;
            }
        }
        
        if (contipo != 0) { 
            
            kpInit();
            impressaoponto(); //IMPRESSÃO PONTO DA CARNE
            for (;;) {
            kpDebounce();
            if (kpRead() != teclay) {
                teclay = kpRead();

                if (BitTst(teclay, 1)) { // MAL PASSADA (7)
                    contponto = 2;
                }
                if (BitTst(teclay, 5)) { // AO PONTO (8)
                    contponto = 3;
                }
                if (BitTst(teclay, 9)) { // BEM PASSADA (9) 
                    contponto = 4;
                }
            }
        
        if (contponto != 0) {
        cont = (contipo * contponto) * 6000;
        lcdInit();
        
        TRISD = 0X00;
        PORTD = 0X00;
        for(;;){  
        lcdPosition(1, 3);
        lcdData('G');
        lcdData('R');
        lcdData('E');
        lcdData('L');
        lcdData('H');
        lcdData('A');
        lcdData('N');
        lcdData('D');
        lcdData('O');
    
        while (cont > 0){                  
            cont--;
            lcdPosition(2, 5);
         
            lcdData((cont / 60000) % 6 + 48);
            lcdData((cont / 6000) % 10 + 48);
            lcdData(':');
            lcdData((cont / 1000) % 6 + 48);
            lcdData((cont / 100) % 10 + 48);
            //ciclo de 10ms +-.
           
           pwmInit(); //Liga cooller
           pwmSet1(96); //Velocidade coller
        }
         
            TRISD = 0b00000000;
            posicao = 0b00000000;
            for (i = 0; i < 9; i++) {
            PORTD = posicao;          //Funçãozinha para os leds piscarem
            tempo(3);
            aux = posicao + 1;
            posicao = posicao + aux; 
        }
            
        if(cont==0){  //Quando a contagem parar...
        pwmSet1(0); //Parar Coller
        lcdInit();
        
        pwmFrequency(10000); //Buzzer ligado

        for (k = 0; k < 3; k++) {
            for (j = 1; j > 0; j = j * 2) {
                bitSet(TRISC, 1);
                PORTB = j;
                PORTD = j;
                atraso_ms(15); //Duração
            }
            bitClr(TRISC, 1);
        }

        PORTB = 0;
        PORTD = 0;
        
        
        
        for(;;){  
        lcdPosition(1, 4);
        {
        lcdData('P');
        lcdData('r');
        lcdData('o');
        lcdData('c');
        lcdData('e');
        lcdData('s');
        lcdData('s');
        lcdData('o');
        }
        
        lcdPosition(2, 3);
        {
        lcdData('F');
        lcdData('i');
        lcdData('n');
        lcdData('a');
        lcdData('l');
        lcdData('i');
        lcdData('z');
        lcdData('a');
        lcdData('d');
        lcdData('o');
        
        }
        PORTD = 0xFF; //Leds Ligado
        }
        }
        }
        }
        }
        }
        }
    }

