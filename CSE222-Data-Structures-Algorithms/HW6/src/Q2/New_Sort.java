package Q2;

// A generic class that extends the Comparable interface.
public class New_Sort<T extends Comparable<? super T>> {
        static int[] max_min = new int[2];

    /**
     * Sort the array from index 0 to index array.length-1
     *
     * @param array the array to be sorted
     */
    public static <T extends Comparable<? super T>> void sort(T[] array){

        sort(array,0,array.length-1);

    }

    /**
     * It takes an array, and two indexes, and swaps the minimum and maximum values in the array between those two indexes
     *
     * @param array the array to be sorted
     * @param head the index of the first element in the array
     * @param tail the last index of the array
     * @return The array is being returned.
     */
    private static <T extends Comparable<? super T>> T[] sort(T[] array, int head, int tail){
        if(head >tail)
            return array;

        max_min = minMaxFinder(array, head, tail);
        T temp = array[head];
        array[head] = array[max_min[0]];
        array[max_min[0]] = temp;

        temp = array[tail];
        array[tail] =array[max_min[1]];
        array[max_min[1]] = temp;
        return  sort(array, head+1, tail-1);
    }

    /**
     * If the array is of size 1, return the index of the only element in the array. Otherwise, find the min and max of the
     * left and right halves of the array, and return the min and max of those four values
     *
     * @param array the array we're searching through
     * @param head the index of the first element in the array
     * @param tail the last index of the array
     * @return The index of the min and max values in the array.
     */
    private static <T extends Comparable<? super T>> int[] minMaxFinder(T[] array, int head, int tail){

       if(head< tail){

               int mid = (head+ tail) /2 ;

               int[] maxMin_left = minMaxFinder(array,head,mid);
               int[] maxMin_right = minMaxFinder(array,mid+1,tail);
               return maxMin(array, maxMin_left, maxMin_right);
       }

       return new int[]{tail,tail};
    }

    /**
     * It takes in an array of type T, and two arrays of ints, and returns an array of ints
     *
     * @param array the array to be searched
     * @param arrayLeft the array of the left side of the array
     * @param arrayRight the right half of the array
     * @return The index of the max and min values in the array.
     */
    private  static<T extends Comparable<? super T>> int[] maxMin(T[] array, int[] arrayLeft, int[]arrayRight){
            int[] indexis = new int[2];

            if(arrayLeft[0]< arrayRight[0] ){
                    indexis[0] = arrayLeft[0];
            }
            else indexis[0] = arrayRight[0];
            if(arrayLeft[1] > arrayRight[1] ){
                    indexis[1] = arrayLeft[1];
            }
            else indexis[1] = arrayRight[1];
            return  indexis;
    }



}
