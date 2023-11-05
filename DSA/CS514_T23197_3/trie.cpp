#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int alphabetSize = 26;
struct sort_word
{
    string str;
    int freq;
};

sort_word sort_words[100];
int count_op = 0;

struct TrieNode
{
    TrieNode *children[alphabetSize];
    bool isEnd;
    int freq;

    TrieNode() : isEnd(false), freq(0)
    {
        for (int i = 0; i < alphabetSize; ++i)
        {
            children[i] = nullptr;
        }
    }
};

TrieNode *createNode()
{
    TrieNode *newNode = new TrieNode;
    return newNode;
}

void insert(TrieNode *root, string word)
{
    TrieNode *node = root;
    for (char ch : word)
    {
        int index = ch - 'a';
        if (!node->children[index])
        {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->isEnd = true;
    node->freq++;
}

bool compareWordsByFrequency(const sort_word &a, const sort_word &b)
{
    return a.freq > b.freq;
}

void findWords(TrieNode *node, string prefix, string currWord, string words[], int &index, sort_word word1[])
{
    if (node->isEnd)
    {
        if (currWord.find(prefix) == 0)
        {
            word1[count_op].str = currWord;
            word1[count_op].freq = node->freq;
            count_op += 1;
            words[index++] = currWord;
        }
    }

    for (int i = 0; i < alphabetSize; ++i)
    {
        if (node->children[i])
        {
            char ch = 'a' + i;
            findWords(node->children[i], prefix, currWord + ch, words, index, word1);
        }
    }
}

int main()
{
    int N;
    cin >> N;
    TrieNode *root = createNode();

    for (int i = 0; i < N; ++i)
    {
        string word;
        cin >> word;
        insert(root, word);
    }

    string query;
    cin >> query;

    TrieNode *node = root;
    for (char ch : query)
    {
        int index = ch - 'a';
        if (!node->children[index])
        {
            cout << "Not found." << endl;
            return 0;
        }
        node = node->children[index];
    }

    string words[N];
    int index = 0;

    sort_word words1[N];

    findWords(node, query, query, words, index, words1);
    sort(words1, words1 + count_op, compareWordsByFrequency);

    cout << "Output: " << endl;

    for (int i = 0; i < count_op; i++)
    {
        cout << words1[i].str << endl;
    }

    return 0;
}
