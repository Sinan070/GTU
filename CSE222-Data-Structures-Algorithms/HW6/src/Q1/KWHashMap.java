package Q1;

// Defining a generic interface.
public interface KWHashMap<K,V> {
    /**
     * Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
     *
     * @param key The key to search for.
     * @return The value associated with the key.
     */
    V get(K key);

    /**
     * Returns true if the stack is empty, false otherwise.
     *
     * @return A boolean value.
     */
    boolean isEmpty();

    /**
     * If the key is not present in the map, then add the key-value pair to the map and return null. If the key is present
     * in the map, then replace the value with the new value and return the old value.
     *
     * @param key The key to be stored in the map
     * @param value The value to be stored in the map.
     * @return The value of the key that was just put.
     */
    V put(K key,V value);


    /**
     * Removes the mapping for the specified key from this map if present.
     *
     * @param key The key of the element to remove from the Map.
     * @return The value of the removed node.
     */
    V remove(K key);


    /**
     * Returns the number of elements in this list.
     *
     * @return The size of the list.
     */
    int size();

    /**
     * The class Entry<K extends Comparable<K> ,V> implements Comparable<Entry<K,V>> is a generic class that implements the
     * Comparable interface
     */
    class  Entry<K extends Comparable<K> ,V> implements Comparable<Entry<K,V>>{
        private final K key;
        private V value;

        // A constructor for the Entry class.
        public Entry(K key, V value){
            this.key = key;
            this.value = value;
        }

        /**
         * > Returns the key stored in this entry
         *
         * @return The key of the node.
         */
        public  K getKey(){
            return key;
        }

        /**
         * > Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key
         *
         * @return The value of the key-value pair.
         */
        public  V getValue(){
            return value;
        }

        /**
         * It sets the value of the current entry to the value passed in as a parameter, and returns the old value
         *
         * @param value The value of the key-value pair.
         * @return The old value of the key-value pair.
         */
        public V setValue(V value){
            V oldValue = this.value;
            this.value = value;
            return oldValue;
        }

        /**
         * If the key of the entry is equal to the key of the entry passed in, return true. Otherwise, return false
         *
         * @param e the entry to be compared with this entry
         * @return The key of the entry.
         */
        public boolean equals(Entry<K,V> e) {
            if(getKey().equals(e.getKey()))
                return true;
            return false;
        }

        /**
         * The toString() method returns a string representation of the object
         *
         * @return The key and value of the node.
         */
        @Override
        public String toString(){
            StringBuilder builder = new StringBuilder();
            builder.append("{" +key+"  , "+ value+" } -> ");
            return builder.toString();
        }

        /**
         * The compareTo() method compares the key of the current entry with the key of the entry passed as an argument
         *
         * @param o The object to be compared.
         * @return The key of the entry.
         */
        @Override
        public int compareTo(Entry<K, V> o) {
            return key.compareTo(o.getKey());
        }
    }


}
