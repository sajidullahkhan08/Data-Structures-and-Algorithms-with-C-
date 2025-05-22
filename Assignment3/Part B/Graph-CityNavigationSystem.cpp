#include <iostream>
#include <string>
using namespace std;

struct Road{
    int dest,distance;
    Road* next;};
struct City{
    string name;
    Road* adjList;};

class CityGraph {
private:
    City cities[50];
    int cityCount;
public:
    CityGraph(){
        cityCount = 0;}

    int findCityIndex(string& name) {
        for (int i = 0; i < cityCount; ++i) {
        if (cities[i].name == name) return i;}
        return -1;}

    void addRoadHelper(int src, int dest, int dist){
        Road* newRoad = new Road{dest, dist, cities[src].adjList};
        cities[src].adjList = newRoad;}

    void addCity(string& name){
        if(cityCount >= 50){
            cout << "City limit reached!\n";
            return;
        }
        if(findCityIndex(name) != -1) {
            cout << "City already exists.\n";
            return;
        }
        cities[cityCount].name = name;
        cities[cityCount].adjList = NULL;
        cityCount++;
        cout<<"City added.\n";
    }

    void addRoad(string& from, string& to, int dist){
        int srcIndex = findCityIndex(from);
        int destIndex = findCityIndex(to);
        if(srcIndex == -1 || destIndex == -1){
            cout<<"One or both cities not found.\n";
            return;
        }
        addRoadHelper(srcIndex, destIndex, dist);
        addRoadHelper(destIndex, srcIndex, dist);
        cout<<"Road added between "<< from<< " and " << to << " (" << dist << " km)\n";
    }

    void deleteRoad(string& from, string& to) {
        int srcIndex = findCityIndex(from);
        int destIndex = findCityIndex(to);
        if(srcIndex == -1 || destIndex == -1) {
            cout <<"City not found.\n";
            return;
        }

        Road** curr = &cities[srcIndex].adjList;
        while(*curr){
            if((*curr)->dest == destIndex){
                Road* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &(*curr)->next;
        }
        curr = &cities[destIndex].adjList;
        while(*curr) {
            if((*curr)->dest == srcIndex){
                Road* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &(*curr)->next;
        }
        cout<<"Road deleted between "<<from<<" and "<<to<<".\n";
    }

    void deleteCity(string& name){
        int index = findCityIndex(name);
        if(index == -1){
            cout<<"City not found.\n";
            return;}

        for(int i=0; i< cityCount; ++i){
            if(i == index) continue;
            Road** curr = &cities[i].adjList;
            while(*curr){
                if((*curr)->dest == index) {
                    Road* temp = *curr;
                    *curr = (*curr)->next;
                    delete temp;
                    continue;
                }
                if((*curr)->dest > index) (*curr)->dest--;
                curr = &(*curr)->next;
            }
        }
        Road* r = cities[index].adjList;
        while(r){
            Road* temp =r;
            r = r->next;
            delete temp;
        }
        for(int i = index; i < cityCount - 1; ++i){
            cities[i] = cities[i + 1];
        }
        cityCount--;
        cout<<"City deleted successfully.\n";
    }

    void displayGraph(){
        cout<< "\n--- City Graph ---\n";
        for(int i = 0; i < cityCount; i++){
            cout<< cities[i].name << " -> ";
            Road* r = cities[i].adjList;
            while(r){
                cout<<cities[r->dest].name<<"(" << r->distance << "km) -> ";
                r = r->next;
            }
            cout<<"NULL\n";
        }
    }

    void dijkstra(string& startCity, string& endCity) {
        int start = findCityIndex(startCity);
        int end = findCityIndex(endCity);

        if (start == -1 || end == -1) {
            cout << "One or both cities not found.\n";
            return;
        }

        int dist[50];
        bool visited[50];
        int prev[50];

        for (int i = 0; i < cityCount; ++i) {
            dist[i] = 50;
            visited[i] = false;
            prev[i] = -1;
        }

        dist[start] = 0;

        for (int count = 0; count < cityCount; ++count) {
            int u = -1;
            for (int i = 0; i < cityCount; ++i) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                    u = i;
            }

            if (dist[u] == 50) break;
            visited[u] = true;

            for (Road* r = cities[u].adjList; r != nullptr; r = r->next) {
                int v = r->dest;
                int weight = r->distance;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }

        if (dist[end] == 50) {
            cout << "No path from " << startCity << " to " << endCity << ".\n";
            return;
        }

        // Print path
        cout << "\nShortest path from " << startCity << " to " << endCity << ":\n";
        int path[50], pathLen = 0;
        for (int v = end; v != -1; v = prev[v])
            path[pathLen++] = v;

        for (int i = pathLen - 1; i >= 0; i--) {
            cout << cities[path[i]].name;
            if (i > 0) cout << " -> ";
        }
        cout << "\nTotal Distance: " << dist[end] << " km\n";
    }
};

int main() {
    CityGraph graph;
    int choice;
    string city1, city2;
    int distance;

    do {
        cout << "\n===== City Navigation Menu =====\n";
        cout << "1. Add City\n2. Add Road\n3. Delete City\n4. Delete Road\n5. Display Graph\n6. Shortest Path (Dijkstra)\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter city name: ";
            cin.ignore();
            getline(cin, city1);
            graph.addCity(city1);
            break;
        case 2:
            cout << "Enter source city: ";
            cin.ignore();
            getline(cin, city1);
            cout << "Enter destination city: ";
            getline(cin, city2);
            cout << "Enter distance (km): ";
            cin >> distance;
            graph.addRoad(city1, city2, distance);
            break;
        case 3:
            cout << "Enter city to delete: ";
            cin.ignore();
            getline(cin, city1);
            graph.deleteCity(city1);
            break;
        case 4:
            cout << "Enter source city: ";
            cin.ignore();
            getline(cin, city1);
            cout << "Enter destination city: ";
            getline(cin, city2);
            graph.deleteRoad(city1, city2);
            break;
        case 5:
            graph.displayGraph();
            break;
        case 6:
            cout << "Enter start city: ";
            cin.ignore();
            getline(cin, city1);
            cout << "Enter end city: ";
            getline(cin, city2);
            graph.dijkstra(city1, city2);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);
    return 0;
}
