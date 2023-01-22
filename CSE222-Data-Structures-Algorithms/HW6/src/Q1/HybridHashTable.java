package Q1;

/**
 * A generic class that implements the KWHashMap interface.
 */
public class HybridHashTable<K extends Comparable<K>,V>  implements KWHashMap<K,V>{
    private  Entry<K,V>[] table;

    private static final int Initial_Capacity = 101;
    private final double Load_Threshold = 0.8;
    private int numKeys = 0;
    private int numDeleted = 0;
    @SuppressWarnings("unchecked")
    // Initializing the table to an array of Entry objects with the size of the array being 101.
    public HybridHashTable(){
        this.table = new Entry[Initial_Capacity];
    }



    /**
     * It takes a key, hashes it, and then iterates through the linked list at the hashed position until it finds the key
     * or reaches the end of the list
     *
     * @param key The key to be searched for
     * @return The Entry object that contains the key and value.
     */
    private Entry<K,V> find(K key) throws NullPointerException{
        int pos = hashFunction(hash1(key),hash2(key),1);
        Entry<K,V> iter = table[pos];
        while (iter != null && !iter.getKey().equals(key)){
            iter = iter.next;
        }
        if(iter != null && !iter.deleteStatus){
            return iter;
        }
        else  return null;
    }


    /**
     * If the key is found, return the value. Otherwise, return null
     *
     * @param key The key to search for.
     * @return The value of the entry.
     */
    @Override
    public V get(K key) throws NullPointerException {
        Entry<K,V> entry = find(key);
        if(entry != null) return  entry.getValue();
        return null;
    }

    /**
     * It checks if the number of keys is 0.
     *
     * @return The number of keys in the tree.
     */
    @Override
    public boolean isEmpty() {
        return numKeys ==0;
    }


    /**
     * The function first checks if the key is already in the table. If it is, it updates the value and returns the old
     * value. If the key is not in the table, it adds the key-value pair to the table and returns null
     *
     * @param key The key to insert into the hash table.
     * @param value the value to be inserted into the hash table
     * @return The old value of the key.
     */
    @Override
    public V put(K key, V value) throws NullPointerException {
        int hash1 = hash1(key);
        int hash2 = hash2(key);
        int i =1;
        int index = hashFunction(hash1,hash2,i);

            while (table[index] != null){
                if(table[index].getKey().equals(key) && !table[index].deleteStatus){
                    V oldVal = table[index].getValue();
                    table[index].setValue(value);
                    return oldVal;
                }
                index = hashFunction(hash1,hash2,i);
                ++i;
                if(index < 0 ) index = index+table.length;
            }
        table[index] = new Entry<>(key,value);
        table[index].hashCode = index;
        ++numKeys;
        Entry<K,V> iter = table[hashFunction(hash1,hash2,1)];

        if( hashFunction(hash1,hash2,1)!= index){
            if(iter != null){
                while (iter.next!=null){
                    iter = iter.next;
                }
            }
            iter.next = table[index];
        }

        double loadFactor = (double) (numKeys + numDeleted) / table.length;
        if(loadFactor > Load_Threshold) rehash();
        return null;
    }


    /**
     * It creates a new hash table with double the size of the current hash table and rehashes all the elements in the
     * current hash table into the new hash table.
     */

    private void rehash(){

        HybridHashTable<K,V> newHashTable = new HybridHashTable<>();
        newHashTable.table = new Entry[table.length*2+1];

        for (Entry<K,V> entry: table) {
            if(entry != null){
                newHashTable.put(entry.getKey(),entry.getValue());
            }
        }
        this.clone(newHashTable);

    }

    /**
     * This function is used to clone the current hash table to a new hash table
     *
     * @param newHashTable The new hash table that we are cloning.
     */
    private void clone(HybridHashTable<K,V> newHashTable) {

        this.table = newHashTable.table;
        this.numKeys = newHashTable.numKeys;


    }

    /**
     * If the key is found, the value is returned and the entry is deleted
     *
     * @param key The key of the entry to be removed.
     * @return The value of the key that was removed.
     */
    @Override
    public V remove(K key) throws  NullPointerException{

        Entry<K,V> entry = find(key);
        if(entry != null){

            V oldValue = entry.getValue();
            if(entry.next != null){

                entry.setValue(entry.next.getValue());
                entry.setKey(entry.next.getKey());
                entry.next = entry.next.next;
            }
            else entry.deleteStatus = true;
            ++numDeleted;
            return oldValue;
        }

        return null;
    }

    /**
     * The size of the hash table is the number of keys minus the number of deleted keys.
     *
     * @return The number of keys in the table.
     */
    @Override
    public int size() {
        return numKeys - numDeleted;
    }

    /**
     * A private static class that is used to store key-value pairs.
     */
    private  static class Entry<K,V>{
        private K key;
        private V value;
        private Entry<K,V> next;

        boolean deleteStatus;
        int hashCode ;

        // The constructor of the Entry class. It is initializing the key, value and next of the Entry class.
        public Entry(K key,V value) {
            this.key = key;
            this.value = value;
            this.next = null;
        }

        /**
         * This function returns the key of the entry
         *
         * @return The key of the node.
         */
        public K getKey() {
            return key;
        }

        /**
         * > Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key
         *
         * @return The value of the key-value pair.
         */
        public V getValue() {
            return value;
        }



        /**
         * This function sets the key of the node to the key passed in as a parameter
         *
         * @param key The key of the node.
         */
        private void setKey(K key) {
            this.key = key;
        }

        /**
         * This function sets the value of the node to the value passed in as a parameter
         *
         * @param value The value of the node.
         */
        public void setValue(V value) {
            this.value = value;
        }

        /**
         * > Sets the hashCode of the object to the given hashCode
         *
         * @param hashCode The hash code of the object.
         */
        private   void  setHashCode(int hashCode){
            this.hashCode = hashCode;
        }

        /**
         * > This function returns the hash code of the object
         *
         * @return The hashCode of the object.
         */
        private  int getHashCode(){
            return hashCode;
        }



        /**
         * The function takes a node and returns a string representation of the node
         *
         * @return The hashcode of the node, the key of the node, and the hashcode of the next node.
         */
        @Override
        public String toString(){
            StringBuilder builder = new StringBuilder();
            String str;
            if(next != null){
                str = Integer.toString(next.getHashCode());
            }
            else str = "null";
            builder.append(String.format("%-20d %-20d %-20s\n",getHashCode(),getKey(), str));

            return builder.toString();

        }

    }

    /**
     * The hash function takes a key and returns an index in the range [0, table.length - 1]
     *
     * @param key the key to be hashed
     * @return The hash value of the key.
     */
    private int hash1(K key){
        return (Integer) key % table.length;
    }

    /**
     * It returns the prime number that is less than the load threshold times the length of the table.
     *
     * @param key the key to be hashed
     * @return The hash function is returning the index of the key in the table.
     */
    private int hash2(K key){
        int primeNumber = primeNumber((int)(Load_Threshold * table.length));
        return primeNumber - ((Integer) key % primeNumber);
    }


    /**
     * The hash function is a linear function of the form: (hash1 + (i * hash2)) % table.length, where i is the number of
     * collisions that have occurred.
     *
     * @param hash1 The first hash function.
     * @param hash2 This is the second hash function. It's a prime number that's less than the size of the table.
     * @param i the number of times we've called the hash function
     * @return The index of the array where the value is stored.
     */
    private int hashFunction(int hash1, int hash2,int i){

        return  (hash1 + (i * hash2))  % table.length;

    }




    /**
     * It returns the largest prime number that is less than or equal to the input number.
     *
     * @param max the maximum number of the prime number
     * @return The largest prime number that is less than or equal to the input number.
     */
    private int primeNumber(Integer max){
        int flag =0 ;
        if(max == 3) return  2;
        for(int i = max ; i>0 ; -- i){
            for(int j = 2 ; j < i ; ++j){
                if(i % j == 0){
                    flag = 1;
                    j =i;
                }
            }
            if(flag == 0){
                return i;
            }
            flag = 0;
        }
            return  -1;
    }






    /**
     * It prints the hash table in a readable format.
     *
     * @return The string representation of the hash table.
     */
    @Override
    public String toString(){
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(String.format("\n%-20s %-20s %-20s\n","Hash Value","Key","Next"));
        for (Entry<K,V> entry : table) {
            if(entry != null){
                stringBuilder.append(entry);
            }
        }
        return stringBuilder.toString();
    }




}
