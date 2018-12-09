#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include "Graph.hpp"
//#include "PriorityQueue.hpp"

using namespace std;

PriorityQueue::PriorityQueue(int queueSize)
{
  this->maxQueueSize = queueSize;
  this->currentQueueSize = 0;
  activity *priorityQueue = new activity[maxQueueSize];
  priorityQueue[0].activity = "";
  priorityQueue[0].rating = -9999;
  this->priorityQueue = priorityQueue;
}

void PriorityQueue::enqueue (string name, int rating)
{
  if(currentQueueSize > maxQueueSize)
  {
    cout << "Cannot Enqueue" << endl;
    return;
  }
  currentQueueSize++;
  priorityQueue[currentQueueSize].activity = name;
  priorityQueue[currentQueueSize].rating = rating;
  repairUpward(currentQueueSize);
}

void PriorityQueue::dequeue()
{
  if(currentQueueSize <= 0)
  {
    return;
  }
  if(currentQueueSize == 1)
  {
    currentQueueSize--;
    return;
  }
  activity temp = priorityQueue[1];
  priorityQueue[1] = priorityQueue[currentQueueSize];
  priorityQueue[currentQueueSize] = temp;
  currentQueueSize--;
  repairDownward(1);
}

bool PriorityQueue::isFull()
{
  return (currentQueueSize == maxQueueSize);
}

bool PriorityQueue::isEmpty()
{
  return (currentQueueSize == 0);
}

void PriorityQueue::repairDownward(int nodeIndex)
{
  activity temp = priorityQueue[nodeIndex];
  int l = 2*nodeIndex;
  int r = 2*nodeIndex + 1;
  int largest  = nodeIndex;

  if(l <= currentQueueSize)
  {
    if(priorityQueue[nodeIndex].rating >= priorityQueue[l].rating)
    {
      largest = l;
    }
  }
  if(r <= currentQueueSize)
  {
    if(priorityQueue[largest].rating >= priorityQueue[r].rating)
    {
      largest = r;
    }
  }
  if(largest != nodeIndex)
  {
    activity temp = priorityQueue[largest];
    priorityQueue[largest] = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = temp;
    repairDownward(largest);
  }
}

void PriorityQueue::repairUpward(int nodeIndex)
{
  activity temp = priorityQueue[nodeIndex];
  int parent = nodeIndex/2;
  int smallest  = nodeIndex;

  if(parent >= currentQueueSize || nodeIndex == 1)
  {
      return;
  }

  if(priorityQueue[nodeIndex].rating <= priorityQueue[parent].rating)
  {
    smallest = parent;
  }

  if(smallest != nodeIndex)
  {
    temp = priorityQueue[smallest];
    priorityQueue[smallest] = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = temp;
    repairUpward(smallest);
  }
}

void PriorityQueue::printQueue()
{
  for(int i = 1; i <= currentQueueSize;i++)
  {
    cout << priorityQueue[i].activity << ", ";
    cout << priorityQueue[i].rating << endl;
  }
}

int PriorityQueue::peekRating()
{
  if(currentQueueSize == 0)
  {
    return -1;
  }
  else
  {
    return priorityQueue[1].rating;
  }
}

Graph::Graph() // Constructor for Graph
{
}

Graph::~Graph() // Destructor for Graph
{

}

vertex *Graph::findVertex(string name) // Finds vertex based off of city name
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == name)
    {
      return &vertices[i];
    }
  }
  return NULL;
}

void Graph::addEdge(string v1, string v2, int distance,string direction,string interstate)
{
  Edge* edgy = new Edge;
  edgy->distance = distance;
  edgy->direction = direction;
  edgy->interstate = interstate;
  vertex *A = findVertex(v1);
  vertex *B = findVertex(v2);
  edgy->v = B;
  A->Edges.push_back(*edgy);

  // Adds "opposite" edge to make graph undirected

  if(direction == "West")
  {
    edgy->v = A;
    edgy->direction = "East";
    B->Edges.push_back(*edgy);
  }
  else if(direction == "East")
  {
    edgy->v = A;
    edgy->direction = "West";
    B->Edges.push_back(*edgy);
  }
  else if(direction == "North")
  {
    edgy->v = A;
    edgy->direction = "South";
    B->Edges.push_back(*edgy);
  }
  else if(direction == "South")
  {
    edgy->v = A;
    edgy->direction = "North";
    B->Edges.push_back(*edgy);
  }
}

void Graph::addVertex(string name,string state)
{
  vertex *V = new vertex;
  V->name = name;
  V->state = state;
  V->visited = false;
  V->solved = false;
  V->distance = 1;
  V->next = NULL;
  PriorityQueue *activities = new PriorityQueue(5);
  V->act = activities;
  vertices.push_back(*V);
}

void Graph::addCities()
{
  // Add all cities
  addVertex("Phoenix","Arizona");
  addVertex("Tucson","Arizona");

  addVertex("San Diego","California");
  addVertex("Los Angeles","California");
  addVertex("San Francisco","California");

  addVertex("Denver","Colorado");

  addVertex("Washington","D.C.");

  addVertex("Jacksonville","Florida");
  addVertex("Orlando","Florida");
  addVertex("Tampa","Florida");
  addVertex("Miami","Florida");

  addVertex("Atlanta","Georgia");

  addVertex("Boise","Idaho");

  addVertex("Chicago","Illinois");

  addVertex("Indianapolis","Indiana");

  addVertex("New Orleans","Louisiana");

  addVertex("Baltimore","Maryland");

  addVertex("Boston","Massachussets");

  addVertex("Detroit","Michigan");

  addVertex("Minneapolis","Minnesota");

  addVertex("Kansas City","Missouri");
  addVertex("St. Louis","Missouri");

  addVertex("Billings","Montana");

  addVertex("Omaha","Nebraska");

  addVertex("Las Vegas","Nevada");

  addVertex("Albuquerque","New Mexico");

  addVertex("Charlotte","North Carolina");
  addVertex("Raleigh","North Carolina");

  addVertex("Columbus","Ohio");

  addVertex("Oklahoma City","Oklahoma");

  addVertex("Portland","Oregon");

  addVertex("Pittsburgh","Pennsylvania");
  addVertex("Philadelphia","Pennsylvania");

  addVertex("Memphis","Tennessee");
  addVertex("Nashville","Tennessee");

  addVertex("New York","New York");

  addVertex("El Paso","Texas");
  addVertex("Dallas","Texas");
  addVertex("San Antonio","Texas");
  addVertex("Austin","Texas");
  addVertex("Houston","Texas");

  addVertex("Salt Lake City","Utah");

  addVertex("Seattle","Washington");
  addVertex("Spokane","Washington");

  addVertex("Milwaukee","Wisconsin");

  addVertex("Cheyenne","Wyoming");

  // San Diego - LA, Phoenix, Tucson
  addEdge("San Diego","Los Angeles",120,"North","I-5");
  addEdge("San Diego","Tucson",480,"East","I-8");
  addEdge("San Diego","Phoenix",355,"East","I-8");

  // Los Angeles - SD, Phoenix, Las Vegas, SF
  addEdge("Los Angeles","Phoenix",375,"East","I-10");
  addEdge("Los Angeles","Las Vegas",270,"North","I-15");
  addEdge("Los Angeles","San Francisco",380,"North","I-5");

  // San Francisco - LA, Portland, SLC
  addEdge("San Francisco","Portland",635,"North","I-5");
  addEdge("San Francisco","Salt Lake City",735,"East","I-80");

  // Portland - Seattle, SF, Boise
  addEdge("Portland","Boise",430,"East","I-84");
  addEdge("Portland","Seattle",175,"North","I-5");

  // Las Vegas - LA, Phoenix, SLC
  addEdge("Las Vegas","Phoenix",300,"South","US-93");
  addEdge("Las Vegas","Salt Lake City",420,"North","I-15");

  // Salt Lake City - LV, Boise, Denver, Cheyenne
  addEdge("Salt Lake City","Denver",520,"East","I-70");
  addEdge("Salt Lake City","Boise",340,"West","I-84");
  addEdge("Salt Lake City","Cheyenne",440,"East","I-80");

  // Seattle - Portland, Spokane
  addEdge("Seattle","Spokane",280,"East","I-90");

  // Spokane - Seattle, Billings
  addEdge("Spokane","Billings",540,"East","I-90");

  // Cheyenne - SLC, Denver, Billings, Omaha
  addEdge("Cheyenne","Billings",450,"South","I-25");
  addEdge("Cheyenne","Denver",100,"South","I-25");
  addEdge("Cheyenne","Omaha",500,"East","I-80");

  // Denver - SLC, Cheyenne, KC, Omaha, Albuquerque
  addEdge("Denver","Kansas City",605,"East","I-70");
  addEdge("Denver","Omaha",540,"East","I-76");
  addEdge("Denver","Albuquerque",450,"South","I-25");
  addEdge("Denver","Las Vegas",750,"East","I-70");

  // Phoenix - LA, SD, LV, Tucson, Albuquerque
  addEdge("Phoenix","Tucson",110,"East","I-10");
  addEdge("Phoenix","Albuquerque",420,"East","I-40");

  // Tucson - LA, SD, Phoenix, El Paso
  addEdge("Tucson","El Paso",320,"East","I-10");

  // Albuquerque - Denver, Phoenix, El Paso, Oklahoma City
  addEdge("Albuquerque","El Paso",265,"South","I-25");
  addEdge("Albuquerque","Oklahoma City",545,"East","I-40");

  // KC - Denver, Omaha, Oklahoma City, St. Louis
  addEdge("Kansas City","Omaha",185,"North","I-29");
  addEdge("Kansas City","Oklahoma City",350,"South","I-35");
  addEdge("Kansas City","St. Louis",250,"East","I-70");

  // El Paso - Tucson, Albuquerque, Dallas, San Antonio
  addEdge("El Paso","Dallas",635,"East","I-20");
  addEdge("El Paso","San Antonio",550,"East","I-10");

  // Dallas - Oklahoma City, El Paso, Austin, Houston, Kansas City, Memphis
  addEdge("Dallas","Austin",195,"South","I-35");
  addEdge("Dallas","Houston",240,"South","I-45");
  addEdge("Dallas","Memphis",450,"East","I-40");

  // San Antonio - El Paso, Austin, Houston
  addEdge("San Antonio","Houston",200,"East","I-10");
  addEdge("San Antonio","Austin",80,"North","I-35");

  // Oklahoma City - Albuquerque, Dallas, Kansas City, Memphis, St. Louis
  addEdge("Oklahoma City","Memphis",465,"East","I-40");
  addEdge("Oklahoma City","St. Louis",500,"East","I-44");

  // Minneapolis - Billings, Milwaukee
  addEdge("Minneapolis","Billings",840,"West","I-94");
  addEdge("Minneapolis","Milwaukee",340,"East","I-94");

  // St. Louis - Memphis, KC, Chicago, OKC, Nashville, Indianapolis
  addEdge("St. Louis","Nashville",340,"East","I-64");
  addEdge("St. Louis","Memphis",280,"South","I-55");
  addEdge("St. Louis","Chicago",300,"North","I-55");
  addEdge("St. Louis","Indianapolis",245,"East","I-70");

  // Chicago - St. Louis, Milwaukee, Indianapolis, Omaha, Detroit
  addEdge("Chicago","Detroit",285,"I-94","East");
  addEdge("Chicago","Omaha",480,"West","I-80");
  addEdge("Chicago","Milwaukee",90,"West","I-94");
  addEdge("Chicago","Indianapolis",185,"South","I-65");

  // New Orleans - Houston, Memphis, Jacksonville
  addEdge("New Orleans","Houston",350,"West","I-10");
  addEdge("New Orleans","Memphis",395,"North","I-55");
  addEdge("New Orleans","Jacksonville",545,"East","I-10");
  addEdge("New Orleans","Atlanta",470,"East","I-20");

  // Nashville - Memphis, Charlotte, Atlanta, Indianapolis
  addEdge("Nashville","Memphis",210,"West","I-40");
  addEdge("Nashville","Charlotte",410,"East","I-40");
  addEdge("Nashville","Indianapolis",290,"North","I-65");
  addEdge("Nashville","Atlanta",260,"East","I-24");

  // Atlanta - Nashville, New Orleans, Jacksonville, Charlotte
  addEdge("Atlanta","Jacksonville",345,"South","I-75");
  addEdge("Atlanta","Charlotte",245,"North","I-85");

  // Orlando - Jacksonville, Tampa, Miami
  addEdge("Orlando","Jacksonville",140,"North","I-95");
  addEdge("Orlando","Tampa",85,"West","I-4");
  addEdge("Orlando","Miami",240,"South","I-95");

  // Washington - Columbus, Charlotte, Baltimore
  addEdge("Washington","Columbus",400,"West","I-70");
  addEdge("Washington","Charlotte",400,"South","I-85");
  addEdge("Washington","Baltimore",40,"North","I-95");

  // Columbus - Indianapolis, Pittsburgh, Detroit
  addEdge("Columbus","Indianapolis",175,"West","I-70");
  addEdge("Columbus","Detroit",210,"North","US-23");
  addEdge("Columbus","Pittsburgh",185,"East","I-70");

  // Detroit - Chicago, Indianapolis, Pittsburgh
  addEdge("Detroit","Indianapolis",320,"South","I-69");
  addEdge("Detroit","Pittsburgh",285,"East","I-80");

  // Philadelphia - Baltimore, Pittsburgh, New York
  addEdge("Philadelphia","Baltimore",100,"South","I-95");
  addEdge("Philadelphia","Pittsburgh",305,"West","I-76");
  addEdge("Philadelphia","New York",95,"North","I-95");

  // NYC - Boston, Philadelphia
  addEdge("New York","Boston",215,"East","I-90");

  // Raleigh - Jacksonville, Charlotte, Washington
  addEdge("Raleigh","Jacksonville",455,"South","I-95");
  addEdge("Raleigh","Charlotte",170,"West","I-85");
  addEdge("Raleigh","Washington",280,"North","I-95");

}

void Graph::addActivity()
{
  vertex *Denver;
  Denver = findVertex("Denver");
  (Denver->act)->enqueue("Red Rocks",10);
  (Denver->act)->enqueue("Go skiing",9);
  (Denver->act)->enqueue("Go downtown",6);
}

void Graph::setParentsNull()
{
  for(int i = 0; i < vertices.size();i++)
  {
    vertices[i].parent = NULL;
    vertices[i].distance = 1;
    vertices[i].solved = false;
  }
}

void Graph::printActivity(string city)
{
  vertex *a = findVertex(city);
  PriorityQueue *activity = a->act;
  activity->printQueue();
}

int Graph::shortestDistance(string city1, string city2)
{
  vertex *start, *end, *parent, *s, *path;
  int minD;

  start = findVertex(city1);
  end = findVertex(city2);

  if(start == NULL || end == NULL)
    return -1;

  start->solved = true;
  start->distance = 0;
  start->parent = NULL;
  vector<vertex*> solved;
  solved.push_back(start);
  while(!end->solved)
  {
    minD = 99999;
    vertex* solvedV = NULL;
    for(int x = 0; x < solved.size();x++)
    {
      s = solved[x];
      for(int y = 0; y < s->Edges.size();y++)
      {
        if(!s->Edges[y].v->solved)
        {
          int dist = s->distance + s->Edges[y].distance;
          if(dist < minD)
          {
            minD = dist;
            parent = s;
            solvedV = s->Edges[y].v;
          }
        }
      }
    }
    solvedV->distance = minD;
    solvedV->parent = parent;
    solvedV->solved = true;
    solved.push_back(solvedV);
  }
  return end->distance;
}

void Graph::getDirections(string city1,string city2)
{
  // vertex *start = findVertex(city1);
  // vertex *end = findVertex(city2);
  vertex *start, *end;
  start = findVertex(city1);
  end = findVertex(city2);
  if(start == NULL || end == NULL)
    return;
  int distance;
  distance = shortestDistance(city1,city2);

  vertex *path = end;
  stack<vertex*> directions;
  while(path->parent != NULL)
  {
    directions.push(path);
    path = path->parent;
  }
  directions.push(path);
  vertex *current;
  vertex *next;
  cout << "Directions from " << city1 << " to " << city2 << ":" << endl;

  while(directions.size() > 1)
  {
    current = directions.top();
    directions.pop();
    next = directions.top();

    int dist;
    string interstate, heading;

    for(int i = 0; i < current->Edges.size();i++)
    {
      if(current->Edges[i].v->name == next->name)
      {
        dist = current->Edges[i].distance;
        interstate = current->Edges[i].interstate;
        heading = current->Edges[i].direction;
        break;
      }
    }
    cout << "Take " << interstate << " " << heading;
    cout << " for " << dist << " miles from " << current->name;
    cout << " to " << next->name << "." << endl;
  }
  cout << "Total Distance: " << distance << " miles." << endl;
}

vertex* Graph::planTrip()
{
  cout << "Welcome to road trip planner!" << endl;
  cout << "Enter the name of the city you would like to visit." << endl;
  cout << "If you are finished, type 'end'." << endl;
  vertex  *a;
  vertex *b;
  string city1, city2;
  cout << "Enter starting city:" << endl;
  getline(cin,city1);
  vertex *head = findVertex(city1);
  if(head == NULL)
  {
    cout << "City does not exist." << endl;
    return NULL;
  }
  city2 = "";

  while(city2 != "end")
  {
    a = findVertex(city1);
    if(a == NULL)
    {
      cout << "City does not exist, try again!" << endl;
      break;
    }

    cout << "Enter the name of a city, or type 'end':" << endl;
    //cin >> city2;
    getline(cin,city2);
    b = findVertex(city2);

    if(b == NULL && city2 != "end")
    {
      cout << "City does not exist, try again!" << endl;
      break;
    }
    if(city2 == head->name)
    {
      city2 = "end";
      a->next = b;
    }
    else if(city2 != head->name)
    {
      a->next = b;
      city1 = city2;
    }
  }
  vertex *temp = head;
  int count = 0;
  while(temp->next != NULL && count > -1)
  {
    cout << temp->name << " --> ";
    if(temp->name != head->name || count == 0)
    {
      temp = temp->next;
      count++;
    }
    if(temp->name == head->name && count !=0)
    {
      count = -1;
    }
  }

  cout << temp->name << endl;
  return head;
}

void Graph::BFT(string startingCity,string endCity)
{
  queue<vertex*> vQueue;

  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i].name == startingCity)
    {
      vertices[i].visited = true;
      vQueue.push(&vertices[i]); // Adds starting city to queue
      break;
    }
  }

  while(!vQueue.empty())
  {
    vertex *current = vQueue.front();
    vQueue.pop();
    cout << current->name << endl;

    if(current->name == endCity)
    {
      return;
    }

    for(int i = 0; i < current->Edges.size();i++)
    {
      if(!current->Edges[i].v->visited)
      {
        current->Edges[i].v->visited = true;
        vQueue.push(current->Edges[i].v);
      }
    }
  }
}

void Graph::DFTraversal(vertex *v)
{
  for(int i = 0; i < v->Edges.size(); i++)
  {
    if(!v->Edges[i].v->visited)
    {
      v->Edges[i].v->visited = true;
      cout << v->Edges[i].v->name << endl;
      DFTraversal(v->Edges[i].v);
    }
  }
}

void Graph::printDFS()
{
  for(int i = 0; i < vertices.size();i++)
  {
    if(vertices[i].visited == false)
    {
      cout << vertices[i].name << endl;
      vertices[i].visited = true;
      DFTraversal(&vertices[i]);
    }
  }
}

void Graph::displayEdges()
{
  string state = vertices[0].state;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(state != vertices[i].state || i == 0)
    {
      state = vertices[i].state;
      cout << "State: " << state << endl;
      cout << endl;
    }

    cout << vertices[i].name;
    cout << "-->";
    for(int j = 0; j < vertices[i].Edges.size(); j++)
    {
      cout << vertices[i].Edges[j].v->name;
      cout << " (" << vertices[i].Edges[j].distance << " miles,";
      cout << vertices[i].Edges[j].interstate << ",";
      cout << vertices[i].Edges[j].direction << ")" << endl;
      if(j != vertices[i].Edges.size() - 1)
      {
        cout << vertices[i].name << "-->";
      }
    }
    cout << endl;
  }
}

void Graph::setAllVerticesUnvisited()
{
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
}

void Graph::updateActivity(string city)
{
  vertex *a = findVertex(city);
  PriorityQueue *activity = a->act;
  string activityToAdd;
  cout << "Enter the name of an activity you would like to add:" << endl;
  getline(cin,activityToAdd);
  cout << "Enter the rating of this activity:" << endl;
  int rate;
  string str;
  getline(cin,str);
  rate = stoi(str);
  if(activity->isFull())
  {
    int rating = activity->peekRating();
    if(rate > rating)
    {
      activity->dequeue();
      activity->enqueue(activityToAdd,rate);
    }
    else
      cout << "Activity has too low of a rating to add" << endl;
  }
  else
    activity->enqueue(activityToAdd,rate);
}

int Graph::printTripDirections(vertex* head)
{
  int count = 0;
  int distance = 0;
  vertex* temp = head;
  while(temp->next != NULL && count > -1)
  {
    setParentsNull();
    getDirections(temp->name,(temp->next)->name);
    cout << endl;
    distance += shortestDistance(temp->name,(temp->next)->name);
    if(temp->name != head->name || count == 0)
    {
      temp = temp->next;
      count++;
    }
    if(temp->name == head->name && count !=0)
    {
      count = -1;
    }
  }
  return distance;
}

int Graph::budgetTrip(vertex *head, int MPG)
{
  double price = 2.54;
  int dist = 0;
  int count = 0;
  vertex* temp = head;
  while(temp->next != NULL && count > -1)
  {
    setParentsNull();
    dist += shortestDistance(temp->name,(temp->next)->name);
    if(temp->name != head->name || count == 0)
    {
      temp = temp->next;
      count++;
    }
    if(temp->name == head->name && count !=0)
    {
      count = -1;
    }
  }
  int totalCost = (dist/MPG)*price;
  return totalCost;
}

void tripPlanner(Graph *g)
{
  bool quit = false;
  string city1;
  vertex *head = NULL;
  while(!quit)
  {
    cout << "======Trip Menu======" << endl;
    cout << "1. Build Trip" << endl;
    cout << "2. View Cities" << endl;
    cout << "3. View Activities" << endl;
    cout << "4. Suggest Activity" << endl;
    cout << "5. Trip Directions" << endl;
    cout << "6. Trip Budget" << endl;
    cout << "7. Main Menu" << endl;

    string s_input;
    int u_input;
    getline(cin, s_input);
    u_input = stoi(s_input);

    switch(u_input)
    {
      case 1:
        head = g->planTrip();
        break;
      case 2:
        g->displayEdges();
        break;
      case 3:
        cout << "Enter city to view activities:" << endl;
        getline(cin,city1);
        g->printActivity(city1);
        break;
      case 4:
        cout << "Enter a city to suggest an activity:" << endl;
        getline(cin,city1);
        g->updateActivity(city1);
         break;
      case 5:
        int distance;
        if(head == NULL)
          cout << "No trip has been planned yet" << endl;
        else
        {
          distance = g->printTripDirections(head);
          cout << "Total trip distance: " << distance << " miles." << endl;
        }
        break;
      case 6:
        if(head == NULL)
          cout << "No trip has been planned yet" << endl;
        else
        {
          int mpg;
          string str;
          cout << "Enter your vehicle's average MPG" << endl;
          getline(cin,str);
          mpg = stoi(str);
          int budget = g->budgetTrip(head,mpg);
          cout << "Gas budget: $" << budget << endl;
        }
        break;
      case 7:
        cout << "Back to main menu!" << endl;
        quit = true;
        break;
      default:
        cout << "Invalid input." << endl;
        break;
    }
  }
}

int main()
{
  Graph *g = new Graph();
  g->addCities();
  g->addActivity();

  bool quit = false;
  string city1, city2;
  while(!quit)
  {
    cout << "======Main Menu======" << endl;
    cout << "1. Get Directions" << endl;
    cout << "2. Plan Trip" << endl;
    cout << "3. Quit" << endl;

    string s_input;
    int u_input;
    getline(cin, s_input);
    u_input = stoi(s_input);

    switch(u_input)
    {
      case 1:
        cout << "Enter starting city:" << endl;
        getline(cin,city1);
        cout << "Enter ending city:" << endl;
        getline(cin,city2);
        g->setParentsNull();
        g->getDirections(city1,city2);
        break;
      case 2:
        tripPlanner(g);
        break;
      case 3:
        cout << "Goodbye!" << endl;
        quit = true;
        break;
      default:
        cout << "Invalid input." << endl;
        break;
    }
  }
  return 0;
}
