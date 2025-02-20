#include "Node.h"


map<string, set<string>> pattern_words;
vector<string> random_words;
ostream& operator<<(ostream& outputStream, const Graph<string>& graph) {
    for (const auto& node : graph.adjacency_lists) {
        outputStream << node.first << "   second ";
        for (const auto& neighbor : node.second)
            outputStream << neighbor << " ";
        outputStream << std::endl;
    }
        return outputStream;
}

void form_n_letters_map(int n, const string& path) {
    std::ifstream inputfile{ path };
    if (!inputfile.is_open())
        throw std::runtime_error("Cannot open file!");
    string word;
    while (inputfile >> word)
        if (word.length() == n)
            for (int i = 0; i < n; i++) {
                random_words.emplace_back(word);
                string word_copy = word;
                word_copy[i] = '*';
                pattern_words[word_copy].insert(word);
            }
}

vector<string> find_transformation(const string& start, const string& end, const Graph<string>& graph) {
    map<string, string> parent;
    queue<string> words_queue;
    set<string> visited;
    vector<string> path;

    words_queue.push(start);
    visited.insert(start);
    parent[start] = start;

    while (!words_queue.empty()) {
        string current = words_queue.front();
        words_queue.pop();

        if (current == end) {
            // Found the end word, print the path
            string node = end;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());


            return path;
        }

        // Traverse neighbors of current node
        for (const auto& neighbor : graph.adjacency_lists.at(current)) {
            if (visited.find(neighbor) == visited.end()) {
                words_queue.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = current; // Set the parent of neighbor to current node
            }
        }
    }
    return path;

}
