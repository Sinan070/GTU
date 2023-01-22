package Utilites;

import java.util.*;


/* This Custom SKİPLIS is implemented using BOOK IMPLEMENTATION*/
public class CustomSkipList<E extends  Comparable<E>> implements Iterable<E> {

    // The head of the list.
    public Entry<E> head;

    private int maxLevel;
    private int size;

    // The default level of the skip list.
    private static int DEFAULT_LEVEL= 2;

    private int maxCap;
    private int counter=1;
    private Random random = new Random();
    private int leftCounter=1;
    static final int MIN = Integer.MIN_VALUE;
    @SuppressWarnings({ "unchecked", "rawtypes" })
    // The constructor of the class.
    public CustomSkipList(){
        size = 0;
        maxLevel = DEFAULT_LEVEL;
        maxCap = computeMaxCap(maxLevel);
        head = new Entry(maxLevel, MIN);
    }

    @SuppressWarnings("unchecked")
    // Searching for the target in the skip list.
    private Entry<E>[] search(E target){
        Entry<E>[] pred = (Entry<E>[]) new Entry[maxLevel];
        Entry<E> current = head;
        for(int i = current.links.length - 1; i >= 0; i--){
            while(current.links[i] != null
                    && current.links[i].data.compareTo(target) < 0){
                if(i == 0){
                    ++leftCounter;
                }
                current = current.links[i];

            }
            pred[i] = current;
        }

        return pred;
    }


    /**
     * It searches for the target in the skip list.
     *
     * @param target the element we are searching for
     * @return The data of the node that is being searched for.
     */
    public E find(E target){
        Entry<E>[] pred = search(target);
        if(pred[0].links != null &&
                pred[0].links[0].data.compareTo(target) == 0){
            return pred[0].links[0].data;
        } else {
            return null;
        }
    }

    /**
     * We create a new node with the item we want to add, and then we traverse the list to find the node that should be
     * before the new node, and then we add the new node to the list
     *
     * @param item the item to be added
     * @return The boolean value of true.
     */
    public boolean add(E item){
        size++;
        if(size > maxCap){

            System.out.print(this);
            System.out.println();
            levelUp();
            maxCap = computeMaxCap(maxLevel);
        }
        Entry<E>[] pred = search(item);
        Entry<E> newNode = new Entry<>(randomize(item), item);

        for(int i = 0; i < newNode.links.length; i++){
            newNode.links[i] = pred[i].links[i];
            pred[i].links[i] = newNode;
        }
        return true;
    }



    /**
     * We add a new link to the head, and then we add a new link to every node in the list
     */
    private void levelUp(){
        ++maxLevel;
        Entry<E> current = head;
        int length = current.links.length;
        current.links = Arrays.copyOf(current.links,length+1);
        head.links[length] = current.links[length-1];
        for(int i = length -1; i >= 1; i--){
            while(current.links[i] != null) {
                current = current.links[i];
                Entry<E> temp = current.links[i];
                current.links = Arrays.copyOf(current.links, current.links.length+1);
                current.links[current.links.length - 1] = temp;

            }
        }

    }

    /**
     * This function returns the previous entry of the item that is passed in
     *
     * @param item the item to be searched for
     * @return The previous entry of the item.
     */
    private Entry<E>[] getPrev(E item){
        return search(item);
    }
    /**
     * It generates a random number between 1 and the total distance of the item, and returns the number of links that the
     * item will have
     *
     * @param item the item to be inserted
     * @return The number of links to be created for the item.
     */
    private int randomize(E item){
        int totalDistance = findTotalDistance(item);
        this.leftCounter = 1;
        int []array = new int[10];
        for(int i = 0 ; i <totalDistance ; ++i){
            array[i] = 1;
        }
        int rnd;
        int linksNum = 0;
        do {
            ++linksNum;
            rnd = random.nextInt(array.length-1);
        }while (array[rnd] == 1 && linksNum < maxLevel);
        //System.out.print(linksNum+" "+ maxLevel);
       /* if(linksNum == maxLevel){
            --linksNum;
        }*/
        return linksNum ;
    }

    /**
     * > The function computes the maximum capacity of the array at a given level
     *
     * @param level the level of the node
     * @return The max capacity of the array.
     */
    private int computeMaxCap(int level){
        //int result = (int) Math.pow(10,counter);
        int result = 10*counter;
        ++counter;
         return result;
    }


    /**
     * The function finds the total distance of the item from the head and tail of the list
     *
     * @param item the item whose distance we want to find
     * @return The total distance of the item from the head.
     */
    private int findTotalDistance(E item){
        Entry<E>[] pred = getPrev(item);
        int maxLevel = pred.length;
        int rightCounter = 0;
        Entry<E> iter;
        if(pred[0]!= null){
            iter=   pred[0].links[0];
        }
        else iter = null;
        while (iter != null){
            if(iter.links.length<2){
                ++rightCounter;
            }
            else break;
            iter = iter.links[0];
        }
        leftCounter /=2;
        ++leftCounter;
        return leftCounter+ rightCounter ;
    }


    /**
     * A generic class that implements the Comparable interface.
     */
    protected static class Entry<E extends  Comparable<E>> implements Comparable<Entry<E>>{
        Entry<E>[] links;
        E data;
        @SuppressWarnings("unchecked")
        // A constructor for the Entry class.
        public  Entry(int level , E data){
            links = (Entry<E>[]) new Entry[level];
            this.data = data;
        }


        /**
         * The compareTo function compares the data of the current object to the data of the object passed in as a
         * parameter
         *
         * @param o The object to be compared.
         * @return The data of the entry.
         */
        @Override
        public int compareTo(Entry<E> o) {
            return this.data.compareTo(o.data);
        }

        /**
         * The toString() function returns a string representation of the data in the node
         *
         * @return The data and the number of links.
         */
        @Override
        public String toString() {
            return (data.toString() + " |" + links.length + "|");
        }
    }



    /**
     * Returns an iterator over the elements in this list in proper sequence.
     *
     * @return An iterator of type E.
     */
    @Override
    public Iterator<E> iterator() throws NullPointerException{
        /* to Do*/
        return null;
    }
    /**
     * It traverses the list from head to tail, and prints out the value of each node
     *
     * @return The toString method is returning a string representation of the SkipList.
     */
    @Override
    public String toString() {

        if(size == 0)
            return "Empty";
        StringBuilder sc = new StringBuilder();
        Entry itr = head;
        sc.append("Head: " + maxLevel);
        int lineMaker = 0;
        while(itr.links[0] != null){
            itr = itr.links[0];
            sc.append(" --> " + itr.toString());
            lineMaker++;
            if(lineMaker == 10){
                sc.append("\n");
                lineMaker = 0;
            }
        }
        return sc.toString();
    }
}
