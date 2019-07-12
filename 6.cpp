#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

// enable only if your implementation supports Add ( ) with more than three parameters
 #define MULTIPLE_STOPS

// Solution inspired by Tomas Pecka's code found here:
// https://edux.fit.cvut.cz/courses/BI-PA2/teacher/peckato1/tut08

template <typename _T, typename _E>
class CAccess
{
private:
    struct Node
    {
        _T destination;
        _E train;
        bool operator < (const Node& a)const
        {
            return destination < a.destination;
        }
    };
    std::multimap < _T,  Node > nodes;
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //determines if argument wanted is already present in "nodes" map
    bool exists(const _T & wanted)const
    {
        if(nodes.count(wanted)==0)return 0;
        return 1;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //this function is needed because of the recursive behaviour of the second saveall below
    void saveall(vector<_T> &positions,const  _T &Isource,const  _T & Idestination)
    {
        positions.push_back(Isource);
        positions.push_back(Idestination);
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    template < typename ..._N >
    //recursive function that fills vector "positions" with cities(or anything else) from multiple arguments
    void saveall(vector<_T> &positions,const  _T &Isource,const  _T & Idestination,_N...n)
    {
        positions.push_back(Isource);
        if(sizeof...(n)){
        saveall(positions,Idestination,n...);
        }
        positions.push_back(Idestination);
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //this function works the same way as add, but has to be called multiple times and doesn't return anything
    void addmany(const  _E & Itrain,const  _T &Isource,const  _T & Idestination)
    {
        Node a{Idestination,Itrain};
        nodes.insert( std::pair<_T,Node> (Isource,a));
        Node b{Isource,Itrain};
        nodes.insert(pair<_T,Node>(Idestination,b));
    }
    //============================================================================================================
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //saves arguments in multimap, first as source->destination, then as destination->source
    CAccess & Add(const  _E & Itrain,const  _T &Isource,const  _T & Idestination)
    {
        //adding elements in this way is unnecessary memory waste since everything is saved two times,
        //but allows for much easier implementation
        Node a{Idestination,Itrain};
        nodes.insert( std::pair<_T,Node> (Isource,a));
        Node b{Isource,Itrain};
        nodes.insert(pair<_T,Node>(Idestination,b));
        
        return *this;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    template < typename ..._N >
    //overloaded Add for multiple arguments
    CAccess & Add(const  _E & Itrain,const  _T &Isource,const  _T & Idestination,_N...n)
    {
        vector<_T> positions;
        
        //first all arguments are saved in vector "positions"
        saveall(positions,Isource,Idestination,n...);
        
        //then all combinations of arguments are saved in multimap
        for(unsigned i = 0; i< (sizeof...(n)+2);i++)
        {
            for(unsigned x = i; x<(sizeof...(n)+2);x++)
            {
                addmany(Itrain,positions[i],positions[x]);
            }
        }
        return *this;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //finds all destinations possible from source
    //if there is no class specified in argument, if statement later returns always true
    map< _T, int> Find(const _T    & wanted,int Idistance = -1,const function<bool(const _E &)> &Iclass = [](const _E &a){return true;})const
    {   
        //if source is not yet in multimap, throws "unknown -source-"
        if(!exists(wanted)){
            stringstream inerrwanted ;
            inerrwanted << "unknown " << wanted;
            string outerrwanted = inerrwanted.str();
            throw invalid_argument(outerrwanted) ;
        }
        
        //declaration of necessary data types
        std::queue<std::pair<_T,int> > que;
        std::set < _T > visited;
        std::map < _T, int > outmap;
        que.push( make_pair(wanted,0));
        visited.insert(wanted);
        outmap.insert(std::pair<_T,int>(wanted,0));
        pair <typename::std::multimap< _T,Node >::const_iterator,
        typename::std::multimap< _T,Node >::const_iterator> iter;
        
        //if there are no elements in que, it means there are no possible paths left
        while(!que.empty())
        {
            //read and temporary save element from que for immediate work
            int distance = que.front().second;
            _T tmpwanted = que.front().first;
            //remove element from queue to signal it has been used later
            que.pop();
            //range of multimap elements with source equal to wanted element
            iter = nodes.equal_range ( tmpwanted );
            
            //check if distance is in range, or no range has been specified
            if(distance+1 <= Idistance || Idistance == -1)
            {
                for(typename::multimap<_T,Node>::const_iterator i = iter.first; i!=iter.second;++i)
                {
                    //if already visited, do nothing and continue, if class of train is not in required do nothing and continue
                    if(visited.count(i->second.destination)==0 && Iclass(i->second.train))
                    {
                        //add destination with distance to queue and to map, add location to visited
                        que.push(make_pair(i->second.destination,distance+1));
                        visited.insert(i->second.destination);
                        outmap.insert(std::pair<_T,int>(i->second.destination,distance+1));
                    }
                }
            }
        }
        return outmap;   
    }
};

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
public:
CTrain   ( const string    & company, 
int               speed )
: m_Company ( company ), 
m_Speed ( speed ) 
{ 
}
//---------------------------------------------------------------------------------------------
string                   m_Company;
int                      m_Speed; 
};
//=================================================================================================
class TrainFilterCompany
{
public:
TrainFilterCompany  ( const set<string> & companies ) 
: m_Companies ( companies ) 
{ 
}
//---------------------------------------------------------------------------------------------
bool  operator () ( const CTrain & train ) const
{ 
return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
}
//---------------------------------------------------------------------------------------------
private:  
set <string>             m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
public:
TrainFilterSpeed  ( int               min, 
int               max )
: m_Min ( min ), 
m_Max ( max ) 
{ 
}
//---------------------------------------------------------------------------------------------
bool      operator ()  ( const CTrain    & train ) const
{ 
return train . m_Speed >= m_Min && train . m_Speed <= m_Max; 
}
//---------------------------------------------------------------------------------------------
private:  
int                      m_Min;
int                      m_Max;
};
//=================================================================================================
bool  NurSchnellzug  ( const CTrain    & zug )
{
return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
int                          main                          ( void )
{
  CAccess<string,CTrain> lines;
  lines 
        . Add ( CTrain (   "DB", 120 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "CD",  80 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "DB", 160 ), "Berlin", "Dresden"  )
        . Add ( CTrain (   "DB", 160 ), "Dresden", "Munchen" )
        . Add ( CTrain (   "CD",  90 ), "Munchen", "Prague"  )
        . Add ( CTrain (   "DB", 200 ), "Munchen", "Linz"    )
        . Add ( CTrain (  "OBB",  90 ), "Munchen", "Linz"    )
        . Add ( CTrain (   "CD",  50 ), "Linz", "Prague"     )
        . Add ( CTrain (   "CD", 100 ), "Prague", "Wien"     )
        . Add ( CTrain (  "OBB", 160 ), "Linz", "Wien"       )
        . Add ( CTrain ( "SNCF", 300 ), "Paris", "Marseille" )
        . Add ( CTrain ( "SNCF", 250 ), "Paris", "Dresden"   )
        . Add ( CTrain ( "SNCF", 200 ), "London", "Calais"   );
  assert ( lines . Find ( "Berlin" ) == (map<string,int>
  {
    make_pair ( "Berlin", 0 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Marseille", 3 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London" ) == (map<string,int>
  {
    make_pair ( "Calais", 1 ),
    make_pair ( "London", 0 )
  }) );
  assert ( lines . Find ( "Wien" ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Marseille", 5 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 3 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 5, NurSchnellzug ) == (map<string,int>
  {
    make_pair ( "Berlin", 4 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Prague", 3,  TrainFilterCompany ( { "CD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 1 ),
    make_pair ( "Dresden", 2 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 1 ),
    make_pair ( "Prague", 0 ),
    make_pair ( "Wien", 1 )
  }) );
  assert ( lines . Find ( "Munchen", 4, TrainFilterSpeed ( 160, 250 ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Munchen", 4, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London", 20, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "London", 0 )
  }) );
  try
  {
     auto res = lines . Find ( "Salzburg" );
     assert ( "No exception thrown" == NULL );
  }
  catch ( const invalid_argument & e )
  {
    assert ( string ( e . what () ) == "unknown Salzburg" );
  }
#ifdef MULTIPLE_STOPS
  lines . Add ( CTrain ( "RZD",  80 ), "Prague", "Kiev", "Moscow", "Omsk", "Irkutsk", "Vladivostok" );
  lines . Add ( CTrain ( "LAV", 160 ), "Malaga", "Cordoba", "Toledo", "Madrid", "Zaragoza", "Tarragona", "Barcelona", "Montpellier", "Marseille" );
  assert ( lines . Find ( "Madrid" ) == (map<string,int>
  {
    make_pair ( "Barcelona", 1 ),
    make_pair ( "Berlin", 4 ),
    make_pair ( "Cordoba", 1 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 6 ),
    make_pair ( "Kiev", 6 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Madrid", 0 ),
    make_pair ( "Malaga", 1 ),
    make_pair ( "Marseille", 1 ),
    make_pair ( "Montpellier", 1 ),
    make_pair ( "Moscow", 6 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 6 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Tarragona", 1 ),
    make_pair ( "Toledo", 1 ),
    make_pair ( "Vladivostok", 6 ),
    make_pair ( "Wien", 6 ),
    make_pair ( "Zaragoza", 1 )
  }) );
  assert ( lines . Find ( "Omsk", 4 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Moscow", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Omsk", 0 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Moscow", 10, TrainFilterCompany ( { "RZD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Moscow", 0 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 1 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 )
  }) );
#endif /* MULTIPLE_STOPS */
  return 0;
}
#endif  /* __PROGTEST__ */
