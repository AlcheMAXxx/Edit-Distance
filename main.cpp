#include "bits/stdc++.h"
using namespace std;

// defines maximum length of a word
#define LEN 20

struct Node {
    // stores the word of the current Node
    string word;
    
    // links to other Node in the tree
    int next[2 * LEN];
    
    // constructors
    Node(string x) : word(x) {
        // initializing next[i] = 0
        for (int i = 0; i < 2 * LEN; i++)
            next[i] = 0;
    }
    Node() {}
};

// stores the root Node
Node RT;

// stores every Node of the tree
vector<Node> tree(10000); // Assuming we may have up to 1000 nodes

// index for current Node of tree
int ptr;

// Edit Distance
// Dynamic-Approach O(m*n)
int editDistance(string& a, string& b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // filling base cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // populating matrix using dp-approach
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] != b[j - 1]) {
                dp[i][j] = min({1 + dp[i - 1][j],  // deletion
                                1 + dp[i][j - 1],  // insertion
                                1 + dp[i - 1][j - 1] // replacement
                              });
            } else
                dp[i][j] = dp[i - 1][j - 1];
        }
    }
    return dp[m][n];
}

// adds curr Node to the tree
void add(Node& root, Node& curr) {
    if (root.word == "") {
        // if it is the first Node
        // then make it the root Node
        root = curr;
        return;
    }

    // get its editDistance from the Root Node
    int dist = editDistance(curr.word, root.word);

    if (tree[root.next[dist]].word == "") {
        /* if no Node exists at this dist from root
         * make it child of root Node*/

        // incrementing the pointer for curr Node
        ptr++;

        // adding curr Node to the tree
        tree[ptr] = curr;

        // curr as child of root Node
        root.next[dist] = ptr;
    } else {
        // recursively find the parent for curr Node
        add(tree[root.next[dist]], curr);
    }
}

vector<string> getSimilarWords(Node& root, string& s, int TOL) {
    vector<string> ret;
    if (root.word == "")
        return ret;

    // calculating edit distance of s from root
    int dist = editDistance(root.word, s);

    // if dist is less than tolerance value
    // add it to similar words
    if (dist <= TOL) ret.push_back(root.word);

    // iterate over the string having tolerance
    // in range (dist - TOL , dist + TOL)
    int start = dist - TOL;
    if (start < 0)
        start = 1;

    while (start <= dist + TOL) {
        vector<string> tmp =
            getSimilarWords(tree[root.next[start]], s, TOL);
        for (auto i : tmp)
            ret.push_back(i);
        start++;
    }
    return ret;
}

// driver program to run above functions
int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> dictionary;
    string word;
    while (infile >> word) {
        dictionary.push_back(word);
    }
    infile.close();

    ptr = 0;
    int sz = dictionary.size();

    // adding dict[] words on to tree
    for (int i = 0; i < sz; i++) {
        Node tmp = Node(dictionary[i]);
        add(RT, tmp);
    }

    cout << "Enter a word: ";
    string input_word;
    cin >> input_word;
    
    cout << "Enter the tolerance level: ";
    int TOL;
    cin >> TOL;

    vector<string> match = getSimilarWords(RT, input_word, TOL);
    cout << "Similar words in dictionary for : " << input_word << ":\n";
    for (auto x : match)
        cout << x << endl;

    return 0;
}
