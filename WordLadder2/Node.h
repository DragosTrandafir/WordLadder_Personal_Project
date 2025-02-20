#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<map>
#include<string>
#include<stdexcept>
#include<queue>
#include<cstdlib>


using std::string;
using std::ostream;
using std::ofstream;
using std::map;
using std::vector;
using std::set;
using std::queue;

template <typename T>
class Node;


template <typename T>
class Graph {
private:
    map<T, set<T>> adjacency_lists; // Adjacency lists representation
public:
    Graph();
    friend ostream& operator<<(ostream& outputStream, const Graph<string>& graph);
    friend vector<string> find_transformation(const string& start, const string& end, const Graph<string>& graph);
};


extern map<string, set<string>> pattern_words;
extern vector<string> random_words;
void form_n_letters_map(int n, const string& path);


template<typename T>
inline Graph<T>::Graph() {
    // Build the graph
    for (auto pattern_word : pattern_words)
        for (auto word : pattern_word.second) {
            for (auto it = pattern_word.second.begin(); it != pattern_word.second.end(); ++it) {
                if (*it != word) {
                        adjacency_lists[*it].insert(word);
                        adjacency_lists[word].insert(*it);
                    }
                }
            }
        }
vector<string> find_transformation(const string& start, const string& end, const Graph<string>& graph);
