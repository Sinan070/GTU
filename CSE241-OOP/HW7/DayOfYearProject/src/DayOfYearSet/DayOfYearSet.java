package DayOfYearSet;

import java.util.ArrayList;

/**
 *  DayOfYearSet class is like set of day of Year. It has inner Day of Year Class. It stores the date through
 * DayofYear array.
 */
public class DayOfYearSet {


    private DayofYear[] DofSet;

    private boolean flag = true;

    /**
     *  Inner class. It stores the date.
     */
    public static class DayofYear{

        /**
         * This constructor check the date then set the date.
         * @param day a value of day
         * @param month a value of month
         */
        public DayofYear(final int day,final int month){
            if(DayOfYearValidator.dateValidate(day,month)){
                this.setDay(day);
                this.setMonth(month);

            }


        }


        private int day;
        private int month;


        /**
         *
         * @return a day of date
         */
        public int getDay(){ return day;}

        /**
         *
         * @return a Month of date
         */
        public int getMonth(){return month;}

        /**
         *
         * Set the  day of date
         */
        private void setDay(final int day){this.day = day;}

        /**
         *
         * Set the month of date
         */
        private void setMonth(final int month){this.month = month;}
    }


    /**
     * Default DayOfYearSet constructor.
     * It creates DayOfYear array then set the initial  number dates in Set zero.
     * It increase the total set number 1 for every DayOfYearSet instance.
     */
    public DayOfYearSet(){
        DofSet = new DayofYear[2];
        _size =0;
        ++_totalDofSet ;
    }

    /**
     * This constructor takes DayOfYearArray list.
     * It increase the total set number 1 for every DayOfYearSet instance.
     * @param set a ArrayList of DayofYear
     */
    public DayOfYearSet(final ArrayList<DayofYear> set){
        this._size = set.size();
        ++_totalDofSet;
        this.DofSet =  set.toArray(new DayofYear[set.size()]);

    }


    /**
     * The function that add dates to DayOfYearset.
     * @param date a date of year
     */
    public void add(final DayofYear date){
        if(!checkDate(date.getDay(), date.getMonth())) {

            if (_size == DofSet.length || _size < DofSet.length / 4) {
                _resizeArray();
            }
            DofSet[_size] = date;
            ++_size;
        }
    }

    /**
     * Remove date from DayOfYearSet
     * @param date a date of year
     */
    public void remove(final DayofYear date){

        for(int i =0 ; i < _size ; ++i){
            if(DofSet[i].getDay() == date.getDay() && DofSet[i].getMonth() == date.month ){
                DofSet[i] = null;
                --_size;
                for(int j =i ; j < _size ; ++j){
                    DofSet[j] = DofSet[j+1];
                }

                return;
            }
        }
    }


    /**
     * This function is overidden. It Compares two DayOfYearSet.
     * @param obj DayOfYearSet object to be compared.
     * @return retunr DateOfYearSet object.
     */
    @Override
    public boolean equals(final Object obj){

        if(obj == this) return  true;
        if(!(obj instanceof  DayOfYearSet)) return  false;

        DayOfYearSet set = (DayOfYearSet) obj;
        if(set._size != this._size) return  false;
        for(int i = 0 ; i < _size ; ++i){
            if(!((set.DofSet[i].getDay() == DofSet[i].getDay()) && (set.DofSet[i].getMonth() == DofSet[i].getMonth()))){
                return  false;
            }
        }
        return  true;
    }

    /**
     * Static function. Find total set number alive.
     * @return a value of total set alive.
     */
    public static int totalSet(){

        return  _totalDofSet;
    }

    private int _size;
    private static int _totalDofSet =0;


    /**
     * Private function that find if the object already exist in DayOfYearSet object.
     * @param day a day of date
     * @param month a month of date
     * @return truth value
     */
    private boolean checkDate(final int day ,final int month){

        for(int i = 0; i<_size; ++i){
            if(DofSet[i].getDay() == day && DofSet[i].getMonth() == month) {return true;}

        }
        return  false;

    }

    /**
     * Find Number of Date in Set.
     * @return  a number of date in Set.
     */
    public int size(){
        return  _size;
    }


    /**
     * Helper function that creates dynamic array.
     * It is unuseful. There is already method in java to create dynamic array.
     */
    private void _resizeArray(){
        if(_size == DofSet.length){
            DayofYear[]  _temp ;
            _temp = new DayofYear[_size*2];

            for(int i = 0 ; i< _size ; ++i){
                _temp[i] = DofSet[i];
            }
            DofSet = null;
            DofSet = _temp;
        }
        else if(_size < DofSet.length/4){
            DayofYear[]  _temp;
            _temp = new DayofYear[_size/2];
            for(int i = 0 ; i< _size ; ++i){
                _temp[i] = DofSet[i];
            }
            DofSet = null;
            DofSet = _temp;

        }
    }

    /**
     * Find intersect set of Two DayOfYearSet object.
     * @param set a DayOfYear object to be instersected.
     * @return a DayOfYearSet Object.
     */
    public DayOfYearSet intersect(final DayOfYearSet set){
        boolean status = false;
        DayOfYearSet temp = new DayOfYearSet();

        for(int i = 0; i < _size ; ++i , status = false) {

            for(int j =0 ; j< set._size && !status; ++j) {
                if((DofSet[i].getDay() == set.DofSet[j].getDay()) && (DofSet[i].getMonth() == set.DofSet[j].getMonth() )){
                    status = true;
                    temp.add(new DayofYear(DofSet[i].getDay() , DofSet[i].getMonth()));
                }

            }
        }
        return  temp;
    }

    /**
     * Find union set of Two DayOfYearSet object.
     * @param set a DayOfYear object to be unified.
     * @return a DayOfYearSet Object.
     */
    public DayOfYearSet union(final DayOfYearSet set){

        DayOfYearSet temp = new DayOfYearSet();

        for(int i = 0; i < _size ; ++i)     temp.add(new DayofYear(DofSet[i].getDay() , DofSet[i].getMonth()));

        for(int i =0 ; i < set._size ; ++i)     temp.add(new DayofYear(set.DofSet[i].getDay() , set.DofSet[i].getMonth()));

        return  temp;

    }

    /**
     * Find complement set of Two DayOfYearSet object.
     * @return a DayOfYearSet Object.
     */
    public  DayOfYearSet complement(){

        DayOfYearSet temp = new DayOfYearSet();

        for(int i = 1 ; i <=12 ; ++i){
            for(int j = 1 ; j<= 31 ; ++j){
                if( DayOfYearValidator.dateValidate(j , i) && ( !checkDate(j , i))) {
                    temp.add(new DayofYear(j,i));
                };
            }
        }


        return temp;
    }

    /**
     * Find diffrence set of Two DayOfYearSet object.
     * @param set a DayOfYear object to be diffired.
     * @return a DayOfYearSet Object.
     */
    public DayOfYearSet difference(final DayOfYearSet set){
        boolean status = false;
        DayOfYearSet temp = new DayOfYearSet();

        for(int i = 0; i < _size ; ++i , status = false) {

            for(int j =0 ; j< set._size && !status; ++j) {
                if((DofSet[i].getDay() == set.DofSet[j].getDay()) && (DofSet[i].getMonth() == set.DofSet[j].getMonth() )) {
                    status = true;

                }
            }
            if(status == false) temp.add(new DayofYear(DofSet[i].getDay() , DofSet[i].getMonth()));
        }
        return  temp;


    }


    /**
     * Overidden finalize method to increase number of total set alive
     */
    @Override
    protected void finalize(){--_totalDofSet;};


    /**
     * Overriden to String. It prints DayOfYearSet details.
     * @return a detail of Object.
     */
    @Override
    public String toString() {
        String temp = new String();

        if(this.size() == 0)    {temp = "THE SET IS EMPTY";}

        else {
            int i ;
            temp ="(DAY , MONTH)\n";
            for (i = 0; i < _size; ++i) {
                temp += ("(" + DofSet[i].getDay() + "  " + DofSet[i].getMonth() + ") , ");
                if(i % 20 ==0) temp += "\n";
            }
        }
        return  temp;
    }
}
