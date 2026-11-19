#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "Deque.h"

void testDeque1( unsigned int size );
void testDeque2( unsigned int size );
void testDeque3( unsigned int size );
void testDeque4( unsigned int size );
void testDeque5();
bool equal( std::deque< int > &data1, deque< int > &data2 );

int main()
{
   for( int i = 1; i <= 5; i++ )
   {
      testDeque1( 8 * i );
      testDeque2( 8 * i );
      testDeque3( 8 * i );
      testDeque4( 8 * i );
   }

   cout << endl;

   for( unsigned int seed = 1; seed <= 20; seed++ )
   {
      srand( seed );
      testDeque5();
   }

   system( "pause" );
}

void testDeque1( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1( 1, 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 ), i );

      deque< int > data2( 1, 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 ), j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.insert( data1.begin() + ( data1.size() / 2 ), i );
      data2.insert( data2.begin() + ( data2.size() / 2 ), j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque2( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1( 1, 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 ), i );

      deque< int > data2( 1, 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 ), j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );
      data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque3( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      data1.insert( data1.begin(), 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );

      deque< int > data2;
      data2.insert( data2.begin(), 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );
      data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque4( unsigned int size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > data1;
      data1.insert( data1.begin(), 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         data1.insert( data1.begin() + ( data1.size() / 2 + 1 ), i );

      deque< int > data2;
      data2.insert( data2.begin(), 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         data2.insert( data2.begin() + ( data2.size() / 2 + 1 ), j );

      if( equal( data1, data2 ) )
         numErrors--;

      data1.insert( data1.begin() + ( data1.size() / 2 ), i );
      data2.insert( data2.begin() + ( data2.size() / 2 ), j );

      if( equal( data1, data2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque5()
{
   std::deque< int > data1;
   deque< int > data2;

   unsigned int numErrors = 1000;
   int value;
   unsigned int position;
   for( unsigned int i = 0; i < 1000; i++ )
   {
      switch( rand() % 2 )
      {
      case 0:         
         value = 1 + rand() % 99;
         position = rand() % ( data1.size() + 1 );
         data1.insert( data1.begin() + position, value );
         data2.insert( data2.begin() + position, value );
         break;
      case 1:
         if( data1.size() > 0 )
         {
            position = rand() % data1.size();
            data1.erase( data1.begin() + position );
            data2.erase( data2.begin() + position );
         }
         break;
      }

      if (equal(data1, data2))
          numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

bool equal( std::deque< int > &data1, deque< int > &data2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &data1 ) + 1 );
   unsigned int mapSize1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 2 );
   unsigned int myOff1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 3 );
   unsigned int mySize1 = *( reinterpret_cast< unsigned int * >( &data1 ) + 4 );

   unsigned int **map2 = *( reinterpret_cast< unsigned int *** > ( &data2 ) );
   unsigned int mapSize2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 1 );
   unsigned int myOff2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 2 );
   unsigned int mySize2 = *( reinterpret_cast< unsigned int * >( &data2 ) + 3 );

   if (mapSize1 != mapSize2)
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
          return true;
      else
          return false;

   if( myOff1 != myOff2 )
       return false;

   if( mySize1 != mySize2 )
       return false;

   size_t row, col;
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
   {
      row = ( i / 4 ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
          return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
          return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
             return false;
      }
   }
   //cout << endl;
   return true;
}