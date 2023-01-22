package MyGraph;

public class Edge implements Comparable<Edge>{
    // A constructor.
    public Edge(double weight,int destId,int sourceId){
        this.edgeWeight = weight;
        this.destId = destId;
        this.sourceId = sourceId;
    }
    public double edgeWeight;
    public int destId;
    public int sourceId;

    /**
     * The compareTo() method returns a negative integer, zero, or a positive integer as this object is less than, equal
     * to, or greater than the specified object
     *
     * @param o The edge to be compared to.
     * @return The difference between the two weights.
     */
    @Override
    public int compareTo(Edge o) {
        int res ;
         if(this.edgeWeight > o.edgeWeight){
             res = 1;
         }
        else if(this.edgeWeight < o.edgeWeight){
            res = -1;
        }
        else res = 0;
        return res;
    }

    /**
     * The clone() method creates a new object with the same values as the original object
     *
     * @return A new Edge object with the same values as the original.
     */
    public Object clone(){
        return new Edge(this.edgeWeight,this.destId,this.sourceId);
    }
}