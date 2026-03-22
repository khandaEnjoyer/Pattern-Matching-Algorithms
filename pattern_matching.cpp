#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Wyszukiwanie naiwne - funkcja pomocnicza
bool MatchesAt(const string& T, const string& W, int p, int wordSize) {
    for(int i = 0; i < wordSize; i++) {
        if(T[p + i] != W[i]) {
            return false;
        }
    }
    return true;
}

// 1. Algorytm naiwny (Zlozonosc: O(textSize * wordSize))
void NaiveSearch(const string& T, const string& W, vector<int>& tab) {
    int wordSize = W.size();
    int textSize = T.size();
    if (wordSize == 0 || wordSize > textSize) return;

    for(int p = 0; p <= textSize - wordSize; p++) {
        if(MatchesAt(T, W, p, wordSize)) {
            tab.push_back(p);
        }
    }
}

// 2. Algorytm Sunday
void SundaySearch(const string& T, const string& W, vector<int>& tab) {
    int wordSize = W.size();
    int textSize = T.size();
    if (wordSize == 0 || wordSize > textSize) return;

    vector<int> lastp(128, -1); 
    
    for(int i = 0; i < wordSize; i++) {
        lastp[(unsigned char)W[i]] = i;
    }

    int p = 0;
    while(p <= textSize - wordSize) {
        if(MatchesAt(T, W, p, wordSize)) tab.push_back(p);
        
        if (p == textSize - wordSize) break;
        
        p += wordSize;
        int nextChar = (unsigned char)T[p];
        p -= lastp[nextChar];
    }
}

// 3. Algorytm Double Sunday
void DoubleSundaySearch(const string& T, const string& W, vector<int>& tab) {
    int wordSize = W.size();
    int textSize = T.size();
    if (wordSize == 0 || wordSize > textSize) return; 
    if (wordSize == 1) { 
        SundaySearch(T, W, tab); 
        return; 
    }

    vector<vector<int>> lastPair(128, vector<int>(128, -2)); 

    int firstIndex = (unsigned char)W[0];
    int lastIndex = (unsigned char)W[wordSize - 1];

    for(int i = 0; i < 128; i++) {
        lastPair[i][firstIndex] = -1;
    }
    for(int i = 0; i < wordSize - 1; i++) {
        lastPair[(unsigned char)W[i]][(unsigned char)W[i + 1]] = i;
    }
    for(int j = 0; j < 128; j++) {
        lastPair[lastIndex][j] = wordSize - 1;
    }

    int p = 0;
    while(p <= textSize - wordSize) {
        int oldP = p;
        if(MatchesAt(T, W, p, wordSize)) tab.push_back(p);
        
        if(p == textSize - wordSize) break;
        
        p += wordSize;
        int nextChar = (unsigned char)T[p];
        
        if(p + 1 < textSize) {
            int nextNextChar = (unsigned char)T[p + 1];
            p -= lastPair[nextChar][nextNextChar];
        } else {
            p -= lastPair[nextChar][0];
        }
        
        if(oldP >= p) p = oldP + 1; 
    }
}

// 4. Algorytm KMP (Knuth-Morris-Pratt)
void KMP(const string& T, const string& W, vector<int>& tab) {
    int textSize = T.size();
    int wordSize = W.size();
    if (wordSize == 0 || wordSize > textSize) return;

    // Tworzenie tablicy LPS (Longest Prefix Suffix)
    vector<int> prefix(wordSize, 0);
    int j = 0;
    
    for(int i = 1; i < wordSize; i++) {
        while(j > 0 && W[i] != W[j]) {
            j = prefix[j - 1];
        }
        if(W[i] == W[j]) {
            j++;
        }
        prefix[i] = j;
    }

    // Właściwe wyszukiwanie KMP
    j = 0;
    for(int i = 0; i < textSize; i++) {
        while(j > 0 && T[i] != W[j]) {
            j = prefix[j - 1];
        }
        if(T[i] == W[j]) {
            j++;
        }
        
        if(j == wordSize) {
            tab.push_back(i - wordSize + 1);
            j = prefix[j - 1];
        }
    }
}

int main() {
    vector<int> result;
    string input = "aabaaabaaa";
    string word  = "aba";

    cout << "--- Naive Search ---" << endl;
    NaiveSearch(input, word, result);
    for(int pos : result) cout << "Znaleziono na pozycji: " << pos << endl;
    result.clear();

    cout << "\n--- Sunday Search ---" << endl;
    SundaySearch(input, word, result);
    for(int pos : result) cout << "Znaleziono na pozycji: " << pos << endl;
    result.clear();

    cout << "\n--- Double Sunday Search ---" << endl;
    DoubleSundaySearch(input, word, result);
    for(int pos : result) cout << "Znaleziono na pozycji: " << pos << endl;
    result.clear();

    cout << "\n--- KMP Search ---" << endl;
    KMP(input, word, result);
    for(int pos : result) cout << "Znaleziono na pozycji: " << pos << endl;
    result.clear();
    
    return 0;
}