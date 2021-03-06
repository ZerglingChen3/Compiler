//
// Created by chenjiyuan3 on 2021/12/2.
//

#ifndef COMPILER_GRAPH_H
#define COMPILER_GRAPH_H

#include <set>
#include <queue>

#define dom(x) (*(dominate[x]))

class Graph {
private:
    int point;
    vector<vector<int>* > edges;
    vector<vector<int>* > backEdges;

    vector<vector<int>* > dominate; //DOM(Y): X dominate Y means that every path from entry to Y all go through X
    vector<set<int>* > df; //DF(Y) = X dominate the prev of Y but not dominate Y

    vector<bool> reach;
    vector<bool> can;
    vector<bool> flag;

    vector<vector<int>* > newBlocks;

public:
    explicit Graph(int N) {
        point = N;
        for (int i = 0; i < N; ++ i) {
            auto* edge = new vector<int>();
            edges.push_back(edge);
            auto* backEdge = new vector<int>();
            backEdges.push_back(backEdge);
        }
        reach.resize(N);
        flag.resize(N);
        for (int i = 0; i < N; ++ i) {
            auto* dom = new vector<int>(N);
            dominate.push_back(dom);
            auto* dfp = new set<int>();
            df.push_back(dfp);
        }
        for (int i = 0; i < N; ++ i) {
            auto* block = new vector<int>(2);
            (*block)[0] = (*block)[1] = -1;
            newBlocks.push_back(block);
        }
    }

    int getBlockNum(int sou, int tar) const {
        for (int i = 0; i < edges[sou]->size(); ++ i)
            if ((*edges[sou])[i] == tar)
                return (*newBlocks[sou])[i];
        cout << "error in get New Block Num : " << sou << " " << tar << endl;
        exit(4343);
    }

    void setBlockNum(int sou, int tar, int num) {
        for (int i = 0; i < edges[sou]->size(); ++ i) {
            if ((*edges[sou])[i] == tar) {
                (*newBlocks[sou])[i] = num;
                return ;
            }
        }
        cout << "error in set New Block Num : " << sou << " " << tar << " " << num << endl;
        exit(8787);
    }
    void addPoint() {
        point ++;
        auto* edge = new vector<int>();
        edges.push_back(edge);
        auto* backEdge = new vector<int>();
        backEdges.push_back(backEdge);

        reach.push_back(true);
        flag.push_back(false);
    }

    void link(int s, int t) {
//        cout << "link : " << s << " " << t << endl;
        edges[s] -> push_back(t);
        backEdges[t] ->push_back(s);
    }

    void bfs(int st) {
        queue<int> Q;
        if (st != 0) Q.push(0);
        for(int i = 1; i < point; ++ i)
            reach[i] = false;
        reach[0] = true;
        if (st > 0) reach[st] = true;
        while (!Q.empty()) {
            int now = Q.front();Q.pop();
            for (auto nx: *edges[now]) {
                if (!reach[nx]) {
                    reach[nx] = true;
                    Q.push(nx);
                }
            }
        }
        if (st >= 0) {
            reach[st] = false;
            for (int i = 0; i < point; ++ i)
                if (!can[i])
                    dom(st)[i] = 0;
                else
                    dom(st)[i] = 1 - reach[i];
        }
    }

    void getDF(int st) {
        for (int i = 0; i < point; ++ i)
            if (dom(st)[i]) {
                for (auto nx: *edges[i]) {
                    if (nx == st || !dom(st)[nx])
                        (*df[st]).insert(nx);
                }
            }
    }

    void debug() {
        cout << "-----------------------dom---------------------" << endl;
        for (int i = 0; i < point; ++ i) {
            cout << "dom : " << i << endl;
            for (int j = 0; j < point; ++ j)
                if (dom(i)[j]) {
                    cout << j << " ";
                }
            cout << endl;
        }


        cout << "-----------------------df---------------------" << endl;
        for (int i = 0; i < point; ++ i) {
            cout << "df : " << i << endl;
            for (auto c: (*df[i])) {
                cout << c << " ";
            }
            cout << endl;
        }
    }

    void ssaInit() {
        bfs(-1);
        for (auto c: reach)
            can.push_back(c);
        for (int i = 0; i < point; ++ i)
            bfs(i);
        for (int i = 0; i < point; ++ i)
            getDF(i);
//        debug();
    }

    vector<bool>* getReach() {
        return &can;
    }

    vector<int>* getPhi(vector<int>* block) {
        for (int i = 0; i < point; ++ i)
            flag[i] = false;
        queue<int> Q;
        vector<int>* ans = new vector<int>();
        for (auto b: *block) {
            for (auto c: (*df[b])) {
                if (!flag[c]) {
                    Q.push(c);
                    ans->push_back(c);
                    flag[c] = true;
                }
            }
        }
        while (!Q.empty()) {
            int now = Q.front(); Q.pop();
            for (auto c: (*df[now])) {
                if (!flag[c]) {
                    Q.push(c);
                    ans->push_back(c);
                    flag[c] = true;
                }
            }
        }
        return ans;
    }

    vector<int>* getOutBlock(int x) {
        return edges[x];
    }

    vector<vector<int>* >* getDominate() {
        return &dominate;
    }

    vector<int>* getEdges(int index) {
        return edges[index];
    }

    vector<int>* getBackEdges(int index) {
        return backEdges[index];
    }
};
#endif //COMPILER_GRAPH_H
