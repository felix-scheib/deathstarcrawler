#include "tilegraph.h"
#include "../engine/management/level.h"

TileGraph::TileGraph(Level* level) :
    level(level) {
}

void TileGraph::initializeGraph() { //init graph (at creation of level)
    auto tileVector = level->getTileVector();

    for(auto& subvector : tileVector) {
        for(auto& tile : subvector) {
            nodeMap[tile] = std::make_shared<Node>(tile, level);    //create map of all nodes
        }
    }
}

void TileGraph::updateGraph() { //update graph (update access)
    auto tileVector = level->getTileVector();

    for(auto& node : nodeMap) { //through all nodes
        node.second->distance = UINT32_MAX; //reset distance
        if(node.first->isAccessible()) {    //tile is accessible
            node.second->isAccessible = true;
            node.second->getEnterableTiles();   //update tiles
        }
        else {    //tile is not accessible
            node.second->isAccessible = false;
        }
    }
}


//dijkstra
std::list<RowColumn>& TileGraph::shortestPath(Tile *begin, Tile *end) {
    updateGraph();  //reset and update graph
    pathList.clear();   //list with path items for return

    if(isInsideGraph(begin) && isInsideGraph(end)) {
        dijkstra(begin, end);
        if(nodeMap[end]->previous) {
            calculatePath(end, begin);
        }
    }
    return pathList;
}

void TileGraph::dijkstra(Tile *begin, Tile *end) {
    std::map<Tile*, std::shared_ptr<Node>> nodeQueue = nodeMap;  //queue for nodes

    for(auto& item : nodeQueue) {   //init queue
        item.second->previous = nullptr;
        item.second->distance = UINT32_MAX;
    }

    Portal* isPortal = dynamic_cast<Portal*>(begin);

    if(isPortal) {  //begin is adj. list from destination
        begin = isPortal->getDestination();
    }


    nodeQueue[begin]->distance = 0;  //init begin
    nodeQueue[begin]->previous = begin;  //init begin


    while(!nodeQueue.empty()) { //main loop, finding nearest next node
        auto closestTile = getClosest(nodeQueue);   //get closest node
        if(!closestTile) {
            break;
        }
        nodeQueue.erase(closestTile);
        auto closestNode = nodeMap[closestTile];
        for(auto& neighbor : closestNode->adjacencyList) {   //all neighbors
            if(neighbor.first) {    //is accessible
                auto neighborNode = nodeMap[neighbor.first];
                auto closestDistance = closestNode->distance;
                auto neighborOffset = neighbor.second;
                auto neighborDistance = neighborNode->distance;
                if(closestDistance + neighborOffset < neighborDistance ) {  //distance over new connection is smaller
                    neighborNode->distance = closestDistance + neighborOffset;   //update distance
                    neighborNode->previous = closestTile;    //update Tile*
                }
            }
        }
    }
}

Tile* TileGraph::getClosest(const std::map<Tile*, std::shared_ptr<TileGraph::Node>>& nodeQueue) const {  //get closest tile from current tile
    uint32_t minDistance = UINT32_MAX;
    Tile* closestTile = nullptr;

    for(auto& node : nodeQueue) {
        if(node.second->distance < minDistance) {
            minDistance = node.second->distance;
            closestTile = node.first;
        }
    }
    return closestTile;
}

void TileGraph::calculatePath(Tile* end, Tile* begin) {
    Tile* currentTile  = end;
    Tile* previousTile = nodeMap[end]->previous;

    while(currentTile != previousTile) {
        pathList.push_front(currentTile->getRowColumn());
        currentTile = previousTile;
        previousTile = nodeMap[previousTile]->previous;
    }
}



//nested struct Node
TileGraph::Node::Node(Tile* tile, Level* level) :
    tile(tile), level(level), rowColumn(tile->getRowColumn()) {
    rowColumn = tile->getRowColumn();
    getEnterableTiles();
    distance = UINT32_MAX;
}

void TileGraph::Node::getEnterableTiles() { //get enterable tiles surrounding a tile
    adjacencyList.clear();  //remove previous tiles

    auto tileVector = level->getTileVector();
    Tile* fromTile = tile;
    Portal* fromPortal = dynamic_cast<Portal*>(tile);
    if(fromPortal) {    //correct tile to portal destination
        fromTile = fromPortal->getDestination();
    }
    RowColumn tempRowColumn = fromTile->getRowColumn();
    for(int row = -1; row <= 1; ++row) {    //all neighbors
        for(int column = -1; column <= 1; ++column) {
            if(!level->insideLevel(RowColumn(tempRowColumn.row + row, tempRowColumn.column + column))) {    //is outside the level dimensions
                continue;
            }
            if(row == 0 && column == 0) {   //is tile itself
                continue;
            }
            Tile* enterTile = tileVector.at(tempRowColumn.row + row).at(tempRowColumn.column + column);
            if(fromTile->isLeaveable(enterTile)) {  //tile can be entered from current tile
                uint32_t distance = 3;
                if(row == 0 || column == 0) {
                    distance = 2;
                }
                adjacencyList.push_back(std::make_pair(enterTile, distance));   //accessible
            } else {
                adjacencyList.push_back(std::make_pair(nullptr, UINT32_MAX));    //not accessible
            }
        }
    }
}

void TileGraph::Node::print() const {
    std::cout << "Tile: " << rowColumn << " dist: " << distance << std::endl;
    std::cout << "Adjacencies: ";

    for(auto& pair : adjacencyList) {
        if(pair.first) {
            std::cout << pair.first->getRowColumn() << " dist: " << int(pair.second) << " ";
        }
    }
    std::cout << std::endl;
}
