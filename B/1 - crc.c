#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define sender   "1000100010001000"
#define reciever "1000100010001000"

void xor(char* input, int len_input, char* poly, int len_poly, char* result){
    int i = 0;
    strcpy(result, input);
    while(i < len_input - len_poly - 1) {
        if(result[i] == '1'){
            int j;
            for(j=0; j<len_poly; j++){
                if(result[i+j] != poly[j]){
                    result[i+j] = '1';
                } else {
                    result[i+j] = '0';
                }
             }
        }
        i++;
    }
}

int main() {
    char poly[17] ="1000100000100001";
    char input[18 + sizeof(poly) - 2] = sender;
    char result[sizeof(input)], crc[sizeof(poly)];

    //Append n-1 zeros to the end of the input.
    int i, j;
    for(i=0; i<sizeof(poly) - 2; i++){
        strcat(input, "0");
    }

    //Divide
    xor(input, sizeof(input) - 1, poly, sizeof(poly) - 1, result);
    

    //Get CRC, and append it to the input
    for(i=sizeof(input) - sizeof(poly) , j = 0; i<sizeof(input) - 1; i++, j++){
        input[i] = result[i];
        crc[j] = result[i];
    }
    crc[j+1] = '\0';

    char r_input[18 + sizeof(poly) - 2] = reciever;
    strcat(r_input, crc);

    xor(r_input, sizeof(r_input) - 1, poly, sizeof(poly) - 1, result);

    int flag = 0;
    for(i=0; i<sizeof(result); i++){
        if(flag == 1 && result[i] == '1'){
            printf("Error in transmission!\n");
            return 1;
        }
        if(result[i] == '1') {
            flag = 1;            
        }
    }

    printf("No error in transmission.\n");
    return 0;

}