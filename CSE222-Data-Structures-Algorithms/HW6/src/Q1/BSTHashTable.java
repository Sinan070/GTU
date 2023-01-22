package Q1;

public class BSTHashTable<K extends Comparable<K>,V> implements KWHashMap<K,V>{


    // Creating a table of BinarySearchTree.
    private BinarySearchTree<Entry<K,V>>[] table;
    private  static final int Initial_Capacity = 11;
    // A constant that is used to determine when to rehash the table.
    private static final double Load_Threshold = 3.0;
    private int numKeys;


    // Creating a table of BinarySearchTree.
    public BSTHashTable(){
        this.table = new BinarySearchTree[Initial_Capacity];
    }

    /**
     * For each entry in the table, insert it into the new table
     */
    private void rehash(){

        BinarySearchTree<Entry<K,V>>[] newBst = new BinarySearchTree[table.length*2+1];
        int index;

        for(BinarySearchTree<Entry<K, V>> bst : table) {
            if(bst != null) {
                for(Entry<K, V> e : bst) {
                    index  = e.getKey().hashCode() % newBst.length;
                    if(index < 0) {
                        index += newBst.length;

                    }
                    if(newBst[index] == null) {
                        newBst[index] = new BinarySearchTree<Entry<K, V>>();
                    }
                    newBst[index].insert(e);
                }
            }

        }
        table = newBst;
    }







    /**
     * If the key is not in the table, return null. Otherwise, return the value associated with the key
     *
     * @param key The key to search for.
     * @return The value of the key.
     */
    @Override
    public V get(K key) throws NullPointerException{
        int index = key.hashCode() % table.length;
        if(index <0) {
            index += table.length;
        }
        if(table[index] == null){
            return null;
        }/*
        for (Entry<K,V> entry: table[index]) {
            if(entry.getKey().equals(key)){
                return entry.getValue();
            }
        }*/
        Entry<K,V> entriy = table[index].find(new Entry<>(key,null));
        if(entriy != null){
            return entriy.getValue();
        }
        return null;
    }



    /**
     * `isEmpty()` returns true if the number of keys in the tree is 0, and false otherwise
     *
     * @return The number of keys in the tree.
     */
    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }



    /**
     * If the key is already in the table, replace the value with the new value. Otherwise, add the new key/value pair to
     * the table
     *
     * @param key the key to be inserted
     * @param value the value to be associated with the specified key
     * @return The old value of the key.
     */
    @Override
    public V put(K key, V value) throws NullPointerException{
        int index = key.hashCode() % table.length;
        if(index < 0) {index += table.length;}

        if(table[index] == null) {table[index] = new BinarySearchTree<>(); };
        /*
        for (Entry<K,V> entry : table[index]) {
            if(entry.getKey().equals(key)){
                V oldValue = entry.getValue();
                entry.setValue(value);
                return oldValue;
            }
        }*/

        Entry<K,V> entry = table[index].find(new Entry<>(key,null));
        if(entry != null){
            V oldValue = entry.getValue();
            entry.setValue(value);
            return oldValue;
        }
        table[index].insert(new Entry<>(key,value));
        ++numKeys;
        if(numKeys > (Load_Threshold * table.length)){
            rehash();
        }
        return null;
    }


    /**
     * If the key is not found, return null. Otherwise, remove the entry from the tree and return the value
     *
     * @param key The key to be removed from the map.
     * @return The value of the key that was removed.
     */
    @Override
    public V remove(K key) throws NullPointerException{
        int index = key.hashCode() % table.length;

        if(index < 0) {
            index += table.length;
        }
        if(table[index] == null)	return null;
/*
        for(Entry<K, V> e :table[index]) {		//Compare the tree element to find removing element
            if(e.getKey().equals(key)) {
                table[index].delete(e);
                numKeys--;
                return e.getValue();		//If we find it returning removed key value
            }
        }*/
        Entry<K,V> entry = table[index].find(new Entry<K,V>(key,null));
        if(entry != null){
            table[index].delete(entry);
            numKeys--;
            return entry.getValue();
        }
        return null;
    }


    /**
     * Returns the number of keys in the symbol table.
     *
     * @return The number of keys in the tree.
     */
    @Override
    public int size() {
        return numKeys;
    }

    /**
     * The function iterates through the table and appends the toString() of each node to a stringBuilder
     *
     * @return The string representation of the hash table.
     */
    @Override
    public  String toString(){

        StringBuilder stringBuilder = new StringBuilder();
        for(int i = 0 ; i< table.length; ++i){
            if(table[i] != null){
                stringBuilder.append(table[i].toString());
            }
        }
        return stringBuilder.toString();
    }



}
