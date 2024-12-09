#include "custom_func.hpp"

void check(bool condition, std::string message, std::string name_func, const bool forceExit) {
    if (condition) return;  //* condition is true, so return

    //! if the program needs the condition to be true, send error
    if (forceExit == ON_ERROR_EXIT) {
        std::cerr << "Error in " + name_func + ": " + message + "\n";
        exit(1);
    }

    //? if the program doesn't need the condition to be true, send warning
    if (forceExit == ON_ERROR_CONTINUE) {
        std::clog << "Warn in " + name_func + ": " + message + "\n";
        exit(1);
    }
}

void checkArguments(MapReduce MapRed) {
    check(MapRed.checkMap(), "We need at least a mapper.",
        "checkArguments", ON_ERROR_EXIT);

    check(MapRed.checkReducers(), "We need at least a reducer.",
        "checkArguments", ON_ERROR_EXIT);

    check(MapRed.checkPath(), "File doesn't exist.",
        "checkArguments", ON_ERROR_EXIT);
}

void process_file(Data *data, int id, File file, int file_id) {
    if (file_id == data->file_num) return;  //* file not found

    std::ifstream fin(file.path.c_str());

    check(fin.is_open(), "File failed to open.", "process_file", ON_ERROR_EXIT);

    std::string word;

    while (fin >> word) {
        //* remove anything that is not a letter
        for (size_t i = 0; i < word.length(); i++) {
            //* each word needs to be in lower case
            if (('A' <= word[i] && word[i] <= 'Z')) word[i] += 32;

            //* each word has only letters
            if (word[i] < 'a' || word[i] > 'z') {
                word.erase(word.begin() + i);
                i--;
            }
        }

        //* either it was a space or some other characters
        if (word == "") continue;

        //* add word
        data->mappers[id].words[word].insert(file_id);
    }

    //* done
    fin.close();
}

void mapper(Data *data, int id) {
    File file;
    int file_id;
    bool isDone = false;

    do {
        isDone = true;  //* at first it assumes there are no more files to read
        file_id = 0;

        pthread_mutex_lock(data->mutex);
        for (File &f : data->files) {
            if (!f.isAlive) { file_id++; continue; }

            f.isAlive = false;
            file = f;

            isDone = false;
            break;
        }
        pthread_mutex_unlock(data->mutex);

        process_file(data, id, file, file_id);
    } while(!isDone);
}

void reducer(Data *data, int id) {
    int n, p, start, end, idx;
    std::string word;

    //* counting from 0 to data->reducers_num;
    idx = id - data->mappers_num;

    p = data->reducers_num;

    //? read in equal parts each mapper
    for (Words mapper : data->mappers) {
        n = (int) mapper.words.size();
        start = (int) (idx * (double) n / p);
        end = std::min((int) ((idx +  1) * (double) n / p), n);

        auto it_start = std::next(mapper.words.begin(), start);
        auto it_end = std::next(mapper.words.begin(), end);

        for (auto it = it_start; it != it_end; it++) {
            word = it->first;

            auto &reducer = data->reducers[id];

            for (int i : mapper.words[word])
                reducer.words[word].insert(i);
        }
    }
}

void output(Data *data, int id) {
    auto &root = data->reducers[id].words;

    //* merge data in the "root" reducer
    for (int i = id + 1; i < id + data->reducers_num; i++) {
        auto words = data->reducers[i].words;

        for (auto it = words.begin(); it != words.end(); it++)
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
                root[it->first].insert(*it2);
    }

    auto it = data->reducers[id].words.begin();

    //* write for each letter the requested data
    for (char ch = 'a'; ch <= 'z'; ch++) {
        std::vector<word> words;

        while (it != data->reducers[id].words.end() && it->first[0] == ch) {
            words.push_back({it->first, it->second});
            it++;
        }

        //* sort the words as requested
        std::sort(words.begin(), words.end(), [](const auto &left, const auto &right) {
            if (left.first[0] == right.first[0]) {
                if (left.second.size() != right.second.size()) {
                    return left.second.size() > right.second.size();
                }
            }

                return left.first < right.first;
        });

        //* writing the output file for the ch.txt
        std::string s{ch};
        std::ofstream g((s + ".txt").c_str());

        check(checkPath(s + ".txt"), "File can't be created or opened.",
            "output", ON_ERROR_EXIT);

        for (auto w = words.begin(); w != words.end(); w++) {
            g << w->first << ":[";

            for (auto s = w->second.begin(); s != w->second.end(); s++) {
                g << *s + 1;

                if (std::next(s) != w->second.end()) g << " ";
            }

            g << "]\n";
        }

        g.close();
    }
}
