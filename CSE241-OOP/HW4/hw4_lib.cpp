#include "hw4.h"
#include <iostream>

/* Day of Year Set Properties*/

/* Default DayofYearSet Constructor*/
DayofYearSet::DayofYearSet() : _capacity(1), _used(0)   {  create();  };

/* Constructor that gets date and month value*/
DayofYearSet::DayofYearSet(int date ,int month) : _capacity(1), _used(0){
    create();
    add(date,month);
}


/* DayofYear Set constructor that gets DayofYear Vector*/
DayofYearSet::DayofYearSet(std::vector<DayofYear>& days){
   
    _capacity=days.size();
    _used=days.size();
    create();
    for(int i = 0 ; i<days.size(); ++i){
        this->dayofYear[i].setDate(days[i].getDate());
        this->dayofYear[i].setMonth(days[i].getMonth());

    }

    
}

/* Copy Constructor*/
DayofYearSet::DayofYearSet(const DayofYearSet &year) :  _capacity(year._capacity), _used(year._used) {
       
    this->create();
        
    for(int i =0 ; i< _used ; ++i){
        this->dayofYear[i].setDate(year[i].getDate());
        this->dayofYear[i].setMonth(year[i].getMonth());

    }
}

/* DayofYearSet destructor*/
DayofYearSet::~DayofYearSet(){
    //delete dayofYear;

}


bool DayofYearSet::findDay(const int  date, const int month) const{
    
    bool status = true;
    int size =this->size((*this));
    for(int i =0; i< size; ++i){
        if((*this)[i].getDate()== date && (*this)[i].getMonth()== month ){
            status =false;
            i= size;
            
        }
    }

    return status;
}
    
bool DayofYearSet::checkDay(const int  date, const int month) const{


    int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(months[month]>= date && date>=1 && month <=12 && month >=1){
        return true;
    }
    return false;

}



/* Add element to DayofYearSet dynamically*/
void DayofYearSet::add(const int date, const int month){
    
    

    if(findDay(date,month) == true){
        resize();
        
        dayofYear[_used].setDate(date);
        dayofYear[_used++].setMonth(month);
        //std::cout <<"Day is added\n";

    }
    //else std::cout<< "There is a Day already in the set\n";
    
}

/* Adjust array lenght For dynamic array*/
void DayofYearSet::resize(){
    
    int status =0;
    int prevCapacity= _capacity;
    if(this->_capacity == this->_used){  _capacity = _capacity*2; status =1;}

    else if(_used < (_capacity/4) && _used ==0){_capacity = _capacity/2; status =1;}

    if(status !=0){

        DayofYear *temp = new DayofYear[prevCapacity];
        
        for(int i=0; i<_used; ++i)  {temp[i]= dayofYear[i];}
       
        delete dayofYear;
        
        this->create();

        for(int i=0; i<_used; ++i)  {dayofYear[i].setDate(temp[i].getDate()); dayofYear[i].setMonth(temp[i].getMonth());} 
        delete temp;
    }
}

/* remove element from DayofYearSet*/
void DayofYearSet::remove(const int date, const int month){
   int index;
   int status =0;
    for(int i=0 ; i< _used ; ++i){
        if(date == this->dayofYear[i].getDate() && month == this->dayofYear[i].getMonth()){ 
            index =i;
            i = _used;
            --_used;
            for(int i= index ; i< _used; ++i)   {dayofYear[i] = dayofYear[i+1]; }
            status =1;
            std::cout <<"Day is removed\n";
        }
    }
    if(status==0) std::cout<<"\nThere is no such a day in set\n";
    
}

/* Convert vector to Array*/
void DayofYearSet::vectortoArray(const std::vector<DayofYear>& days ){

    this->dayofYear = new DayofYear[days.size()];

    for(int i=0 ; i< days.size(); ++i)  {dayofYear[i] = days[i];}

}

/* Get size of DayofYearSet elements*/
int DayofYearSet::size( const DayofYearSet& year)   {return year._used;}

/* Create new DayofYear Array*/
void DayofYearSet::create() {this->dayofYear = new DayofYear[_capacity];}


/* Complement operator for DayofYearSet. It returns Complement Set*/
DayofYearSet DayofYearSet::operator !() {
    
    DayofYearSet complement;
    
    int status = 0;
    int counter =0;
    
        for(int i=1 ; i<=12 ; ++i){
            for(decltype(i) j =1 ; j<= 30 ; ++j){
                for(decltype(j) k = 0; k< _used; ++k){
                    
                    if((dayofYear[k].getDate() == j && dayofYear[k].getMonth() == i)){
                        status =1;                       
                        k=_used;
                    }
                    else {status =0; }
                }            
                if(status == 0) { counter++; complement.add(j,i); }
            }
        }
        
    return complement;
    
}

/* Returns Desired Element of DayofYearSet*/
DayofYearSet::DayofYear& DayofYearSet::operator[](int size) const   {return this->dayofYear[size];}


/* Overloaded binary operator returns the union set.*/
DayofYearSet operator+(DayofYearSet &set1 ,DayofYearSet &set2){

    
    DayofYearSet sum;
    
    int size = (set1-set2).size((set1-set2)) + (set2-set1).size((set2-set1)) + (set1^set2).size((set1^set2));
    

    int size1 = (set1-set2).size((set1-set2)); /* find differences set*/
    int size2 = (set2-set1).size((set2-set1)); /* find differences set*/
    int size3 =(set1^set2).size((set1^set2)); /* find intersection set*/
       
    int j =0;

    /* Concanetation proccess*/
    for(int i=0 ; i< size ; ++i, ++j){
        
        
        if(i< size1){   sum.add((set1-set2)[j].getDate(), (set1-set2)[j].getMonth()); }
        else if( i>= size1 && i<size-size3)  {sum.add( (set2-set1)[j-size1].getDate(), (set2-set1)[j-size1].getMonth()) ;}
        else {sum.add( (set1^set2)[j-(size2+size1)].getDate(), (set1^set2)[j-(size2+size1)].getMonth());}
        
        
    } 
    
return sum;

}

/*Overloaded binary operator returns the difference set.*/
DayofYearSet operator -(const DayofYearSet &set1,const DayofYearSet &set2){


DayofYearSet temp;
DayofYearSet intersect;

/* find intersection set*/
intersect = set1 ^ set2;
int status= 0;

/* differ set from intersection set*/
for(int i =0 ; i < set1.size(set1); ++i){

    for(int j =0 ; j<intersect.size(intersect) ; ++j){
        if(intersect[j].getDate( ) == set1[i].getDate() && intersect[j].getMonth( ) == set1[i].getMonth()){
            status =1;
            j=intersect.size(intersect);
        }
           
    }
    
    if(status == 0) {temp.add(set1[i].getDate(), set1[i].getMonth() );}

    status=0;
}

return temp;

}


/*Overloaded binary operator ^ returns the intersection set.*/
DayofYearSet operator ^(const DayofYearSet &set1, const DayofYearSet &set2){
    
    int status = 0;
    /* FİND MIN MAX SIZE OF SETS*/
    auto min = set1.size(set1) < set2.size(set2) ?  set1.size(set1) :set2.size(set2) ;
    auto max = set1.size(set1) > set2.size(set2) ?  set1.size(set1) :set2.size(set2) ;
    
    DayofYearSet temp;

    /* find intersection set*/
    if(set1.size(set1) < set2.size(set2))   {status =1;}

    for(int i =0 ; i< min ; ++i){
        
        for(int j = 0 ; j< max ; ++j){
            
            if(status ==1){
            
                if(set1[i].getDate() == set2[j].getDate() && set1[i].getMonth() == set2[j].getMonth()){
                    temp.add(set1[i].getDate(),set1[i].getMonth() );
                    j = max;
                }
            }

            else if(status ==0){
        
                if(set2[i].getDate() == set1[j].getDate() && set2[i].getMonth() == set1[j].getMonth()){
                    temp.add(set2[i].getDate(),set2[i].getMonth() );
                    j = max;
                }
            }
        }
    }


return temp;

}

/*Overloaded stream insertion operator operator will print DayofYearSet details.*/
std::ostream& operator <<(std::ostream &out,const DayofYearSet &year){
    std::cout <<"(Day  Month)   \n";
    for(int i=0 ; i< year.size(year) ; ++i ){ out << "("<<year[i].getDate()<<"   "<< year[i].getMonth()<<")  ,  ";
    }
    std::cout<<"\n";
return out;
}

/* Overloaded operator for comparing DayofYearSet objects. Two sets are equal if their elements are equal regardless of the keeping order.*/
bool operator ==(const DayofYearSet &set1,const DayofYearSet &set2){
    
    bool status = true;
    
    auto min = set1.size(set1) < set2.size(set2) ?  set1.size(set1) :set2.size(set2) ;
    auto max = set1.size(set1) > set2.size(set2) ?  set1.size(set1) :set2.size(set2) ;
    
    if(min !=max)   {status = false;}
    else{
        for(int i=0 ; i< min ; ++i){
           if(!(set1[i].getDate() == set2[i].getDate() && set1[i].getMonth() == set2[i].getMonth())){
            status = false;
            i=min;  
           } 
        }
    }

return status;

}

/* Overloaded operator for comparing DayofYearSet objects. Two sets are equal if their elements are equal regardless of the keeping order.*/
bool operator !=(const DayofYearSet &set1,const DayofYearSet &set2)     {return !(set1==set2);}



/* DAY OF YEAR CLASS PROPERTIES*/

/* DayofYear Constructor with setter and getters*/
DayofYearSet::DayofYear::DayofYear(int date, int month){
    setMonth(month);
    setDate(date);
}

/* setter for month*/
void DayofYearSet::DayofYear::setMonth(int month)   {if(!(month >12 || month<1) )    _month = month;}

/*getter for month*/
int DayofYearSet::DayofYear::getMonth() const   {return _month;}

/* setter for date*/
void DayofYearSet::DayofYear::setDate(int date){
    
    if(date>=1 && date <=30)  _date =date;
    else{_date = 0;}
    
}
/* getter for date*/
int DayofYearSet::DayofYear::getDate() const    {return _date;}