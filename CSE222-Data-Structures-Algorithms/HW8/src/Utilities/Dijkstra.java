package Utilities;

import MyGraph.MyGraph;

import java.util.*;

import  MyGraph.Vertex;
import  MyGraph.Edge;

public class Dijkstra {


    /**
     * The function takes in a graph and a source vertex and returns a hashmap of distances from the source vertex to all
     * other vertices in the graph
     *
     * @param graph The graph that you want to run Dijkstra's algorithm on.
     * @param Id The id of the vertex you want to start from
     * @return A HashMap of the shortest distance from the source vertex to every other vertex in the graph.
     */
    public  static  HashMap<Integer,Double> dijkstra(MyGraph graph, int Id){

        int numV = graph.getNumV();;
        HashMap<Integer,Double> distance = new HashMap<>();

        HashSet<Integer> vMinusS = new HashSet<>(numV);



        Iterator<Map.Entry<Integer,Vertex>> vertices =  graph.iterator();
           // This is initializing the distance hashmap and the vMinusS hashset.
           while (vertices.hasNext()){
               int id = vertices.next().getKey();
               distance.put(id,Double.POSITIVE_INFINITY);
               vMinusS.add(id);
           }

        // This is initializing the distance hashmap and the vMinusS hashset.
        Iterator<Edge> edges = graph.iterator(Id);
        while (edges.hasNext()){
            Edge edge =edges.next();
            distance.put(edge.destId,edge.edgeWeight);
        }

        distance.put(Id,0.0);



        // This is the main part of the algorithm. It is going through the graph and updating the distance hashmap.
        while (!vMinusS.isEmpty()){
            double minDist = Double.POSITIVE_INFINITY;
            int u = -1;
            for(int v : vMinusS){
                if(distance.get(v) < minDist){
                    minDist = distance.get(v);
                    u = v;
                }
            }
            vMinusS.remove(u);

            Iterator<Edge> iterator = graph.iterator(u);
            Vertex vertex = graph.get(u);

            //int currIndex = edge1.destId;
            while (iterator.hasNext()){
                Edge edge1 = iterator.next();
                int v = edge1.destId;

                if(vMinusS.contains(v)) {
                    double total =0;

                    total =distance.get(u) + edge1.edgeWeight;

                    if( (edge1.sourceId != Id)){

                        total -= vertex.getWeight();
                    }

                    if (total< distance.get(edge1.destId)) {
                        distance.put(edge1.destId,total);
                    }
                }
            }

        }
        return distance;

    }


}
