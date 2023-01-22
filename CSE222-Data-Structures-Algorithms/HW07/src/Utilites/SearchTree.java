package Utilites;

// Creating a generic interface that is a search tree.
public interface SearchTree<E extends Comparable<E>> {

    /**
     * Adds the specified element to the end of the list.
     *
     * @param data The data to be added to the list.
     * @return A boolean value.
     */
    boolean add(E data);
    /**
     * Returns true if the list contains the given data, false otherwise.
     *
     * @param data The data to search for in the tree.
     * @return A boolean value.
     */
    /**
     * Returns true if the list contains the given data, false otherwise.
     *
     * @param data The data to search for in the tree.
     * @return A boolean value.
     */
    boolean contains(E data);
    /**
     * Find the node with the given data and return it.
     *
     * @param data The data to be searched for.
     * @return The data that is being returned is the data that is being searched for.
     */
    E find(E data);
    /**
     * Delete the first occurrence of data from the list.
     *
     * @param data The data to be deleted from the tree.
     * @return The data that was deleted.
     */
    E delete(E data);
    /**
     * Removes the first occurrence of the specified element from this list, if it is present
     *
     * @param data The data to be removed from the list.
     * @return A boolean value.
     */
    boolean remove(E data);


}
