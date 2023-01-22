

/**
 * The method search() is a recursive method that takes in an array, start and end index, and a value to be searched.
 * If the value is found, it returns the index of the value. If the value is not found, it returns -1
 */
public class Q2 {
    public  int findValueBetweenTwo(int[]array,int start,int end) throws StackOverflowError{

        if(array == null){
            throw new NullPointerException("ARRAY IS NULL");
        }
        if(start > end){
            throw  new RuntimeException("START VALUE MUST BE LESS THAN END VALUE ");
        }

        else{
            return search(array,0,array.length-1,start,end,0);
        }
    }

    /**
     * Given an array of integers, find the number of integers that are between start and end (inclusive)
     *
     * @param array the array to search
     * @param left The left index of the current subarray.
     * @param right The rightmost index of the array.
     * @param start The start of the range.
     * @param end The end of the range.
     * @param number the number of elements that are within the range.
     * @return The number of elements in the array that are within the range [start, end].
     */
    private int search(int[] array,int left,int right,int start,int end,int number){
        if(left == right){
            if(array[left] >= start && array[left] <=end){
                ++number;
            }
        }
        if(left < right) {
             int mid = (right + left) / 2;
             number =search(array, left, mid, start, end,number);
             number =search(array, mid + 1, right, start, end,number);
        }
        return  number;
    }


}
