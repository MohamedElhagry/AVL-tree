#include <iostream>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
    int height;

public:
    Node(){
        left = 0;
        right = 0;
        height = 1;
    }

    Node(int data){
        this->data = data;
        left = 0;
        right = 0;
        height = 1;
    }

    Node* getRight(){
        return right;
    }

    Node* getLeft(){
        return left;
    }

    void setRight(Node* n){
        right = n;
    }

    void setLeft(Node* n){
        left = n;
    }

    int getData(){
        return data;
    }

    void setData( int data){
        this->data = data;
    }

    int getHeight(){
        return height;
    }

    void setHeight(int h){
        height = h;
    }



};


class myBST{

    Node* root;

    void inOrderTraversal(Node *n){
        if(!n) return;

        inOrderTraversal(n->getLeft());
        cout << n->getData() << endl;
        inOrderTraversal(n->getRight());
    }

    void postOrderTraversal(Node *n){
        if(!n) return;

        postOrderTraversal(n->getLeft());
        postOrderTraversal(n->getRight());
        cout << n->getData() << endl;
    }

    void preOrderTraversal(Node *n){
        if(!n) return;

        cout << n->getData() << endl;
        preOrderTraversal(n->getLeft());
        preOrderTraversal(n->getRight());

    }

    int getHeight(Node* node){
        if(node != 0)
            return node->getHeight();
        return 0;
    }

    int getBalanceFactor(Node* node){
        if(node == 0) return 0;
        return getHeight(node->getLeft()) - getHeight(node->getRight());
    }

    Node* getPred(Node* n){
        Node* current = n->getLeft();
        while(true){
            if(current->getRight() == 0)
                return current;
            else current = current->getRight();
        }
    }

    Node* rotateRight(Node* current){
        Node* LeftChild = current->getLeft();
        Node* LeftRightGChild = LeftChild->getRight();

        LeftChild->setRight(current);
        current->setLeft(LeftRightGChild);

        current->setHeight( max(getHeight(current->getLeft()), getHeight(current->getRight())) + 1 );
        LeftChild->setHeight( max(getHeight(LeftChild->getLeft()), getHeight(LeftChild->getRight())) + 1 );

        return LeftChild;
    }

    Node* rotateLeft(Node* current){
        Node* RightChild = current->getRight();
        Node* RightLeftGChild = RightChild->getLeft();

        RightChild->setLeft(current);
        current->setRight(RightLeftGChild);
        
        current->setHeight( max(getHeight(current->getLeft()), getHeight(current->getRight())) + 1 );
        RightChild->setHeight( max(getHeight(RightChild->getLeft()), getHeight(RightChild->getRight())) + 1 );

        return RightChild;
    }

    Node* insert(Node* current, int value){

        if(current == 0){
            return new Node(value);
        }

        if(value > current->getData()){
            current->setRight( insert(current->getRight(), value));
        }
        else if(value < current->getData()){
            current->setLeft( insert(current->getLeft(), value) );
        }
        else return current;


        current->setHeight( max( getHeight(current->getLeft()), getHeight(current->getRight()) ) + 1);
        int balanceFactor = getHeight(current->getLeft()) - getHeight(current->getRight());
        
        

        if(balanceFactor > 1){
            if(value < current->getLeft()->getData()){
                current = rotateRight(current);
            }
            else if(value > current->getLeft()->getData()){
                current->setLeft(rotateLeft(current->getLeft()));
                current = rotateRight(current);
            }
        }

        if(balanceFactor < -1){
            if(value > current->getRight()->getData()){
                current = rotateLeft(current);
            }
            else if(value < current->getRight()->getData()){
                current->setRight(rotateRight(current->getRight()));
                current = rotateLeft(current);
            }

        }

        return current;
    }

    Node* remove(Node* current, int value){
        if(current == 0)
            return 0;
        
        if(value > current->getData()){
            current->setRight( remove(current->getRight(), value));
        }
        else if(value < current->getData()){
            current->setLeft( remove(current->getLeft(), value));
        }
        else {
            if(current->getLeft() == 0 && current->getRight() == 0){
                current = 0;
            }
            else if(current->getLeft() != 0 && current->getRight() == 0){
                Node* temp = current;
                current = current->getLeft();
                delete temp;
            }
            else if(current->getLeft() == 0 && current->getRight() != 0){
                Node* temp = current;
                current = current->getRight();
                delete temp;
            }
            else{
                Node* pred = getPred(current);
                int data = pred->getData();
                current->setData(data);

                current->setLeft( remove(current->getLeft(), data) );
            } 
                
        }
        if (current == 0)
            return 0;
        
        

        
        current->setHeight( max(getHeight(current->getLeft()), getHeight(current->getRight())) +1);
        int balanceFactor = getBalanceFactor(current);


        if(balanceFactor > 1){
            
            if(getBalanceFactor(root->getLeft()) >= 0 ){
                current = rotateRight(current);
            }
            
            else if(getBalanceFactor(root->getLeft()) < 0){
                current->setLeft( rotateLeft(current->getLeft()));
                current = rotateRight(current);
            }
        }

        if(balanceFactor < -1){
            if(getBalanceFactor(root->getRight()) <= 0){
                current = rotateLeft(current);
            }
            else if(getBalanceFactor(root->getRight()) > 0){
                current->setRight(rotateRight(current->getRight()));
                current = rotateLeft(current);
            }
        }

        return current;

    }

public:
    myBST(){
        root = 0;
    }

    myBST(int data){
        root = new Node(data);
    }

    void insert(int d){
        root = insert(root , d);
    }

    bool searchTree(int d){
        Node* current = root;

        while(current != 0){
            if(d > current->getData())
                current = current->getRight();
            else if(d < current->getData())
                current = current->getLeft();
            else
                return true;
        }
        return false;
    }

    void remove(int d){
        root = remove(root, d);
    }

    void inOrderTraversal(){
        inOrderTraversal(root);
    }

    void postOrderTraversal(){
        postOrderTraversal(root);
    }

    void preOrderTraversal(){
        preOrderTraversal(root);
    }

    Node* getParent(int d){
        Node* parent = root;
        Node* current = root;

        if(root->getData() == d)
            return 0;

        if(d > current->getData())
            current = current->getRight();
        else if(d < current->getData())
            current = current->getLeft();

        while(true){
            if(d > current->getData())
                current = current->getRight();
            else if(d < current->getData())
                current = current->getLeft();
            else{
                return parent;
            }

            if(d > parent->getData())
                parent = parent->getRight();
            else
                parent = parent->getLeft();

        }
    }


};



int main()
{

    myBST tree;

    tree.insert(14);
    tree.insert(17);
    tree.insert(11);
    tree.insert(7);
    tree.insert(53);
    tree.insert(4);
    tree.insert(13);
    tree.insert(12);
    tree.insert(8);
    tree.preOrderTraversal();
    cout << "before deletion" << endl;
    tree.remove(53);
    tree.preOrderTraversal();


    

    return 0;
}
