#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  clear();
  delete(head_);
}

/**
 * Inserts a new node at the end of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  Node * ins = new Node(ndata);
  Node * temp = head_->prev;

  ins->next = head_;
  head_->prev = ins;

  ins->prev = temp;

  temp->next = ins;
  length_++;
}

/**
 * Modifies the Chain by moving the subchain of len Nodes,
 * starting at position startPos, dist positions toward the
 * end of the chain.  If startPos + len - 1 + dist > length
 * then dist = length - startPos - len + 1 (to prevent gaps
 * in the new chain).
 * The subchain occupies positions (startPos + dist) through
 * (startPos + dist + len - 1) of the resulting chain.
 * The order of subchain nodes is not changed in the move.
 * You may assume that: 1 <= startPos <= length - len + 1,
 * 0 <= dist <= length, and 0 <= len <= length.
 */
void Chain::moveBack(int startPos, int len, int dist){
    if(dist != 0) {
    
    if (startPos + len - 1 + dist > length_) {
      dist = length_ - startPos - len + 1;
    }

    Node * start = walk(head_,startPos);
    Node * end =   walk(head_,startPos + len - 1);
    Node * preMoveNext = end->next;
    Node * preMovePrevious = start->prev;

    
    Node * postMovePrevious = walk(head_, startPos + len - 1 + dist);
    Node * postMoveNext = postMovePrevious->next;

    
    preMovePrevious->next = preMoveNext;
    preMoveNext->prev = preMovePrevious;
    
    start->prev = postMovePrevious;
    end->next = postMoveNext;
    
    postMovePrevious->next = start;
    postMoveNext->prev = end;
    
    }

}


/**
 * Modfies the current chain such that a node at position i swaps with a node at position n-i
 * That is node a node with distance x from the sentinel node, should swap with another node of distance x
 * Should only touch nodes within limit distance of the sentinel
 *
 * @param limit the maximum distance from the sentinel to swap at, so at most 2*limit nodes should be affected
 *      You may assume that 2*limit <= _length, so there will always be enough nodes to swap
 *
 */
void Chain::mirrorSwap(int limit){
  int counter = 1;
  int ending = (length_ - counter +1 );
    while(counter <= limit){
      if (counter == length_ / 2) {
          Node* first = walk(head_, counter);
          Node* tail = walk(head_, ending);
          Node* tailNext = tail->next;
          Node* firstPrev = first->prev;
          first->next = tailNext;
          tailNext->prev = first;
          first->prev = tail;
          tail->next = first;
          tail->prev = firstPrev;
          firstPrev->next = tail;
        } else {
        Node* first = walk(head_, counter);
        Node* tail = walk(head_, ending);
        Node* tailNext = tail->next;
        Node* tailPrev = tail->prev;
        Node* firstNext = first->next;
        Node* firstPrev = first->prev;
        first->next = tailNext;
        tailNext->prev = first;
        first->prev = tailPrev;
        tailPrev->next = first;
        tail->next = firstNext;
        firstNext->prev = tail;
        tail->prev = firstPrev;
        firstPrev->next = tail;
      }
    counter++;
    ending--;
   }
}


/**
 * Removes every block where the average saturation is greater than 'threshold'
 * Should also update _length to accurately reflect the new chain length
 *
 * eg: if we set threshold = 0, the function will remove all blocks with color
 * @param threshold the maximum allowable saturation value in a block
 */
void Chain::lazyFilter(double threshold){
    Node * temp = head_->next;
    //cout<<length_<<endl;

    while (temp!=head_){
      double sat = temp->data.avgSaturation();
      Node * tempNext = temp->next;
      Node * tempPrev = temp->prev;
      

      if (sat > threshold) {
        delete temp;
       // cout<<"WE MADE IT"<<endl;
        tempNext->prev = tempPrev;
        tempPrev->next = tempNext;
        length_--;
      }
    temp = tempNext;
  }
 // cout<<length_<<endl;

}

/*
* Modifies both the current chain and the "other" chain by removing
* nodes from the other chain and adding them between the nodes
* of the current chain -- one "other" node between two current nodes --
* until one of the two chains is exhausted.  Then the rest of the
* nodes in the non-empty chain follow.
* The length of the resulting chain should be the sum of the lengths
* of current and other. The other chain should have only
* the head_ sentinel at the end of the operation.
* The weave fails and the original
* chains should be unchanged if block sizes are different.
* In that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
if (height_ != other.height_ || width_ != other.width_){
    cout << "Block sizes differ." << endl;
    return;
  }
  else if (other.length_ == 0) {
    return;
  }
  else {
    Node * thisNode = head_->next->next;
    Node * otherNode = other.head_->next;
    Node * otherNextNode;

      while (other.head_ != otherNode && head_->next != thisNode) {

        otherNextNode = otherNode->next;

        otherNode->prev = thisNode->prev;
        otherNode->next = thisNode;
        thisNode->prev->next = otherNode;
        thisNode->prev = otherNode;

        otherNode = otherNextNode;
        thisNode = thisNode->next;
      }

      if (length_ < other.length_) {
        otherNextNode = otherNode->next;
        otherNode->prev->next = otherNode;
        otherNode = otherNextNode;
        while (otherNode != other.head_) {
          otherNextNode = otherNode->next;
          otherNode = otherNextNode;
        }
        otherNode->prev->next = head_;
        head_->prev = otherNode->prev;
      }

      length_ += other.length_;
      other.length_ = 0;
      other.head_->next = other.head_;
      other.head_->prev = other.head_;
  }


  //  if (width_ != other.width_ || height_ != other.height_) {
  //    cout << "Block sizes differ." << endl;
  //    return;
  //  } else if (other.length_ == 0) {
  //    return;
  //  } else {

  //  Node * mainChain = head_->next;
  //  Node * ref = other.head_;
  //  Node * secondaryChain = ref->next;
  
  // if (length_>other.length_) {

  //  while (secondaryChain != ref) {
  //    Node * afterNode = mainChain->next;
  //    Node * temp = secondaryChain->next;
  //    mainChain->next = secondaryChain;
  //    afterNode->prev = secondaryChain;
  //    secondaryChain->next = afterNode;
  //    secondaryChain->prev = mainChain;

  //    mainChain = afterNode;
  //    secondaryChain = temp;
  //    length_++;
  //    other.length_ -= 1;
  //  }
   
  // } else {
  //   while(mainChain != head_) {
  //    Node * afterNode = mainChain->next;
  //    Node * temp = secondaryChain->next;
  //    mainChain->next = secondaryChain;
  //    afterNode->prev = secondaryChain;
  //    secondaryChain->next = afterNode;
  //    secondaryChain->prev = mainChain;

  //    mainChain = afterNode;
  //    secondaryChain = temp;
  //    length_++;
  //    other.length_ -= 1;
  //   }

  //   while(secondaryChain != ref) {
  //     Node * beforeLast = head_->prev;
  //     head_->prev = secondaryChain;
  //     beforeLast->next = secondaryChain;
  //     secondaryChain = secondaryChain->next; 
  //   }
  // }
  //  }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class except for the sentinel head_. Sets length_
 * to zero.  After clear() the chain represents an empty chain.
 */
void Chain::clear() {
  Node* top = head_;
  
  for (int i = length_; i > 0; i--) {
    Node* temp = walk(top,i);
    delete(temp);
  }

  head_->prev = head_;
  head_->next = head_;

  length_ = 0;

}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
  Node * temp = other.head_->next;
  height_= other.height_;
  width_= other.width_;

  for (int i = 0; i < other.length_; i++) {
    insertBack(temp->data);
    temp = temp->next;
  }
 // cout << length_ << endl;

}
