#include <bits/stdc++.h>
#include "json.hpp"
#define rep(i, n) for(int i = 0; i < n; i++)

using namespace std;
using json = nlohmann::json;

/* 変数の先宣言 */
int counter = 0;

vector<int> stringToVector(const string& str)
{
    vector<int> row;
    for(char c : str) row.push_back(c - '0');

    return row;
}

//型の読み込み
void loadBoard(const json& j, vector<vector<int>>& startB, vector<vector<int>>& goalB)
{
    for(const auto& line : j["board"]["start"]) startB.push_back(stringToVector(line.get<string>()));
    for(const auto& line : j["board"]["goal"]) goalB.push_back(stringToVector(line.get<string>()));
}

//一致率計算
double calculateMatchRate(const vector<vector<int>>& startBoard, const vector<vector<int>>& goalBoard) 
{
    int totalElements = 0;
    int matchCount = 0;
    rep(i, startBoard.size()){
        rep(j, startBoard[i].size()){
            if (startBoard[i][j] == goalBoard[i][j]) matchCount++;
            totalElements++;
        }
    }
    return (double)matchCount / totalElements * 100.0;
}

void infoPrint(const vector<vector<int>>& startB, const vector<vector<int>>& goalB, const int& width, const int& height)
{
    //型の表示
    rep(i, height){
        rep(j, width){
           if(startB[i][j] == goalB[i][j]) cout << "\033[31m" << startB[i][j] << "\033[m" << " ";
           else cout << startB[i][j] << " ";
        }
        cout << endl;
    }

    //一致率, 手数
    system("clear");

    double score = calculateMatchRate(startB, goalB);
    cout << "Match Rate: " << score << "%" << endl;
    cout << "Count: " << counter << endl;
}

int main()
{
    //時間を計測
    chrono::system_clock::time_point start = chrono::system_clock::now();

    //Json読み込み
    ifstream ifs("sample.json");
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>()); 
    json j = json::parse(str);
    vector<vector<int>> startB, goalB;
    loadBoard(j, startB, goalB);
    const int width = j["board"]["width"].get<int>();
    const int height = j["board"]["height"].get<int>();

    //抜き型
    vector<int> {1};

    //ソート開始
    rep(i, height){
        rep(j, width){
            if(startB[i][j] != goalB[i][j]){
                int si = INT_MAX;
                int sj = INT_MAX;

                bool flag1 = false;

                //欲しい数の最短場所を探す。
                rep(ki, height){
                    rep(kj, width){
                        if(startB[ki][ki] == goalB[i][j] && (ki < si && kj < sj)){
                            si = ki;
                            sj = kj;

                            if(ki > si && kj > sj) flag1 = true;

                            if(flag1) break;
                        }
                        if(flag1) break;
                    }
                }

                
            }
        }
    }
}