// Implements djikstra algorithm, supoort for inter class interaction, field variables as both variables and arrays.

class Graph {
    int V=100;
    int graph[][] = new int[V][V];

    Graph( int v) {
        V = v;
    }

    

    public void addEdge(int src, int dest, int weight) {
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }
    private void printDistances(int dist[]) {
                
        for (int i = 0; i < V; i++) {
            System.out.println(dist[i]);
        }
    }
    void printGraph() {
        
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                System.out.println(graph[i][j]);
            }
          
        }
    }

    public void dijkstra(int start) {
        int visited [] = new int[V];
        int dist [] = new int[V];
        for (int i = 0; i < V; i++) {
            dist[i] = 1000000000;
        }
        dist[start] = 0;

        for (int i = 0; i < V - 1; i++) {
            int minDist = 1000000000;
            int minIndex = -1;

            for (int j = 0; j < V; j++) {
                if (visited[j]==0 && dist[j] < minDist) {
                    minDist = dist[j];
                    minIndex = j;
                }
            }
            if(minIndex==-1){
                break;
            }

            visited[minIndex] = 1;

            for (int k = 0; k < V; k++) {
                if (graph[minIndex][k] != 0 && visited[k]==0 && dist[minIndex] != 1000000000
                        && dist[minIndex] + graph[minIndex][k] < dist[k]) {
                    dist[k] = dist[minIndex] + graph[minIndex][k];
                }
            }
        }
        System.out.println(dist[0]);

        printDistances(dist);
    }

    
}

public class Dijkstra {

    void addEdge(int a, int b, int c){
        System.out.println(-1);
    }

    public static void main(String args[]) {
        Graph g = new Graph(5);
        g.addEdge(0, 1, 9);
        g.addEdge(0, 2, 6);
        g.addEdge(0, 3, 5);
        g.addEdge(0, 4, 3);
        g.addEdge(2, 1, 2);
        g.addEdge(2, 3, 4);

        g.dijkstra(0);
        // g.printGraph();
        System.out.println(g.V);
    }
}