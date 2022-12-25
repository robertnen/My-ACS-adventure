#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void binaryConvertor(unsigned int number, char converted[]);
unsigned int decimalConvertor(char binary[]);
unsigned int sum(unsigned int num_1, unsigned int num_2);
unsigned int xor(unsigned int num_1, unsigned int num_2);
unsigned int swapBit(unsigned int num_1, unsigned int num_2);
unsigned int leftRotation(unsigned int num_1, unsigned int num_2);
void copyString(char destination[], char source[], int n);

int main() {

    int n, pos;
    unsigned int number, result;
    char binary[32], num[5], op[3];

    unsigned int (*operation[4])(unsigned int, unsigned int) = {sum, swapBit, leftRotation, xor};

    scanf("%d%d", &n, &number);

    binaryConvertor(number, binary);
    strcpy(binary, binary + 28 - n * 6);

    copyString(num, binary, 4);
    num[4] = '\0';

    result = decimalConvertor(num); //primul numar
    pos = 4;

    for(int i = 0; i < n; i++) { // am n operatii

        copyString(op, binary + pos, 2);
        op[2] = '\0';

        pos += 2;

        copyString(num, binary + pos, 4);
        num[4] = '\0';

        pos += 4;

        result = (*operation[decimalConvertor(op)])(result, decimalConvertor(num));
    }

    printf("%d", result);

    return 0;
}

void binaryConvertor(unsigned int number, char converted[]) {

    int index, n;

    for(index = 0; index < 32; index++) converted[index] = '0';

    index = 0;

    while(number > 0) {

        converted[index++] = number % 2 + '0';
        number /= 2;
    }

    converted[32] = '\0';

    n = strlen(converted);

    for(index = 0; index <= 15; index++) {

        //swap
        converted[index] ^= converted[n - 1 - index];
        converted[n - 1 - index] ^= converted[index];
        converted[index] ^= converted[n - 1 - index];
    }
}

unsigned int decimalConvertor(char binary[]) {

    unsigned int number = 0;
    int length = strlen(binary), i;

    for(i = 0; i < length; i++)
        if(binary[i] == '1')
            number += (1 << (length - 1 - i));

    return number;
}

unsigned int sum(unsigned int num_1, unsigned int num_2) {

    unsigned int transport = 1, directSum;

    while(transport) { //cat timp nu adun 2 biti de 1

        transport = (num_1 & num_2);
        directSum = (num_1 ^ num_2);

        num_1 = (transport << 1);
        num_2 = directSum;
    }

    return num_2 % 16; // 1000 + 1001 = 0001
}

unsigned int xor(unsigned int num_1, unsigned int num_2) {

    unsigned int result, addition;

    result = (num_1 | num_2); //suma maxima posibila
    addition = (num_1 & num_2); //ce trebuie sa dispara

    //printf("result = %d addition = %d\n",  result, addition);

    if((addition & 8)) //vad daca bitul de pe poz 3 e in plus
        result &= 7; // 7 = 0111

    if((addition & 4))
        result &= 11; // 11 = 1011

    if((addition & 2))
        result &= 13; // 13 = 1101

    if((addition & 1))
        result &= 14; // 14 = 1110

    return result;
}

unsigned int swapBit(unsigned int num_1, unsigned int num_2) {

    unsigned int p_1, p_2, aux, bit_1, bit_2;

    aux = 15; // 1111
    p_2 = (num_2 & 3); //vreau doar ultimii 2 biti
    p_1 = (num_2 >> 2); // primii 2 biti

    bit_1 = num_1 & (1 << (3 - p_1));
    bit_2 = num_1 & (1 << (3 - p_2));

    aux = aux ^ (1 << (3 - p_1));
    aux = aux ^ (1 << (3 - p_2));

    num_1 = num_1 & aux; //pastrez momentan ce nu se schimba

    if(bit_1 > 0) bit_1 = 1;
    if(bit_2 > 0) bit_2 = 1;

    num_1 = num_1 | (bit_1 << (3 - p_2));
    num_1 = num_1 | (bit_2 << (3 - p_1));

    return num_1;
}

unsigned int leftRotation(unsigned int num_1, unsigned int num_2) {

    unsigned int aux = 0;

    num_2 = num_2 % 4; //4 e perioada pentru rotatie

    aux = num_1 & ((1 << (4 - num_2)) - 1);
    num_1 >>= (4 - num_2);

    aux <<= num_2;
    aux += num_1;

    return aux;
}

void copyString(char destination[], char source[], int n) {

   for(int i = 0; i < n; i++)
        destination[i] = source[i];

}