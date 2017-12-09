#include <bits/stdc++.h>
using namespace std;

// BST implementation
// remove counter

bool removed;
Node * root=nullptr;
int ans;

Node * insert(Node * root,int key,Node * par){
    // insert a element "key" into the tree
    // supports multiple elements by keeping a counter in the nodes
    if(root==nullptr)
        return root=new Node(key,par);
    if(root->val==key)
        root->counter++;
    else if(key<root->val){
        root->index++;
        root->left=insert(root->left,key,root);
    }else
        root->right=insert(root->right,key,root);
    return root;
}

Node * findMin(Node * root) {
    // find the min element in the subtree root
    if(root->left!=nullptr)
        return findMin(root->left);
    return root;
}

Node * remove(Node * root,int key){
    // remove key from tree if it exists
    if(root==nullptr)
        return root;
    if(root->val>key){
        root->left=remove(root->left,key);
        if(removed)
            root->index--;
    }else if(root->val<key)
        root->right=remove(root->right,key);
    else{
        removed=1;
        if(root->counter>1)
            root->counter--;
        else if(root->left==nullptr&&root->right==nullptr){
            delete root;
            root=nullptr;
        }else if(root->left==nullptr)
            root=root->right;
        else if(root->right==nullptr)
            root=root->left;
        else {
            Node * temp=findMin(root->right);
            root->val=temp->val;
            root->right=remove(root->right,temp->val);
        }
    }
    return root;
}

Node * findIndex(Node * root,int x){
    // find the value at index x
    // answer stored in global var "ans"
    if(x>=root->index&&x<root->index+root->counter)
        ans=root->val;
    else if(x<root->index)
        root->left=findIndex(root->left,x);
    else
        root->right=findIndex(root->right,x-root->index-root->counter+1);
    return root;
}

Node * findVal(Node * root,int key,int x){
    // find the index of key in the tree
    // answer stored in global var "ans"
    // -1 if key does not exist in tree
    if(root==nullptr){
        ans=-1;
        return root;
    }
    if(root->val==key)
        ans=root->index+x;
    else if(key<root->val)
        root->left=findVal(root->left,key,x);
    else
        root->right=findVal(root->right,key,x+root->index+root->counter-1);
    return root;
}

void inOrder(Node * root){
    // inorder traversal of tree
    // displays all elements in the tree in sorted order
    if(root==nullptr)
        return;
    inOrder(root->left);
    for(int i=0;i<root->counter;++i)
        printf("%d ", root->val);
    inOrder(root->right);
    return;
}

int main(){
    return 0;
}
