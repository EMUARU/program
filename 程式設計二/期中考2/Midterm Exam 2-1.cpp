// list test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "List.h" // include definition of class template list

void testList();

// return true iff left == right
bool equal( list< int > &left, std::list< int > &right );

const unsigned int number = 1000;

int main()
{
   for( unsigned int seed = 1; seed <= 30; seed++ )
   {
      srand( seed );
      testList();
   }

   cout << endl;

   system( "pause" );
}

void testList()
{
   list< int > list1;
   std::list< int > list2;

   unsigned int numErrors = number; // number of errors
   unsigned int position;
   int value;
   list< int >::iterator it1;
   std::list< int >::iterator it2;
   unsigned int choice;
   for( unsigned int i = 0; i < number; i++ )
   {
      choice = rand() % 2;
      switch( choice )
      {
      case 0:
         position = rand() % ( list1.size() + 1 );
         value = 1 + rand() % 99;

         it1 = list1.begin();
         it2 = list2.begin();
         for( unsigned int i = 0; i < position; i++ )
         {
            ++it1;
            ++it2;
         }

         list1.insert( it1, value );
         list2.insert( it2, value );
         break;
      case 1:
         if( !list1.empty() )
         {
            position = rand() % list1.size();

            it1 = list1.begin();
            it2 = list2.begin();
            for( unsigned int i = 0; i < position; i++ )
            {
               ++it1;
               ++it2;
            }

            list1.erase( it1 );
            list2.erase( it2 );
         }
         break;
      default:
         break;
      }

      if( equal( list1, list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff left == right
bool equal( list< int > &left, std::list< int > &right )
{
   if( left.size() != right.size() ) // different number of elements
      return false;

   list< int >::iterator it1 = left.begin();
   std::list< int >::iterator it2 = right.begin();
   for( ; it1 != left.end() && it2 != right.end(); ++it1, ++it2 )
      if( *it1 != *it2 )
         return false;

   return true;
}