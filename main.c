#include <stdio.h>
#include <stdlib.h>
#define max(a,b) a>b?a:b

typedef struct AVLtree avlt;

struct AVLtree{
    int data;
    struct AVLtree *right;
    struct AVLtree *left;
    int height;
};

avlt *root=NULL;

//Creates new node

avlt *createNode(int val){
    avlt *temp = (avlt*)malloc(sizeof(avlt));
    temp->data = val;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=1;
    return temp;
}

//gets the height of the specified node

int getHeight(avlt *node){
    if(node==NULL) return 0;

    return node->height;
}

//gets the Balance Factor of the specified node

int getBalanceFactor(avlt *node){

    if(node==NULL) return 0;

    return getHeight(node->left)-getHeight(node->right);
}


//Rotates the sub-tree towards right

avlt* rightRotation(avlt *y){
    //if(y==NULL) return NULL;

    //else{
        avlt *x = y->left;
        avlt *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left),getHeight(y->right))+1;
        x->height = max(getHeight(x->left),getHeight(x->right))+1;
        return x;
    //}
    //return x;
}

//Rotates the sub-tree towards left

avlt* leftRotation(avlt *x){
    //if(x==NULL) return NULL;

    //else{
        avlt *y = x->right;
        avlt *T2 = y->left;

        y->left = x;
        x->right = T2;

        y->height = max(getHeight(y->left),getHeight(y->right))+1;
        x->height = max(getHeight(x->left),getHeight(x->right))+1;
        return y;
    //}
    //return y;
}



avlt* insertNode();
avlt* deleteNode();
void searchNode();
void printInOrder();
void printPreOrder();
void printPostOrder();

int main()
{

    int choice;
    printf("---------------------\n");
    printf("AVL TREE\n"); // AVL (Adelson-Velskii and Landis) Tree
    printf("---------------------\n");

    do{
    printf("\n____________________________");
    printf("\nCHOOSE AN OPERATION\n(1)INSERT\n(2)DELETE\n(3)SEARCH\n(4)DISPLAY\n(5)EXIT\n");
    printf("____________________________");

    printf("\nENTER YOUR CHOICE :");
    scanf("%d",&choice);

    switch(choice)
    {
              //Node insertion case
        case 1:{
                int val;
                printf("\nENTER A NODE: ");
                scanf(" %d",&val);
                root = insertNode(root,val);
               }
               break;
            //Node deletion case
    case 2: {
             int val;
             if(root==NULL) printf("\nAVL TREE EMPTY");
             else{
                printf("\nENTER A NODE: ");
                scanf(" %d",&val);
                root = deleteNode(root,val);
             }

            }
            break;
            //Node searching case
    case 3: {
             int key;
             if(root==NULL) printf("\nAVL TREE EMPTY");
             else{
                printf("\nENTER A KEY FOR SEARCH : ");
                scanf(" %d",&key);
                searchNode(key);
             }
            }
            break;
            //Displays AVL tree
    case 4: {
                printf("\n----------------------------");
                printf("\nCHOOSE A DISPLAY OPERATION\n\n(1)PRINT TREE\n(2)PRINT INORDER\n(3)PRINT PREORDER\n(4)PRINT POSTORDER\n(5)EXIT\n");
                printf("\n----------------------------");
                int option;
                printf("\nENTER YOUR CHOICE :");
                scanf("%d",&option);
                printf("\n----------------------------");
                if(root==NULL) printf("\nAVL TREE EMPTY");
                else{
                    switch(option){
                    case 1:
                            break;


                    case 2: printf("\nIN-ORDER TRAVERSAL : ");
                            printInOrder(root);
                            break;

                    case 3: printf("\nPRE-ORDER TRAVERSAL : ");
                            printPreOrder(root);
                            break;

                    case 4: printf("\nPOST-ORDER TRAVERSAL : ");
                            printPostOrder(root);
                            break;

                    case 5: printf("\nEXIT\n");
                            break;

                    default: printf("\nINVALID CHOICE!!\nPLEASE ENTER A VALID OPTION\n");
                 }
                }


            }
            break;

    case 5: printf("\nEXIT");
            break;

    default: printf("\nINVALID CHOICE!!\nPLEASE ENTER A VALID OPTION\n");

    }
  }while(choice!=5);


    getch();
    return 0;
}

//Print InOrder of the AVL Tree

void printInOrder(avlt *root){

        if(root->left!=NULL)
        printInOrder(root->left);

        printf("%d ",root->data);

        if(root->right!=NULL)
        printInOrder(root->right);

}

// Print PreOrder traversal of the AVL Tree

void printPreOrder(avlt *root){

            printf("%d ",root->data);

            if(root->left!=NULL)
            printPreOrder(root->left);

            if(root->right!=NULL)
            printPreOrder(root->right);

}


//Print PostOrder traversal of the AVL Tree

void printPostOrder(avlt *root){

        if(root->left!=NULL)
        printPostOrder(root->left);

        if(root->right!=NULL)
        printPostOrder(root->right);

        printf("%d ",root->data);

}

// Searching a Node with in BST using iteration

void searchNode(int key){

        avlt* ptr = root;
        while(ptr!=NULL){

            if(ptr->data==key){

              printf("\nNODE : %d FOUND",ptr->data);
              return ;
            }

            else if(key<ptr->data) ptr = ptr->left;

            else ptr = ptr->right;
        }

        printf("\nNODE : %d NOT FOUND",key);

}

//Inserts a node into the AVL Tree

avlt *insertNode(avlt *node,int val){

    if(node==NULL) return(createNode(val));

    if(val<node->data)
        node->left = insertNode(node->left,val);
    else if(val>node->data)
        node->right = insertNode(node->right,val);
    else
        return node;

    node->height = 1+max(getHeight(node->left),getHeight(node->right));
    int bf = getBalanceFactor(node);

    //LL rotation case
    if(bf>1 && val<node->left->data){
        return rightRotation(node);
    }
    //RR rotation case
    if(bf<-1 && val>node->right->data){
        return leftRotation(node);
    }
    //LR rotation case
    if(bf>1 && val>node->left->data){
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    //RL rotation case
    if(bf<-1 && val<node->right->data){
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    return node;

}


//Searches for InOrder Successor

avlt *searchInOrderSuccessor(avlt* root){
    root = root->right;
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}

//Searches for InOrder Predecessor

avlt *searchInOrderPredecessor(avlt* root){
    root = root->left;
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

avlt *deleteNode(avlt *node,int val){

    if(node==NULL)return node;

    if(val<node->data)
        node->left = deleteNode(node->left,val);

    else if(val>node->data)
        node->right = deleteNode(node->right,val);

    else{
        if(node->left==NULL||node->right==NULL){
            avlt *temp = node->left ? node->left : node->right;
            if(temp==NULL){
                temp = node;
                node = NULL;
            }
            else{
                *node = *temp;
                free(temp);
            }

        }
        else{
            avlt *temp = searchInOrderSuccessor(node);
            node->data = temp->data;
            node->right = deleteNode(node->right,temp->data);
        }
    }
    if(node==NULL) return node;

    node->height = 1+max(getHeight(node->left),getHeight(node->right));
    int bf = getBalanceFactor(node);

    //LL rotation case
    if(bf>1 && val<node->left->data){
        return rightRotation(node);
    }
    //RR rotation case
    if(bf<-1 && val>node->data){
        return leftRotation(node);
    }
    //LR rotation case
    if(bf>1 && val>node->left->data){
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    //RL rotation case
    if(bf<-1 && val<node->right->data){
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    return node;


}
