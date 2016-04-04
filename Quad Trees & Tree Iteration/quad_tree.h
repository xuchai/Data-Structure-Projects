// ===================================================================
// We provide the Point class and the implementation of several
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>


// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point():x(number_type()),y(number_type()){};
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

// -------------------------------------------------------------------
// NODE CLASS 
template <class number_type,class label_type>
class Node {
public:
  //default constructor that arssigns all children and parent pointers to NULL 
  Node() :  parent(NULL) { 
    children[0]=NULL;
    children[1]=NULL;
    children[2]=NULL;
    children[3]=NULL;
  }
  //A constructor that takes in an initiated value as the labe
  Node(const label_type& init) : label(init), parent(NULL),children(NULL)
   {pt.x=number_type();pt.y=number_type(); }
   // A copy constructor that takes in a Point object as pt and an initiated value as label
  Node(const Point<number_type> &old, const label_type& init )
  :parent(NULL),children(), label(init)
  { pt.x= old.x;pt.y=old.y;}
  label_type label;
  Node<number_type,label_type>* children[4];
  Node<number_type,label_type>* parent; // to allow implementation of iterator increment & decrement
  Point<number_type> pt; 
}; 

template <class number_type,class label_type> class QuadTree;


// -------------------------------------------------------------------
// DEPTH ITERATOR CLASS
template <class number_type, class label_type>
class DepthIterator {
public:
  //CONSTRUCTORS
  //defualt constructor
  DepthIterator() : ptr(NULL){}
  // copy constructor that takes in a Node pointer and assign that pointer to ptr_
  DepthIterator(Node<number_type, label_type>* p) 
    : ptr(p) {}
  // copy constructor that takes in a DepthIerator and copy the old to a new one 
  DepthIterator(DepthIterator<number_type, label_type> *old) 
    : ptr(old->ptr){}



  // OPERATORS   
  // = assginment operator 
  DepthIterator<number_type, label_type>& operator=
    (const DepthIterator<number_type,label_type>& old){
      ptr=old.ptr;  return *this;
    }
  // operator* gives constant access to the Point object inside of the Node
  const Point<number_type>& operator*() const { return this->ptr->pt; }
  const Point<number_type>& operator*() { return this->ptr->pt; }

  // comparions operators for equals and not equals
  bool operator== (const DepthIterator& dit) { return (ptr == dit.ptr ); }
  bool operator!= (const DepthIterator& dit) { return (ptr!= dit.ptr); }


 // ACCESSORS
 // function that gives out the label of the Node that is pointed at
  const label_type& getLabel()const {return ptr->label;}


 // function that traverse back to the root of the 
 //tree and calculate the depth from the the 
  //currently pointed Node to the root 
  int getDepth()const{
    int depth=0;
    Node<number_type,label_type> *temp=ptr;
    while(temp->parent!=NULL){
      ++depth;
      temp=temp->parent;
    }
    return depth;
  };

  // An copy of the above function that is used for non const objects
  int getDepth(){
    int depth=0;
    Node<number_type,label_type> *temp=ptr;
    while(temp->parent!=NULL){
      ++depth;
      temp=temp->parent;
    }
    return depth;
  }


  // ACCESSING ITS CHILDREN
  //A function that returns the left-most child of the creetnyl pointed Node 
  Node<number_type,label_type>* left_most_child(Node<number_type,label_type>* current_node){
    Node<number_type,label_type>* temp=NULL;
    for( int i=0;i<4;++i){
      if(current_node->children[i]!=NULL){temp=current_node->children[i]; break;}
    }
    return temp; //left_most_child is possible to be null
  }

  // A function that returns the right-most child of the currently pointed Node 
  Node<number_type,label_type>* right_most_child(Node<number_type,label_type>* current_node){
    Node<number_type,label_type>* temp=NULL;
    for( int i=3;i>-1;--i){
      if(current_node->children[i]!=NULL){temp=current_node->children[i]; break;}
    }
    return temp; //right_most_child is possible to be null
  }

 // A function that retuens the number of non-NULL children of the Node currently pointed at
  int num_of_children(Node<number_type,label_type> *current_node){
    int num_children=0;
    for(int i=0;i<4;++i){
      if(current_node->children[i]!=NULL)++num_children;
    }
    return num_children;
  }


  //ACCESSING ITS SIBLINGS
  //A function that looks for the sibling of the currently pointed Node,
  // a sibling is the next child on the right side of the currently pointed Node's parent
  Node<number_type,label_type>* next_child_of_its_parent(const Node<number_type,label_type> *current_node, bool 
    &is_its_parents_leftmost, bool &is_its_parents_rightmost){
    if(current_node->parent !=NULL){ //eliminating empty trees
      Node<number_type,label_type>* temp=current_node->parent;
      if(current_node==right_most_child(temp)){
      //if the current node is the right_most child of its parent
        //modify the right-most indicator
        is_its_parents_rightmost=true;
        if(num_of_children(temp)==1) {
          // if the current node is also the only child of its parent 
          //modify the left-most indicator
          is_its_parents_leftmost=true;}
        else {
          //current_node is the RIGHT_most child of its parent, but not the only child
          //modify the left-most indicator
          is_its_parents_leftmost=false;
        }
        //in both cases, the current node has no sibling on its right side
        //thus return NULL   
        return NULL;
      }
      else if(current_node==left_most_child(temp)){
        // current_node is the LEFT_most child of its parent 
        //modify the left-most indicator
        is_its_parents_leftmost=true;
        if(num_of_children(temp)==1){
          //current_node is the left_most and the only child of its parent 
          //modify the right-most indicator
          is_its_parents_rightmost=true;   
          //the current node has no sibling at all  
          return NULL;
        }
        else{
          //current_node is the left_most child of its parent, but not the only child
          //modify the right-most indicator
          is_its_parents_rightmost=false;   
          Node<number_type,label_type> *temp_child=NULL;
          for(int i=0;i<4;++i){
            //finding the next child of current_node->parent when current_node
            //is the left_most child of its parent and there are other children
            //besides current_node, 
            //then the next child of current_node must be less than children[3] 
            if(temp->children[i]==current_node){
              //we've found the current child itself from its parent
              assert(i<3);
              for(int j=i+1;j<4;++j){
                //finding the next non-NULL sibling of current_node that is not NULL
                if(temp->children[j]!=NULL){
                  //assign to temp_child
                  temp_child=temp->children[j];
                  //and break once its sibling is found
                  break;
                }
                else continue;
              }
              //break once the next sibling of the current node is found
              break;
            }
          }
          //return its sibling
          return temp_child;
        }
      }
      else {
        //current_node is neither the left_most child nor the right_most child
        //then current_node->parent must has more than one children
        assert(num_of_children(temp)>1);
        //modify the left-most and right-most indicator
        is_its_parents_leftmost=false;
        is_its_parents_rightmost=false;
        Node<number_type,label_type> *temp_child=NULL;
        //finding the next child of current_node->parent
        for(int i=0;i<4;++i){
          //we've found the current child itself from its parent
          if(temp->children[i]==current_node){
            //the current better not be the last child of its parents,
            //otherwise, this contradicts the condition
            assert(i<3);
            for(int j=i+1;j<4;++j){
                //finding the next sibling of current_node that is not NULL
                if(temp->children[j]!=NULL){
                  //assign to temp_child
                  temp_child=temp->children[j];
                  //and break once its sibling is found
                  break;
                }
                else continue;
              }
              //break once the next sibling of the current node is found
              break;
            }          
          }
          return temp_child;
        }
      }
      else{
        //it is an empty Node
        // current_node ==root_
        is_its_parents_leftmost=true;
        is_its_parents_rightmost=true;
        return NULL;

      }
  
    }



  // increment & decrement operators
  //overwrite the operator ++ to perform a depth first visit on Nodes
  DepthIterator<number_type,label_type> & operator++() {  // pre-increment, ++itr
    if(ptr!=NULL){
      if(num_of_children(ptr)!=0){ 
        // std::cout<<ptr->label<<" is NOT a leaf node "<<std::endl;
        //if we are not at leaf node, than return the left_most child
        ptr=left_most_child(ptr);
        return *this;
      }
      else{
        // the current node is a leaf node 
        bool is_its_parents_leftmost, is_its_parents_rightmost;
        //we are at a leaf node
        if(next_child_of_its_parent(ptr,is_its_parents_leftmost, is_its_parents_rightmost)!=NULL){
          //if the node we currently at is a leaf node and has a sibling node next to it,
          //then find its sibling next to is on the right side
          ptr=next_child_of_its_parent(ptr,is_its_parents_leftmost, is_its_parents_rightmost);
          return *this;
        }
        else{
          //if the node we currently at has no sibling to the right
          //(it is the right_most child of its parent),
          //which means all the children of its parent have been visited
          //then return up until we find a parent node who has a child node on
          //the right to the node we have(which has not been visited yet)
          bool is_its_parents_leftmost, is_its_parents_rightmost;

          // the current Node has no sibling on its right
          Node<number_type,label_type>* temp_1=next_child_of_its_parent(ptr,is_its_parents_leftmost, is_its_parents_rightmost);
          // the result of the above function better be NULL and the right-most indicator better be true         
          assert((is_its_parents_rightmost==true)&& (temp_1==NULL));
          Node<number_type,label_type> *temp=ptr;
          while((temp->parent!=NULL)&&(is_its_parents_rightmost)){
            temp=temp->parent;
            next_child_of_its_parent(temp,is_its_parents_leftmost, is_its_parents_rightmost);

          }

          if(temp->parent==NULL){
            ptr=NULL;
            return *this; }
          else{
            ptr=next_child_of_its_parent(temp,is_its_parents_leftmost, is_its_parents_rightmost);
            return *this;
          }
        } 
      }
    }
    else {
      // std::cout<<" ptr starts as NULL"<<std::endl;
      ptr=NULL;
      return *this;
    }
  }


 //same functionality with the above function but used for post-increment itr++
  DepthIterator<number_type,label_type> operator++(int){
    DepthIterator<number_type,label_type> temp(*this);
    ++(*this);
    return temp;
  } 



private:
  // representation
  Node<number_type,label_type>* ptr;

};

// -------------------------------------------------------------------
// BREADTH ITERATOR CLASS
template <class number_type, class label_type>
class BreadthIterator {
public:
  //CONSTRUCTORS
  //constructor
  BreadthIterator() : ptr(NULL) {}
  // copy constructor that takes in a Node pointer and assign that pointer to ptr
  BreadthIterator(Node<number_type, label_type>* p) : ptr(p) {}
  // copy constructor that takes in a BreadthIerator and copy the old to a new one 
  BreadthIterator(BreadthIterator<number_type, label_type>* old) : ptr(old->ptr) {}

  //OPERATORS
  // = assginment operator 
  BreadthIterator<number_type, label_type>& operator=
    (const BreadthIterator<number_type,label_type>& old){
      ptr=old.ptr; return *this;
    }
  // operator* gives constant access to the label at the pointer
  const Point<number_type>& operator*() const { return this->ptr->pt; }
  const Point<number_type>& operator*(){ return this->ptr->pt; }
  // comparions operators are straightforward
  bool operator== (const BreadthIterator& bit) { return (ptr == bit.ptr ); }
  bool operator!= (const BreadthIterator& bit) { return (ptr!= bit.ptr); }
  

  //ACCESSORS
  const label_type& getLabel()const {return ptr->label;}

  int getDepth()const{
    int depth=0;
    Node<number_type,label_type> *temp=ptr;
    while(temp->parent!=NULL){
      ++depth;
      temp=temp->parent;
    }
    return depth;
  };
  int getDepth(){
    int depth=0;
    Node<number_type,label_type> *temp=ptr;
    while(temp->parent!=NULL){
      ++depth;
      temp=temp->parent;
    }
    return depth;
  }

  // PRE ++ OPERATOR
  BreadthIterator<number_type,label_type> &operator++ () {
      if(ptr==NULL){
        //eliminating empty tree and if
        //current_node is pointing to a NULL tree node
        return *this;
      }
      else  {
        //find the depth of the current_node
        int depth=this->getDepth();
        //then traverse up to the root node
        Node<number_type,label_type>* temp_root=ptr;
        while(temp_root->parent!=NULL){temp_root=temp_root->parent; }
        assert(temp_root->parent==NULL);
        //then we have current_node pointing to the current node, and 
        //temp_root pointing to the root of the entire tree
        //do a breadth_first while loop that collects 
        //all node pointers in the same level with current_node

        //create a vector that will collect all node in the current_level
        std::vector<Node<number_type,label_type>*> current_level;
        //fisrt from the root
        current_level.push_back(temp_root);
        // use bottom_level to indicate the bottom level
        bool bottom_level=false;

        //if we haven't reached the current level 
        //and the number of node in the current level is not== 0,
        // which means we have not reached the bottom level of the entire tree yet
        //continue moving to the next level
        while ( (depth>0)&&(current_level.size() != 0)) {
          //create a list to collect all nodes in the next level
          std::vector<Node<number_type,label_type>*> next_level;
          //for each node in the current level list, 
          //we push_back all its non-NULL children
          for (int i=0;i<current_level.size(); ++i) {
            if (current_level[i]->children[0] != NULL) { next_level.push_back(current_level[i]->children[0]); }
            if (current_level[i]->children[1] != NULL) { next_level.push_back(current_level[i]->children[1]); }
            if (current_level[i]->children[2] != NULL) { next_level.push_back(current_level[i]->children[2]); }
            if (current_level[i]->children[3] != NULL) { next_level.push_back(current_level[i]->children[3]); }
          }
          //if are not at the bottom level yet,
          //we swap the current_level collection with the next_level and proceed to the next level
          if(next_level.size()>0){
            current_level = next_level;
            --depth; //decrement depth
          }
          else {
            // the current node is at the bottom level
            //else if we have no node in the next_level, 
            //then we have reached the bottomm level   
            // make the indicator true and exit looping 
            bottom_level=true;
            --depth;//decrement depth
            //depth better be 0, or we have problem in claculating the depth of the current_node
            break;}

          // we have keep both current_level and next_level for detecting the bottom level
        }

        //then current_level vector can never be empty

        //if by the end of the while loop, we have reached the bottom 
        //level current_level.size()==0
        //but the level that contains the current_node has not yet been reached
        //depth>0
        // then there is a logic bug 
      
        //if depth>0, then we have not found the level that contains the current_node, 
        //that means somthing is wrong in our depth() calculation or the above while loop


        assert((depth==0)&&(current_level.size()>0));

        // if we have reached the bottom level and this is the level that contains the current_node
        if((bottom_level) &&(depth==0)){
          std::cout<<"the bottom level and this is the level that contains the current_node"<<std::endl;
          // special case : when we are at the very last element of the entire tree
          if(ptr==current_level[current_level.size()-1]){ ptr=NULL;   return *this;} 

          // else the current_node is in the bottom level but not the last element
          else{
            //return the next child in current_level
            //first find itself within the current_level
            for(int i=0;i<current_level.size();++i){
              if(current_level[i]==ptr){
                //check the current_node is not the last element in current_level
                assert(i<current_level.size()-2);
                //then return the next sibling of the current node
                ptr=current_level[i+1]; break;
              }
              else continue;
            }
            return *this;
          }
        }
        //if the current_node resides at a level higher than the bottom level
        else if( (depth==0)&&(!bottom_level)){
          //two case 
          //1. current_node is not the last one (in the middle/ or front) of the current_level vector
          if(ptr!= current_level[current_level.size()-1]){
            //just find itself from the current_level and return the next node
            for(int i=0;i<current_level.size();++i){
              if(current_level[i]==ptr){
                //check it is not the last element
                assert(i<current_level.size()-1);
                //then return its next sibling
                ptr=current_level[i+1];break;
              }
              else continue;
            }
            return *this;
          }
          //else current_node is the last elment of in the current_level
          else{
             //we have to collect another level of node for special case: we are at the last element of the current_node
            //then go and collect all the nodes in the next level
            std::vector<Node<number_type,label_type>*> temp_next_level;
            for(int i=0;i<current_level.size();++i){
              if(current_level[i]->children[0]!=NULL){temp_next_level.push_back(current_level[i]->children[0]);}
              if(current_level[i]->children[1]!=NULL){temp_next_level.push_back(current_level[i]->children[1]);}
              if(current_level[i]->children[2]!=NULL){temp_next_level.push_back(current_level[i]->children[2]);}
              if(current_level[i]->children[3]!=NULL){temp_next_level.push_back(current_level[i]->children[3]);}

            }
            // if the next level has no node, then we are at the last element of the entire tree
            //return NULL
            if(temp_next_level.size()==0){ptr=NULL; return *this;}
            else{
              //else, just return the first node in the next level
              ptr=temp_next_level[0];
              return *this;
            }
          }

        }
        else{
          // other cases besides what we have above will result a NULL pointer
          ptr=NULL;
          return *this;
        }
      }
  }

  //POST ++ OPERATOR
  BreadthIterator<number_type,label_type> operator++(int){
    BreadthIterator<number_type,label_type> temp(*this);
    ++(*this);
    return temp;
  } 



private:
  // representation
  Node<number_type,label_type>* ptr;
};


// -------------------------------------------------------------------
// QUADTREE CLASS
template<class number_type, class label_type>
class QuadTree{

public:
  //CONSTRUCTORS
  //default constructor
  QuadTree():root_(NULL), size_(0){}
  // copy constructor that takes in a Node pointer and assign that pointer to root_
  QuadTree(Node<number_type, label_type>* p) : root_(p) {}
  // copy constructor that takes in a QuadTree and copy the old to a new one 
  QuadTree(const QuadTree<number_type, label_type> &old) : size_(old.size_) {
    root_ = this->copy(old.root_,NULL);
  }

  // = assginment operator 
  QuadTree<number_type, label_type>& operator=
    (const QuadTree<number_type,label_type> &old){
      if(&old!=this){ // if we are not copying from ourselves
        this->destroy(root_);// first destroy what we have now
        root_=this->copy(old.root_,NULL);// then copy the given tree
        size_=old.size_;
      }
      return *this; //return the QuadTree object by deferencing this pointer
  }
  
  //DECONSTRUCTOR
  ~QuadTree(){
    //a post order destroy function that deletes all node objects on heap mempry
    this->destroy(root_);
    root_=NULL;
  } 
  

  //define the two types of iterators
  typedef BreadthIterator<number_type, label_type> bf_iterator;
  typedef DepthIterator<number_type, label_type> iterator;


  //ACCESSORS
  //function that returns how many Node are in the tree
  unsigned int size()const{ return size_;}

  //retuens a NULL pointer wrapped into a depthiterator for the end of the tree
  iterator end() const { Node<number_type,label_type>* temp=NULL;  return iterator(temp); }
  //retuens a NULL pointer wrapped into a breadthiterator for the end of the tree
  bf_iterator bf_end() const { Node<number_type,label_type>* temp=NULL;  return bf_iterator(temp); }
  //retuens a pointer to the root of the tree, wrapped into a breadthiterator 
  bf_iterator bf_begin() const {   return bf_iterator(root_); }
  //retuens a pointer to the root of the tree, wrapped into a depthiterator 
  iterator begin() const { return iterator(root_);}

  // function that gives out the height of the entire tree
  int height() {   
    // use the private height function to calculate 
    //the max distance of each sub-trees from the root
    return height(root_);
  }
  






  //MODIFIERS
  //clear function that clean out the current QuadTree
  //using the destroy function
  //used in student test cases
  void clear(){
    this->destroy(root_);
    root_=NULL;
  }

  //public insert function that takes in a Point 
  //object and insert it properly in the tree 
  std::pair<iterator,bool> insert( const Point<number_type> &p, const label_type& key_value){
    //if we have an empty tree
    if(root_==NULL){
      //create a new Node object
      root_=new Node<number_type,label_type>(p,key_value);
      //make this Node as the root of the tree
      root_->parent=NULL;
      //increment size_
      ++(this->size_);
      //return a pointer to this new Node
      return std::pair<iterator,bool> (iterator (root_),true);
    }

    else {
      //we already have some nodes in the tree
      Node<number_type,label_type>* temp= root_;
      //then use the private insert function to navigate
      //the new Node to be put in a proper place
      return insert(p, key_value, temp, temp->parent);
    }
  }



  //the find function returns either a pointer to the founded tree node
  //or NULL if such node is not in the tree
  iterator find(const label_type &x,const label_type &y) { return find(x,y,root_);}









// ==============================================================
// PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
// ==============================================================

// NOTE: this function only works for quad trees with non negative
// integer coordinates and char labels

// NOTE2: this function assumes that no two points have the same x
// coordinate or the same y coordinate.

// plot driver function
// takes in the maximum x and y coordinates for these data points
// the optional argument draw_lines defaults to true
void plot(int max_x, int max_y, bool draw_lines=true) const {
  // allocate blank space for the center of the board
  std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
  // edit the board to add the point labels and draw vertical and
  // horizontal subdivisions
  plot(root_,board,0,max_x,0,max_y,draw_lines);
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  for (int i = 0; i <= max_y; i++) {
    // print each row of the board between vertical border bars
    std::cout << "|" << board[i] << "|" << std::endl;
  }
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
}


// actual recursive function for plotting

void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
          int x_min, int x_max, int y_min, int y_max, bool draw_lines) const 
{
  // base case, draw nothing if this node is NULL
  if (p == NULL) return;
  // check that the dimensions range of this node make sense
  assert (x_min >= 0 && x_min <= x_max);
  assert (board.size() >= y_max);
  assert (board[0].size() >= x_max);
  // verify that the point stored at this node fits on the board
  assert (p->pt.y >= 0 && p->pt.y < board.size());
  assert (p->pt.x >= 0 && p->pt.x < board[0].size());
  // draw the vertical and horizontal bars extending across the
  // range of this node
  if (draw_lines) {
    for (int x = x_min; x <= x_max; x++) {
      board[p->pt.y][x] = '-';
    }
    for (int y = y_min; y <= y_max; y++) {
      board[y][p->pt.x] = '|';
    }
  }
  // draw this label
  board[p->pt.y][p->pt.x] = p->label;
  // recurse on the 4 children
  plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
  plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
}


// ==============================================================

// prints all of the tree data with a pre-order (node first, then
// children) traversal of the tree structure

// driver function
void print_sideways() const { print_sideways(root_,""); }

// actual recursive function
void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
  // base case
  if (p == NULL) return;
  // print out this node
  std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
  // recurse on each of the children trees
  // increasing the indentation
  print_sideways(p->children[0],indent+"  ");
  print_sideways(p->children[1],indent+"  ");
  print_sideways(p->children[2],indent+"  ");
  print_sideways(p->children[3],indent+"  ");
}

// ==============================================================
// ==============================================================


friend class DepthIterator<number_type, label_type>;
friend class BreadthIterator<number_type, label_type>;
private:
  Node<number_type,label_type>* root_;
  unsigned int size_;


  std::pair<iterator,bool> insert(const Point<number_type> &p,const label_type& key_value, 
    Node<number_type, label_type>* &child,Node<number_type, label_type>* &the_parent){ 
    // have to pass those two pointers by reference
    // if not, any modification of the objects they pointed to will not 
    //apply to the actual object structured in the tree

      
    //base case
    //if the child is NULL, which means the root_is still NULL
    //create a new Node object and assign to root_, return the pair
    if((!child) ){
      child=new Node<number_type,label_type>(p , key_value);
      child->parent=the_parent;
      //increment size_
      ++(this->size_);
      return std::pair<iterator,bool>(iterator(child),true);}

    //if a duplicated Point object is given, then return a pointer 
    //to that existing point and return false;
    if((child->pt.x)==(p.x)&&(child->pt.y)==(p.y)){
      return std::pair<iterator,bool>(iterator(child),false);
    }

    else if((p.x)<=(child->pt.x)&&(p.y)<(child->pt.y)){
      //the new Point belongs to the first Quadrant of its parent 
      return insert(p,key_value,child->children[0],child);

    }
    else if((p.x)>(child->pt.x)&&(p.y)<=(child->pt.y)){
      //the new Point belongs to the second Quadrant of its parent 
      return insert(p,key_value,child->children[1],child);
    }

    else if((p.x)<(child->pt.x)&&(p.y)>=(child->pt.y)){
      //the new Point belongs to the third Quadrant of its parent 
      return insert(p,key_value,child->children[2],child);
    }

    else if((p.x)>=(child->pt.x)&&(p.y)>(child->pt.y)){
      //the new Point belongs to the fourth Quadrant of its parent 
      return insert(p,key_value,child->children[3],child);
    }

    else 
      //other points that can not be added in to the class
      return std::pair<iterator,bool>(iterator(child), false);
  }



  // private copy function that are used in constructors and the = operator
  // it takes all
  Node<number_type,label_type>* copy(
  Node<number_type,label_type>* old,
  Node<number_type,label_type>* the_parent)
{
  if(old==NULL) return NULL;// if it's an empty tree, return NULL
  //else, do a pre-order copying process that visit all nodes in the tree
  Node<number_type,label_type>* temp=
   new Node<number_type,label_type>(old->pt,old->label);
  temp->children[0]=copy(old->children[0],temp);
  temp->children[1]=copy(old->children[1],temp);
  temp->children[2]=copy(old->children[2],temp);
  temp->children[3]=copy(old->children[3],temp);
  temp->parent=the_parent;
  return temp;
}



 // private height function that digs into the tree to find the maximum height in pre-order 
  int height(Node<number_type,label_type>* qt){
    if(qt==NULL) return -1; //an empty tree has height -1
    // if we are at either a leaf node or the root node, return 0
    if((qt->children[0]==NULL) && (qt->children[1]==NULL) &&(qt->children[2]==NULL)&&(qt->children[3]==NULL))
      return 0;
    //go find the height of all four sub-trees
    int A=height(qt->children[0]);
    int B=height(qt->children[1]);
    int C=height(qt->children[2]);
    int D=height(qt->children[3]);
    //return the maximum height of the entire tree
    return 1+std::max((std::max(A,B)),(std::max(C,D)));
  }

 // private find function that searchs the desired Node from the root of the tree in pre-order 
  iterator find(const label_type &X, const label_type &Y, Node<number_type,label_type>* qt){
    //if it is a NULL pointer, return NULL
    if(!qt) return end(); 
    // if the given point falls into qt's first quandrant
    if((X<= qt->pt.x)&&(Y< qt->pt.y))
      //go and search in the first quandrant
      return find(X,Y,qt->children[0]);

    // if the given point falls into qt's second quandrant
    else if((X> qt->pt.x)&&(Y<= qt->pt.y))
      //go and search in the second quandrant
      return find(X,Y,qt->children[1]);

    // if the given point falls into qt's third quandrant
    else if((X< qt->pt.x)&&(Y>= qt->pt.y))
      //go and search in the third quandrant
      return find(X,Y,qt->children[2]);

    // if the given point falls into qt's fourth quandrant
    else if((X>= qt->pt.x)&&(Y> qt->pt.y))
      //go and search in the fourth quandrant
      return find(X,Y,qt->children[3]);

    // if the given point doesn't fall into any of qt's  quandrants
    //return a poiter to itself
    else return iterator(qt);
  }  

  // private desrtoy function that delete all Node objects in post-order 
  void destroy(Node<number_type,label_type>* p) {
    if (!p) return;
    //delete all nodes in the first quandrant
    destroy(p->children[0]);
    //delete all nodes in the second quandrant
    destroy(p->children[1]);
    //delete all nodes in the third quandrant
    destroy(p->children[2]);
    //delete all nodes in the fourth quandrant
    destroy(p->children[3]);
    delete p;
  }


};
#endif
