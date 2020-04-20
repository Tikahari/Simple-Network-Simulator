#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <fstream>
#include "lib.h"

#define debug 0

int NEIGHBOUR_DISTANCE;

int main(int argc, char * argv[]){
    if(argc!=4){
        cout << "pass 3 files data/nodes.txt data/obstacles.txt data/gridval.txt\n" << argc;
        cout << argv[1] << endl;
        cout << argv[2] << endl;
        return 0;
    }
    NEIGHBOUR_DISTANCE = 100;
    string inputfile = argv[1];
    string obstaclefile = argv[2];
    string gridval = argv[3];

    set<point> points;
    vector<line> obstacles;
    map<point, vector<point>> list;
    float hops;
    float coverage;

    get_nodes(points, inputfile);
    get_obstacles(obstacles,obstaclefile);
    get_adj_list(points, list);

    if(debug){
        printf("list size %d\n", list.size());
        printlist(list);
        printlist2(list);
        for(auto i: points)
            i.print();
    }
    
    // for(auto& p: points){
    //     std::map<point,std::vector<point>>::iterator ps = list.find(p);
    //     ps->second[1].print();
    // }
    get_Hops(&hops, list, obstacles, gridval);
	printf("average number of hops is %f\n", hops);
    // int res = bfs(src, dest, list, obstacles);
    // cout << "min hops " << res << endl;

    get_Coverage(gridval);
} 	