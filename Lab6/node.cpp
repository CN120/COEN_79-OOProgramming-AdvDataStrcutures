// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        size_t answer;
        
        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            ++answer;
        
        return answer;
    }
    
    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
        head_ptr = new node(entry, head_ptr);
    }
    
    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
        node *insert_ptr;
        
        insert_ptr = new node(entry, previous_ptr->link( ));
        previous_ptr->set_link(insert_ptr);
    }
    
    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        const node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    void list_head_remove(node*& head_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = head_ptr;
        head_ptr = head_ptr->link( );
        delete remove_ptr;
    }
    
    void list_remove(node* previous_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = previous_ptr->link( );
        previous_ptr->set_link( remove_ptr->link( ) );
        delete remove_ptr;
    }
    
    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }
    
    //duplicates source and creates a new linked list with head_ptr pointing to its head, and tail_ptr pointing to to its tail
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        
        // Handle the case of the empty list.
        if (source_ptr == NULL)
            return;
        
        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, source_ptr->data( ));
        tail_ptr = head_ptr;
        
        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        source_ptr = source_ptr->link( );
        while (source_ptr != NULL)
        {
            list_insert(tail_ptr, source_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            source_ptr = source_ptr->link( );
        }
    }
    
    //creates a new linked list from a subset of a given linked list
    //begins at start_ptr and goes up to but not including end_ptr
    //sublist has head head_ptr and tail tail_ptr
    void list_piece(node* start_ptr, node* end_ptr, node* &head_ptr, node* &tail_ptr){
        if (start_ptr==NULL){
            //nothing to do in this case
            head_ptr = NULL;
            tail_ptr=head_ptr;
        }
        else if(start_ptr==end_ptr){
            //still nothing to do
            head_ptr =NULL;
            tail_ptr=head_ptr;
        }
        else{
            head_ptr = new node(start_ptr->data());
            tail_ptr = head_ptr;
            //will keep inserting and moving tail_ptr until end_ptr is found
            while (start_ptr->link()!=end_ptr) {
                list_insert(tail_ptr, start_ptr->link()->data());
                tail_ptr = tail_ptr->link();
                start_ptr = start_ptr->link();
            }
            
        }
        
    }
    
    //returns number of occurances of target in the list
    size_t list_occurrences(node* head_ptr, const node::value_type &target){
        size_t count=0;
        for(node* cursor = head_ptr; cursor->link()!=NULL; cursor=cursor->link()){
            //checks each node
            if (cursor->data()==target){
                ++count;
            }
        }
        return count;
    }
    
    //inserts new node with given value at specified position in list
    void list_insert_at(node* &head_ptr, const node::value_type &entry, size_t position){
        assert(position>0 && position<= list_length(head_ptr)+1);
        if (head_ptr==NULL){
            list_head_insert(head_ptr, entry);
        }
        else{
            node* temp = head_ptr;
            //moves temp to node before new node will be inserted
            for(int i=2; i<position; i++){
                temp = temp->link();
            }
            
            node* insert_ptr = new node(entry, temp->link());  //new node points to its next node
            temp->set_link(insert_ptr); //points temp at new node
            cout<<"if"<<endl;
            
            
        }
        
        
        
    }
    
    //returns value from removed node
    node::value_type list_remove_at(node* &head_ptr, size_t position){
        assert(position>0 && position<= list_length(head_ptr));
        node* temp = head_ptr;
        //moves temp to node before new node will be inserted
        for(int i=2; i<position; i++){
            temp = temp->link();
        }
        node* remove_ptr = temp->link();
        temp->set_link(temp->link()->link());
        node::value_type val = remove_ptr->data();
        delete remove_ptr;
        return val;
        
    }
    
    //copies a subset of the list
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert(start>=1 && start<=finish && finish<=list_length(head_ptr));
        node* head;
        node* tail;
        node* newHead;
        node* newTail;
        head = list_locate(head_ptr, start);
        tail = list_locate(head_ptr, finish);
        list_piece(head, tail, newHead, newTail);
        return head_ptr;
        
        
        

    }
    
    //removes duplicates of the list, nodes with same data
    void list_remove_dups(node* head_ptr){
        if (head_ptr==NULL || head_ptr->link()==NULL){
            return;
            //in either case, duplicates cannot exist
        }
        else{
            node* check;
            //will run until loop has cycled through the list
            while(head_ptr!= NULL && head_ptr->link()!=NULL){
                check = head_ptr;
                //once a "head" is choses to check against, the rest of the list is run and compared to the "head"
                while(check->link()!=NULL){
                    if(head_ptr->data() == check->link()->data()){
                        node* dlt_ptr = check->link();  //node to delete
                        check->set_link(dlt_ptr->link());
                        delete dlt_ptr;
                        list_print(head_ptr);
                    }
                    else{
                        check = check->link();
                    }
                }
    
                head_ptr=head_ptr->link();
            }
        }
    }
    
    void list_print(const node* head_ptr){
        const node* runner =head_ptr;
        while(runner!= NULL){
            cout << runner->data()<< ' ';
            runner = runner->link();
        }
        cout<<endl;
        
    }
    
    node* list_detect_loop(node* head_ptr){
        node* slow_run = head_ptr;
        node* fast_run = head_ptr;
        
        while(fast_run!=NULL && fast_run->link()!=NULL){
            slow_run = slow_run->link();
            fast_run = fast_run->link()->link();
            if (fast_run==slow_run)
                break;
        }
        if (fast_run==NULL && fast_run->link()!=NULL){
            return NULL;
        }
        
        //reset slow runner
        slow_run = head_ptr;
        //wait for pointers to meet
        while(slow_run!=fast_run){
            slow_run=slow_run->link();
            fast_run=fast_run->link();
        }
        //return pointer to node where they meet; aka start of loop
        return fast_run;
    }
    

}
    

                        
