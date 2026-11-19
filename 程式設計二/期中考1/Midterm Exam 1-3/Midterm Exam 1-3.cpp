// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <ctime>
using std::time;

#include "HugeInteger.h" // include definition of class HugeInteger

template< typename T >
void testHugeInteger( ofstream &outFile, ifstream &inFile );

template< typename T >
void print( ostream &outFile, HugeInteger< T > &hugeInteger );

int main()
{
   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ofstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   srand( static_cast< unsigned int >( time( 0 ) ) );

   const int numTestCases = 19;
   for( int i = 0; i < numTestCases; i++ )
      if( rand() % 2 == 0 )
         testHugeInteger< vector< unsigned int > >( outFile, inFile );
      else
         testHugeInteger< vector< unsigned short > >( outFile, inFile );

   outFile.close();
   inFile.close();

   system( "pause" );
}

template< typename T >
void testHugeInteger( ofstream &outFile, ifstream &inFile )
{
   char digit;
   T inputNumber;
   while( ( digit = inFile.get() ) != '\n' )
      inputNumber.insert( inputNumber.begin(), digit - '0' );

   HugeInteger< T > hugeInteger( inputNumber );

   print( cout, hugeInteger );
   print( outFile, hugeInteger );
}

template< typename T >
void print( ostream &outFile, HugeInteger< T > &hugeInteger )
{
   outFile << hugeInteger << endl;

   HugeInteger< T > sqrt( hugeInteger.squareRoot() );
   outFile << sqrt << endl;

   if( sqrt.square() <= hugeInteger )
      outFile << sqrt.square() << endl;

   ++sqrt;
   if( hugeInteger < sqrt.square() )
      outFile << sqrt.square() << endl << endl;
}