package MyGraph;

import Utilities.Dijkstra;

import java.util.*;

/**
 * It's a graph that can be modified
 */
public class MyGraph implements DynamicGraph{
    HashMap<Integer,Vertex> vertices;
    private static int ID = -1;
    private boolean directed;
    // It's a constructor that takes a boolean value and initializes the graph.
    public  MyGraph(boolean isDirected){
        this.directed = isDirected;
        vertices = new HashMap<>();
    }


    /**
     * > This function creates a new vertex with a label and weight and returns it
     *
     * @param label The label of the vertex.
     * @param weight The weight of the vertex.
     * @return A new vertex with the given label and weight.
     */
    @Override
    public Vertex newVertex(String label, double weight) {
        ++ID;
        return new Vertex(label, weight,ID);
    }


    /**
     * This function adds a vertex to the graph
     *
     * @param vertex The vertex to be added to the graph.
     */
    @Override
    public void addVertex(Vertex vertex) {

        vertices.put(vertex.getID(),vertex);

    }

    /**
     * This function adds an edge between two vertices
     *
     * @param ver1Id The id of the first vertex
     * @param ver2Id The id of the vertex that the edge is going to.
     * @param weight the weight of the edge
     * @return A boolean value.
     */
    @Override
    public boolean addEdge(int ver1Id, int ver2Id,double weight) {
        Vertex ver1 = vertices.get(ver1Id);
        Vertex ver2  = vertices.get(ver2Id);
        boolean res = false;
        if(ver1 != null || ver2 != null /*&& ver2List !=null*/){
            //ver1 = (Vertex) getVertexById(ver1Id).clone();
            ver1.edges.add(new Edge(weight,ver2Id,ver1Id));
            if(this.directed){
                ver2.edges.add(new Edge(weight,ver1Id,ver1Id));
            }
            res = true;
        }

        return res;
    }


    /**
     * > Remove the edge from the graph
     *
     * @param ver1Id The id of the first vertex
     * @param ver2Id The id of the destination vertex
     * @return The method returns a boolean value.
     */
    @Override
    public boolean removeEdge(int ver1Id, int ver2Id) {

        Edge deleted =null,deleted2=null;
        boolean res = false;


        Vertex sourceVertex = vertices.get(ver1Id);
        if(sourceVertex == null){
            return false;
        }
        List<Edge> edge1List = sourceVertex.edges;

        if(edge1List != null){

            for (Edge edge: edge1List) {
                if(edge.destId == ver2Id){
                    deleted = edge;
                    break;
                }
            }
            if(deleted != null) {
                edge1List.remove(deleted);
                res = true;
            }

        }



        if(!directed) {
            List<Edge> edgeList = vertices.get(ver2Id).edges;
            if (edge1List != null || edgeList != null) {

                for (Edge edge : edgeList) {
                    if (edge.destId == ver2Id) {
                        deleted2 = edge;
                        break;
                    }
                }
                if(deleted2 != null){
                    edgeList.remove(deleted2);
                }
                else  res = false;
            }
        }

        return res;
    }
    @SuppressWarnings("unchecked")
    // It's removing the vertex from the graph.
    @Override
    public Vertex removeVertex(int verId) {
        Vertex vertex = this.get(verId);
        if(vertex == null){
            return null;
        }

        Set<Map.Entry<Integer,Vertex>> entrySet = this.vertices.entrySet();
        Iterator<Map.Entry<Integer,Vertex>> iter = entrySet.iterator();

        while (iter.hasNext()){
            Map.Entry<Integer,Vertex> entry =  iter.next();
            Vertex vertex1 = entry.getValue();
            Edge deleted = null;
            for (Edge edge: vertex1.edges) {
                if(edge.destId == verId){
                    deleted = edge;
                    break;
                }
            }
            if(deleted != null){
                vertex1.edges.remove(deleted);
            }
        }

        this.vertices.remove(verId);
        return  vertex;
  }

    /**
     * It removes a vertex from the graph.
     *
     * @param label The label of the vertex to remove.
     * @return null
     */
    @Override
    public Vertex removeVertex(String label) {
        return null;
    }

    /**
     * > This function returns a new graph that contains only the vertices that have a property with the given key and
     * value
     *
     * @param key the key of the property to filter on
     * @param filter the value of the property to filter on
     * @return A new graph with vertices that have the same label and weight as the original graph.
     */
    @SuppressWarnings("unchecked")
    @Override
    public MyGraph filterVertices(String key, String filter) {

        MyGraph newGraph = new MyGraph(false);
        Iterator iterator = this.iterator();
        while (iterator.hasNext()){
            Map.Entry<Integer,Vertex> entry = (Map.Entry<Integer,Vertex>) iterator.next();
            Vertex vertex = entry.getValue();
            String val = vertex.properties.get(key);
            if(val != null) {
                if (vertex.properties.get(key).equals(filter)) {
                    Vertex newVertex = this.newVertex(vertex.getLabel(),vertex.getWeight());
                    newGraph.addVertex(newVertex);
                }
            }

        }



        return newGraph;
    }

    /**
     * This function returns the number of vertices in the graph
     *
     * @return The number of vertices in the graph.
     */
    public int getNumV(){
        return  this.vertices.size();
    }

    /**
     * Returns true if the graph is directed, false otherwise.
     *
     * @return The boolean value of the directed variable.
     */
    @Override
    public boolean isDirected() {
        return directed;
    }

    /**
     *
     *
     * @param source the source vertex
     * @param des the destination vertex
     */
    @Override
    public boolean isEdge(int source, int des) {
        return vertices.get(source).edges.contains(des);
    }

    /**
     * > This function returns the edge between the source and destination vertex
     *
     * @param source the source node of the edge
     * @param des the destination node of the edge
     * @return The edge between the source and destination.
     */
    @Override
    public Edge getEdge(int source, int des) {
        Iterator<Edge> iterator = this.iterator(source);
        while (iterator.hasNext()){
            Edge edge = iterator.next();
            if(edge.destId == des){
                return edge;
            }
        }
        return  null;
    }



    /**
     * It adds an edge to the graph.
     *
     * @param e the edge to be inserted
     */
    @Override
    public void insert(Edge e) {
        addEdge(e.sourceId,e.destId,e.edgeWeight);
    }

    /**
     * The function iterates through the vertices and for each vertex, it iterates through the edges and adds the edge
     * weight to the adjacency matrix
     *
     * @return The adjacency matrix of the graph.
     */
    @Override
    public double[][] exportMatrix() {
        Set entrySet = vertices.entrySet();

        // Obtaining an iterator for the entry set
        Iterator it = entrySet.iterator();
        int size = vertices.size();
        double[][] adjacencyMatrix = new double[size][size];
        int i = 0;
        while(it.hasNext()){
            Map.Entry me = (Map.Entry)it.next();

            Vertex vertex = (Vertex) me.getValue();
            List<Edge> edges = vertex.edges;
            for (Edge edge : edges) {

                adjacencyMatrix[i][edge.destId] = edge.edgeWeight;

            }
            ++i;
        }
        return  adjacencyMatrix;
    }

    @SuppressWarnings("unchecked")
    // It's printing the graph.
    @Override
    public void printGraph() {

        Set entrySet = vertices.entrySet();

        Iterator it = entrySet.iterator();

        while(it.hasNext()){

            Map.Entry<Integer,Vertex> entry =(Map.Entry<Integer,Vertex>) it.next();
            Vertex vertex = entry.getValue();
            Iterator edgeIterator = vertex.edges.iterator();
            System.out.print(vertex);
            while (edgeIterator.hasNext()){
                Edge edge = (Edge) edgeIterator.next();
                Vertex ver = get(edge.destId);
                System.out.print("\tDest Node: " + ver.getLabel() +",  Id: "+ ver.getID()+ ", Edge weight: " + edge.edgeWeight + "\n");
            }
        }

    }
    /**
     * This function adds a property to a vertex
     *
     * @param Id The id of the vertex you want to add the property to.
     * @param key The key of the property.
     * @param val The value of the property
     */
    public void addProperties(int Id,String key, String val){
        Vertex vertex = vertices.get(Id);
        vertex.properties.put(key,val);
    }
    /**
     * > This function returns an iterator of all the edges of a vertex
     *
     * @param id The id of the vertex you want to get the iterator for.
     * @return An iterator of the edges of the vertex with the given id.
     */
    public Iterator<Edge> iterator(int id){

        Vertex vertex =   vertices.get(id);
        return  vertex.edges.iterator();

    }

    /**
     * The function returns an iterator that iterates over the vertices of the graph
     *
     * @return The iterator is returning the set of entries in the vertices map.
     */
    public Iterator iterator(){

        Set entrySet = vertices.entrySet();
        return  entrySet.iterator();
    }

    /**
     * Given an id, return the vertex with that id.
     *
     * @param id The id of the vertex to get.
     * @return The vertex with the given id.
     */
    public Vertex get(int id){
        return vertices.get(id);
    }


}

