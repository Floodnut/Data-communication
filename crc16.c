#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int evenParity(char chr[],size_t len){
    int i = 0, asc = 0,character, temp;

		for(int j = 0 ; j < len ; j++){
            if(j != 0)
                asc = (asc << 8);
            character = chr[j] <<1;
            temp = chr[j];
			for(i = 0 ; temp !=0 ; i++) {
				temp &= (temp-1);
			}
			if((i % 2)){
				character |= 1 ; 
			}
            asc |= character;
		}
	return asc;
}

void CRC16(int message, int length){
    int shiftedMessage = message << 16;
    int messageString[1025] = {0,};
    int genString[18] = {1, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,0,1};
    int tmp = message;

    int indexCnt = 0;
    for(int i = (8*length)-1 ; indexCnt < (length * 8) | i >= 0 ; i--){
        messageString[i] = tmp % 2;
        tmp = tmp / 2;
        indexCnt += 1;
        if(tmp == 1){
            messageString[i-1] = tmp;
            break;
        }
    }

    int counter = 0;
    while(17 <= ((8*length)+16 - counter) && counter < (length*8)){
        if(messageString[0] == 1){
            memmove(messageString-1,messageString,1024);
            counter += 1;
            for(short j = 0; j < 16;j++)
                messageString[j] ^= genString[j+1];
        }
        else{
            memmove(messageString-1,messageString,1024);
            counter += 1;
        } 
    }
    for(int i = 0; i < 16; i++){
        printf("%d",messageString[i]);
    }
    puts("");
}

int main(){
	char string[1024];
	scanf("%s",string);
    
    CRC16(evenParity(string,strlen(string)),(int)strlen(string));
}