#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <fstream>
#include "lib.h"

#define debug 0
int main(char** args){
    set<point> pnts;
    point src({-1, -1, -1});
    point dest({-1, -1, -1});
    get_nodes(pnts, src, dest, "data/nodes.txt");
    map<point, vector<point>> list;
    get_adj_list(pnts, list);
    if(debug)
        printlist(list);void printlist(map<point,vector<point>> &list);
    int res = bfs(src, dest, list);
    cout << "min hops " << res << endl;
    return 0;
}