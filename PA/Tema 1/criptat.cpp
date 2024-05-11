#include <bits/stdc++.h>

int isIn(char letter, const char *letters, const int size);
void rememberInput(short freq[][8], const std::string *words, const int n,
                   char *letters, std::vector<int>& freqs,
                   int &total, short &unique);

int main() {
    std::ifstream fin("criptat.in");
    std::ofstream fout("criptat.out");

    std::string words[1000];
    short freq[1000][8], n, unique = 0;
    char letters[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int total = 0, dp[10001];
    std::vector<int> freqs(8, 0);

    //* citire
    fin >> n;

    for (int i = 0; i < n; i++)
        fin >> words[i];

    //* initializare
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 8; j++) freq[i][j] = 0;

    //* memorez numarul de aparitii pentru fiecare litera
    rememberInput(freq, words, n, letters, freqs, total, unique);

    int ans = 0, w, p;

    for (int i = 0; i < unique; i++) {
        //* resetez dp pentru fiecare caracter
        for (int j = 0; j <= total; j++) dp[j] = 0;

        for (int j = 0; j < n; j++) {
            w = words[j].length();  //? w este greutatea ca la rucsac
            p = freq[j][i];         //? p este profitul ca la rucsac

            for (int k = total - w; k > -1; k--)
                if (dp[k] > 0 || !k) {
                    dp[k + w] = std::max(dp[k + w], dp[k] + p);

                    if (dp[k + w] > (k + w) / 2 && ans < k + w)
                        ans = k + w;
                }
        }
    }

    //* afisare
    fout << ans;

    //* eliberare memorie
    fin.close();
    fout.close();

    return 0;
}

int isIn(char letter, const char *letters, const int size) {
    for (int i = 0; i < size; i++)
        if (letters[i] == letter) return i;

    return -1;
}

void rememberInput(short freq[][8], const std::string *words, const int n,
                   char *letters, std::vector<int>& freqs,
                   int &total, short &unique) {
    int len, pos;

    for (int i = 0; i < n; i++) {
        len = words[i].length();
        total += len;

        for (int j = 0; j < len; j++) {
            pos = isIn(words[i][j], letters, unique);

            if (pos == -1) {  //? caracterul nu e in vector, deci il adaug
                letters[unique] = words[i][j];
                freq[i][unique] = 1;
                freqs[unique++] = 1;
            } else {  //? caracter gasit, marim numarul de aparitii
                freq[i][pos]++;
                freqs[pos]++;
            }
        }
    }
}
