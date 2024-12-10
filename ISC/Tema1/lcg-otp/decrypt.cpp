#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class LCG {
public:
    LCG(int a, int b) : a(a), b(b), mod(65536), state(0) {}

    unsigned short next() {
        state = (a * state + b) % mod;
        return state;
    }

private:
    int a, b, mod, state;
};

//* from https://stackoverflow.com/questions/15366319/how-to-read-the-binary-file-in-c
std::vector<unsigned char> readFile(const char* filename) {
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<unsigned char> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

const std::string encrypted = "L3wfbdNbnS07SjLdsU1bYuCmh+MFSdL0zW1ipfd5HCi1SAfbR5QJMODrZ3g7BMEh2Dv+Kt4MRRdpmvAcOwaJTaGpOgZwt5Zg3+arjmgYbISuw7r+LhnmuQNXhQqctRvgs+93Vb7cMQ==";
const std::string command = "echo \"" + encrypted + "\" | base64 --decode > encrypted.bin";

int main() {
    system(command.c_str());

    std::vector<unsigned char> message;

    message = readFile("encrypted.bin");

    for (int a = 1337; a <= 10000; a++) {
        if (a % 500 == 0) std::cout << "a = " << a << "\n";
        for (int b = 1337; b <= 10000; b++) {
            LCG lcg(a, b);
            std::vector<unsigned char> try_decrypt = message;

            for (size_t i = 0; i < try_decrypt.size(); i += 2) {
                unsigned short state = lcg.next(), fst, snd;

                fst = state & 0xFF;
                snd = (state >> 8) & 0xFF;

                try_decrypt[i] ^= fst;
                try_decrypt[i + 1] ^= snd;
            }

            int i = 0;

            while (i < try_decrypt.size() - 5) {
                if (try_decrypt[i] != 'S') { i++; continue; }

                if (try_decrypt[i + 1] == 'p' && try_decrypt[i + 2] == 'e' &&
                    try_decrypt[i + 3] == 'i' && try_decrypt[i + 4] == 's') {
                    std::cout << "Message found:\n";

                    for (unsigned char ch : try_decrypt) std::cout << ch;

                    std::cout << "\na = " << a << " & b = " << b << "\n\n\n";
                    // return 0;
                }

                i++;
            }
        }
    }

    std::cout << "Failed to find correct parameters.\n";
    return 0;
}
