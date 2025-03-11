#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        vector<string> row;
        size_t rowLetters = 0;

        for (const string& word : words) {
            // If we place the word in this row, it will exceed the maximum width.
            // Therefore, we cannot put the word in this row and have to pad spaces
            // for each word in this row.
            if (rowLetters + row.size() + word.length() > maxWidth) {
                const int spaces = maxWidth - rowLetters;
                if (row.size() == 1) {
                    // Pad all the spaces after row[0].
                    for (int i = 0; i < spaces; ++i)
                        row[0] += " ";
                } else {
                    // Evenly pad all the spaces to each word (expect the last one) in
                    // this row.
                    for (int i = 0; i < spaces; ++i)
                        row[i % (row.size() - 1)] += " ";
                }
                ans.push_back(join(row, ""));
                row.clear();
                rowLetters = 0;
            }
            row.push_back(word);
            rowLetters += word.length();
        }
        ans.push_back(ljust(join(row, " "), maxWidth));

        return ans;
    }

private:
    string join(const vector<string>& words, const string& s) {
        string joined;
        for (int i = 0; i < words.size(); ++i) {
            joined += words[i];
            if (i != words.size() - 1)
                joined += s;
        }
        return joined;
    }

    string ljust(string s, int width) {
        while (s.length() < width)
            s += " ";
        return s;
    }
};

void printOutput(const vector<string>& result) {
    cout << "[" << endl;
    for (const string& line : result) {
        cout << "  \"" << line << "\"," << endl;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    vector<string> words1 = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth1 = 16;
    cout << "Input: words = [\"This\", \"is\", \"an\", \"example\", \"of\", \"text\", \"justification.\"], maxWidth = 16" << endl;
    cout << "Output:" << endl;
    vector<string> result1 = solution.fullJustify(words1, maxWidth1);
    printOutput(result1);

    vector<string> words2 = {"What", "must", "be", "acknowledgment", "shall", "be"};
    int maxWidth2 = 16;
    cout << "Input: words = [\"What\",\"must\",\"be\",\"acknowledgment\",\"shall\",\"be\"], maxWidth = 16" << endl;
    cout << "Output:" << endl;
    vector<string> result2 = solution.fullJustify(words2, maxWidth2);
    printOutput(result2);

    vector<string> words3 = {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"};
    int maxWidth3 = 20;
    cout << "Input: words = [\"Science\",\"is\",\"what\",\"we\",\"understand\",\"well\",\"enough\",\"to\",\"explain\",\"to\",\"a\",\"computer.\",\"Art\",\"is\",\"everything\",\"else\",\"we\",\"do\"], maxWidth = 20" << endl;
    cout << "Output:" << endl;
    vector<string> result3 = solution.fullJustify(words3, maxWidth3);
    printOutput(result3);

    return 0;
}
