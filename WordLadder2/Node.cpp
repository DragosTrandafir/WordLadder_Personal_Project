#include "Node.h"


map<string, set<string>> pattern_words;
vector<string> random_words;
ostream& operator<<(ostream& os2, const Graph<string>& g) {
    for (const auto& node : g.adjacency_lists) {
        os2 << node.first << "   second ";
        for (const auto& neighbor : node.second)
            os2 << neighbor << " ";
        os2 << std::endl;
    }
        return os2;
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

vector<string> find_transformation(const string& start, const string& end, const Graph<string>& g) {
    map<string, string> parent;
    queue<string> q;
    set<string> visited;
    vector<string> path;

    q.push(start);
    visited.insert(start);
    parent[start] = start;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

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
        for (const auto& neighbor : g.adjacency_lists.at(current)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = current; // Set the parent of neighbor to current node
            }
        }
    }
    return path;

}
