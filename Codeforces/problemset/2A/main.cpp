#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>
#define MAX_RECORD 1010

using namespace std;

typedef struct {
    string name;
    int score;
} Record;

typedef struct {
    int score;
    int index;
    bool isFirst;
} value;

int main () {
    string name;
    int score, n;
    unordered_map <string, value> map;
    Record records [MAX_RECORD];
    string name_list [MAX_RECORD];
    int name_list_ind;
    int max_score, n_max_score;
    bool is_winner [MAX_RECORD];

    cin >> n;

    for (int i = 0; i < n; ++ i) {
        cin >> name >> score;
        records[i].name = name;
        records[i].score = score;
    }

    // 1st iteration of records, initialize all names
    for (int i = 0; i < n; ++ i) {
        map [records[i].name].score = 0;
        map [records[i].name].isFirst = true;
    }

    // 2nd iteration of records, accumulate all scores, extract all names
    name_list_ind = 0;
    for (int i = 0; i < n; ++ i) {
        map[records[i].name].score += records[i].score;
        if (map[records[i].name].isFirst) {
            map[records[i].name].index = name_list_ind;
            name_list[name_list_ind++] = records[i].name;
            map[records[i].name].isFirst = false;
        }
    }

    // 1st iteration of name list, find max score and num winners
    max_score = - 100000;
    n_max_score = 0;
    for (int i = 0; i < name_list_ind; ++ i) {
        if (map[name_list[i]].score > max_score) {
            max_score = map[name_list[i]].score;
            n_max_score = 1;
        } else if (map[name_list[i]].score == max_score) {
            ++ n_max_score;
        }
    }

    // 2nd iteration of name list, find winners
    for (int i = 0; i < name_list_ind; ++ i) {
        is_winner[i] = false;
    }
    for (int i = 0; i < name_list_ind; ++ i) {
        if (map[name_list[i]].score == max_score) {
            is_winner[i] = true;
        }
    }

    /*
    // then find the winner
    if (n_max_score == 1) {
        // single winner
        for (int i = 0; i < name_list_ind; ++ i) {
            if (is_winner[i]) {
                cout << name_list[i] << endl;
                break;
            }
        }
    } else { */
        // multiple winners
        for (int i = 0; i < name_list_ind; ++ i) {
            map[name_list[i]].score = 0;
        }
        for (int i = 0; i < n; ++ i) {
            map[records[i].name].score += records[i].score;
            if (is_winner[map[records[i].name].index] && map[records[i].name].score >= max_score) {
                cout << name_list[map[records[i].name].index] << endl;
                break;
            }
        }
    //}

    return 0;
}