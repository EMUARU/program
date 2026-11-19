// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <string>
#include "String.h"

void testInsert1();
void testInsert2();
void testString();

// return true iff left == right
bool equal( string &left, std::string &right );

const unsigned int number = 1000;

int main()
{
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
      testString();
   }

   cout << endl;

   system( "pause" );
}

void testInsert1()
{
   string string1;
   std::string string2;

   unsigned int numErrors = number;
   unsigned int position;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      position = rand() % ( string1.size() + 1 );
      value = static_cast< char >( 97 + rand() % 26 );
      string1.insert( string1.begin() + position, value );
      string2.insert( string2.begin() + position, value );

      if( equal( string1, string2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   string str;

   unsigned int numErrors = number;
   unsigned int position;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      size_t oldSize = str.size();
      size_t oldCapacity = str.capacity();

      char *oldAddress = str.begin(); // oldAddress = str.myData.myPtr()

      position = rand() % ( str.size() + 1 );
      value = static_cast< char >( 97 + rand() % 26 );
      str.insert( str.begin() + position, value );

      char *newAddress = str.begin(); // newAddress = str.myData.myPtr()

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
   // the array pointed by str.myData.bx.ptr before
   // the excution of str.insert( str.begin() + position, value ) is the same as
   // the array pointed by str.myData.bx.ptr after
   // the excution of str.insert( str.begin() + position, value )
   // i.e., there is no memory allocation during the excution of
   // str.insert( str.begin() + position, value )

   cout << "There are " << numErrors << " errors\n";
}

void testString()
{
   string str1;
   std::string str2;

   unsigned int numErrors = number;
   unsigned int position;
   char c;
   unsigned int choice;
   for( unsigned int i = 0; i < number; i++ )
   {
      choice = rand() % 2;
      switch( choice )
      {
      case 0:
         // Randomly generates a lower-case letter of English.
         c = static_cast< char >( 97 + rand() % 26 );
         position = rand() % ( str2.size() + 1 );
         str1.insert( str1.begin() + position, c ); // Inserts c into str1 right before the position.
         str2.insert( str2.begin() + position, c ); // Inserts c into str2 right before the position.
         break;
      case 1:
         if( !str2.empty() )
         {
            position = rand() % str2.size();
            str1.erase( str1.begin() + position ); // Erases the character of str1 at the position.
            str2.erase( str2.begin() + position ); // Erases the character of str2 at the position.
         }
         break;
      }

      if( equal( str1, str2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff left == right
bool equal( string &left, std::string &right )
{
   if( left.capacity() != right.capacity() )
      return false;

   if( left.size() != right.size() )
      return false;

   for( size_t i = 0; i < right.size(); i++ )
      if( left[ i ] != right[ i ] )
         return false;

   return true;
}