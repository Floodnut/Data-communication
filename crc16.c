/*
    Written by Floodnut, 09.21.2021
    Error fixed 09.23.2021
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int bufSize = 1024;

char *int2bin(int target){
    int tmp = target;
    static char retArr[9]={0,};

    for(int i = (8/*len*/)-1 ; i >= 0 ; i--){
        retArr[i] = 48 + (tmp % 2);
        tmp = tmp / 2;
        if(tmp == 1){
            retArr[i-1] = 48 + tmp;
            break;
        }
    }
    return (char*) retArr;
}

char *evenParity(char *chr,size_t len){
    int i = 0, asc = 0, character, temp;

    static char retArr[2049] = {0,};
		for(int j = 0 ; j < len ; j++){

            character = chr[j] <<1;
            temp = chr[j];
			for(i = 0 ; temp !=0 ; i++) {
				temp &= (temp-1);
			}
			if((i % 2)){
				character |= 1 ; 
			}
            memcpy(retArr+(j*8),int2bin(character),9);
		}
	return (char*)retArr;
}

void CRC16(char *message, int length){

    char messageString[2049] = {0,};
    int genString[17] = {1, 1,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,0,1};

    memcpy(messageString,message,2049);

    int counter = 0;
    while(17 <= ((8*length)+16 - counter) && counter < (length*8)){
        if(messageString[0] == 49){
            memmove(messageString-1,messageString,2049);
            counter += 1;
            for(short j = 0; j < 16;j++){
                if(messageString[j] == 49){
                    messageString[j] = 48 + (1 ^ genString[j+1]);
                }
                else{
                    messageString[j] = 48 + (0 ^ genString[j+1]);
                }
            }
        }
        else{
            memmove(messageString-1,messageString,2049);
            counter += 1;
        } 
    }
    for(int i = 0; i < 16; i++){
        printf("%c",messageString[i]);
    }
    puts("");
}

int main(){
	char string[2049];
	scanf("%s",string);
    CRC16(evenParity(string,strlen(string)),(int)strlen(string));
}