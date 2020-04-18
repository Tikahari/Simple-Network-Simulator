#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <fstream>
#include "lib.h"

#define debug 0

int main(int argc, char * argv[]){
    if(argc!=3){
        cout << "pass 2 files data/input.txt data/obstacles.txt\n" << argc;
        cout << argv[1] << endl;
        cout << argv[2] << endl;
        return 0;
    }
    string inputfile = argv[1];
    string obstaclefile = argv[2];

    set<point> points;
    vector<line> obstacles;

    point src({-1, -1});
    point dest({-1, -1});
    get_nodes(points, src, dest, inputfile);

    get_obstacles(obstacles,obstaclefile);

    map<point, vector<point>> list;
    get_adj_list(points, list);
    // printlist(list);	    int res = bfs(src, dest, list, obstacles);
    int res = bfs(src, dest, list, obstacles);
    cout << "min hops " << res << endl;
} 	