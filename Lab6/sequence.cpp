//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }
    
    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }
    
    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        many_nodes = source.many_nodes;
        if (source.is_item()){
            //cout<<"test7"<<endl;
               
            list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
            list_piece(source.cursor, NULL, cursor, tail_ptr);
            //cout<<"test10"<<endl;
            if(precursor!=NULL){
                precursor->set_link(cursor);
            }
            //cout<<"test11"<<endl;
            
        }
        else{
            //cout<<"test8"<<endl;

            list_copy(source.head_ptr, this->head_ptr, this->tail_ptr);
            cursor = NULL;
            precursor = NULL;
            
        }
        
            
        /*
        init();
        *this = source;
         */
    }
    
    
    sequence::~sequence(){
        list_clear(head_ptr);
    }
    
    
    //sets cursor to start of list if it exits
    void sequence::start(){
        if(head_ptr ==NULL){
            return;
        }
        else{
            cursor = head_ptr;
            precursor = NULL;
        }
    }
    
    //sets precursor and cursor to end of list
    void sequence::end(){
        if(head_ptr==NULL){
            return;
        }
        else{
            precursor = list_locate(head_ptr,many_nodes-1);
            cursor = tail_ptr;
        }
        
    }
    
    //moves cursor and precursor ahaed one node
    void sequence::advance(){
        assert(is_item());
        if(cursor->link()==NULL){
            cursor = NULL;
            precursor = NULL;
        }
        else{
            precursor = cursor;
            cursor = cursor->link();
        }
    }
    
    //inserts item into sequence before current position and at head if no current item
    void sequence::insert(const value_type &entry){
        //before current
        if(is_item()){
            value_type val = entry;
            list_insert(precursor, val);
            cursor = precursor->link();
            ++many_nodes;
            
        }
        //at head
        else{
            list_head_insert(head_ptr, entry);
            cursor = list_locate(head_ptr,1);
            ++many_nodes;
        }
        
        
    }
    
    //inserts item into sequence after current item or at end if no current item
    void sequence::attach(const value_type &entry){
        value_type val = entry;
        ++many_nodes;
        //after current
        if(is_item()){
            list_insert(cursor, val);
            precursor = cursor;
            cursor = cursor->link();
            
        }
        //at end
        else{
            //cout<<"test2"<<endl;
            if (tail_ptr==NULL) {
                list_head_insert(this->head_ptr, val);
                //cout<<"test5"<<endl;
                this->tail_ptr = head_ptr;
                cursor = head_ptr;
                //cout<<"test6"<<endl;
            }
            else{
                //cout<<"test2.5"<<endl;
                list_insert(tail_ptr, val);
                //cout<<"test3"<<endl;
                
                precursor = tail_ptr;
                tail_ptr = tail_ptr->link();
                cursor = tail_ptr;
            }
        }
        
    }
    
    //equality operaot
    void sequence::operator=(const sequence &source){
        list_clear(this->head_ptr);  //clears previous heap data
        many_nodes = source.many_nodes;
        //uses list piece if current
        if (source.is_item()){
            list_piece(source.head_ptr, source.cursor, this->head_ptr, this->precursor);
            list_piece(source.cursor, NULL, this->cursor, this->tail_ptr);
            this->precursor->set_link(this->cursor);
        }
        //uses list copy if no current
        else{
            list_copy(source.head_ptr, this->head_ptr, this->tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }
    }
    
    void sequence::remove_current(){
        if(precursor==NULL && cursor!=NULL){
            //cout<<"test12"<<endl;
            
            list_head_remove(head_ptr);
            cursor = head_ptr;
            //head_ptr =
        }
        else{
            //cout<<"test13"<<endl;
            cursor= cursor->link();
            //cout<<"test14"<<endl;
            list_remove(precursor);
            
        }
    }
    
    sequence::size_type sequence::size() const{
        return many_nodes;
    }
    
    bool sequence::is_item() const{
        return (cursor!=NULL);
    }
    
    sequence::value_type sequence::current() const{
        assert(is_item());
        return cursor->data();
    }
    
}
