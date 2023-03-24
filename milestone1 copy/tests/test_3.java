import java.util.*;

public class DijkstraAlgorithm {
    public static void main(String args[]) {
        // create graph
        int graph[][] = {
            { 0, 10, 0, 5, 0 },
            { 0, 0, 1, 2, 0 },
            { 0, 0, 0, 0, 4 },
            { 0, 3, 9, 0, 2 },
            { 7, 0, 6, 0, 0 }
        };
        int source = 0;
        int distances = dijkstra(graph, source);
    }
    
    public static int dijkstra(int graph[][], int source) {
        int n = graph.length;
        int distances [] = new int[n];
        Arrays.fill(distances, Integer.MAX_VALUE);
        distances[source] = 0;
        
        int visited[] = new int[n];
        
        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (visited[j] == 0 && (u == -1 || distances[j] < distances[u])) {
                    u = j;
                }
            }
            visited[u] = 1;
            
            for (int v = 0; v < n; v++) {
                if (graph[u][v] != 0) {
                    int newDistance = distances[u] + graph[u][v];
                    if (newDistance < distances[v]) {
                        distances[v] = newDistance;
                    }
                }
            }
        }
        
        return distances[0];
    }
}
