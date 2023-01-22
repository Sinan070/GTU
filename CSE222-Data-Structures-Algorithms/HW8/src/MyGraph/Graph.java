package MyGraph;

import java.util.Iterator;

public interface Graph {

    /**
     * Returns the number of vertices in the graph.
     *
     * @return The number of vertices in the graph.
     */
    int getNumV();
    /**
     * Returns true if the graph is directed, false otherwise
     *
     * @return A boolean value.
     */
    boolean isDirected();
    /**
     * Insert an edge into the graph
     *
     * @param e The edge to be inserted.
     */
    void insert(Edge e);
    /**
     * Returns true if there is an edge from node source to node des, false otherwise
     *
     * @param source The source vertex of the edge.
     * @param des The destination vertex.
     * @return boolean
     */
    boolean isEdge(int source , int des);
    /**
     * It returns the edge between the source and destination.
     *
     * @param source The source vertex of the edge.
     * @param des The destination vertex of the edge.
     * @return The edge between the source and destination.
     */
    Edge getEdge(int source , int des);

}
