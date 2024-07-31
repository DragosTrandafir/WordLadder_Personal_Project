#define _CRT_SECURE_NO_WARNINGS
#include "Node.h"
#include <algorithm>
#include <chrono>
#include<sstream>
using std::ifstream;

bool available_word(const string& prev_word, const string& word) {


    if (std::find(random_words.begin(), random_words.end(), word) != random_words.end()) {
        int c = 0;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] != prev_word[i])
                c++;
            if (c == 2)
                return false;
        }
        return true;
    }
    return false;
}
int index_of_different_letter(const string& prev_word, const string& word) {
    for (int i = 0; i < word.length(); i++) 
        if (word[i] != prev_word[i])
            return i;
}
int main() {
    try {
        srand(time(nullptr));

        bool stop = false;
        int option;
        int subcase;
        while (!stop) {
            std::cout << "Option: ";
            std::cin >> option;
            switch (option) {
            case 0:
                stop = true;
                break;
            case 1:
            {
                string start, end;
                std::cout << "Enter start word: ";
                std::cin >> start;
                std::cout << "Enter target word: ";
                std::cin >> end;
                form_n_letters_map(start.length(), "english_words.txt");
                Graph<string> g1;
                vector<string> path = find_transformation(start, end, g1);
                std::cout << "Shortest transformation from " << start << " to " << end << ":" << std::endl;
                for (const auto& word : path)
                   std::cout << word << " ";
                std::cout << std::endl;
            }
            break;
            case 2:
            {
                int nr_hints = 0;
                int nr_moves = 0;
                set<string> words_used;

                random_words.clear();
                string name;
                std::cout << "Enter name: ";
                std::cin >> name;

                int length;
                std::cout << "Enter length of word: ";
                std::cin >> length;

                form_n_letters_map(length, "english_words.txt");
                Graph<string> g1;

                string start, end;
                int random_index;

                random_index = rand() % random_words.size();
                start = random_words[random_index];

                random_index = rand() % random_words.size();
                end = random_words[random_index];

                std::ofstream outfile{ name + ".csv" , std::ios::app };

                std::cout << start << " " << end << std::endl;
                outfile << start << " " << end << std::endl;
                string word, prev_word = start;
                while (word != end) {
                    std::cout << "Enter 10 if you want a hint or any other number if you do not: ";
                    std::cin >> subcase;
                    if (subcase == 10) {
                        nr_hints++;
                        vector<string> path = find_transformation(prev_word, end, g1);
                        int j = index_of_different_letter(prev_word, path[1]);
                        if (path.size() >= 2) { // Check if the path has at least two elements
                            int j = index_of_different_letter(prev_word, path[1]);
                            for (size_t i = 0; i < path[1].length(); i++) {
                                if (i == j) {
                                    std::cout << "\033[1;32m" << path[1][i] << "\033[0m";
                                }
                                else {
                                    std::cout << path[1][i];
                                }
                            }
                            std::cout << std::endl;
                        }
                        else {
                            std::cout << "No transformation path found." << std::endl;
                        }
                    }
                    std::cout << "Enter next word: ";
                    std::cin >> word;
                    nr_moves++;
                    words_used.insert(word);
                    if (!available_word(prev_word, word)) {
                        std::cout << "Invalid word. Choose another." << std::endl;
                        continue;
                    }
                    prev_word = word;
                }
                outfile << "End word reached." << std::endl;
                outfile << "Number of hints " << nr_hints << std::endl;


                const auto now = std::chrono::system_clock::now();
                const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
                outfile << "The system clock is currently at " << std::ctime(&t_c);
                //outfile << std::endl;

                outfile << name << " used the words : ";
                for (auto elem : words_used)
                    outfile << elem << " ";
                outfile << std::endl;

                outfile << name << " made : " << nr_moves << " moves. The nr of optimal moves is : " << find_transformation(start, end, g1).size() - 1 << std::endl;
                //outfile << std::endl;
                outfile.close();


                for (auto elem : words_used)
                    std::cout << elem << " ";
                std::cout << std::endl;

                std::cout << std::endl;
                std::ifstream inputfile{ name + ".csv" };
                string line;
                while (getline(inputfile, line))
                    std::cout << line << std::endl;
                std::cout << std::endl;
            }
                break;
            default:
                std::cout << "Invalid choice";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
