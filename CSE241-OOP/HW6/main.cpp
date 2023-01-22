#include "GtuVector.h"
#include "StlGlobalFunctions.h"
#include "GtuSet.h"
#include "GtuArray.h"
using namespace GTU;


template<typename T>
            void test(GtuIterator<T> other){
                if(!(other == nullptr)) std::cout <<*other<<" ";

            }



void test(){
    /* Gtu vector class test*/
    GtuVector<int> v1;
    
    
    /* Push back operation*/
    
    std::cout <<"Insert element to V1 using Push back operation:";
    for(int i =0 ; i <5 ; ++i){
        v1.push_back(i*3);       
    }
    
    std::cout <<"\n\nV1 is:   ";
    for(int i = 0 ; i < v1.size(); ++i){
        std::cout <<v1[i]<<" ";
    }


    /* Size*/
    std::cout <<"Size of V1 : "<<v1.size();
    std::cout<<std::endl;
   

    /* pop_back()*/
    std::cout <<"\n\nDelete element from V1 using pop_back operation\n";
    v1.pop_back();
    
    std::cout <<"New V1 is :    ";
    for(auto i = v1.begin(); i!= v1.end(); ++i){
        std::cout << *i<<" ";
    }
    std::cout <<*v1.end()<<" ";
    
    std::cout <<"\nSize of V1 : "<<v1.size();
    
    std::cout<<std::endl;

    
    /* begin() iterator op*/

    std::cout <<"\n\nValue of Iterator pointer to beginnig of the V1 : "<<*(v1.begin());
    

    /* end() iterator op*/
    std::cout <<"\n\nValue of Iterator pointer to end of the V1 : "<<*(v1.end());
    

    /* iterator increment op*/
    std::cout<<"\n\nPrint the V1 using iterator increment and range base for loop :";
    for(auto& element : v1){
        std::cout << element<<" ";
    }
    std::cout << *(v1.end());    
    

    /* Find operation*/
    std::cout <<"\n\nFind second element\n";
    GtuIterator<int> it = ++v1.begin();
    std::cout <<"Founded element is :  " <<*it;
    

    /* foreach*/
    std::cout<<"\n\nPrint the V1 using iterator increment and foreach :";
    for_each(v1.begin(),v1.end(),test<int>);
    

    /* Erase element from vector*/
    std::cout <<"\n\nErase first element from V1 using iterator\n";
    v1.erase(v1.begin());
    std::cout <<"New V1 is:  ";
    
    for(auto i = v1.begin(); i != v1.end(); ++i){
        std::cout << *i<<" ";
    }
    std::cout << *v1.end();
    
    std::cout <<"\nSize of V1 : "<<v1.size();
    

    /* Create new vector using copy constructor*/
    std::cout<<"\n\nNew vector V2 was created from V1 using copy constructor\n";
    GtuVector<int> v2(v1);
    std::cout <<"Vector is :   ";
    
    for(auto& element : v2){
        std::cout<<element;
    }
    std::cout <<*v2.end();
    
    std::cout <<"\nSize of V2 : "<<v2.size();
    
    
    /* Push_back*/
    std::cout <<"\n\nCall push_Back op on V2\n";
    v2.push_back(78);
    v2.push_back(7);

    std::cout<< "V2 is using operator[]  :   ";
    for(int i = 0 ; i < v2.size(); ++i){
        std::cout <<v2[i]<<" ";
    }
    std::cout <<"\nSize of V2 : "<<v2.size();
    

    /* Assigment op*/
    std::cout<<"\n\nAssign V2 to V1 using assigment op\n";
    v1 = v2;
    std:: cout<<"The V1 vector is now :   ";
    
    for(auto i = v1.begin(); i!= v1.end(); ++i){
        std::cout << *i<<" ";
    }  
    std::cout << *v1.end();
    
    std::cout <<"\nSize of V1 : "<<v2.size();
    
    
    /* Move assigment op*/
    std::cout <<"\n\nMove assigment op V1 to V2.\nV1 is going to be empty\n";
    v2 = std::move(v1);
    
    std::cout<<"V2 is:    ";
    for_each(v2.begin(), v2.end(), test<int>);
    
    std::cout<<"\nV1 is:    ";
    for_each(v2.begin(), v2.end(), test<int>);


    /*Clear op*/
    std::cout <<"\n\nClear the V2\n";
    v1.clear();    
    std::cout <<"V2 is :       ";
    v1.print();

    
    /* Gtu Set class test*/
    std::cout <<"\n\n\nSET TEST\n";
    GtuSet<int> s1;
    
    /* Add operation*/
    std::cout <<"\n\nAdd element to S1 using add() twice\n";
    for(int i =0 ; i <5 ; ++i){
        s1.add(i*3);
    }
    for(int i =0 ; i <5 ; ++i){
        s1.add(i*3);
    }
    std::cout <<"S1 is :             ";
    for(auto & element : s1){
        std::cout << element<<" ";
    }
    std::cout << *s1.end();    
    /* Size of set*/
    std::cout <<"\nSize of S1 : "<<s1.size();
    

    /* Delete element*/

    std::cout <<"\n\nDelete last element from S1\n";
    s1.erase(s1.end());
    for(auto i = s1.begin(); i!= s1.end(); ++i){
        std::cerr << *i<<" ";
    }
    std::cerr << *s1.end();
    std::cout <<"\nSize of S1 : "<<s1.size();

    
    GtuSet<int> s2;
    /* Copy assigment operator*/
    std::cout <<"\n\nCopy assignment S1 to S2\n";
    s2 = s1;
    std::cout <<"S2 is:    ";
    s2.print();

    GtuSet<int> s3;
    s3 = s2.intersectSet(s1);
    std::cout <<"\n\nIntersection Set of S1 and S2: \n";
    for(auto & element : s3){
        std::cout << element <<" ";
    }
    std::cout << *s3.end();



    /* Add ()*/
    std::cout<<"\n\nAdd 75 to S2\n";
    /*ADD*/
    s2.add(75);
    
    /*Delete*/
    std::cout<<"\n\nDelete first element from S2 using iterator (s2.begin())\n";

    GtuIterator<int> iter = s2.begin();
    s2.erase(iter);
    std::cout <<"\n\nPrint S2 using for_each :      ";
    /* Foreach*/
    for_each(s2.begin(), s2.end(), test<int>);

    /* Find()*/

    std::cout <<"Find last element from S2 using find()\n";
    std::cout <<"Founded element is :   ";
    std::cout <<*find(s2.begin(), s2.end(), *s2.end());
    
    /* clear*/
    std::cout <<"\n\nClear S2\n";
    s2.clear();
    std::cout <<"S2 is :   ";
    s2.print();
    
    
    
    /*Gtu array class test*/
    std::cout <<"\n\n\n\nGTU ARRAY TEST\n\n";
    
    std::cout <<"Negative index test using try cath block\n";
    try
    {
       GtuArray<int, -1> ar0; 
    }
    catch(const char* message)
    {
        std::cout <<message<<std::endl;
    }
    
    
    
    GtuArray<int,5> ar1;
    /* Assigment operation*/
    
    std::cout <<"\n\nAdd elements to AR1 using operator[]\n";
    for(int i = 0 ; i <5; ++i){
        ar1[i] = 5*i;
    }


    std::cout <<"AR1 is:       ";
    for(int i = 0 ; i <ar1.size(); ++i){
        std::cout<<ar1[i]<<" ";
    }

    std::cout <<"\nSize of array : "<<ar1.size();
   
   
    /* Access using front() and back()*/
    std::cout <<"\n\nAcces to the first element :  "<<ar1.front();
    std::cout <<"\n\nAcces to the last element :  "<<ar1.back();

    
    /* copy assigment operator*/
    std::cout <<"\n\nCreate AR2 with copy assigment op\n";
    GtuArray<int,5>ar2(ar1);
    
    std::cout <<"\nChange the second elemet of AR2 using operator[]\n";
    ar2[1]= 665;
    
    /*print*/
    std::cout <<"\nPrint AR2 using range based for loop\n";
    for(auto & element : ar2){
        std::cout <<element<<" ";
    }
    std::cout<< *ar2.end();

    /* Assign operator*/
    std::cout <<"\n\nCreate AR3 then assign AR2 to AR3 using assign operator\n";
    GtuArray<int,5> ar3;
    ar3 = ar2;

    
    /* for_each function*/
    std::cout << "Print ar3 using for_each\n";
    std::cout <<"AR3 is:   ";
    for_each(ar3.begin(), ar3.end(), test<int>);
    

    /* find function*/
    std::cout <<"\n\nFind last element using Find function\n";
    std::cout<<"Founded element is:  ";
    std::cout <<*(find(ar3.begin(), ar3.end(),*ar3.end()));

    
    /* Move assigment*/
    std::cout <<"\n\nUse Move assigment , AR3 to AR1. AR3 is going to be empty\n";
    ar1 = std::move(ar3);
    
    std::cout <<"AR1 is:   ";
    for(auto i = ar1.begin() ; i!=ar1.end(); ++i){
        std::cout <<*i<<" ";
    }
    std::cout << *ar1.end();

    
    /* Fill() function*/
    std::cout <<"\n\nFill The Array with number Using Fill()\n";
    ar1.fill(15);
    
    std::cout <<"AR1 is:   ";
    for(auto& element : ar1){
        std::cout <<element<<" ";
    }
    std::cout << *ar1.end();
    
    std::cout <<"\nSize of array : "<<ar1.size();



}


int main(){
    
    test();
    return 0;
    
   
}