void delay_sec(unsigned int sec);
void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void uart0_init(unsigned int band);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
unsigned uarto_tx_string(char *ptr);
unsigned char uart0_rx(void);
void uart0_rx_string(char *ptr,unsigned int max_bytes);
void uart0_tx_int(int);

