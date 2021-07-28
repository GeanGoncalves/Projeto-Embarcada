# 1 "main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main.c" 2







# 1 "./config.h" 1
# 38 "./config.h"
#pragma config MCLRE=ON
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config DEBUG = OFF
#pragma config WDTPS = 1
# 8 "main.c" 2

# 1 "./pic18f4520.h" 1
# 9 "main.c" 2

# 1 "./lcd.h" 1
# 32 "./lcd.h"
    void lcd_init(void);
    void lcd_cmd(unsigned char val);
    void lcd_dat(unsigned char val);
 void lcdCommand(unsigned char cmd);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdPosition(unsigned char linha, unsigned char coluna);
# 10 "main.c" 2

# 1 "./keypad.h" 1
# 23 "./keypad.h"
 unsigned int kpRead(void);
 void kpDebounce(void);
 void kpInit(void);
# 11 "main.c" 2

# 1 "./delay.h" 1



void tempo(unsigned char);
# 12 "main.c" 2

# 1 "./pwm.h" 1
# 23 "./pwm.h"
 void pwmSet1(unsigned char porcento);
 void pwmSet2(unsigned char porcento);
 void pwmFrequency(unsigned int freq);
 void pwmInit(void);
# 13 "main.c" 2

# 1 "./atraso.h" 1
# 26 "./atraso.h"
void atraso_ms(unsigned int valor);
# 14 "main.c" 2

# 1 "./bits.h" 1
# 15 "main.c" 2


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
    lcd_cmd(0x01);

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

    (*(volatile __near unsigned char*)0xF95) = 0X00;
    (*(volatile __near unsigned char*)0xF83) = 0X00;

    inicio();
    kpInit();
    impressao();
    for (;;) {

        kpDebounce();

        if (kpRead() != tecla) {
            tecla = kpRead();

            if (((tecla) & (1<<3))) {
                contipo = 10;
            }
            if (((tecla) & (1<<7))) {
                contipo = 7.5;
            }
            if (((tecla) & (1<<11))) {
                contipo = 8;
            }
            if (((tecla) & (1<<2))) {
                contipo = 9;
            }
        }

        if (contipo != 0) {

            kpInit();
            impressaoponto();
            for (;;) {
            kpDebounce();
            if (kpRead() != teclay) {
                teclay = kpRead();

                if (((teclay) & (1<<1))) {
                    contponto = 2;
                }
                if (((teclay) & (1<<5))) {
                    contponto = 3;
                }
                if (((teclay) & (1<<9))) {
                    contponto = 4;
                }
            }

        if (contponto != 0) {
        cont = (contipo * contponto) * 6000;
        lcdInit();

        (*(volatile __near unsigned char*)0xF95) = 0X00;
        (*(volatile __near unsigned char*)0xF83) = 0X00;
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


           pwmInit();
           pwmSet1(96);
        }

            (*(volatile __near unsigned char*)0xF95) = 0b00000000;
            posicao = 0b00000000;
            for (i = 0; i < 9; i++) {
            (*(volatile __near unsigned char*)0xF83) = posicao;
            tempo(3);
            aux = posicao + 1;
            posicao = posicao + aux;
        }

        if(cont==0){
        pwmSet1(0);
        lcdInit();

        pwmFrequency(10000);

        for (k = 0; k < 3; k++) {
            for (j = 1; j > 0; j = j * 2) {
                (((*(volatile __near unsigned char*)0xF94)) |= (1<<(1)));
                (*(volatile __near unsigned char*)0xF81) = j;
                (*(volatile __near unsigned char*)0xF83) = j;
                atraso_ms(15);
            }
            (((*(volatile __near unsigned char*)0xF94)) &= ~(1<<(1)));
        }

        (*(volatile __near unsigned char*)0xF81) = 0;
        (*(volatile __near unsigned char*)0xF83) = 0;



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
        (*(volatile __near unsigned char*)0xF83) = 0xFF;
        }
        }
        }
        }
        }
        }
        }
    }
