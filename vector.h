/***********************************************************************
 * Header:
 *    VECTOR
 * Summary:
 *    Our custom implementation of std::vector
 *
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        vector                 : A class that represents a Vector
 *        vector::iterator       : An iterator through Vector
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
#include <new>      // std::bad_alloc
#include <memory>   // for std::allocator
#include <iostream> // DELETE ME
class TestVector; // forward declaration for unit tests
class TestStack;
class TestPQueue;
class TestHash;

namespace custom
{

/*****************************************
 * VECTOR
 * Just like the std :: vector <T> class
 ****************************************/
template <typename T>
class vector
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   
   // 
   // Construct
   //

   vector();
   vector(size_t numElements                );
   vector(size_t numElements, const T & t   );
   vector(const std::initializer_list<T>& l );
   vector(const vector &  rhs);
   vector(      vector && rhs);
   ~vector();

   //
   // Assign
   //

   void swap(vector& rhs)
   {
      custom::vector<int> temp;
      temp.data = this->data;
      temp.numElements = this->numElements;
      temp.numCapacity = this->numCapacity;
      
      this->data = rhs.data;
      this->numElements = rhs.numElements;
      this->numCapacity = rhs.numCapacity;
      
      rhs.data = temp.data;
      rhs.numElements = temp.numElements;
      rhs.numCapacity = temp.numCapacity;
      
      
      
      
   }
   vector & operator = (const vector & rhs);
    vector& operator = (vector&& rhs);

   //
   // Iterator
   //

   class iterator;
   iterator       begin() { return iterator(data);}
   iterator       end() { return iterator(data+numCapacity); }

   //
   // Access
   //

         T& operator [] (size_t index);
   const T& operator [] (size_t index) const;
         T& front();
   const T& front() const;
         T& back();
   const T& back() const;

   //
   // Insert
   //

   void push_back(const T& t);
   void push_back(T&& t);
   void reserve(size_t newCapacity);
   void resize(size_t newElements);
   void resize(size_t newElements, const T& t);

   //
   // Remove
   //

   void clear();
   void pop_back();
   void shrink_to_fit();

   //
   // Status
   //

   size_t  size()          const { return numElements;}
   size_t  capacity()      const { return numCapacity;}
   bool empty()            const
   {
       if (numElements <= 0)
       {
           return true;
       }
       else{
           return false;
       }
       
   }
   
   // adjust the size of the buffer
   
   // vector-specific interfaces
   
private:

   int nextCapacity();
   
   T *  data;                 // user data, a dynamically-allocated array
   size_t  numCapacity;       // the capacity of the array
   size_t  numElements;       // the number of items currently used
};


/**************************************************
 * Convenience function for finding the size of the
 * next buffer.
 **************************************************/
template<typename T>
int vector<T>::nextCapacity()
{
   assert(numCapacity >= 0);
   if (numCapacity == 0)
      return 1;
   return numCapacity * 2;
}

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <typename T>
class vector <T> ::iterator
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   // constructors, destructors, and assignment operator
   iterator()                           { p=NULL; }
   iterator(T* p)                       { this->p = p; }
   iterator(const iterator& rhs)        { *this = rhs; }
   iterator(size_t index, vector<T>& v) { this->p = v.data+index; }
   iterator& operator = (const iterator& rhs)
   {
      this->p = new T;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator& rhs) const { return true; }
   bool operator == (const iterator& rhs) const { return true; }

   // dereference operator
   T& operator * ()
   {
      //if(p == NULL){throw "Error: dereferencing null data in iterator.";}
      return *p;   }

   // prefix increment
   iterator& operator ++ ()
   {
      if(p != NULL){p++;}
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmpIterator(*this);
      if(p != NULL){p++;}
      return tmpIterator;
   }

   // prefix decrement
   iterator& operator -- ()
   {
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      return *this;
   }

private:
   T* p;
};

/*****************************************
 * VECTOR :: DEFAULT constructors
 * Default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector()
{
    
    data = NULL;
    //std::allocator<custom::vector<T>>alloc;
    //alloc.allocate(0);
   numCapacity = 0;
   numElements = 0;
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num, const T & t) 
{
   data = new T[num];
   numCapacity = num;
   numElements = num;
    for (int i = 0; i < num; i++)
    {
        data[i] = t;
    }
}

/*****************************************
 * VECTOR :: INITIALIZATION LIST constructors
 * Create a vector with an initialization list.
 ****************************************/
template <typename T>
vector <T> :: vector(const std::initializer_list<T> & l) 
{
   data = new T[l.size()];
   numCapacity = l.size();
   numElements = l.size();
   int counter = 0;
   std::initializer_list<int>::iterator it;
   for (it  = l.begin() ; it != l.end() ; it++)
   {
      data[counter] = *it;
      counter++;
   }
   
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num) 
{
   //data = new T[num];
    if (num <= 0)
    {
        data = NULL;
    }
    else{
        data = new T[num];
        for(int i = 0;i<num;i++)
        {
            data[i] = 0;
        }
    }
    
    numCapacity = num;
   numElements = num;
}

/*****************************************
 * VECTOR :: COPY CONSTRUCTOR
 * Allocate the space for numElements and
 * call the copy constructor on each element
 ****************************************/
template <typename T>
vector <T> :: vector (const vector & rhs) 
{
    
    if(rhs.empty())
    {
        data = NULL;
        numCapacity = 0;
        numElements = 0;
    }
    else{
        if(rhs.capacity() != rhs.size())
        {
            data = new T[rhs.size()];
            numCapacity = rhs.size();
        }
        else{
            data = new T[rhs.capacity()];
            numCapacity = rhs.capacity();
        }
       numElements = 0;
        for (int i =0;i<rhs.size();i++)
        {
            data[i] = rhs.data[i];
           numElements++;
        }
        
        
        
        
        /*for (int i =0;i<rhs.size();i++)
        {
            
            std::cout<< rhs.data[i] << std::endl;;
        }*/
        
        
        
    }
   
}

/*****************************************
 * VECTOR :: MOVE CONSTRUCTOR
 * Steal the values from the RHS and set it to zero.
 ****************************************/
template <typename T>
vector <T> :: vector (vector && rhs)
{
    
    this->data = rhs.data;
    this->numElements = rhs.size();
    this->numCapacity = rhs.capacity();
    if(rhs.capacity() == 0)
    {
        data = NULL;
        numCapacity = 0;
        numElements = 0;
    }
    /*else{
    
        
        if(rhs.capacity() != rhs.size())
        {
            data = new T[rhs.size()];
            numCapacity = rhs.size();
        }
        else{
            data = new T[rhs.capacity()];
            numCapacity = rhs.capacity();
        }
    for (int i =0;i<rhs.size();i++)
    {
        data[i] = rhs.data[i];
        numElements++;
        
    }
    }*/
    rhs.data = NULL;
    rhs.numCapacity = 0;
    rhs.numElements = 0;
   
   
   
}

/*****************************************
 * VECTOR :: DESTRUCTOR
 * Call the destructor for each element from 0..numElements
 * and then free the memory
 ****************************************/
template <typename T>
vector <T> :: ~vector()
{
    delete this->data;
}

/***************************************
 * VECTOR :: RESIZE
 * This method will adjust the size to newElements.
 * This will either grow or shrink newElements.
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: resize(size_t newElements)
{
   resize(newElements, 0);
}

template <typename T>
void vector <T> :: resize(size_t newElements, const T & t)
{
   if (newElements > numCapacity)
   {
      // Reallocate
      reserve(newElements);
   }
   if (newElements > numElements)
   {
      // Fill remaining space
      for (int i = numElements; i < newElements; i++) {
         data[i] = t;
      }
   }
   numElements = newElements;
}

/***************************************
 * VECTOR :: RESERVE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: reserve(size_t newCapacity)
{
   auto newData = new T[newCapacity];
   for (int i = 0; i < numElements; i++)
      newData[i] = data[i];
   delete data;
   data = newData;
   numCapacity = newCapacity;
}

/***************************************
 * VECTOR :: SHRINK TO FIT
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: shrink_to_fit()
{
   assert(numCapacity >= numElements); // Ensure we are actually shrinking
   numCapacity = numElements;
   if (numCapacity == 0)
   {
      data = nullptr;
   }
}



/*****************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: operator [] (size_t index)
{
   return data[index];
   
}

/******************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: operator [] (size_t index) const
{
   return data[index];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: front ()
{
   
   return data[0];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: front () const
{
   return data[0];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: back()
{
   return data[numCapacity-1];
}

/******************************************
 * VECTOR :: FRONT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: back() const
{
   return data[numCapacity-1];
}

/***************************************
 * VECTOR :: PUSH BACK
 * This method will add the element 't' to the
 * end of the current buffer.  It will also grow
 * the buffer as needed to accommodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 **************************************/
template <typename T>
void vector <T> :: push_back (const T & t)
{
   if (numElements == numCapacity)
      reserve(nextCapacity());
   data[numElements++] = t;
}

template <typename T>
void vector <T> ::push_back(T && t)
{
   // Not sure if this should just be copy-pasted from the other push_back...
   if (numElements == numCapacity)
      reserve(nextCapacity());
   data[numElements++] = t;
}

/***************************************
 * VECTOR :: ASSIGNMENT
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the vector to copy from
 *     OUTPUT : *this
 **************************************/
template <typename T>
vector <T> & vector <T> :: operator = (const vector & rhs)
{
   if (rhs.data !=NULL)
   {
      //data = rhs.data;
      
      this->numElements = rhs.size();
      if(this->numCapacity <rhs.capacity())
      {
         this->data = new T[rhs.capacity()];
         this->numCapacity = rhs.capacity();
      }
      
      //this->data = new T[rhs.size()];
      for (int i =0;i<rhs.size();i++ )
      {
          this->data[i] = rhs.data[i];
      }
   }
   
   return *this;
}

template <typename T>
vector <T>& vector <T> :: operator = (vector&& rhs)
{
   
   if (rhs.data != NULL)
   {
      
      data = rhs.data;
      this->numElements = rhs.size();
      this->numCapacity = rhs.capacity();
      this->data = new T[rhs.capacity()];
      for (int i =0;i<rhs.size();i++ )
      {
          this->data[i] = rhs.data[i];
      }
   }
   rhs.numCapacity = 0;
   rhs.numElements = 0;
   rhs.data = NULL;
   return *this;
}


template<typename T>
void vector<T>::pop_back() {
   if (numElements <= 0)
      return;
   numElements--;
}

template<typename T>
void vector<T>::clear()
{
   numElements = 0;
}


} // namespace custom

