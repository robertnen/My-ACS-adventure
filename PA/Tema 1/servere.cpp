#include <bits/stdc++.h>

//* functie de calculeaza ce putere are un server
double inline f_server(int p, int c, double x);

//* functie ce calculeaza puterea minima in anumite conditii
double getMinPower(const std::vector<int>& powers,
                   const std::vector<int>& nec_curs, double x);

//* functie de cauta puterea sistemului
double getPower(const std::vector<int>& powers,
                const std::vector<int>& nec_curs,
                double left, double right);

int main() {
    std::ifstream fin("servere.in");
    std::ofstream fout("servere.out");

    std::vector<int> powers;
    std::vector<int> nec_curs;
    int size, minim = INT_MAX, maxim = INT_MIN, x;

    //* citire
    fin >> size;

    for (int i = 0; i < size; i++) {
        fin >> x;
        powers.push_back(x);
    }

    //* in timpul citirii caut si intervalul
    for (int i = 0; i < size; i++) {
        fin >> x;
        if (x > maxim) maxim = x;
        if (x < minim) minim = x;

        nec_curs.push_back(x);
    }

    //* afisare
    fout << std::fixed << std::setprecision(1)
         << getPower(powers, nec_curs, minim, maxim);

    //* eliberare memorie
    fin.close();
    fout.close();

    return 0;
}

double inline f_server(int p, int c, double x) {
    return p - fabs(x - c);
}

double getMinPower(const std::vector<int>& powers,
                   const std::vector<int>& nec_curs, double x) {
    double minim = INT_MAX, tmp;
    int n = powers.size();

    for (int i = 0; i < n; i++) {
        tmp = f_server(powers[i], nec_curs[i], x);

        if (tmp < minim) minim = tmp;
    }

    return minim;
}

double getPower(const std::vector<int>& powers,
                const std::vector<int>& nec_curs,
                double left, double right) {
    double mid, *pows = new double[5];  //* -1.0 -0.5 0.0 +0.5 1.0
    double ans = INT_MIN, max_local;

    while (left < right) {
        mid = (left + right) / 2;

        //* vad intervalul [mid - 1; mid + 1]
        for (unsigned char i = 0; i < 5; i++)
            pows[i] = getMinPower(powers, nec_curs, mid - 1 + (double) i / 2.);

        //? caut maximul local pe intervalul [mid - 1, mid + 1]
        max_local = pows[0];

        for (unsigned char i = 1; i < 5; i++)
            if (max_local < pows[i]) max_local = pows[i];

        if (ans < max_local) ans = max_local;

        //? ca sa am la zecimale .0 sau .5 merg pe partea intreaga
        if (floor(pows[2]) == pows[2]) {
            if (pows[0] <= pows[2]) left = mid + 1;
            else
                right = mid - 1;
        } else {  //? am .5 si schimb intervalul cu .5
            if (pows[0] <= pows[2]) left = mid + .5;
            else
                right = mid - .5;
        }
    }

    delete[] pows;

    return ans;
}
