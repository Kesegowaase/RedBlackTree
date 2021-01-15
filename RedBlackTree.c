#include <stdio.h> 
#include <stdlib.h> 
struct node{ 
	int number; // number 
	char color; // 'r'-red, 'b'-black 
	struct node* parent; // parent 
	struct node* right; // right-child 
	struct node* left; // left child 
}; 

struct node* root = NULL; 
int Max(int leftHight,int rightHight){
    if(rightHight <= leftHight)
        return leftHight;
    else if(rightHight >= leftHight)
        return rightHight;
}

struct node* newNode(int number){ 
    struct node* temp = (struct node*)malloc(sizeof(struct node)); 
    temp->right = NULL; 
    temp->left = NULL; 
    temp->parent = NULL; 
    temp->number =  number;
    temp->color = 'R'; 
    return temp; 
} 

struct node* bst(struct node* trav, struct node* temp){ 
    
    if (trav == NULL){
        return temp;
    } 
    if(trav != NULL){

        if(temp->number > trav->number){ 
            trav->right = bst(trav->right, temp); 
            trav->right->parent = trav; 
            return trav; 
        } 
        else if (temp->number < trav->number){ 
            trav->left = bst(trav->left, temp); 
            trav->left->parent = trav; 
            return trav; 
        } 
    }
} 



void rightrotate(struct node* temp){ 
	struct node* left = temp->left; 
    struct node * rightofleft = left->right; 
	temp->left = rightofleft;
	if (temp->left != 0) 
		temp->left->parent = temp; 
	left->parent = temp->parent; 
	if (!temp->parent != 0) 
		root = left; 
	else if (temp == temp->parent->left) 
		temp->parent->left = left; 
	else
		temp->parent->right = left; 
	left->right = temp; 
	temp->parent = left; 
} 

void leftrotate(struct node* temp) 
{ 
	struct node* right = temp->right; 
    struct node * leftofright = right->left;
	temp->right = leftofright; 
	if (temp->right != 0) 
		temp->right->parent = temp; 
	right->parent = temp->parent; 
	if (!temp->parent != 0) 
		root = right; 
	else if (temp == temp->parent->left) 
		temp->parent->left = right; 
	else
		temp->parent->right = right; 
	right->left = temp; 
	temp->parent = right; 
} 


void fixup(struct node* root, struct node* pt) 
{ 
	struct node* parent_pt = NULL; 
	struct node* grand_parent_pt = NULL; 

	while ((pt != root) && (pt->color != 'B') && (pt->parent->color == 'R')) { 
		parent_pt = pt->parent; 
		grand_parent_pt = pt->parent->parent; 

		if (parent_pt == grand_parent_pt->left) 
		{ 

			struct node* uncle_pt = grand_parent_pt->right; 

			if (uncle_pt != NULL && uncle_pt->color == 'R') 
			{ 
                grand_parent_pt->color = 'R'; 
                parent_pt->color = 'B'; 
                uncle_pt->color = 'B'; 
                pt = grand_parent_pt; 
			} 

			else { 

				if (pt == parent_pt->right) { 
					leftrotate(parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				rightrotate(grand_parent_pt); 
				int t = parent_pt->color; 
				parent_pt->color = grand_parent_pt->color; 
				grand_parent_pt->color = t; 
				pt = parent_pt; 
			} 
		} 

		else { 
			struct node* uncle_pt = grand_parent_pt->left; 

			if ((uncle_pt != NULL) && (uncle_pt->color == 'R')){ 
				grand_parent_pt->color = 'R'; 
				parent_pt->color = 'B'; 
				uncle_pt->color = 'B'; 
				pt = grand_parent_pt; 
			} 
			else { 

				if (pt == parent_pt->left) { 
					rightrotate(parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				leftrotate(grand_parent_pt); 
				int t = parent_pt->color; 
				parent_pt->color = grand_parent_pt->color; 
				grand_parent_pt->color = t; 
				pt = parent_pt; 
			} 
		} 
	} 

	
}

void displayAllTree(struct node* head){
    struct node* temp = head;
    if(temp == NULL)
        return;
    displayAllTree(temp -> left);
    printf("%d\n",temp -> number);
    displayAllTree(temp -> right);
    
}

int treeHight(struct node* head){
    if(head == NULL)
        return 0;
    else{
        int leftHight = treeHight(head -> left);
        int rightHight = treeHight(head -> right);
        return Max(leftHight,rightHight)+1;
    }
}
void printChild(struct node* head){
    if(head -> left != NULL){
        printf("%d ",head -> left ->number);
        printf("%c ",head -> left -> color);
        printf("(%d L) ",head -> number);
    }
    if(head -> right != NULL){
        printf("%d ",head -> right ->number);
        printf("%c ",head -> right -> color);
        printf("(%d R) ",head -> number);
    }
}
void level(struct node *head,int firstLevel,int lastLevel){
    if(head == NULL)
        return;
    if(firstLevel == lastLevel){
        printChild(head);
        return;
    }
    firstLevel+=1;
    level(head -> left,firstLevel,lastLevel);
    level(head -> right,firstLevel,lastLevel);
}

int main(){ 
    struct node* temp;
    struct node* temp2;
    int number;
    while(1){ 
        scanf("%d",&number);
        if (number == -1)
            break;
        temp2 = newNode(number);
        root = bst(root, temp2); 
        
        fixup(root, temp2); 
        root->color = 'B'; 
    } 
    temp = root;
    displayAllTree(temp);
    printf("\n");
    int height = treeHight(temp);
    temp = root;
    if(temp != NULL){
        printf("%d ",temp -> number);
        printf("%c\n",temp -> color);
    }
    for(int i=1;i < height;i++){
        level(temp,1,i);
        printf("\n");
        temp = root;
    }

}
