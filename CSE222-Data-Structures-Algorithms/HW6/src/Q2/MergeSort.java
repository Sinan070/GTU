package Q2;

/**
 * MergeSort is a class that sorts an array of integers using the merge sort algorithm.
 */
public class MergeSort{

/**
 * If the array has more than one element, split the array into two halves, sort each half, and merge the two halves into a
 * single sorted array
 *
 * @param array The array to be sorted.
 */
public static <T extends Comparable<? super T>> void sort(T[] array) throws ClassCastException{
        if(array.length > 1){
            int halfSize = array.length/2;
            T[] leftSub= (T[]) new Comparable[halfSize];
            T[] rightSub = (T[]) new Comparable[array.length - halfSize];
            System.arraycopy(array,0,leftSub,0,halfSize);
            System.arraycopy(array,halfSize,rightSub,0,array.length- halfSize);
            sort(leftSub);
            sort(rightSub);
            merge(array,leftSub,rightSub);
        }
}

/**
 * The function takes in an array, and two subarrays, and merges the subarrays into the array
 *
 * @param array the array to be sorted
 * @param leftSub the left subarray
 * @param rightSub the right subarray
 */
private static <T extends Comparable<? super T>> void merge(T[]array,T[] leftSub, T[] rightSub){
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < leftSub.length && j < rightSub.length){
        if(leftSub[i].compareTo(rightSub[j]) <0){
            array[k++] = leftSub[i++];
        }

        else{
            array[k++] = rightSub[j++];
        }
    }

    while (i < leftSub.length ){
        array[k++] = leftSub[i++];
    }


    while (j < rightSub.length ){
        array[k++] = rightSub[j++];
    }

}


}
