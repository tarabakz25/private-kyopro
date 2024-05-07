#include <bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

vector<int> nukigataSize = {1, 2, 4, 8, 16, 32, 64, 128, 256};
map<int, vector<vector<int>>> nukigata;


// 文字列からベクトルに変換する関数
vector<int> stringToVector(const string& str) {
    vector<int> row;
    for (char c : str) {
        row.push_back(c - '0');  // 文字を整数に変換
    }
    return row;
}

// JSONからボードを読み込む関数
int loadBoard(const json& jobj, vector<vector<int>>& startBoard, vector<vector<int>>& goalBoard) {
    for (const auto& line : jobj["board"]["start"]) 
    {
        startBoard.push_back(stringToVector(line.get<string>()));
    }
    for (const auto& line : jobj["board"]["goal"]) 
    {
        goalBoard.push_back(stringToVector(line.get<string>()));
    }
    return 0;
}

// JSONから抜き型を読み込む関数
int generateNukigata(const json& jobj) 
{
    for(const auto& pattern : jobj["general"]["patterns"]) 
    {
        int patternId = pattern["p"];
        vector<vector<int>> patternCells;
        for (const auto& line : pattern["cells"]) {
            patternCells.push_back(stringToVector(line.get<string>()));
        }
        nukigata[patternId] = patternCells;
    }
    return 0;
}

// ボードを表示する関数
void printBoard(const vector<vector<int>>& board1, const vector<vector<int>>& board2, bool action) {
    if (action) {
        for (int i = 0; i < board1.size(); i++) {
            for (int j = 0; j < board1[i].size(); j++) {
                if (board1[i][j] == board2[i][j]) {
                    cout << "\033[31m" << board1[i][j] << "\033[m" << " ";
                } else {
                    cout << board1[i][j] << " ";
                }
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < board1.size(); i++) {
            for (int j = 0; j < board1[i].size(); j++) {
                cout << board1[i][j] << " ";
            }
            cout << endl;
        }
    }
}

// 一致率を計算する関数
double calculateMatchRate(const vector<vector<int>>& startBoard, const vector<vector<int>>& goalBoard) {
    int totalElements = 0;
    int matchCount = 0;
    for (int i = 0; i < startBoard.size(); i++) {
        for (int j = 0; j < startBoard[i].size(); j++) {
            if (startBoard[i][j] == goalBoard[i][j]) {
                matchCount++;
            }
            totalElements++;
        }
    }
    return (double)matchCount / totalElements * 100.0;
}

int main() {
    //抜き型生成
    nukigata[0] = {{1}};
    int count = 1;
    for(int i = 1; i < nukigataSize.size(); i++)
    {
        for(int n = 0; n < 3; n++)
        {
            vector<vector<int>> tmp(nukigataSize[i], vector<int>(nukigataSize[i], 0));
            for(int j = 0; j < nukigataSize[i]; j++)
            {
                for(int k = 0; k < nukigataSize[i]; k++)
                {
                    if(n == 0){
                        tmp[j][k] = 1;
                    }
                    if(n == 1){
                        if(j % 2 == 0) tmp[j][k] = 1;
                    }
                    if(n == 2){
                        if(k == 0) tmp[j][k] = 1;
                        if(k > 0 && tmp[j][k-1] == 0) tmp[j][k] = 1;
                    }
                }
            }
            nukigata[count] = tmp;
            count ++;
        }
    }

    ifstream ifs("./sample.json");
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    json jobj = json::parse(str);
    vector<vector<int>> startBoard, goalBoard;
    if (loadBoard(jobj, startBoard, goalBoard) != 0 || generateNukigata(jobj) != 0) {
        cout << "Failed to load configurations." << endl;
        return -1;
    }

    //while (calculateMatchRate(startBoard, goalBoard) < 100.0) {
        system("clear");
        printBoard(startBoard, goalBoard, true);
        cout << "一致率: " << calculateMatchRate(startBoard, goalBoard) << " %" << endl;
    //}

    for(int n = 0; n < nukigata.size(); n++)
    {
        cout << n << " : " << endl;
        for(int i = 0; i < nukigata[n].size(); i++)
        {
            for(int j = 0; j < nukigata[n].size(); j++)
            {
                cout << nukigata[n][i][j] << " ";
            }
            cout << endl;
        }
    }
}
