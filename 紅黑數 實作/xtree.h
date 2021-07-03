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
       TreeNode< value_type >* p = node->parent;
       TreeNode< value_type >* g = p->parent;
       if ( ( p == g->left && (g->right)->color == Color::Red ) || ( p == g->right && (g->left)->color == Color::Red ) )//XXR
       {
           /*p->color = Color::Black;//pu 紅色變黑色

           if(p == g->left)//gu的另外一個child 紅色變黑色
               (g->right)->color = Color::Black;
           else
               (g->left)->color = Color::Black;*/

           (g->right)->color = (g->left)->color = Color::Black;//gu的兩個child 紅色變黑色

            if (g->parent != myHead)//如果gu不是根節點 就把gu 黑色變紅色
            {
                g->color = Color::Red;
                if ((g->parent)->color == Color::Red)//如果因此違反規則2 就一路往上平衡
                    reBalance(g);
            }
       }
       else//XXB   LL RR 對稱   RL LR 對稱
       {//變色 旋轉
           g->color = Color::Red;

           if (node == p->left && p == g->left) /*&& (g->right)->color == Color::Black*/ //LL
           {
               p->color = Color::Black;
               /*g->color = Color::Red;*/
               LLRotation(p);
           }
           if (node == p->left && p == g->right) /*&& (g->left)->color == Color::Black*/ //RL
           {
               node->color = Color::Black;
               /*g->color = Color::Red;*/
               RLRotation(node);
           }
           if (node == p->right && p == g->left) /*&& (g->right)->color == Color::Black*/ //LR
           {
               node->color = Color::Black;
               /*g->color = Color::Red;*/
               LRRotation(node);
           }
           if (node == p->right && p == g->right) /*&& (g->left)->color == Color::Black*/ //RR
           {
               p->color = Color::Black;
               /*g->color = Color::Red;*/
               RRRotation(p);
           }
       }
   }

   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {
       TreeNode< value_type >* g = p->parent;

       if (g->parent == myHead)//如果g是根
           myHead->parent = p;//p變成新的根
       else
           if (g == (g->parent)->left)//以下順時針旋轉
               (g->parent)->left = p;
           else
               (g->parent)->right = p;

       p->parent = g->parent;
       g->left = p->right;

       if (p->right != myHead)//記得判斷 不然g會變根
           (p->right)->parent = g;

       g->parent = p;
       p->right = g;
   }

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< value_type > *node )
   {
       TreeNode< value_type >* p = node->parent;
       TreeNode< value_type >* g = p->parent;

       if (g->parent == myHead)//如果g是根
           myHead->parent = node;//node變成新的根
       else
           if (g == (g->parent)->left)//node跑到g的位置
               (g->parent)->left = node;
           else
               (g->parent)->right = node;

       node->parent = g->parent;

       g->left = node->right;//node右腳給g當新的左腳

       if (node->right != myHead)//記得判斷 不然g會變根
           (node->right)->parent = g;

       node->right = g;//g變成node右腳
       g->parent = node;

       p->right = node->left;//node左腳給p當新的右腳

       if (node->left != myHead)//記得判斷 不然p會變根
           (node->left)->parent = p;

       node->left = p;//p變成node左腳
       p->parent = node;
   }

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< value_type > *node )//完全對稱
   {
       TreeNode< value_type >* p = node->parent;
       TreeNode< value_type >* g = p->parent;

       if (g->parent == myHead)
           myHead->parent = node;
       else
           if (g == (g->parent)->left)
               (g->parent)->left = node;
           else
               (g->parent)->right = node;

       node->parent = g->parent;

       g->right = node->left;//node左腳給g當新的右腳

       if (node->left != myHead)
           (node->left)->parent = g;

       node->left = g;//g變成node左腳
       g->parent = node;

       p->left = node->right;//node右腳給p當新的左腳

       if (node->right != myHead)
           (node->right)->parent = p;
       
       node->right = p;//p變成node右腳
       p->parent = node;
   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )//完全對稱
   {
       TreeNode< value_type >* g = p->parent;

       if (g->parent == myHead)
           myHead->parent = p;
       else
           if (g == (g->parent)->left)//以下逆時針旋轉
               (g->parent)->left = p;
           else
               (g->parent)->right = p;

       p->parent = g->parent;
       g->right = p->left;

       if (p->left != myHead)
           (p->left)->parent = g;

       g->parent = p;
       p->left = g;
   }

   // erase node provided that the degree of node is at most one
   // 刪掉一個degree最多一的節點
   // degree就是有幾個真的小孩
   // 刪掉節點 指標連好
   void eraseDegreeOne( TreeNode< value_type > *node )  
   {
       TreeNode< value_type >* M = node;
       TreeNode< value_type >* P = node->parent;
       TreeNode< value_type >* C = node->left->isNil ? node->right : node->left;

       if (M->color == Color::Black && C->color == Color::Black && P->isNil)//M是黑色 C是黑色 M是根節點
       {//C變成新的根節點
           myHead->parent = C;
           C->parent = myHead;
           delete M;
           --mySize;
           return;
       }

       M == P->left ? P->left = C : P->right = C;//C是M的小孩
       if (!C->isNil)//如果C是真的節點就接好
           C->parent = P; //P接到C

       //M是黑色 C是黑色 M不是根節點
       if (M->color == Color::Black && C->color == Color::Black)/*(M->color == Color::Black && C->color == Color::Black && !P->isNil)*/
           fixUp(C, P);//有十種情況

       if (M->color == Color::Black && C->color == Color::Red)//M是黑色 C是紅色
           C->color = Color::Black;//C變黑色

       delete M;
       --mySize;

       /*if( node->color == Color::Black )
           fixUp( child, node->parent );

       delete node;
       mySize--;*/
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {//十種情況 五五對稱
        TreeNode< value_type > *S, *SL, *SR, *C = N;

        while (1)
        {
            if (C == P->left)//定義
            {
                S = P->right;
                SL = S->left;
                SR = S->right;
            }
            else//相反
            {
                S = P->left;
                SL = S->right;
                SR = S->left;
            }

            if (S->color == Color::Red)//case1 S 是紅色
            {
                P->color = Color::Red;//S 和 P 的顏色對調
                S->color = Color::Black;

                if (C == P->left)
                    RRRotation(S);//逆時針旋轉
                else//相反
                    LLRotation(S);//順時針旋轉
                // 會變成2 3 4其中一種
            }
            else
            {
                if (SR->color == Color::Red)//case2 S 是黑色, SR 是紅色
                {
                    S->color = P->color;//S 和 P 的顏色對調
                    P->color = Color::Black;
                    SR->color = Color::Black;//SR 紅色變黑色

                    if(C == P->left)
                        RRRotation(S);//逆時針旋轉
                    else//相反
                        LLRotation(S);//順時針旋轉

                    return;//結束
                }
                else
                {
                    if (SL->color == Color::Red)//case3 S 和 SR 是黑色, SL 是紅色
                    {
                        S->color = Color::Red;//SL 和 S 的顏色對調
                        SL->color = Color::Black;

                        if (C == P->left)
                            LLRotation(SL);//順時針旋轉
                        else//相反
                            RRRotation(SL);//逆時針旋轉

                        //會變成case2 所以不回傳 繼續處理
                    }
                    else
                    {
                        if (P->color == Color::Red)//case4 S 和 SR 和 SL 是黑色,  P 是紅色
                        {
                            P->color = Color::Black;// S 和 P 的顏色對調
                            S->color = Color::Red;
                            return;//結束
                        }
                        else//case5 S 和 SR 和 SL 和 P 是黑色
                        {
                            if (S != myHead)//如果S不是根節點
                                S->color = Color::Red;//S 黑色變紅色

                            if (P == myHead->parent)//如果P是根節點 結束
                                return;
                            else//如果P不是根節點 就把P變成新的C 重新平衡
                            {
                                C = P;
                                P = P->parent;
                            }
                        }
                    }
                }
            }
        }
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
       if (scaryVal.mySize == 0)//如果沒有元素
       {
           TreeNode< value_type >* root = new TreeNode< value_type >();//生成一個根節點
           
           root->myval = val;
           root->left = scaryVal.myHead;
           root->right = scaryVal.myHead;
           root->isNil = false;
           root->parent = scaryVal.myHead;
           root->color = Color::Black;
           scaryVal.myHead->left = root;
           scaryVal.myHead->parent = root;
           scaryVal.myHead->right = root;
           scaryVal.mySize = 1;
       }
       else//如果有元素
       {
           TreeNode< value_type >* node = scaryVal.myHead->parent;//節點指向根

           while (val != node->myval)//當前節點值跟插入值不同時
           {
               if (keyCompare(val, node->myval))//往左或往右跑 找到正確位置
                   if (node->left != scaryVal.myHead)
                       node = node->left;
                   else
                       break;
               else
                   if (node->right != scaryVal.myHead)
                       node = node->right;
                   else
                       break;
           }
           
           if (val != node->myval)//值不重複時
           {
               TreeNode< value_type >* newNode = new TreeNode< value_type >();//新增節點
               
               newNode->myval = val;
               newNode->left = scaryVal.myHead;//新增節點一定是leaf node
               newNode->right = scaryVal.myHead;
               newNode->isNil = false;
               newNode->parent = node;
               newNode->color = Color::Red;//新增節點一定是紅色
               scaryVal.mySize++;
               
               if (keyCompare(val, node->myval))//判斷新節點應該放哪裡
                   node->left = newNode;
               else
                   node->right = newNode;

               if (scaryVal.myHead->left->myval > val)//判斷新節點是否為全樹最小
                   scaryVal.myHead->left = newNode;

               if (scaryVal.myHead->right->myval < val)//判斷新節點是否為全樹最大
                   scaryVal.myHead->right = newNode;

               if (node->color == Color::Red)//如果違反規則二 就重新平衡
                   scaryVal.reBalance(newNode);
           }
       }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val ) // 找到右邊subtree裡面最小的 內容複製到要刪掉的節點 再把它刪掉
   {
       TreeNode< key_type >* node = scaryVal.myHead->parent;//從根開始

       while (node != scaryVal.myHead && node->myval != val)//尋找
       {
           if (keyCompare(val, node->myval))
               node = node->left;
           else
               node = node->right;
       }

       if (node == scaryVal.myHead)//沒找到
           return 0;
       else
       {
           if (node->left == scaryVal.myHead || node->right == scaryVal.myHead)//是能刪的點
               scaryVal.eraseDegreeOne(node);
           else
           {
               TreeNode< value_type >* rightSubtreeMin = node->right;

               while (rightSubtreeMin->left != scaryVal.myHead)//一路往左找
                   rightSubtreeMin = rightSubtreeMin->left;

               node->myval = rightSubtreeMin->myval;
               scaryVal.eraseDegreeOne(rightSubtreeMin);//刪掉右邊最小
           }

           return 1;
       }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE