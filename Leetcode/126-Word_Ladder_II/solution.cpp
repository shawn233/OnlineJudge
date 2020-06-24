/*
 * @Author: shawn233
 * @Date: 2020-06-06 11:16:07
 * @LastEditors: shawn233
 * @LastEditTime: 2020-06-24 12:24:57
 * @Description: Leetcode 126 Word Ladder II solution
 */ 
class Solution {
public:
    // 36ms (99.42%) 12.6MB (88.05%) solution 4: super-fast bidirectional BFS based on solution 2
    // This solution follows the same thought as solution 2, except for the details of
    // implemention. Bidirectional BFS searches from both the starting point and the 
    // ending point. When two search paths overlap, the transformation path is found.
    // Acknowledgement: Hua Hua @ Youtube
    // Reference: https://www.youtube.com/watch?v=vWPCm69MSfs
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) return 0;
        
        unordered_set<string> q1({beginWord});
        unordered_set<string> q2({endWord});
        
        int l = beginWord.size();
        int level = 0;
        
        while (!q1.empty() && !q2.empty()) {
            ++ level;
            
            // CLEVER TRICK: always expand the smaller set
            if (q2.size() < q1.size())
                std::swap(q1, q2);
            
            unordered_set<string> q;
            
            for (string word: q1) {
                for (int i = 0; i < l; ++ i) {
                    char ch = word[i];
                    
                    for (char c = 'a'; c <= 'z'; ++ c) {
                        word[i] = c;
                        if (q2.count(word))
                            return level + 1;
                        if (!words.count(word))
                            continue;
                        words.erase(word);
                        q.insert(word);
                    }
            
                    word[i] = ch;
                }
            }
            
            std::swap(q, q1);
        }
        
        return 0;
    }
    
    // 132ms (78.25%) 30MB (15.53%) solution 3: not-so-intuitive BFS, official solution
    // create intermediate nodes to easily construct the graph
    // hit -> *it, h*t, hi* (3 intermediate nodes)
    // hit -> h*t -> hot -> *ot -> dot -> ...
    int ladderLength3(string beginWord, string endWord, vector<string>& wordList) {
        // mapping intermediate words (h*t) to possible combinations ([hot, hit])
        unordered_map<string, vector<string>> combo_dict;
        unordered_map<string, bool> visited;
        for (const string& word: wordList)
            visited[word] = false;
        if (!visited.count(endWord))
            return 0;
        
        int n = wordList.size();
        int l = beginWord.size();
        
        // pre-processing: fill the combo_dict
        // Time complexity: O(N * L^2)
        for (int t = 0; t < n; ++ t) {
            string word = wordList[t];
            for (int i = 0; i < l; ++ i) {
                word[i] = '*';
                if (!combo_dict.count(word))
                    combo_dict[word] = vector<string>({wordList[t]});
                else
                    combo_dict[word].push_back(wordList[t]);
                word[i] = wordList[t][i];
            }
        }
        
        queue<string> q;
        q.push(beginWord);
        int level = 0;
        
        while (!q.empty()) {
            ++ level;
            
            for (int sz = q.size(); sz > 0; -- sz) {
                string& word = q.front();
                
                for (int i = 0; i < l; ++ i) {
                    char ch = word[i];
                    word[i] = '*';
                    
                    if (combo_dict.count(word)) {
                        for (string& combo: combo_dict[word]) {
                            if (!visited[combo]) {
                                if (combo == endWord)
                                    return level+1;
                                q.push(combo);
                                visited[combo] = true;
                            }
                        }
                    }
                    
                    word[i] = ch;
                }
                
                q.pop();
            }
        }
        
        return 0;
    }
    
    // 100ms (86.74%) 13.1MB (61.25%) solution 2: intuitive BFS
    // - Node expansion: replace every character in a word
    // with [a - z], and use a hash set to check if the new word
    // is in the word list.
    // - Cycle prevention: remove a word from the hash set 
    // when the word is added to the searching queue
    // - Time complexity: O(N) * O(L) * O(26) * O(L) = O(N * L^2)
    // - Acknowledgement: Hua Hua @ Youtube
    // - Reference: https://www.youtube.com/watch?v=vWPCm69MSfs
    int ladderLength2(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) return 0;
        queue<string> q;
        
        int level = 1;
        int l = beginWord.size();
        
        q.push(beginWord);
        while (!q.empty()) {
            ++ level;
            
            for (int sz = q.size(); sz > 0; -- sz) {
                string& oldWord = q.front();
                
                for (int i = 0; i < l; ++ i) {
                    char ch = oldWord[i];
                    
                    for (char c = 'a'; c <= 'z'; ++ c) {
                        oldWord[i] = c;
                        // the order of the conditional statements is important
                        // For most new words, it's not in the word list
                        // So do the O(1) check first
                        if (!words.count(oldWord))
                            continue;
                        if (oldWord == endWord)
                            return level;
                        words.erase(oldWord); // BRILLIANT: to prevent cycles
                        q.push(oldWord);
                    }
                    
                    oldWord[i] = ch;
                }
                
                q.pop();
            }
        }
        
        return 0;
    }
    
    // 880ms (21.23%) 14.4MB (39.95%) solution 1: silly counting-based BFS
    // Using counting-based approach to find neighboring words is very costly.
    // Analysis shows that this solution has O(N^2 * L) time complexity, where
    // N is the number of words, and L is the length of a word.
    int ladderLength1(string beginWord, string endWord, vector<string>& wordList) {
        if (wordList.empty())
            return 0;
        
        int end_node = -1;
        for (int i = 0; i < wordList.size(); ++ i)
            if (endWord.compare(wordList[i]) == 0) {
                end_node = i;
                break;
            }
        if (end_node == -1)
            return 0;
        
        vector<int> visited(wordList.size(), 0);
        vector<int> layer(visited.size(), -1);
        vector<vector<int>> graph(wordList.size());
        
        for (int i = 0; i < wordList.size(); ++ i) {
            for (int j = 0; j < i; ++ j) {
                if (countDif(wordList[i], wordList[j]) == 1) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        
        queue<int> q;
        
        for (int i = 0; i < wordList.size(); ++ i) {
            if (countDif(beginWord, wordList[i]) == 1) {
                q.push(i);
                visited[i] = 1;
                layer[i] = 1;
            }
        }
        
        bool stop_flag = false;
        while (!stop_flag && !q.empty()) {
            int n = q.front();
            q.pop();
            
            for (int i: graph[n]) {
                if (!visited[i]) {
                    layer[i] = layer[n] + 1;
                    if (i == end_node) {
                        stop_flag = true;
                        break;
                    }
                    visited[i] = 1;
                    q.push(i);
                }
            }
        }
        
        return layer[end_node]+1;
    }
    
    // intuitive but very silly
    int countDif(string& a, string& b) {
        // count the number of different letters (early stop if dif > 1)
        int dif = 0;
        for (int i = 0; i < a.size(); ++ i) {
            if (a[i] != b[i])
                ++ dif;
            if (dif == 2)
                break; // early stop
        }
        return dif;
    }
};