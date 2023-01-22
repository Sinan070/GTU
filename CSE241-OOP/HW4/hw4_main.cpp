#include "hw4.h"
#include <iostream>
#include <fstream>
using namespace std;


namespace Test{

    /* fiil randomly Year Set*/
    void fill_randomly(DayofYearSet &set ,int daySize, int monthSize){

        int random1;
        int random2;

        random1 = rand() % daySize +1;
        random2 = rand() % monthSize +1;
        
        for(int i =1; i<=random1; ++i){
            for(int j =1 ; j <=random2 ; ++j){
               set.add(j,i);
               
            }
        }
        
    
    }
    /* stream insertion (<<) test*/
     void streamInsertion(DayofYearSet& set){
       
        cout << set<<endl;
    }
    /* intersection operator (s1^s2) test*/
     void  intersectionOp(DayofYearSet & set,DayofYearSet & set2){
        DayofYearSet set3 = set^set2;
        cout <<"Set 1: ";
        streamInsertion(set);
        cout <<"Set 2 :";
        streamInsertion(set2);
        cout <<"Intersection set  of sets : ";
        streamInsertion(set3);
        cout <<"Size of Intersection Set : "<<DayofYearSet::size(set3)<<"\n";


    }
    /* union operator (s1+s2) test*/
    void unionOp(DayofYearSet & set,DayofYearSet & set2){
        DayofYearSet set3 = set+set2;
        cout <<"Set 1: ";
        streamInsertion(set);
        cout <<"Set 2 :";
        streamInsertion(set2);

        cout <<"Union set : ";
    
        streamInsertion(set3);
        cout <<"Size of Union Set : "<<DayofYearSet::size(set3)<<"\n";

    }
    
    /* Complement Operator (!s1) test*/
    void complementOp(DayofYearSet & set){
        DayofYearSet set3 = !set;
        
        cout <<"Size of Set : "<<DayofYearSet::size(set)<<"\n";
        cout<<"Set : ";
        streamInsertion(set);
        
        cout <<"Size of Complement Set : "<<DayofYearSet::size(set3)<<"\n";
        cout <<"Complement Set : ";
        
        streamInsertion(set3);


    }
    /* Differences Operator (s1-s2) test*/
    void differOp(DayofYearSet & set,DayofYearSet & set2){
        
        DayofYearSet set3 = set- set2;
        cout <<"Set 1: ";
        streamInsertion(set);
        cout <<"Set 2 :";
        streamInsertion(set2);
        
        cout <<"Differences set between sets : ";
        streamInsertion(set3);
        cout <<"Size of Differences Set : "<<DayofYearSet::size(set3)<<"\n";

    }

    /* Add function test*/
    void add(DayofYearSet &set){
        
        cout << "\nAdd (6,12) to Set ->>>"; set.add(6,12);
        cout<< "Size of Set is : "<<DayofYearSet::size(set)<<endl<<"Set is: "<<set;
    
    }
    /* Remove function test*/
    void remove(DayofYearSet &set){
        cout <<"\nRemove (15,7) from Set ->>"; set.remove(15,7);
        cout<< "Size of Set is : "<<DayofYearSet::size(set)<<endl<<"Set is: "<<set;

    }
    /* Size function test*/
    void size(DayofYearSet &set) {
        cout <<"\nSize of Set is : "<<DayofYearSet::size(set)<<endl;
        

    }
    /* Equal Operator (==) Test*/
    void equalOp(DayofYearSet& set,DayofYearSet& set1){
    
        cout<<"1.Set : ";
        streamInsertion(set);
        cout <<"2.Set: ";
        streamInsertion(set1);

        if(set==set1){    cout <<"\nSets are equal\n";}
        else cout <<"\nSets are not equal";

    }

    /* Not Eqaul Operator (!=) Test*/
    void notEqualOp(DayofYearSet& set,DayofYearSet& set1){
       
        cout<<"1.Set : ";
        streamInsertion(set);
        cout <<"2.Set: ";
        streamInsertion(set1);;

        if(set!=set1){    cout <<"Sets are not eqaul\n";}
        else cout <<"Sets are equal";

    }
    /* Demorgan Rule (!(s1 + s2) == !s1 ^ !s2 ) Test*/
    void deMorgan(DayofYearSet &set,DayofYearSet &set2){
        cout<<endl<<endl;
        cout<<"1.Set : ";
        streamInsertion(set);
        cout <<"2.Set: ";
        streamInsertion(set2);
        if(!(set + set2) == ((!set) ^ (!set2))){
            cout <<"De Morgan Rule (!(s1 + s2) == !s1 ^ !s2) is true\n";

        }
        else    cout <<"De Morgan Rule (!(s1 + s2) == !s1 ^ !s2) is false\n";
        
    }
    /* Calling Set by value Test*/
    void callbyValue(DayofYearSet set,DayofYearSet set2 ){
       unionOp(set,set2);
        
    }
    /* Calling Set by references Test*/
    void callbyReference(DayofYearSet& set,DayofYearSet& set2){
        
        unionOp(set,set2);

    }
    
}


int main(){
    srand(time(NULL));
    /* Create Set*/
    DayofYearSet s1(15,1);
    DayofYearSet s2;
    DayofYearSet s3;
    DayofYearSet s4;
    DayofYearSet s5;
    DayofYearSet s6;
    
    /* Fill Set With Random Days*/
    Test::fill_randomly(s1,2,3);
    Test::fill_randomly(s2,2,4);
    Test::fill_randomly(s3,2,5);
    Test::fill_randomly(s4,3,4);
    Test::fill_randomly(s5,3,6);
    cout<<"------------------\nSet : ";
    Test::streamInsertion(s1); //Print the s1
    
    Test::size(s1); // Print s1 size
  
    Test::add(s1); // Add day to s1
     
    Test::remove(s1); //Remove day from s1

    cout<<"------------------\n\n";


    cout<<"------------------\n";

    /* De morgon Tests*/
    cout <<"De morgan\n"; 
      
    

    Test::deMorgan(s1,s2); 
    cout<<"------------------\n\n";

    cout<<"------------------\n";

    cout <<"De morgan\n";
    Test::deMorgan(s2,s3);
    cout<<"------------------\n\n";

    cout<<"------------------\n";

    cout <<"De morgan\n";
    Test::deMorgan(s3,s4);
    cout<<"------------------\n\n";

    cout<<"------------------\n";

    cout <<"De morgan\n";
    Test::deMorgan(s4,s5);
    cout<<"------------------\n\n";

    cout<<"------------------\n";

    cout <<"De morgan\n";
    Test::deMorgan(s3,s5);

    cout<<"------------------";


    s6 =s1; /* equalization s6 to s1*/
    cout<<"\n\n------------------\n";

    /* Eqaul Operataor TEST*/
    cout <<"Equal Operator (==)\n\n";
    Test::equalOp(s1,s6);
    cout<<"------------------";
    cout<<"\n\n------------------\n";
    
    /* Not equal Operator*/
    cout <<"Not Equal Operator (!=)\n\n";
    Test::notEqualOp(s1,s2);
    cout<<"------------------\n\n";

    /* Union Test*/
    cout <<"--------------------\nUnion Operator(s1+s2)\n\n";
    Test::unionOp(s1,s2);
    cout<<"------------------\n\n";
    
    /* Intersection Test*/
    cout <<"--------------------\nIntersection Operator(s1^s2)\n\n";
    Test::intersectionOp(s1,s2);
    cout<<"------------------\n\n";

    /* Differences Set*/
    cout <<"--------------------\nDifferences Operator(s1^s2)\n\n";
    Test::differOp(s1,s2);
    cout<<"------------------\n\n";

    /* Complement Set*/
    cout <<"--------------------\nComplement Operator(s1^s2)\n\n";
    Test::complementOp(s1);
    cout<<"------------------\n\n";
    
    /* Call by value*/
    cout <<"--------------------\nUnion Operator(s1+s2) with Call by Value\n\n";
    Test::callbyValue(s1,s2);
    /* Call by refernce*/
    cout <<"--------------------\nUnion Operator(s1+s2) with Call by References\n\n";
    Test::callbyReference(s1,s2);
    
    /* Print Set to Text*/
    fstream my_file;
    my_file.open("s1.txt", ios::out);
    if (!my_file)   {
        cerr << "File is not created\n";
        my_file.close();    
    }
    else my_file << s1;
    cout << "S1 is written to the text file\n";
    my_file.close();
    return 0;
}
