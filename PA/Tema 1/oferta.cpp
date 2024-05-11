#include <bits/stdc++.h>

inline double duo(double a, double b);
inline double trio(double a, double b, double c);

int main() {
    std::ifstream fin("oferta.in");
    std::ofstream fout("oferta.out");

    const double MAX_PRICE = 2147483647;  //? limita superioara
    std::vector<double> prices;
    int n, k, price;
    bool flag;

    //* citire
    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> price;
        prices.push_back(price);
    }

    std::vector<std::vector<double>> dp(10001, std::vector<double>());
    double sums[3], minim, du, tri, last;
    int i1, i2, i3, s1, s2, s3;

    //? i1-3 reprezinta indecsii
    //? s1-3 reprezinta lungimile sumelor memorate

    //* afiseare pentru cazurile de baza
    //* si eliberare de memorie
    if (n == 1 && k <= n) {
        fout << std::fixed
             << std::setprecision(1)
             << prices[0];

        fin.close();
        fout.close();

        return 0;
    }

    if (n <= 2 && k > n) {
        fout << -1;

        fin.close();
        fout.close();

        return 0;
    }

    dp[0].push_back(0);
    dp[1].push_back(prices[0]);
    dp[2].push_back(duo(prices[0], prices[1]));

    //? gruparea produselor incepand cu al doilea
    for (int i = 2; i < n; i++) {
        du = duo(prices[i - 1], prices[i]);
        tri = trio(prices[i - 2], prices[i - 1], prices[i]);

        //* reinitializare indecsi si ultima suma
        last = -1;

        i1 = i2 = i3 = 0;

        s1 = dp[i].size();
        s2 = dp[i - 1].size();
        s3 = dp[i - 2].size();

        //? eu merg pe sume precalculate si vad unde pot
        //? adauga obtinand un nou minim
        flag = i1 < s1 || i2 < s2 || i3 < s3;

        while ((int) dp[i + 1].size() < k && flag) {
            sums[0] = sums[1] = sums[2] = MAX_PRICE;

            //? pot pune o suma noua
            if (i1 < s1) sums[0] = dp[i][i1] + prices[i];
            if (i2 < s2) sums[1] = dp[i - 1][i2] + du;
            if (i3 < s3) sums[2] = dp[i - 2][i3] + tri;

            //* calculez noul minim
            minim = sums[0];
            if (minim > sums[1]) minim = sums[1];
            if (minim > sums[2]) minim = sums[2];

            //* verific sa fie deja precalculat
            if (last != minim) {
                last = minim;
                dp[i + 1].push_back(minim);
            }

            //? vad unde l-am pus
            if (minim == sums[0]) i1++;
            if (minim == sums[1]) i2++;
            if (minim == sums[2]) i3++;

            flag = i1 < s1 || i2 < s2 || i3 < s3;
        }
    }

    //* afisare
    fout << std::fixed
         << std::setprecision(1)
         << dp[n][k - 1];

    //* eliberare memorie
    fin.close();
    fout.close();

    return 0;
}

inline double duo(double a, double b) {
    return a + b - (a > b ? b : a) / 2.;
}

inline double trio(double a, double b, double c) {
    return a + b + c - (a > b ? (b > c ? c : b)
                              : (a > c ? c : a));
}
