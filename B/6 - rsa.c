#include "stdio.h"
#include "math.h"

char alpha[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//Encrypt with (M^E) Mod N
long long encrypt(int m,int e,int n){
   long long tmp = pow(m,e);
   return tmp % n; 
}

//Decrypt with (C^D) Mod N
long long decrypt(int c,int d,int n){
   long long tmp = pow(c,d);
   return tmp % n; 
}

int find(char C){
    int i;
    for(i = 0; i < 26; i++){
        if(C == alpha[i]){
            return i;
        }
    }
}

int main(){
    int n = 33;
    int e = 3, d = 7;
    int i;
    long long int code[100];
    //Public key is (n,e)
    //Private key is (n,d)

    char msg[100];
    printf("Enter uppercase text: ");
    scanf("%s", msg);

    printf("Message is: ");
    for(i = 0; msg[i] != '\0'; i++){
        printf("%d ", find(msg[i]));
    }
    printf("\n");

    printf("Codeword is: ");
    for(i = 0; msg[i] != '\0'; i++){
        code[i] = encrypt(find(msg[i]), e, n);
        printf("%llu ",  code[i]);
    }
    printf("\n");

    printf("Decrypted word is: ");
    for(i = 0; msg[i] != '\0'; i++){
        //printf("%d ", d);
        printf("%c ", alpha[decrypt(code[i], d, n)]);
    }
    printf("\n");
}