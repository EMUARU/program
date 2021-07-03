// xtree internal header

#ifndef XTREE
#define XTREE

enum class Color{ Red, Black }; // colors for link to parent

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
   using value_type = Ty;

   NodePtr    left;   // left subtree, or smallest element if head
   NodePtr    parent; // parent, or root of tree if head
   NodePtr    right;  // right subtree, or largest element if head
   Color      color;  // Red or Black, Black if head
   bool       isNil;  // true only if head (also nil) node
   value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = Color::Black;
      myHead->isNil = true;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion
   void reBalance( TreeNode< value_type > *node )
   {  // node->parent cannot be the root

   }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {

   }

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< value_type > *node )
   {

   }

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< value_type > *node )//完全對稱
   {

   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )//完全對稱
   {

   }

   // erase node provided that the degree of node is at most one
   // 刪掉一個degree最多一的節點
   // degree就是有幾個真的小孩
   // 刪掉節點 指標連好
   void eraseDegreeOne( TreeNode< value_type > *node )  
   {


       /*if( node->color == Color::Black )
           fixUp( child, node->parent );

       delete node;
       mySize--;*/
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {

   }
//410
   // preorder traversal and inorder traversal
   void twoTraversals()
   {
      cout << "Preorder sequence:\n";
      preorder( myHead->parent );

      cout << "\nInorder sequence:\n";
      inorder( myHead->parent );
      //cout << endl;
   }

   // preorder traversal
   void preorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         preorder( node->left );
         preorder( node->right );
      }
   }

   // inorder traversal
   void inorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         inorder( node->left );
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         inorder( node->right );
      }
   }

   NodePtr myHead;   // pointer to head node
   size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
   using value_type = typename Traits::value_type;

protected:
   using ScaryVal = TreeVal< value_type >;

public:
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
       

   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val ) // 找到右邊subtree裡面最小的 內容複製到要刪掉的節點 再把它刪掉
   {

   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE