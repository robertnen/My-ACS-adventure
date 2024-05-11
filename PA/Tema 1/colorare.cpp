#include <bits/stdc++.h>

const long MOD = 1000000007;

long long fast_pow(long long base, int exponent) {
    long long ans = 1LL;

    while (exponent > 0) {
        if (exponent % 2) ans = (ans * base) % MOD;

        base = (base * base) % MOD;
        exponent /= 2;
    }

    return ans;
}

int main() {
    std::ifstream fin("colorare.in");
    std::ofstream fout("colorare.out");

    long long ans = 1;
    int k, x;
    char ch, bfh;  //? bfh = before (c)har

    fin >> k;

    //* iau prima pereche sa verific daca e orizontala
    fin >> x >> bfh;

    //* daca prima pereche e H pot avea 6 posibilitati, iar pentru V 3
    ans = bfh == 'H' ? fast_pow(3, x - 1) * 6
                     : fast_pow(2, x - 1) * 3;

    for (int i = 1; i < k; i++) {
        fin >> x >> ch;

        if (bfh == ch) {  //! 2 doua perechi "similare"
            if (bfh == 'H')  //* H -> H
                ans = (3 * ans) % MOD * fast_pow(3, x - 1) % MOD;
            else             //* V -> V
                ans = (2 * ans) % MOD * fast_pow(2, x - 1) % MOD;
        } else {  //! 2 perechi "opuse"
            if (bfh == 'H')  //* H -> V
                ans = ans % MOD * fast_pow(2, x - 1) % MOD;
            else             //* V -> H
                ans = (2 * ans) % MOD * fast_pow(3, x - 1) % MOD;
        }

        bfh = ch;
    }

    //* afisare
    fout << ans;

    //* eliberare memorie
    fin.close();
    fout.close();

    return 0;
}
