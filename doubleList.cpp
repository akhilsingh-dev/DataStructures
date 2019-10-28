#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>

//doublelist is similar to the singlelist except it adds a pointer to previous node on each node
//there are a few things tried purely for experimenting with the code...

template <class T>
class doublelist;

template <class T>
class node{
private:
    T data;
    node *next,*prev;
    bool is_init;

public:
    node(T d){
        data = d;
        prev = NULL;
        next = NULL;
        is_init = true;
    }
    node(){
        next = NULL;
        is_init = false;
    }
    void print_node(){
        std::cout << "\nPrinting Node Status...\nNode Data :" << data << "\nPrevious Address: " << prev;
        std::cout<< "\nNode Address: " << this << "\nNext Address : " << next;
        std::cout<< "\nNode initialization status: " << is_init << std::endl;
    }

    friend class doublelist<T>;

};


template <class T>
class doublelist{
private:
    node<T> *head;                      //holds head
    node<T> *tail;                      //holds tail
    bool is_rev;                        //defines if reversed or not
    int len;                            //holds length of link list

public:
    //a few things are being tried out for pure experimentation purposes...
    doublelist(){                               //empty ctor
        head = NULL;
        tail = head;
        is_rev = false;
        len = 0;
    }

    int traverse(node<T> *&n_ptr, int index){    //move n_ptr to index
        int i;
        if(!is_rev){
            n_ptr = head;
            for(i=0; ( (i<index) && (n_ptr->next != NULL) ) ;i++){
                n_ptr = n_ptr->next;
            }
        }
        else if(is_rev){
            n_ptr = tail;
            for(i=0; ( (i<index) && (n_ptr->prev != NULL) ) ; i++){
                n_ptr = n_ptr->prev;
            }
        }

        if(index > len){
            return 1;
        }
        else if(i == index){
            return 0;
        }
        else{
            return 1;
        }
    }

    void display(){
        int i;
        node<T> *temp;
        std::cout<<"\n======================================================================================="<<std::endl;
        if(len == 0){
            std::cout<<"\n\t\t\tEmpty List!" << std::endl;
        }
        else if(len > 0){
            if(!is_rev){                                        //default situation
                temp = head;
                std::cout <<"Double link List of type : "<< typeid(temp->data).name() << "\nLength = " << len << std::endl;
                for(i=0;temp!=NULL&&i<len;i++){
                    std::cout << temp->data << " <=> ";
                    //temp->print_node();
                    temp = temp->next;
                }
            }
            else if(is_rev){                                    //reverse situation
                temp = tail;
                std::cout <<"Double link List of type : "<< typeid(temp->data).name() << "\nLength = " << len << std::endl;
                for(i=0;temp!=NULL&&i<len;i++){
                    std::cout << temp->data << " <=> ";
                    //temp->print_node();
                    temp = temp->prev;
                }
            }
        }

        else{
            std::cout<< "\n\t\t\tUndefined Behaviour!" << std::endl;
        }
        std::cout<<"\n======================================================================================="<<std::endl;
    }

    int ins(T d, int index){                    //insert an element with data "d" at "index"
        int stat = 256;
        node<T> *temp=NULL;
        if(len == 0){                                                   //inserting the very first element
            head = new node<T>(d);
            tail = head;                                                //update tail
            len = 1;
            return 0;
        }
        else if(index == 0){                                            //insert at beginning
            std::cout << "This will change the indexing of existing elements!" <<std::endl;
            temp = new node<T>(d);
            if(!is_rev){                                                //if the list is fwd alligned
                temp->next = head;
                head->prev = temp;
                head = temp;
            }
            else if(is_rev){                                                 //if list is bwd alligned
                tail->next = temp;                                      //create fwd link
                temp->prev = tail;                                      //create bwd link
                tail = temp;                                            //update tail
            }
            len++;
            return 0;
        }
        else if (index != 0){                                           //insert at end or in middle
            //temp = head;
            stat = traverse(temp, index-1);

            if(stat == 1){                                              //incorrect traversal
                std::cout << "Could not insert element\nTraversal error: " << stat << std::endl;
                return 1;
            }

            else if(stat == 0){                                         //correct traversal
                node<T> *newnode = new node<T>(d);

                if(index == len){                                       //insert at end
                    if(!is_rev){
                        temp->next = newnode;
                        newnode->prev = temp;
                        tail = newnode;                                 //update tail due to end
                    }
                    else if(is_rev){
                        temp->prev = newnode;
                        newnode->next = temp;                           //establish links
                        head = newnode;                                 //update head
                    }
                    len++;
                }

                else{                                                   //insert in middle
                    std::cout << "This will change the indexing of some existing elements!" <<std::endl;
                    if(!is_rev){
                        newnode->next = temp->next;
                        temp->next = newnode;
                        newnode->prev = temp;
                        newnode->next->prev = newnode;
                    }
                    else if(is_rev){
                        newnode->prev = temp->prev;
                        newnode->next = temp->prev->next;               //create single links to newnode
                        newnode->prev->next = newnode;
                        temp->prev = newnode;                           //reinforce the other links
                    }
                    len++;
                }
                return 0;                                               //element inserted successfully
            }

            else{                                                       //undefined traversal
                std::cout << "Undefined traversal behavior: "<< stat << std::endl;
                return 1;
            }
        }

    }

    int del(int index){
        node<T> *temp;
        if(index==0){                           //beginning element deletion
            if(len > 1){
                if(!is_rev){                    //start with head
                    temp = head;
                    head->next->prev = NULL;
                    head = head->next;
                }
                else if(is_rev){                //start with tail
                    temp = tail;
                    tail->prev->next = NULL;
                    tail = tail->prev;
                }
                free(temp);
                len--;
            }
            else if(len == 1){
                temp = head;
                head = NULL;
                tail = NULL;
                free(temp);
                len--;
            }
            return 0;
        }
        else if(index > 0 && index < len-1){
            node<T> *temp1 = head;
            int stat = traverse(temp,index-1);
            //int stat1 = traverse(temp1,index);
            if(stat != 0){
                std::cout << "Traversal Error!\nThe element will not be deleted!\nPointer1: " << stat << std::endl;
                return 1;
            }

            if(!is_rev){
                temp1 = temp->next;
                temp->next = temp1->next;
                temp1->next->prev = temp;
                free(temp1);
            }
            else if(is_rev){
                temp1 = temp->prev;
                temp->prev = temp1->prev;
                temp1->prev->next = temp;
                free(temp1);
            }
            len--;
            return 0;
        }

        else if(index == len-1){
            std::cout<<"\nLAST element deletion!\n\n" << std::endl;
            int stat = traverse(temp,index-1);
            node<T>* temp1;
            if(stat!=0){
                std::cout << "Traversal Error!\nThe element will not be deleted!\nPointer: " << stat << std::endl;
                return 1;
            }

            if(!is_rev){
                temp1 = temp->next;
                temp->next = NULL;
                tail = tail->prev;
            }
            else if(is_rev){
                temp1 = temp->prev;
                temp->prev = NULL;
                head = head->next;
            }
            free(temp1);
            len--;
            return 0;
        }

        else{
            std::cout << "Undefined behaviour!\nThe element will not be deleted!" << std::endl;
            return 1;
        }

    }

    int bubsort(){
        bool x= is_rev;
        if(is_rev){                     //flip reverse
            is_rev = !is_rev;
        }

        node<T> *t1, *t2;
        t1 = head;
        t2 = head->next;
        for(t1 = head; t1 != NULL ; t1 = t1->next){
            for(t2 = head ; t2 != NULL ; t2 = t2->next){
                if(t1->data < t2->data){
                    T temp = t1->data;
                    t1->data = t2->data;
                    t2->data = temp;
                }
            }
        }
        is_rev = x;
        return 0;
    }

    int rev(){                                                    //reverses the list
        is_rev = !is_rev;
        return 0;
    }

    int srch(T query){
        node<T> *temp=NULL;
        if(!is_rev)
            temp = head;
        else if(is_rev)
            temp = tail;
        int i = 0;
        while(query != temp->data){
            i++;
            if(!is_rev)
                temp = temp->next;
            else if(is_rev)
                temp = temp->prev;
            if(temp == NULL)
                break;
        }
        if(i > -1 && i < len){
            return i;
        }
        else{
            return -1;
        }

    }

    doublelist<T> cpy(){
        doublelist<T> target;
        node<T> *temp;
        if(!is_rev){
            temp = head;        //initialize temp as per allignment
        }
        else if(is_rev){
            temp = tail;
        }
        int i = 0;
        while(temp != NULL){
            target.ins(temp->data,i);
            i++;
            if(!is_rev)
                temp = temp->next;
            else if(is_rev)
                temp = temp->prev;

        }


        return target;
    }

    int get_len(){
        return len;
    }

    void concat(doublelist<T> &source){

        if(!(this->is_rev) && !(source.is_rev)){
            this->tail->next = source.head;
            source.head->prev = this->tail;
        }
/*
        else if(this->is_rev && source.is_rev){
            this->head->prev = source.tail;
            source.tail->next = this->head;
        }

        else if(this->is_rev && !(source.is_rev)){
            this->head->prev = source.head;
            source.head->next = this->head;
        }
        else if(!(this->is_rev) && source.is_rev){
            this->tail->next = source.tail;
            source.tail->prev = this->tail;
        }

        */

        len += source.len;
        delete &source;
    }

    doublelist<T> merger(const doublelist<T> &source,int xr=2,int yr=2){
        doublelist<T> target;
        node<T> *temp=head,*temp1=source.head;
        int k=0;
        while(temp != NULL && temp1 != NULL){             //while there are elements in both lists
            int i=0,j=0;
            do{
                target.ins(temp->data,k);               //insert xr times from list1
                temp = temp->next;
                k++;
                i++;
            }while(i%xr != 0 && temp != NULL);
            //target.display();
            do{
                target.ins(temp1->data,k);              //insert yr times from list2
                temp1 = temp1->next;
                k++;
                j++;
            }while(j%yr != 0 && temp1 != NULL);
            //target.display();
        }
        std::cout<<"Exit loop 1"<<std::endl;

        while(temp!=NULL){
            target.ins(temp->data,k);
            k++;
            temp = temp->next;
        }
        std::cout<<"Exit loop 2"<<std::endl;

        while(temp1!=NULL){
            target.ins(temp1->data,k);
            k++;
            temp1 = temp1->next;
        }
        std::cout<<"Exit loop 3"<<std::endl;
        return target;
    }

    doublelist<T> unite(doublelist<T> &source){
        doublelist<T> target;
        this->bubsort();
        source.bubsort();
        node<T> *temp=this->head, *temp1 = source.head;
        int k =0;

        while(temp != NULL && temp1 != NULL){
            if(temp->data == temp1->data){
                target.ins(temp->data,k);
                temp=temp->next;
                temp1 = temp1->next;
                k++;
            }
            else if(temp->data < temp1->data){
                target.ins(temp->data,k);
                temp=temp->next;
                k++;
            }
            else if(temp->data > temp1->data){
                target.ins(temp1->data,k);
                temp1=temp1->next;
                k++;
            }

        }
        while(temp != NULL){
            target.ins(temp->data,k);
            temp=temp->next;
            k++;
        }
        while(temp1 != NULL){
            target.ins(temp1->data,k);
            temp1=temp1->next;
            k++;
        }
        return target;
    }

    doublelist<T> intersect(doublelist<T> &source){
        doublelist<T> target;
        this->bubsort();
        source.bubsort();
        node<T> *temp=this->head;
        node<T> *temp1 = source.head;
        int k = 0;

        while(temp != NULL && temp1 != NULL){
            if(temp->data == temp1->data){
                target.ins(temp->data,k);
                temp=temp->next;
                temp1 = temp1->next;
                k++;
            }
            else{
                temp1 = temp1->next;
                temp = temp->next;
            }
        }


        return target;
    }

};




int main(){

    doublelist<int> l1;
    doublelist<int> l2;
    doublelist<int> l3,l4,l5;

    l1.ins(15,0);
    l1.ins(16,1);
    l1.ins(17,2);
    l1.ins(18,3);

    l2.ins(15,0);
    l2.ins(16,1);
    l2.ins(19,2);
    l2.ins(20,3);


    int sel0,sel1;
    int n,x;
    do{
    std::cout << "===============================  DOUBLE LINK LIST  =========================="<<std::endl;
    std::cout << "1.Insertion\n2.Display\n3.Deletion\n4.Reverse\n5.Sort\n6.Search\n7.Copy"<<std::endl;
    std::cout << "8.Concatenate\n9.Merge\n10.Union\n11.Intersection\n" << std::endl;
    std::cout<<"Enter your choice: ";
    std::cin >> sel1;
    switch(sel1){
    case 1:                                                         //insert
        for(int i=0;i<3;i++){
            std::cout << "Enter where you want to insert: ";
            std::cin >> n;

            std::cout << "Enter what you want to insert: ";
            std::cin >> x;
            l1.ins(x,n);
        }
        l1.display();
        break;

    case 2:                                                         //DISPLAY
        l1.display();
        break;

    case 3:                                                         //DELETE
        l1.display();
        std::cout<<"Enter index of your element: ";
        std::cin >> x;
        if(x > -1 && x < l1.get_len()){
            l1.del(x);
        }
        std::cout<<"This is how it looks now : " <<std::endl;
        l1.display();
        break;

    case 4:
        l1.rev();
        l1.display();
        break;

    case 5:
        l1.display();
        l1.bubsort();
        l1.display();
        break;

    case 6:
        std::cout<<"Enter search element: ";
        std::cin >> x;
        std::cout<< "Query Found at index: "<<l1.srch(x)<<std::endl;
        break;

    case 7:
        l2 = l1.cpy();
        l2.display();
        break;

    case 8:
        l1.concat(l2);
        l1.display();
        break;

    case 9:
        l3 = l1.merger(l2,3,2);
        l3.display();
        break;

    case 10:
        l4 = l1.unite(l2);
        l4.display();
        break;

    case 11:
        l5 = l1.intersect(l2);
        l5.display();
        break;

    default:
        break;
    }


    std::cout<<"Try Again? (1/0) : " ;
    std::cin >> sel0;
    }while(sel0==1);



    return 0;
}
