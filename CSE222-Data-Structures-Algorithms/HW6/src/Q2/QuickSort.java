package Q2;

/**
 * A class that implements the QuickSort algorithm.
 */
public class QuickSort{

    // This is the quick sort algorithm.
    public  static <T extends Comparable<? super T>> void sort(T[] array){
        quickSort(array,0,array.length-1);
    }

    private static <T extends Comparable<? super T>> void quickSort(T[] array, int first, int last){
        if(first <last){
            int pivot = partitioning(array,first, last);
            quickSort(array,first,pivot-1);
            quickSort(array,pivot+1,last);
        }

    }

    /**
     * The function takes an array, a first index, and a last index. It then partitions the array into two parts, one part
     * with elements less than or equal to the pivot, and the other part with elements greater than the pivot. The function
     * returns the index of the pivot
     *
     * @param array the array to be sorted
     * @param first the first index of the array
     * @param last the last index of the array
     * @return The index of the pivot element.
     */
    private static <T extends Comparable<? super T>> int  partitioning(T[] array, int first, int last) {
        T pivot = array[first];
        int right = first+1;
        int left = first;
        do{
            if(array[right].compareTo(pivot) <=0){
                ++left;
                T temp = array[right];
                array[right] = array[left];
                array[left] = temp;
            }
            ++right;
        }while (right <= last);

        T temp  = array[first];
        array[first] = array[left];
        array[left] = temp;
        return left;
    }




    }
