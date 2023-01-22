package MyGraph;

// Extending the Graph interface.
public interface DynamicGraph extends Graph{



     /**
      * Create a new vertex with the given label and weight.
      *
      * @param label The label of the vertex.
      * @param weight The weight of the edge.
      * @return A new vertex with the given label and weight.
      */
     Vertex newVertex(String label, double weight);

     /**
      * Adds a vertex to the graph
      *
      * @param vertex The vertex to add to the graph.
      */
     void addVertex(Vertex vertex);
     /**
      * Adds an edge between two vertices
      *
      * @param ver1Id The id of the first vertex.
      * @param ver2Id The id of the vertex to which the edge is to be added.
      * @param weight The weight of the edge.
      * @return boolean
      */
     boolean addEdge(int ver1Id, int  ver2Id, double weight);
     /**
      * Removes the edge between the two vertices with the given IDs
      *
      * @param ver1Id The id of the first vertex.
      * @param ver2Id The id of the vertex to which the edge is to be removed.
      * @return boolean
      */
     boolean removeEdge(int ver1Id,int  ver2Id);
     /**
      * Remove a vertex from the graph.
      *
      * @param verId The id of the vertex to be removed.
      * @return The vertex that was removed.
      */
     Vertex removeVertex(int verId);
     /**
      * "Remove the vertex with the given label from the graph."
      *
      * The function should return the vertex that was removed. If the vertex doesn't exist, the function should return
      * null
      *
      * @param label The label of the vertex to remove.
      * @return The vertex that was removed.
      */
     Vertex removeVertex(String label);
     /**
      * "Return a new graph that contains only the vertices that pass the filter."
      *
      * The filter is a string that contains a JavaScript expression. The expression is evaluated for each vertex in the
      * graph. If the expression evaluates to true, then the vertex is included in the new graph
      *
      * @param key The key to filter on.
      * @param filter The filter to apply to the vertices.
      * @return A new graph with the vertices that match the filter.
      */
     MyGraph filterVertices(String key, String filter);
     /**
      * This function returns a 2D array of doubles that represents the matrix.
      *
      * @return A 2D array of doubles.
      */
     double[][] exportMatrix();
     /**
      * It prints the graph.
      */
     void printGraph();

}
