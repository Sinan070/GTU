package DayOfYearSet;

/**
 * DayOfYearValidator class is used for Date Validation
 */
public  class DayOfYearValidator {
    /**
     * This dateValidate function check the Given date and return boolean.
     * @param day the day of the date
     * @param month the month of the date
     * @return truth value
     */
    public static boolean dateValidate(final int day, final int month) {
        boolean status = true;

        if(day <1 || month >12 || month<1){
            status = false;
        }
        else if( (month == 4 || month == 6 || month == 9 || month ==11) && day >30){
            status = false;
        }
        else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ) && day>31){
            status = false;
        }
        else if(month == 2 && day >28){
            status = false;
        }



        return  status;
    }



}
