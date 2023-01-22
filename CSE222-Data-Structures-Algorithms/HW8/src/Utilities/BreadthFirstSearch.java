package Utilities;

import MyGraph.MyGraph;
import MyGraph.Vertex;
import MyGraph.Edge;

import java.util.*;

/**
 * It's a breadth-first search that uses a queue to keep track of the nodes to visit
 */
public class BreadthFirstSearch {

    // It's a constructor.
    public BreadthFirstSearch(MyGraph graph){

    }

    /**
     * It takes a graph and returns a HashMap of PriorityQueues of Edges
     *
     * @param graph The graph that we want to find the MST of.
     * @return A HashMap of PriorityQueues.
     */
    @SuppressWarnings("unchecked")
    private static HashMap<Integer,PriorityQueue<Edge>> convertToPriorityQueue(MyGraph graph){

        HashMap<Integer,PriorityQueue<Edge>> tempGraph = new HashMap<>();


        Iterator it = graph.iterator();
        int i  = 0;
        while(it.hasNext()){

            Map.Entry<Integer,Vertex> entry =(Map.Entry<Integer,Vertex>) it.next();
            Vertex vertex = entry.getValue();
            Iterator edgeIterator = vertex.edges.iterator();
            tempGraph.put(vertex.getID(),new PriorityQueue<>());
            PriorityQueue<Edge> tempPq = tempGraph.get(vertex.getID());
            while (edgeIterator.hasNext()){
                Edge edge = (Edge) edgeIterator.next();
                tempPq.add(edge);
            }
        }
        return tempGraph;
    }


    /**
     * This function takes in a graph, a source node, and a hashmap of distances from the source node to all other nodes.
     * It returns a hashmap of parents of all nodes
     *
     * @param graph the graph we are searching
     * @param Id the id of the source node
     * @param distance a HashMap that stores the distance from the source node to each node.
     * @return The parent of each node in the graph.
     */
    public static HashMap<Integer, Integer> breadFirstSearch(MyGraph graph, int Id,HashMap<Integer,Double > distance){
        ArrayList<Integer> visited = new ArrayList<>();
        ArrayList<Integer> identified = new ArrayList<>();
        //ArrayList<Integer> identified = new ArrayList<>();
        HashMap<Integer,Integer> parent = new HashMap<>();
        Queue<Integer> queue = new LinkedList<>();

        identified.add(Id);
        queue.offer(Id);

        HashMap<Integer,PriorityQueue<Edge>> tempGraph = convertToPriorityQueue(graph);
        while (!queue.isEmpty()){

            int current = queue.remove();
            visited.add(current);

            PriorityQueue<Edge> priorityQueue = tempGraph.get(current);
            while (priorityQueue.size()!=0){
                Edge  edge1 = (Edge) priorityQueue.remove();

                if(!identified.contains(edge1.destId)){
                    identified.add(edge1.destId);
                    queue.offer(edge1.destId);
                    parent.put(edge1.destId,current);
                    if(!visited.contains(edge1.destId)){
                        distance.put(edge1.destId,distance.get(current)+ edge1.edgeWeight);
                    }
                }
            }
        }
        return parent;

    }


}
