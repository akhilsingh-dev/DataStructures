#include <iostream>

using namespace std;



class node{
private:
    int data;
    node* links[2];
    //bool isthread[2];

public:
    node(int d){
        links[0] = NULL;
        links[1] = NULL;
        //isthread[0] = isthread[1] = false;
        this->data = d;
    }

    node(){
        cout<<"[WARNING] : Empty node created!" << endl;
        links[0] = NULL;
        links[1] = NULL;
        //isthread[0] = isthread[1] = true;
    }

    void print_node(){
        cout <<"Printing Node status..."<<"\nNode data: " << this->data << "\nNode Address: "<<this << endl;
        cout <<"Left link: " << this->links[0] << endl;//"\t\tIs thread left: "<< this->isthread[0] <<endl;
        cout <<"Right Link: " << this->links[1] <<"\n" <<endl;//"\t\tIs thread Right: " << this->isthread[1] << "\n"<<endl;
    }

    bool isleaf(){
        if (links[0]== NULL && links[1] == NULL )
            return true;

        else{
            return false;
        }
    }

    friend class BSTree;
};

class BSTree{
private:
    node *root;
    int len;

    void disp(node* temp,int order=0){
        if(temp!=NULL){
            switch(order){
            case -1:                            //pre-order
                temp->print_node();          //P
                disp(temp->links[0],order);        //L
                disp(temp->links[1],order);        //R
                break;

            case 0:                             //in-order
                disp(temp->links[0],order);        //L
                temp->print_node();          //P
                disp(temp->links[1],order);        //R
                break;

            case 1:                             //post-order
                disp(temp->links[0],order);        //L
                disp(temp->links[1],order);        //R
                temp->print_node();          //P
                break;
            default:
                cout<<"[ERROR] : Invalid order value!"<<endl;
                break;
            }
        }

    }

    node* srch(node *qptr,int key){
        static node* retval=NULL;

        if(qptr==NULL){
            return NULL;
        }
        else if(qptr->data > key){
            retval = srch(qptr->links[0],key);
            return retval;
        }
        else if(qptr->data < key){
            retval = srch(qptr->links[1],key);
            return retval;
        }
        else if(qptr->data == key){
            return qptr;
        }
    }


    node* del(node* toor,int key){
        if(toor==NULL){                     //this is the exception case where you dont find the data
            cout << "Element not found or tree is empty!"<<endl;
            return toor;
        }

        //the next two statements determine the exiting from recursion if node is present

        if(toor->data > key){                           //if key is smaller
            toor->links[0] = del(toor->links[0],key);   //try deleting in the "left sub-tree" and not left link
            return toor;                                //return the current link back to exit
        }
        else if(toor->data < key){                      //do the same for bigger key with right sub-tree
            toor->links[1] = del(toor->links[1],key);
            return toor;
        }


        //this part deals with actual deletion, zero and one-child cases are handled as shown...
        if(toor->links[0] == NULL){                     //
            cout << "Nothing to the left!"<<endl;
            node* temp = toor->links[1];
            delete toor;
            return temp;
        }
        else if(toor->links[1] == NULL){
            cout << "Nothing to the right!"<<endl;
            node* temp = toor->links[0];
            delete toor;
            return temp;
        }

        else{
            node* succparent = toor->links[1];
            node* succ = toor->links[1];


            while(succ->links[0] != NULL){
                succparent = succ;
                succ = succ->links[0];
            }
            succparent->links[0] = succ->links[1];                      //error detected,link reset problem change here

            if(succ == succparent){
                toor->links[1] = succ->links[1];
            }

            toor->data = succ->data;
            delete succ;
            return toor;
        }




    }



public:
    BSTree(){
        root = NULL;
        len = 0;
        cout<<"[INFO] : A Binary Search Tree was formed!"<<endl;
    }

    void ins(int d){
        node *newnode = new node(d);

        if(root == NULL){
            root = newnode;
            len++;
        }
        else{
            node *temp = root;

            while(true){
                if(newnode->data <= temp->data){
                    if(temp->links[0] == NULL){
                        temp->links[0] = newnode;
                        break;
                    }
                    else{
                        temp = temp->links[0];
                    }
                }
                else if(newnode->data > temp->data){
                    if(temp->links[1] == NULL){
                        temp->links[1] = newnode;
                        break;
                    }
                    else{
                        temp = temp->links[1];
                    }
                }
            }
            temp = newnode;
            len++;
        }
    }

    void display(int order = 0){
        cout<<"\n\n===================================================================\n"<<endl;
        cout << "Number of nodes in the tree: " << len<<"\n"<<endl;
        disp(root,order);

        cout<<"\n===================================================================\n\n"<<endl;
    }

    node* srch(int key){
        node* x = srch(root,key);
        return x;
    }

    node* del(int key){
        node* temp = del(root,key);
        if(temp!=NULL){
            len--;
        }
        return temp;
    }

};



int main(){

    BSTree bs1;
    bs1.ins(25);
    bs1.ins(15);
    bs1.ins(20);
    bs1.ins(30);
    bs1.ins(10);
    bs1.ins(5);
    bs1.ins(12);
    bs1.ins(11);
    bs1.ins(14);
    bs1.ins(60);

    bs1.display();

    bs1.del(15);

    bs1.display();

    return 0;
}
