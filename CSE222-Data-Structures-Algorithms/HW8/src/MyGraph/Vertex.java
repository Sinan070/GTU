package MyGraph;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;


/**
 * A vertex is a node in a graph. It has a name, a list of edges, and a distance from the source.
 */
public class Vertex implements Comparable<Vertex>{
    private int ID = 0;
    private String label;
    private double weight;

    public List<Edge> edges;
    public HashMap<String,String> properties;

    public double edgeWeight;


    // This is a constructor. It is called when you create a new Vertex object.
    public Vertex(){
        this.edges = new LinkedList<>();
    }

     // This is a constructor. It is called when you create a new Vertex object.
     public Vertex(String label, double weight, int id) {
        this.ID = id;
        this.label = new String(label);
        this.weight =weight;
        this.properties = new HashMap<>();
        this.edges = new LinkedList<>();
    }



    /**
     * This function returns the label of the node
     *
     * @return The label of the card.
     */
    public String getLabel(){
        return label;
    }
    /**
     * This function returns the ID of the current object
     *
     * @return The ID of the student.
     */
    public int getID(){
        return ID;
    }

    /**
     * This function returns the weight of the object.
     *
     * @return The weight of the object.
     */
    public double getWeight(){
        return weight;
    }

    /**
     * If the ID of the vertex is the same as the ID of the vertex passed in, then the two vertices are equal
     *
     * @param obj The object to compare with.
     * @return The hashcode of the vertex.
     */
    @Override
    public boolean equals(Object obj) {
        Vertex vertex = (Vertex) obj;
        if(this.getID() == vertex.getID()){
            return true;
        }
        return false;
    }
    /**
     * The clone() method creates a new object that is a copy of the original object
     *
     * @return A new Vertex object with the same label, weight, and ID as the original.
     */
    public Object clone()
    {
       return new Vertex(this.label, this.weight,this.ID);
    }

    /**
     * The toString() function is a function that is called when you try to print a Node object
     *
     * @return The label, id, and weight of the node.
     */
    @Override
    public String toString(){
        StringBuilder builder = new StringBuilder();

        builder.append("Source Node ");
        builder.append(this.getLabel());
        builder.append(",  Id: ");
        builder.append(this.getID() );
        builder.append(",  Boosted Val: ");
        builder.append(this.getWeight() );
        builder.append("-->\n");

        return  builder.toString();
    }

    /**
     * The compareTo function is used to compare two vertices and return a value based on the comparison
     *
     * @param o The vertex to compare to
     * @return The difference between the two edge weights.
     */
    @Override
    public int compareTo(Vertex o) {
        int res;
        if(this.edgeWeight > o.edgeWeight){
            res = 1;
        }
        else if(this.edgeWeight < o.edgeWeight){
            res = -1;
        }
        else res = 0;
        return res;
    }
}
