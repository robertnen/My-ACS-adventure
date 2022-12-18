#include <stdio.h>
#include <string.h>

void swapC(char* a, char* b, int iPos, int fPos); //swap de substringuri
 //returneaza daca I sau al II-lea nr este mai mare (0 daca a = b)
int compareNumbers(char* a, char* b, int size);
void readString(char *p, int size); //citeste un string
void sum(char* a, char* b, int size); //suma a doua numere
void dif(char* a, char* b, int size); //diferenta a doua numere
void output(char* a, char* b, int size); //afiseaza rezultatul

int main() {

    int size; // n
    char number[1001], number_2[1001];
    char operator = 'L';  //e initializat ca o sa verific mereu daca e 0

    scanf("%d\n", &size);
    readString(number, size);
    scanf(" %c", &operator); //citesc prima operatie

    while(operator != '0') { //cat timp trebuie sa adun/scad, operatorul nu e 0

        getchar(); //golesc bufferul

        readString(number_2, size);

        if(operator == '+') sum(number, number_2, size);
        else dif(number, number_2, size);

        output(number, number_2, size);
        scanf(" %c", &operator);
    }
    return 0;
}

void swapC(char* a, char* b, int iPos, int fPos) { //swap de substringuri

    int i;

    for(i = iPos; i <= fPos; i++) {char aux = a[i]; a[i] = b[i]; b[i] = aux;}
}

//returneaza daca I sau al II-lea nr este mai mare (0 daca a = b)
int compareNumbers(char* a, char* b, int size) {

    int i = 0;

    while(i < size)
        if(a[i] > b[i]) {return 1; break;} // a > b
        else if(a[i] < b[i]) {return 2; break;} // a < b
             else i++;

    return 0; // a = b

}

void readString(char *p, int size) {

    fgets(p, size, stdin);
    p[size] = '\0';

}

//suma a doua numere
void sum(char* a, char* b, int size) {

    //notez cu P() partea reala sau imaginara a unui numar dupa caz

    int sign, length = (size - 1) / 2, step, i;

    // step = 0 atunci P(z) = Re(z), altfel P(z) = Im(z)
    for(step = 0; step < size - 1; step += length) { 
        if(a[step] == b[step]) { // P(a) * P(b) > 0

            sign = a[step]; //semnul va fi mereu sgn(P(a))

            for(i = length - 1 + step; i > step; i--) {
                if(a[i] + b[i] - 2 * '0' > 9) a[i - 1]++;

                a[i] = (a[i] + b[i] - 2 * '0') % 10 + '0';
            }
            a[step] = sign;

        } else { //P(a) * P(b) < 0

            //vad care din P(a) si P(b) e mai mare
            int whichIsBigger = compareNumbers(a + step + 1, b + step + 1, length - 1);

            if(!whichIsBigger) for(i = step; i < length + step; i++)
                a[i] = '0'; //|P(a + b)| = 0
            else {
                if(whichIsBigger == 1) sign = a[step]; //|P(a)| > |P(b)|
                else {

                    sign = b[step]; //|P(a)| < |P(b)|
                    swapC(a, b, step + 1, length - 1 + step);
                }

                for(i = length - 1 + step; i > step; i--)
                    if(a[i] - b[i] < 0) {

                        int j = i - 1;

                        //cat timp cifrele din stanga sus sunt 0, ele devin 9
                        while(a[j] == '0' && j > step) a[j--] = '9';

                        a[j]--; //am gasit o cifra care nu e 0 si scad 1
                        a[i] = 10 + a[i] - b[i] + '0';

                    } else a[i] = a[i] - b[i] + '0';

                a[step] = sign;
            }
        }
    }
}

//diferenta a doua numere (analog ca sum doar ca se schimba == cu != in if)
void dif(char* a, char* b, int size) {

    //notez cu P() partea reala sau imaginara a unui numar dupa caz

    int sign, length = (size - 1) / 2, step, i;

    // step = 0 atunci P(z) = Re(z), altfel P(z) = Im(z)
    for(step = 0; step < size - 1; step += length) {
        if(a[step] != b[step]) { // //P(a) * P(b) < 0

            sign = a[step]; //semnul va fi mereu sgn(P(a))

            for(i = length - 1 + step; i > step; i--) {

                if(a[i] + b[i] - 2 * '0' > 9) a[i - 1]++;

                a[i] = (a[i] + b[i] - 2 * '0') % 10 + '0';

            }

            a[step] = sign;

        } else { //P(a) * P(b) > 0

            //vad care din P(a) si P(b) e mai mare
            int whichIsBigger = compareNumbers(a + step + 1, b + step + 1, length - 1);

            if(!whichIsBigger)
                for(i = step; i < length + step; i++) a[i] = '0'; //|P(a + b)| = 0
            else {

                if(whichIsBigger == 1) sign = a[step];
                else {

                    //sgn(P(a + b)) = -sgn(P(b)),
                    //deci pun opusul semnului lui P(b)
                    sign = (!(b[step] - '0')) + '0';

                    swapC(a, b, step + 1, length - 1 + step);
                }

                for(i = length - 1 + step; i > step; i--) {
                    if(a[i] - b[i] < 0) {

                        int j = i - 1;

                        //cat timp cifrele din stanga sus sunt 0, ele devin 9
                        while(a[j] == '0' && j > 0) a[j--] = '9';

                        a[j]--; //am gasit o cifra care nu e 0 si scad 1
                        a[i] = 10 + a[i] - b[i] + '0';

                    } else a[i] = a[i] - b[i] + '0';
                }
                a[step] = sign; 
            }
        }
    }
}

void output(char* a, char* b, int size) {

    printf("%s\n", a);
}