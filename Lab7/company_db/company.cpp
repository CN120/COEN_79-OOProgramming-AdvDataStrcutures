// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        // IMPLEMENTATION COMPLETED
        assert(company_name.length() > 0);
        this->company_name = company_name; //name parameter assigned to local company name variable
        head_ptr = NULL;  //head and tail are NULL until products are added
        tail_ptr =NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        // IMPLEMENTATION COMPLETED
        company_name = src.company_name;
        
        //head node copied
        head_ptr = new node(src.get_head()->getName(), src.get_head()->getPrice(), NULL);
        node* adder = head_ptr;
        //copies rest of nodes
        for(node* runner = src.head_ptr->getLink(); runner!=NULL; runner=runner->getLink()){
            adder->setLink(new node(runner->getName(), runner->getPrice(), NULL));
            adder = adder->getLink();
        }
        tail_ptr = adder;
        
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
    
        // IMPLEMENTATION COMPLETED
        list_clear(head_ptr);
        
        company_name = src.company_name;  //transfer company name
        
        node* ptr = src.head_ptr;
        //insert all products
        while (ptr != NULL) {
            insert(ptr->getName(), ptr->getPrice());
            ptr = ptr->getLink();
        }
        
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // IMPLEMENTATION COMPLETED
            head_ptr = new node(product_name, price, NULL); //creates a head ponter if list is NULL
            tail_ptr = head_ptr;
        }
        else {
            // IMPLEMENTATION COMPLETED
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        // IMPLEMENTATION COMPLETED
        
        //if head_ptr is target product, delete head
        if(head_ptr->getName()==product_name){
            list_head_remove(head_ptr);
            return true;
        }
    
        /*
        (using search funtion does not work since need node previous to node to be erased)
        run looks for product in linked list
        run = tail if not found
        if target product found, run = the target products previous node
         
        */
        node* run = head_ptr;
        while(run!=tail_ptr && run->getLink()->getName()!=product_name){
            //tail->getLink()->getName() shouldn't seg fault because run!=tail_ptr is checked first
            run = run->getLink();
        }
        
        if(run==tail_ptr) {
            return false;
        }
        else {
            //points previous node to rmv's next and deletes rmv
            node* rmv = run->getLink();
            run->setLink(rmv->getLink());
            delete rmv;
            return true;
            
            
        }
    }
    
    
}
