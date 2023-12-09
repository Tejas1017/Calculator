#include <LPC21xx.H>
#include "header.h"
#include <string.h>
void evaluateExpression(int *ptr,int len){
	int i=0;
	int found;
	int j;
	while (1) {
         found = 0;
        for (i = 1; i < len; i = i + 2) {
            if (ptr[i] == '*') {
                ptr[i - 1] = ptr[i - 1] * ptr[i + 1];
                for ( j = i; j < len - 2; j++) {
                    ptr[j] = ptr[j + 2];
                }
                len -= 2;
                found = 1;
                break;
            } else if (ptr[i] == '/') {
                if (ptr[i + 1] != 0) {
                    ptr[i - 1] = ptr[i - 1] / ptr[i + 1];
                } else {
                    uarto_tx_string("\r\nFloating point expection");
                    return;
                }
                
                for ( j = i; j < len - 2; j++) {
                    ptr[j] = ptr[j + 2];
                }
                len -= 2;
                found = 1;
                break;
            }
        }

        if (!found) {
            break;
        }
    }

			for (i = 1; i < len; i = i + 2) {
        if (ptr[i] == '+') {
            ptr[i - 1] = ptr[i - 1] + ptr[i + 1];
           
            for ( j = i; j < len - 2; j++) {
                ptr[j] = ptr[j + 2];
            }
            len -= 2;
            i -= 2;
        } else if (ptr[i] == '-') {
            ptr[i - 1] = ptr[i - 1] - ptr[i + 1];
        
            for ( j = i; j < len - 2; j++) {
                ptr[j] = ptr[j + 2];
            }
            len -= 2;
            i -= 2; 
        }
    }
			
		uart0_tx_int(ptr[0]);
	
		
}
void charArrayIntoIntArray(char *chr) {
    int l = strlen(chr);
    int IntArray[100];
    int num = 0;
    int intCount = 0; // Count of integers in IntArray
		int i;
	
		i=0;
	if(chr[0]=='-'){
		i=1;
		
	}
    for ( ; i < l; i++) {
        if (chr[i] == '+' || chr[i] == '-' || chr[i] == '*' || chr[i] == '/' || chr[i] == '\0') {
            
                IntArray[intCount++] = num;
                num = 0;
            
            IntArray[intCount++] = chr[i];
        } else {
            num = num * 10 + chr[i] - '0';
        }
    }

    // If there's a trailing number
    if (num != 0) {
        IntArray[intCount++] = num;
    }
	if(chr[0]=='-')
	IntArray[0]=-IntArray[0];
		uarto_tx_string("\r\n");
		evaluateExpression(IntArray,intCount);
		//uart0_tx(IntArray[0]/10+48);
		//uart0_tx(IntArray[0]%10+48);
		
}
	
int main() {
    char receiverString[100];
    uart0_init(9600);

    while (1) {
        uart0_rx_string(receiverString, 99);
        charArrayIntoIntArray(receiverString);
				uarto_tx_string("\r\n");
    }
}
