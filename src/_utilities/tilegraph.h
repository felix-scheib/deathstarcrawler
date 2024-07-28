#ifndef COORDINATEGRAPH_H
#define COORDINATEGRAPH_H

#include "../engine/tile/tile.h"
#include "rowcolumn.h"

#include <iostream>

#include <map>
#include <vector>
#include <array>
#include <utility>
#include <memory>
#include <list>

class Level;
class Tile;

class TileGraph {
public:
    TileGraph(Level* level);
    ~TileGraph() = default;

    void updateGraph();

    std::list<RowColumn>& shortestPath(Tile* begin, Tile* end);

    inline bool isInsideGraph(Tile* tile) const {return nodeMap.find(tile) != nodeMap.end();}

    void initializeGraph();
private:
    Level* level;

    struct Node {   //nested struct
        Node() = default;
        Node(Tile* tile, Level* level);

        Tile* tile;
        Level* level;
        std::vector<std::pair<Tile*, uint32_t>> adjacencyList;
        RowColumn rowColumn;

        //Dijkstra Stuff
        bool isAccessible;
        Tile* previous;
        uint32_t distance;

        void getEnterableTiles();
        void print() const;
    };

    std::map<Tile*, std::shared_ptr<Node>> nodeMap;  //Map for quick search



    //dijkstra
    std::list<RowColumn> pathList;



    void dijkstra(Tile* begin, Tile* end);
    Tile* getClosest(const std::map<Tile*, std::shared_ptr<Node>>& nodeQueue) const;
    void calculatePath(Tile* end, Tile* begin);
};

#endif // COORDINATEGRAPH_H
