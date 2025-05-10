// Part B: City Navigation System using Graph and Dijkstra's Algorithm
#include <iostream>
#include <climits> // for INT_MAX
#include <cstring> // for strcmp
using namespace std;

const int MAX_CITIES = 10; // Max number of cities

// Structure for each road (edge)
struct Road {
    int dest;
    int distance;
    Road* next;
};

// Structure for each city (node)
struct City {
    char name[30];
    Road* adjList; // adjacency list (linked list of roads)
};

class CityGraph {
private:
    City cities[MAX_CITIES];
    int cityCount;

    int findCityIndex(const char* name) {
        for (int i = 0; i < cityCount; ++i) {
            if (strcmp(cities[i].name, name) == 0)
                return i;
        }
        return -1;
    }

    void addRoadHelper(int src, int dest, int dist) {
        Road* newRoad = new Road{dest, dist, cities[src].adjList};
        cities[src].adjList = newRoad;
    }

public:
    CityGraph() {
        cityCount = 0;
    }

    void addCity(const char* name) {
        if (cityCount >= MAX_CITIES) {
            cout << "City limit reached!\n";
            return;
        }
        if (findCityIndex(name) != -1) {
            cout << "City already exists.\n";
            return;
        }
        strcpy(cities[cityCount].name, name);
        cities[cityCount].adjList = nullptr;
        cityCount++;
        cout << "City added.\n";
    }

    void addRoad(const char* from, const char* to, int dist) {
        int srcIdx = findCityIndex(from);
        int destIdx = findCityIndex(to);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "One or both cities not found.\n";
            return;
        }
        addRoadHelper(srcIdx, destIdx, dist);
        addRoadHelper(destIdx, srcIdx, dist); // undirected road
        cout << "Road added between " << from << " and " << to << " (" << dist << " km)\n";
    }

    void deleteRoad(const char* from, const char* to) {
        int srcIdx = findCityIndex(from);
        int destIdx = findCityIndex(to);
        if (srcIdx == -1 || destIdx == -1) {
            cout << "City not found.\n";
            return;
        }

        // Delete road from src to dest
        Road** curr = &cities[srcIdx].adjList;
        while (*curr) {
            if ((*curr)->dest == destIdx) {
                Road* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &(*curr)->next;
        }

        // Delete road from dest to src
        curr = &cities[destIdx].adjList;
        while (*curr) {
            if ((*curr)->dest == srcIdx) {
                Road* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                break;
            }
            curr = &(*curr)->next;
        }
        cout << "Road deleted between " << from << " and " << to << ".\n";
    }

    void deleteCity(const char* name) {
        int idx = findCityIndex(name);
        if (idx == -1) {
            cout << "City not found.\n";
            return;
        }

        // Remove all roads to this city
        for (int i = 0; i < cityCount; ++i) {
            if (i == idx) continue;
            Road** curr = &cities[i].adjList;
            while (*curr) {
                if ((*curr)->dest == idx) {
                    Road* temp = *curr;
                    *curr = (*curr)->next;
                    delete temp;
                    continue;
                }
                if ((*curr)->dest > idx) (*curr)->dest--; // adjust indices
                curr = &(*curr)->next;
            }
        }

        // Delete all roads from this city
        Road* r = cities[idx].adjList;
        while (r) {
            Road* temp = r;
            r = r->next;
            delete temp;
        }

        // Shift cities left
        for (int i = idx; i < cityCount - 1; ++i) {
            cities[i] = cities[i + 1];
        }
        cityCount--;
        cout << "City deleted.\n";
    }

    void displayGraph() {
        cout << "\n--- City Graph ---\n";
        for (int i = 0; i < cityCount; i++) {
            cout << cities[i].name << " -> ";
            Road* r = cities[i].adjList;
            while (r) {
                cout << cities[r->dest].name << "(" << r->distance << "km) -> ";
                r = r->next;
            }
            cout << "NULL\n";
        }
    }

    void dijkstra(const char* startCity, const char* endCity) {
        int start = findCityIndex(startCity);
        int end = findCityIndex(endCity);

        if (start == -1 || end == -1) {
            cout << "One or both cities not found.\n";
            return;
        }

        int dist[MAX_CITIES];
        bool visited[MAX_CITIES];
        int prev[MAX_CITIES];

        for (int i = 0; i < cityCount; ++i) {
            dist[i] = INT_MAX;
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

            if (dist[u] == INT_MAX) break; // remaining unreachable
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

        if (dist[end] == INT_MAX) {
            cout << "No path from " << startCity << " to " << endCity << ".\n";
            return;
        }

        // Print path
        cout << "\nShortest path from " << startCity << " to " << endCity << ":\n";
        int path[MAX_CITIES], pathLen = 0;
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
    char city1[30], city2[30];
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
            cin.getline(city1, 30);
            graph.addCity(city1);
            break;
        case 2:
            cout << "Enter source city: ";
            cin.ignore();
            cin.getline(city1, 30);
            cout << "Enter destination city: ";
            cin.getline(city2, 30);
            cout << "Enter distance (km): ";
            cin >> distance;
            graph.addRoad(city1, city2, distance);
            break;
        case 3:
            cout << "Enter city to delete: ";
            cin.ignore();
            cin.getline(city1, 30);
            graph.deleteCity(city1);
            break;
        case 4:
            cout << "Enter source city: ";
            cin.ignore();
            cin.getline(city1, 30);
            cout << "Enter destination city: ";
            cin.getline(city2, 30);
            graph.deleteRoad(city1, city2);
            break;
        case 5:
            graph.displayGraph();
            break;
        case 6:
            cout << "Enter start city: ";
            cin.ignore();
            cin.getline(city1, 30);
            cout << "Enter end city: ";
            cin.getline(city2, 30);
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
