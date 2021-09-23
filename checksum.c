/*
    Written by Floodnut, 23.09.2021
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int bufSize = 1024;

int *int2bin(int target){
    int tmp = target;
    static int retArr[8]={0,};

    for(int i = (8/*len*/)-1 ; i >= 0 ; i--){
        retArr[i] = (tmp % 2);
        tmp = tmp / 2;
        if(tmp == 1){
            retArr[i-1] = tmp;
            break;
        }
    } 
    return (int*) retArr;
}

int *evenParity(char *chr,size_t len){
    int i = 0, asc = 0, character, temp;

    static int retArr[2048] = {0,};
	for(int j = 0 ; j < len ; j++){
        character = chr[j] <<1;
        temp = chr[j];
		for(i = 0 ; temp !=0 ; i++) {
			temp &= (temp-1);
		}
		if((i % 2)){
			character |= 1 ; 
		}
        memcpy(retArr+(j*8),int2bin(character),sizeof(int) * 8);
	}
	return (int*)retArr;
}

void checksum(int *message, int length){
    int messageString[2048] = {0,};

    int addition[16] = {0, };
    int carry = 0 ;
    int carryLast = 0 ;

    memcpy(messageString, message, sizeof(int) * 2048);

    
    for(int k = 0 ; k < (length/2) ; k++){
        for(int j = 0 ; j < 16 ; j++){
            addition[j] += messageString[(k*16) + j];
        }
    }
    
    if( (length%2) ){
        for(int j = 0 ; j < 8 ; j++){
            addition[j] += messageString[((length/2)*16) + j];
        }
    }

    do{
        for(int j = 15 ; j >= 0 ; j--){
            addition[j] += carry;
            carry = addition[j]/2;
            addition[j] %= 2;
        }
        carryLast = carry;
    }while(carryLast != 0 );


    for(int i = 0; i < 16; i++){
        if(addition[i])
            printf("0");
        else
            printf("1");
   }
    puts("");
}

int main(){
	char string[2049];
	scanf("%s",string);
    checksum(evenParity(string,strlen(string)),(int)strlen(string));
}