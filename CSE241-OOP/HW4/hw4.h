#include <vector>
#include <iostream>


class DayofYearSet{
    

    public :

        class DayofYear{
                    
            private:
                int _month, _date;
            
            public:
                explicit DayofYear(int date=1, int month=1);
                
                void setMonth(int month);
                int getMonth() const;
                
                void setDate(int date);
                int getDate() const;
                
                
               
        };

    private:
                    
                    int _capacity;
                    int _used;
                    
                    
                    DayofYear * dayofYear;
                    
                
                    void resize();
                    void create();

                    void vectortoArray(const std::vector<DayofYear>& days );

                    bool findDay(const int  date, const int month) const;
                    bool checkDay(const int  date, const int month) const;
            
        
        public:
             DayofYearSet();
             DayofYearSet(int date, int month);
             DayofYearSet(const DayofYearSet &);
            DayofYearSet(std::vector<DayofYear>&);
            
            void add(const int date, const int month);
            void remove(const int date, const int month);
            static int size(const DayofYearSet&);
           
            

            DayofYear& operator[](int size) const;
            DayofYearSet operator !() ;
            

            friend DayofYearSet operator+(DayofYearSet &set ,  DayofYearSet&set1);
            friend DayofYearSet operator -(const DayofYearSet &set, const DayofYearSet& set1);
            friend DayofYearSet operator ^(const DayofYearSet &, const DayofYearSet&);
            friend std::ostream& operator <<(std::ostream &out,const DayofYearSet&);
            friend bool operator ==(const DayofYearSet &, const DayofYearSet&);
            friend bool operator !=(const DayofYearSet &,const DayofYearSet&);
            
            ~DayofYearSet();

            

};

    /* operators*/
    std::ostream& operator <<(std::ostream &out,const DayofYearSet::DayofYear&);
    DayofYearSet operator +( DayofYearSet &, DayofYearSet&);
    DayofYearSet operator -(const DayofYearSet &, const DayofYearSet&);
    DayofYearSet operator ^(const DayofYearSet &,const  DayofYearSet&);
    bool operator ==(const DayofYearSet &, const DayofYearSet&);
    bool operator !=(const DayofYearSet &,const DayofYearSet&);




