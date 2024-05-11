#include <bits/stdc++.h>

void read_input(int& size, std::vector<int>& arr,
                    std::ifstream& fin, int& sum);

int main() {
    std::ifstream fin("compresie.in");
    std::ofstream fout("compresie.out");

    int n, m, sumA, sumB, i, j, len = 0;
    std::vector<int> arrA, arrB;

    //* citire (calculez si sumele vectorilor)
    read_input(n, arrA, fin, sumA);
    read_input(m, arrB, fin, sumB);

    if (sumA != sumB) {  //? nu merge compresia
        fout << -1;

        //* eliberare memorie
        fin.close();
        fout.close();

        return 0;
    }

    sumA = sumB = 0;  //? le refolosesc
    i = j = 0;

    while (i < n && j < m) {
        if (sumA == sumB && sumA) {  //* se poate face o compresie
            sumA = sumB = 0;
            len++;
            continue;
        }

        //* momentan nu am egalat vectorii ca sume
        if (sumA > sumB) sumB += arrB[j++];
        else
            sumA += arrA[i++];
    }

    //? calculez si ultima suma ramasa
    while (i < n) sumA += arrA[i++];
    while (j < m) sumB += arrB[j++];

    if (sumA == sumB) len++;

    //* afisare
    fout << len;

    //* eliberare memorie
    fin.close();
    fout.close();

    return 0;
}

void read_input(int& size, std::vector<int>& arr,
                    std::ifstream& fin, int& sum) {
    int x;

    fin >> size;
    sum = 0;

    for (int i = 0; i < size; i++) {
        fin >> x;

        sum += x;
        arr.push_back(x);
    }
}
