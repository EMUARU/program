// string internal header

#ifndef STRING
#define STRING

// CLASS StringVal
template < typename ValueType >
class StringVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   StringVal()
      : bx(),
        mySize( 0 ),
        myRes( 15 )
   {
   }

   value_type* myPtr()
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   const value_type* myPtr() const
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   union Bxty // storage for small buffer or pointer to larger one
   {
      value_type buf[ 16 ];
      pointer ptr;
   } bx;

   size_type mySize; // current length of string
   size_type myRes;  // current storage reserved for string
};

class string // null-terminated transparent array of elements
{
   using ScaryVal = StringVal< char >;

public:
   using value_type = char;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty string constructor (default constructor)
   // Constructs an empty string, with a length of zero characters.
   string()
      : myData()
   {
   }

   // String destructor
   // Destroys the string object.
   // Deallocates all the storage capacity allocated by the string.
   ~string()
   {
      if( myData.myRes > 15 )
         delete[] myData.bx.ptr;
   }

   // Inserts character ch into the string right before the character
   // indicated by "where".
   iterator insert( const_iterator where, const char ch )
   {
      if( where >= myData.myPtr() && where <= myData.myPtr() + myData.mySize )
      {
		  int newSize = size() + 1, oldSize = size();

		  int newcapacity = (capacity() * 1.5 >= (newSize / 16) * 16 + 15) ? capacity() * 1.5 : ((newSize / 16) * 16 + 15);

		  if (newSize > capacity())
		  {
			  char* p = new char[newcapacity]();

			  for (int i(0); i < oldSize + 1; i++)
			  {
				  if (i != where - myData.myPtr())
				  {
					  if (i < where - myData.myPtr())
						  p[i] = myData.myPtr()[i];
					  else
						  p[i] = myData.myPtr()[i - 1];
				  }
				  else
					  p[i] = ch;
			  }

			  if(myData.mySize > 15)
				delete[] myData.bx.ptr;
			  myData.bx.ptr = p;
			  myData.myRes = newcapacity;

		  }
		  else
		  {
			  for (int i(oldSize); i >= 0; i--)
			  {
				  if (i == where - myData.myPtr())
					  myData.myPtr()[i] = ch;
				  else if (i > where - myData.myPtr())
					  myData.myPtr()[i] = myData.myPtr()[i - 1];
			  }
			  
		  }

		  myData.mySize++;
		  return myData.myPtr();
      }
      else
         return nullptr;
   }

   // Erases the character pointed by p.
   iterator erase( const_iterator where )
   {
      if( where >= myData.myPtr() && where < myData.myPtr() + myData.mySize )
      {
		  for (int i(where - myData.myPtr()); i < size() - 1; i++)
			  myData.myPtr()[i] = myData.myPtr()[i + 1];

		  myData.mySize--;

		  return myData.myPtr();
      }
      else
         return nullptr;
   }

   // Erases the contents of the string, which becomes an empty string
   // (with a length of 0 characters).
   void clear()
   {
      myData.mySize = 0;
      myData.myPtr()[ 0 ] = value_type();
   }

   // Returns an iterator pointing to the first character of the string.
   iterator begin()
   {
      return iterator( myData.myPtr() );
   }

   // Returns an iterator pointing to the first character of the string.
   const_iterator begin() const
   {
      return const_iterator( myData.myPtr() );
   }

   // Returns an iterator pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character
   // that would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   iterator end()
   {
      return iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
   }

   // Returns an iterator pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character
   // that would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
   }

   // Returns a reference to the character at position pos in the string.
   reference operator[]( const size_type off )
   {
      if( off > myData.mySize )
      {
         cout << "string subscript out of range\n";
         exit( 1 );
      }

      return myData.myPtr()[ off ];
   }

   // Returns a reference to the character at position pos in the string.
   const_reference operator[]( const size_type off ) const
   {
      if( off > myData.mySize )
      {
         cout << "string subscript out of range\n";
         exit( 1 );
      }

      return myData.myPtr()[ off ];
   }

   // Returns the length of the string, in terms of bytes.
   // This is the number of actual bytes that conform the contents of the string,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns the size of the storage space currently allocated for the string,
   // expressed in terms of bytes.
   // This capacity is not necessarily equal to the string length.
   // It can be equal or greater, with the extra space allowing the object
   // to optimize its operations when new characters are added to the string.
   size_type capacity() const
   {
      return myData.myRes;
   }

   // Returns whether the string is empty (i.e. whether its length is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

private:
   ScaryVal myData;
};

#endif // STRING