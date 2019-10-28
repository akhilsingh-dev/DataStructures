#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>

//This file declares two classes, circlist and singlelist both of which use a class "node" as atomic type 
//both the classes are a "collection" of "nodes".
//Each list can be initialized with a specific datatype (My take on creating something similar to the "vector").



template <class T>
class circlist;
template <class T>
class singlelist;


template <class T>
class node{
private:
    T data;
    node* next;
    bool is_init;

public:
    node(T d){
        data = d;
        next = NULL;
        is_init = true;
    }
    node(){
        next = NULL;
        is_init = false;
    }
    void print_node(){
        std::cout << "\nPrinting Node Status...\nNode Data :" << data << "\nNode Address: " << this;
        std::cout << "\nNext Address : " << next << "\nNode initialization status: " << is_init << std::endl;
    }

    friend class singlelist<T>;
    friend class circlist<T>;
};

template <class T>
class singlelist{
protected:
    node<T> *head;
    node<T> *tail;
    int len;

public:

    singlelist(){                               //empty ctor
        head = NULL;
        tail = head;
        len = 0;
    }

    int traverse(node<T> *&n_ptr, int index){    //move n_ptr to index
        int i;
        n_ptr = head;
        //std::cout<<index << "\t" << len << "\n\n"<<std::endl;

        for(i=0; ( (i<index) && (n_ptr->next != NULL) ) ;i++){
            //n_ptr->print_node();
            n_ptr = n_ptr->next;
        }
        if(index > len){
            return 1;
        }
        else if(i == index){
            //std::cout<<"Inside traverse: "<<std::endl;
            //n_ptr->print_node();
            return 0;
        }
        else{
            return 1;
        }
    }

    void display(){
        int i;
        node<T> *temp;
        temp = head;
        std::cout<<"\n======================================================================================="<<std::endl;

        if(len == 0){
            std::cout<<"\n\t\t\tEmpty List!" << std::endl;
        }
        else if(len > 0){
            std::cout <<"Single link List of type : "<< typeid(temp->data).name() << "\nLength = " << len << std::endl;

            for(i=0;temp!=NULL&&i<len;i++){
                std::cout << temp->data << "\t";
                temp = temp->next;
            }
        }
        else{
            std::cout<< "\n\t\t\tUndefined Behaviour!" << std::endl;
        }

        std::cout<<"\n======================================================================================="<<std::endl;
    }

    int ins(T d, int index){                    //insert an element with data "d" at "index"
        int stat = 256;
        node<T> *temp;


        if(len == 0){                                                   //insert first element
            head = new node<T>(d);
            tail = head;
            len = 1;
            return 0;
        }

        else if(index == 0){                                            //insert at beginning
            std::cout << "This will change the indexing of existing elements!" <<std::endl;
            temp = new node<T>(d);

            temp->next = head;
            head = temp;
            len++;

            return 0;
        }

        else if (index != 0){                                           //insert at end or in middle
            temp = head;
            stat = traverse(temp, index-1);

            if(stat == 1){                                              //incorrect traversal
                std::cout << "Could not insert element\nTraversal error: " << stat << std::endl;
                return 1;
            }

            else if(stat == 0){                                         //correct traversal
                node<T> *newnode = new node<T>(d);

                if(index == len){                                       //insert at end
                    temp->next = newnode;
                    tail = newnode;                                     //update tail ptr
                    len++;
                }

                else{                                                   //insert in middle
                    std::cout << "This will change the indexing of some existing elements!" <<std::endl;
                    newnode->next = temp->next;
                    temp->next = newnode;
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
        node<T> *temp = head;
        node<T> *temp1;
        if(index==0){
            temp = head;
            head = head->next;
            free(temp);
            len--;
            return 0;
        }
        else if(index > 0 && index < len-1){
            node<T> *temp1 = head;
            int stat = traverse(temp,index-1);
            int stat1 = traverse(temp1,index);
            if(stat != 0 || stat1 != 0){
                std::cout << "Traversal Error!\nThe element will not be deleted!\nPointer1: " << stat << "\tPointer 2: " << stat1<<std::endl;
                return 1;
            }
            temp->next = temp1->next;
            free(temp1);
            len--;
            return 0;
        }

        else if(index == len-1){
            //std::cout<<"\nLAST element deletion!\n\n" << std::endl;

            int stat = traverse(temp,index-1);
            temp1 = temp->next;
            if(stat!=0){
                std::cout << "Traversal Error!\nThe element will not be deleted!\nPointer: " << stat << std::endl;
                return 1;
            }

            free(temp1);
            temp->next = NULL;
            tail = temp;
            //tail->print_node();
            len--;
            return 0;
        }

        else{
            std::cout << "Undefined behaviour!\nThe element will not be deleted!" << std::endl;
            return 1;
        }

    }

    /*A*/int del(node<T> *n_ptr){                    //delete element at n_ptr
        if(n_ptr == head){                      //delete first element
            head = n_ptr->next;
            free(n_ptr);
            len--;
            return 0;
        }
        else if(n_ptr->next == NULL){           //deleting last element
            node<T> *t1;
            while(t1->next != n_ptr){
                t1 = t1->next;
            }
            t1->next = n_ptr->next;
            free(n_ptr);
            len--;
            return 0;
        }

        else{
            node<T> *t1,*t2;
            while(t1->next != n_ptr){
                t1 = t1->next;
            }
            t1->next = n_ptr->next;
            free(n_ptr);
            len--;
            return 0;
        }


    }

    int bubsort(){
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
        return 0;
    }

    int concat(singlelist<T> &source){

        //std::cout << "Lengths of each list: " << len << "\t" << source.len << std::endl;
        if(typeid(head->data).name()!=typeid(source.head->data).name()){
            std::cout<<"Type mismatch! Catenation Failed!" << std::endl;
            return 1;
        }
        else if(len == 0 || source.len == 0){
            std::cout<<"One or more lists is/are empty, Catenation failed!" << std::endl;
            return 1;
        }
        else{
            node<T> *temp;
            int stat = traverse(temp,len-1);
            if(stat==1){
                std::cout << "Traversal error!" << std::endl;
                return 1;
            }
            else if(stat == 0){
                temp->next = source.head;
                len += source.len;
                std::cout<<"Catenation successful\nThe Second list will now be deleted!" << std::endl;
                source.head = NULL;
                source.len = 0;
                //std::cout<<"Lengths of lists after catenation: " << len << "\t" << source.len << std::endl;
                return 0;
            }
            else{
                std::cout<<"Undefined Behaviour!" << std::endl;
                return 1;
            }

        }
    }

    int rev(){                                                    //reverses the
        node<T> *fwd,*bwd,*curr;
        fwd = head;
        curr = bwd = NULL;
        while(fwd!=NULL){
            bwd = curr;
            curr = fwd;
            fwd = fwd->next;
            curr->next = bwd;
        }head = curr;
        return 0;
    }

    singlelist<T> intersect(const singlelist<T> &l2){             //takes two SETS and returns their intersection
        singlelist<T> target;

        node<T>* temp1;
        node<T>* temp2;

        for(temp1=head; temp1!=NULL; temp1=temp1->next){
            for(temp2=l2.head; temp2!=NULL; temp2=temp2->next){
                if(temp1->data == temp2->data){
                    target.ins(temp2->data,0);
                }
            }
        }

        //target.display();
        return target;
    }

    singlelist<T> sortunite(singlelist<T> &l2){                       //takes two SETS and returns their union
        this->bubsort();
        l2.bubsort();

        node<T> *t1,*t2;
        singlelist<T> target;
        int i = 0;

        t1 = head;
        t2 = l2.head;


        while(t1 !=NULL && t2 != NULL){

            if(t1->data == t2->data){
                target.ins(t1->data,i);
                i++;
                t1 = t1->next;
                t2 = t2->next;
            }
            else if(t2->data < t1->data){
                target.ins(t2->data,i);
                i++;
                t2 = t2->next;
            }
            else if(t2->data > t1->data){
                target.ins(t1->data,i);
                i++;
                t1 = t1->next;
            }
        }

        while(t1!= NULL){
            target.ins(t1->data,i);
            i++;
            t1 = t1->next;
        }

        while(t2!= NULL){
            target.ins(t2->data,i);
            i++;
            t2 = t2->next;
        }
     return target;
    }

};

template <class T>
class circlist : public singlelist<T>{
private:

public:
    circlist(){
        std::cout<<"Circular list created!" << std::endl;
    }

    int ins(T d,int index){
        int stat = 256;
        if(index == 0){                                                 //front insertion
            if(singlelist<T>::len == 0){
                stat = singlelist<T>::ins(d,index);
                singlelist<T>::tail->next = singlelist<T>::head;
            }
            else if(singlelist<T>::len != 0){
                stat = singlelist<T>::ins(d,index);
                singlelist<T>::tail->next = singlelist<T>::head;
            }
        }
        else if(index == singlelist<T>::len){                           //back insertion
            stat = singlelist<T>::ins(d,index);
            singlelist<T>::tail->next = singlelist<T>::head;
            //singlelist<T>::head->print_node();
            //singlelist<T>::tail->print_node();
        }
        else if(index < singlelist<T>::len){                            //insert in middle
            stat = singlelist<T>::ins(d,index);
        }
        else{
            std::cout << "Parameter index out of bounds!\nPlease check: Passed index = " << index << "\tTotal length = " << singlelist<T>::len << std::endl;
        }

        return stat;
    }

    void display(){
        int i;
        node<T> *temp;
        temp = singlelist<T>::head;
        std::cout<<"\n======================================================================================="<<std::endl;

        if(singlelist<T>::len == 0){
            std::cout<<"\n\t\t\tEmpty List!" << std::endl;
        }
        else if(singlelist<T>::len > 0){
            std::cout <<"Circular link List of type : "<< typeid(temp->data).name() << "\nLength = " << singlelist<T>::len << std::endl;
            temp = singlelist<T>::head;                                //initialize iterators
            int i=0;
            do{
                std::cout << temp->data << "\t";        //print data
                //temp->print_node();
                temp = temp->next;                      //iterator update
                i++;
            }while(temp != singlelist<T>::head && temp!=NULL && i<singlelist<T>::len);                 //exit control

            if(temp!=NULL)
                std::cout << "  Repeat head: " << temp->data << "\t";            //print head once more using temp
            else{
                std::cout << "Circularity undefined!";
            }
        }
        else{
            std::cout<< "\n\t\t\tUndefined Behaviour!" << std::endl;
        }

        std::cout<<"\n======================================================================================="<<std::endl;
    }

    int del(int index){
        int stat = 256;
        int n = singlelist<T>::len;
        //std::cout<<"index = " << index<<"n-1 = " << n-1 <<"\n\n"<<std::endl;

        if(index > -1 && index < singlelist<T>::len){                           //delete if index is in bounds
            stat = singlelist<T>::del(index);
        }
        else{
            std::cout << "Index Out of Bounds! Cannot delete!"<<std::endl;
            stat = 1;
        }

        if(index==0){                                                       //if deleting first element
            singlelist<T>::tail->next = singlelist<T>::head;                //update circularity
        }

        else if(index == n-1){                                              //if deleting last element
            //std::cout<<"I WON'T"<<std::endl;
            singlelist<T>::tail->next = singlelist<T>::head;                //update circularity
        }
        return stat;
    }

    circlist<T> cpy(){
        circlist<T> target;
        node<T> *temp = singlelist<T>::head;
        int i=0;
        do{
            target.ins(temp->data,i);
            i++;
            temp = temp->next;
        }while(temp!=singlelist<T>::head);
        return target;
    }

    int concat(circlist<T> &source){
        node<T> *temp;
        int stat = 256;

        temp = source.head;
        singlelist<T>::tail->next = source.head;
        source.tail->next = singlelist<T>::head;
        stat = 0;
        singlelist<T>::len+=source.len;
        return stat;
    }

    void bubsort(){
        node<T> *t1, *t2;
        t1 = singlelist<T>::head;
        t2 = singlelist<T>::head->next;

        do{
            do{
               if(t1->data < t2->data){
                    T temp = t1->data;
                    t1->data = t2->data;
                    t2->data = temp;
                }
                t2 = t2->next;

            }while(t2!=singlelist<T>::head);
            t1 = t1->next;

        }while(t1!=singlelist<T>::head);
    }

    void rev(){
        node<T> *fwd, *bwd, *curr;
        fwd = singlelist<T>::head;
        bwd = curr = singlelist<T>::tail;
        do{
            bwd = curr;
            curr = fwd;
            fwd = fwd->next;
            curr->next = bwd;

        }while(fwd != singlelist<T>::head);
        singlelist<T>::head = curr;
    }

    int srch(T query){
        int hit = -2;
        node<T>* t = singlelist<T>::head;
        do{
            hit++;
            if(t->data == query){
                break;
            }
            t = t->next;
        }while(t != singlelist<T>::head);

        if(hit < singlelist<T>::len-1){
            std::cout << "The Query was found at index: " << hit << std::endl;
            std::cout << "It has been returned for any further use!" << std::endl;
        }
        else if(hit == singlelist<T>::len - 1){
            if(singlelist<T>::tail->data != query){
                std::cout<<"No match found!"<<std::endl;
                hit = -1;
            }
        }


        else{
            std::cout<<"No match found!"<<std::endl;
            hit = -1;
        }
        return hit;
    }


};



int main(){

    singlelist<int> l1;
    circlist<int> cl1,cl2;
    int a;
    cl1.ins(65,0);
    cl1.ins(66,0);
    cl1.ins(67,2);
    cl1.ins(68,1);
    cl1.ins(69,3);

    cl2.ins(15,0);
    cl2.ins(16,1);
    cl2.ins(17,2);

    int x,n;
    int sel0,sel1;
    unsigned int i,l=0;

    do{
    std::cout << "==================================  CIRCULAR LINK LISTS  ==============================" << std::endl;

    std::cout << "1.Insertion\n2.Display\n3.Deletion\n4.Copy\n5.Concat\n6.Sort\n7.Reverse\n8.Search\n9.Exit\n" << std::endl;
    std::cout<<"Enter your choice: ";
    std::cin >> sel1;
    switch(sel1){
    case 1:                                                                 //INSERTION
        std::cout<<"Enter how many elements you want to insert: " ;
        std::cin >> l;
        for(i=0;i<l;i++){
            std::cout << "Enter where you want to insert: ";
            std::cin >> n;
            std::cout << "Enter what you want to insert: ";
            std::cin >> x;
            cl1.ins(x,n);
        }
        std::cout << "Your list looks like this: " << std::endl;
        cl1.display();
        break;

    case 2:                                                                 //DISPLAY
        cl1.display();
        break;

    case 3:                                                                 //DELETION
        cl1.display();
        std::cout<<"Enter index you want to delete: ";
        std::cin >> i;
        cl1.del(i);
        cl1.display();
        break;

    case 4:
        cl1.display();
        cl2 = cl1.cpy();
        cl2.display();
        break;

    case 5:
        cl1.display();
        cl1.concat(cl2);
        cl1.display();
        break;

    case 6:
        cl1.display();
        cl1.bubsort();
        cl1.display();
        break;
    case 7:
        cl1.display();
        cl1.rev();
        cl1.display();
        break;
    case 8:
        std::cout<<"Enter number you want to search: ";
        std::cin >> a;
        x = cl1.srch(a);
        std::cout<<"Index = " << x <<std::endl;
        break;

    default:
        break;

    }
    std::cout<< "TRY AGAIN? (1/0) : ";
    std::cin >> sel0;
    }while(sel0 == 1);
    return 0;
}
