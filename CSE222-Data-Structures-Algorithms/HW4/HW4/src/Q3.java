import java.util.ArrayList;

public class Q3 {
    /**
     * Given an array of integers, find all combinations of integers that sum to a given value
     *
     * @param array the array to search
     * @param value The value we're looking for
     * @return An ArrayList of ArrayLists of Integers
     */
    @SuppressWarnings("unchecked")
    public ArrayList<ArrayList<Integer>> findSum(int [] array, int value) throws StackOverflowError{
        if(array == null){
            throw new NullPointerException("ARRAY IS NULL");
        }
        ArrayList<Integer> list = new ArrayList();
        ArrayList<ArrayList<Integer>> totalList = new ArrayList<>();
        findSum(array,value,0,0,0,list,totalList);
        return totalList;
    }

    /**
     * Find all the combinations of numbers in an array that sum to a value
     *
     * @param array the array to search
     * @param value The value we're trying to find a subset of.
     * @param i The index of the current element in the array.
     * @param j The current index of the array.
     * @param sum the sum of the current subarray
     * @param list The list of numbers that we are adding together.
     * @param totalList This is the list that will contain all the possible combinations of the array.
     */
    @SuppressWarnings("unchecked")
    private void findSum(int[] array , int value, int i,int j, int sum, ArrayList<Integer> list,ArrayList<ArrayList<Integer>> totalList){
        if(j> array.length-1){
            return;
        }
        sum += array[j];
        if(sum > value){
            list.clear();
            j = i++;
            sum = 0;
        }
        else{
            list.add(j);
            if((j+1) < array.length-1){
                if(array[j+1] == 0){
                    list.add(j+1);
                }
            }
        }
        if(sum == value){
            totalList.add((ArrayList<Integer>) list.clone());
            list.clear();
            j = i++;
            sum = 0;
        }
        findSum(array,value,i,++j,sum,list,totalList);
    }
}
