#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <cstdlib>
using namespace std;

void generate_stacks(vector<stack<int>> &stks){
    map<int, int> mp;
    mp[1] = 3;
    mp[2] = 3;
    mp[3] = 3;

    int rmd = 9;
    int ind = 0;

    while(rmd){
        int ran = rand()%3+1; // 1~3
        if(mp[ran] != 0){
            rmd--;
            mp[ran]--;
            
            if(stks[ind].size() == 3){
                ind++;
            }

            stks[ind].push(ran);
        }
    }
}

void show_stack(vector<stack<int>> &stks){
    vector<stack<int>> tmp = stks;
    vector<vector<int>> mp(4, vector<int>(3, 0));

    for(int i = 0; i < 4; i++){
        int n = tmp[i].size();
        for(int j = 0; j < n; j++){
            mp[i][j] = tmp[i].top();
            tmp[i].pop();
        }
    }

    cout << " Stack " << 1 << "  ";
    cout << " Stack " << 2 << "  ";
    cout << " Stack " << 3 << "  ";
    cout << " Stack " << 4 << "  " << endl;

    for(int i = 0; i < 3; i++){
        cout << "|    ";
        for(int j = 0; j < 4; j++){
            cout << ((mp[j][i]!=0)? char(mp[j][i]+'0'): '#') << "    |    ";
        }
        cout << endl;
    }
}

bool check_vic(vector<stack<int>> &stks){
    int vic = 0;

    for(int i = 0; i < 4; i++){
        stack<int> tmp = stks[i];
        bool dif = true;
        int cnt = 0;
        int cur = (tmp.empty())? 0: tmp.top();

        while(!tmp.empty()){
            int cur_tmp = tmp.top();
            tmp.pop();
            cnt++;
            if(cur != cur_tmp){
                dif = false;
                break;
            }
        }

        if(dif && (cnt==3 || cnt == 0)) vic++;
    }

    return vic==4;
}

void move_stack(vector<stack<int>> &stks, int from, int to){
    from--;
    to--;
    int f_i = stks[from].top();
    stks[from].pop();
    stks[to].push(f_i);
}

int start_game(vector<stack<int>> &stks){
    system ("clear");
    generate_stacks(stks);
    int moves = 0;

    while(!check_vic(stks)){
        show_stack(stks);
        int from = 0, to = 0;
        cout << "Move from(1-4), to (1-4)" << endl;
        cin >> from >> to;

        system ("clear");

        while(from < 1 || from > 4 || to < 1 || to > 4 || from == to || stks[from-1].empty() || stks[to-1].size() >= 3){
            cout << "Invalid move!" << endl;
            cout << "Move from(1-4), to (1-4)" << endl;
            cin >> from >> to;
        }

        moves++;
        move_stack(stks, from, to);
    }

    return moves;
}

int main(){
    vector<stack<int>> stks(4, stack<int>());
    int choice = 0;

    cout << "Welcome to 3 stacks game!" << endl;

    while(choice != 2){
        int moves = 0;
        cout << "Start game(1)" << endl;
        cout << "Exit(2)" << endl;
        cin >> choice;
        cout << endl;

        if(choice == 1){
            moves = start_game(stks);
            show_stack(stks);
            cout << endl << "Game Over!" << endl;
            cout << "Used " << moves << " moves" << endl << endl;
        }else if(choice == 2) break;
        else cout << "Invalid Choice!" << endl;
    }

    return 0;
}