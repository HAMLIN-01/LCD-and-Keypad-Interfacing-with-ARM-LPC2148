#include <lpc214x.h>
#define LCD_DATA_MASK (0xFF<<16)  
#define lcd_clear_data() (IO0CLR=LCD_DATA_MASK)
#define lcd_set_data(val) (IO0SET=((val) & 0xFF) << 16)
#define RS (1<<8)
#define RW (1<<9)
#define EN (1<<10)
#define R1 (1<<16)
#define R2 (1<<17)
#define R3 (1<<18)
#define R4 (1<<19)
#define C1 (1<<20)
#define C2 (1<<21)
#define C3 (1<<22)
#define C4 (1<<23)
void lcd_init(void);
void cmd(unsigned char);
void dat(unsigned char);
void lcd_string(const char *);
void delay(unsigned int);
void keypad(void);
int main() {
    lcd_init();
    while(1) {
        cmd(0x80);
        lcd_string("Enter the key:");
        cmd(0xC7);
        keypad();
    }
}
void keypad() {
    IO1DIR|=(R1|R2|R3|R4);
    IO1DIR&=~(C1|C2|C3|C4);
    IO1SET|=(C1|C2|C3|C4);
    IO1CLR=R1;
    IO1SET=R2|R3|R4;
    if(!(IO1PIN&C1)){
        while(!(IO1PIN&C1));
        dat('7');
    }else if(!(IO1PIN&C2)){
        while(!(IO1PIN&C2));
        dat('8');
    }else if(!(IO1PIN&C3)){
        while(!(IO1PIN&C3));
        dat('9');
    }else if(!(IO1PIN&C4)){
        while(!(IO1PIN&C4));
        dat('/');
    }
    IO1CLR=R2;
    IO1SET=R1|R3|R4;
    if(!(IO1PIN&C1)){
        while(!(IO1PIN&C1));
        dat('4');
    }else if(!(IO1PIN&C2)){
        while(!(IO1PIN&C2));
        dat('5');
    }else if(!(IO1PIN&C3)){
        while(!(IO1PIN&C3));
        dat('6');
    }else if(!(IO1PIN&C4)){
        while(!(IO1PIN&C4));
        dat('B');
    }
    IO1CLR=R3;
    IO1SET=R1|R2|R4;
    if(!(IO1PIN&C1)){
        while(!(IO1PIN&C1));
        dat('1');
    }else if(!(IO1PIN&C2)){
        while(!(IO1PIN&C2));
        dat('2');
    }else if(!(IO1PIN&C3)){
        while(!(IO1PIN&C3));
        dat('3');
    }else if(!(IO1PIN&C4)){
        while(!(IO1PIN&C4));
        dat('C');
    }
    IO1CLR=R4;
    IO1SET=R1|R2|R3;
    if(!(IO1PIN&C1)){
        while(!(IO1PIN&C1));
        dat('*');
    }else if(!(IO1PIN&C2)){
        while(!(IO1PIN&C2));
        dat('0');
    }else if(!(IO1PIN&C3)){
        while(!(IO1PIN&C3));
        dat('#');
    }else if(!(IO1PIN&C4)){
        while(!(IO1PIN&C4));
        dat('D');
    }
}
void lcd_init(void) {
    IO0DIR|=(LCD_DATA_MASK | RS | RW | EN);
    cmd(0x38);  
    cmd(0x0E);  
    cmd(0x06);  
    cmd(0x01);  
}
void cmd(unsigned char command) {
    lcd_clear_data();
    lcd_set_data(command);
    IO0CLR=RS;    
    IO0CLR=RW;   
    IO0SET=EN;
    delay(200);
    IO0CLR=EN;
}
void dat(unsigned char data) {
    lcd_clear_data();
    lcd_set_data(data);
    IO0SET=RS;    
    IO0CLR=RW;    
    IO0SET=EN;
    delay(200);
    IO0CLR=EN;
}
void lcd_string(const char *s) {
    while (*s) {
        dat(*s++);
    }
}
void delay(unsigned int z) {
    unsigned int i, j;  
    for (i=0; i<z; i++) {
        for (j=0; j<100; j++);  
    }
}
