public class Q1 {

    /**
     * Given a mainString and a subString, find the index of the first occurrence of the subString in the mainString
     *
     * @param mainString The string in which we are searching for the subString
     * @param subString The string to be searched for
     * @param index The index of the mainString where the search starts.
     * @return The index of the substring in the main string.
     */
    public int findIndexedSubString(String mainString, String subString,int index) throws StackOverflowError{
        if(mainString == null || subString == null){
            throw new NullPointerException("STRING IS NULL");
        }
        int[] flag = new int[1];
        return findIndexedSubString(mainString,subString,index-1,0,flag);
    }

    /**
     * Given a string, find the index of the first occurrence of a substring
     *
     * @param mainString The string to search in.
     * @param subString The string to be searched for.
     * @param index The index of the string to be searched.
     * @param foundedIndex The index of the subString that we are looking for.
     * @param flag an array of size 1 that is used to indicate whether the substring has been found or not.
     * @return The index of the first occurrence of the substring in the main string.
     */
    private int findIndexedSubString(String mainString, String subString,int index,int foundedIndex,int[]flag){

        int startindex = mainString.indexOf(subString);
        int endIndex = startindex + subString.length();
        if(startindex == -1){
            flag[0] = 1;
            return -1;
        }
        if(index == foundedIndex){
            return  startindex;
        }

        int result =  endIndex + findIndexedSubString(mainString.substring(endIndex), subString, index, ++foundedIndex,flag);

        if(flag[0] == 1) result =   -1;
        return result;


    }
}
