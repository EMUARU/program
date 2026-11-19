// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <vector>
#include "Vector.h"

void testFillConstructor();
void testCopyConstructor();
void testInsert1();
void testInsert2();
void testVector();

// Determines if two vectors are equal.
bool equal( vector< int > &left, std::vector< int > &right );

const unsigned int number = 1000;

int main()
{
   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testFillConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testCopyConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert1();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert2();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testVector();
   }

   system( "pause" );
}

void testFillConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   for( unsigned int i = 0; i < number; i++ )
   {
      length = rand() % 200;
      vector< int > vector1( length );
      std::vector< int > vector2( length );

      if( equal( vector1, vector2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      vector< int > vector1;
      std::vector< int > vector2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         vector1.insert( vector1.end(), value );
         vector2.insert( vector2.end(), value );
      }

      vector< int > vector3( vector1 );
      std::vector< int > vector4( vector2 );

      if( equal( vector3, vector4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert1()
{
   vector< int > vector1;
   std::vector< int > vector2;

   unsigned int numErrors = number;
   unsigned int position;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      position = rand() % ( vector1.size() + 1 );
      value = 1 + rand() % 99;
      vector1.insert( vector1.begin() + position, value );
      vector2.insert( vector2.begin() + position, value );

      if( equal( vector1, vector2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   vector< int > v;

   unsigned int numErrors = number;
   unsigned int position;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      size_t oldSize = v.size();
      size_t oldCapacity = v.capacity();

      int *oldAddress = v.begin(); // oldAddress = v.myData.myFirst

      position = rand() % ( v.size() + 1 );
      value = 1 + rand() % 99;
      v.insert( v.begin() + position, value );

      int *newAddress = v.begin(); // newAddress = v.myData.myFirst

      if( oldSize == oldCapacity )
      {
         if( newAddress != oldAddress )
            numErrors--;
      }
      else
         if( newAddress == oldAddress )
            numErrors--;
   }

   // newAddress == oldAddress if and only if
   // the array pointed by v.myData.myFirst before
   // the excution of v.insert( v.begin() + position, value ) is the same as
   // the array pointed by v.myData.myFirst after
   // the excution of v.insert( v.begin() + position, value )
   // i.e., there is no memory allocation during the excution of
   // v.insert( v.begin() + position, value )

   cout << "There are " << numErrors << " errors.\n";
}

void testVector()
{
   vector< int > vector1;
   std::vector< int > vector2;

   unsigned int numErrors = number; // number of errors
   unsigned int position;
   int value;
   unsigned int choice;
   for( unsigned int i = 0; i < number; i++ )
   {
      choice = rand() % 2;
      switch( choice )
      {
      case 0:
         position = rand() % ( vector1.size() + 1 );
         value = 1 + rand() % 99;
         vector1.insert( vector1.begin() + position, value );
         vector2.insert( vector2.begin() + position, value );
         break;
      case 1:
         if( !vector1.empty() )
         {
            position = rand() % vector1.size();
            vector1.erase( vector1.begin() + position );
            vector2.erase( vector2.begin() + position );
         }
         break;
      default:
         break;
      }

      if( equal( vector1, vector2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two vectors are equal.
bool equal( vector< int > &left, std::vector< int > &right )
{
   if( left.capacity() != right.capacity() )
      return false;

   if( left.size() != right.size() )
      return false;

   for( size_t i = 0; i < right.size(); ++i )
      if( left[ i ] != right[ i ] )
         return false;

   return true;
}