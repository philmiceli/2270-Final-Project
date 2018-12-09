#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct vertex;
class Graph;

/*This is the struct for the adjacent vertices for each
vertex in the graph. */
struct activity
{
    string activity;
    int rating;
};

class PriorityQueue
{
public:
  PriorityQueue(int queueSize);
  ~PriorityQueue();
  void enqueue (string name, int rating);
  void dequeue();
  bool isFull();
  bool isEmpty();
  void printQueue();
  int peekRating();
private:
  void repairUpward(int nodeIndex);
  void repairDownward(int nodeIndex);
  activity* priorityQueue; //pointer to the array used to implement priority queue
  int currentQueueSize; //number of patients currently in priority queue
  int maxQueueSize; //maximum capacity of priority queue
};

struct Edge
{
    vertex *v;
    int distance;
    string direction;
    string interstate;
};

/*this is the struct for each vertex in the graph. */
struct vertex
{
    std::string name;
    string state;
    bool visited;
    std::vector<Edge> Edges; //stores edges to adjacent vertices
    bool solved;
    int distance;
    vertex *parent;
    vertex *next;
    PriorityQueue *act;
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addCities();
    void addEdge(string v1, string v2, int distance,string direction,string interstate);
    void addVertex(std::string name,string state);
    void displayEdges();
    void printDFS();
    void printBFS();
    void setAllVerticesUnvisited();
    void setParentsNull();
    void BFT(std::string startingCity,std::string endCity);
    int shortestDistance(string city1,string city2);
    void getDirections(string city1,string city2);
    int printTripDirections(vertex *head);
    int budgetTrip(vertex *head,int MPG);
    vertex* planTrip();
    void addActivity();
    void updateActivity(string city);
    void printActivity(string city);
  private:
    std::vector<vertex> vertices; //stores vertices
    vertex *findVertex(std::string name);
    void DFTraversal(vertex *v);

};

#endif // GRAPH_HPP
