//非常好的一个链表的应用
//用链表实现集合的基本操作：并集、交集、差集

#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

struct Node{
    char data; 
    Node* next;
    Node(char c):data(c),next(NULL){}//构造函数
};

void insert(Node* &head, char c){
    Node* newNode = new Node(c);//创建新节点，用来存放字符c
    if(head == NULL || c < head->data){
        head = newNode;
        return;
    }//空链表或插入头部

    //找到插入位置，保持升序
    Node* p = head;
    while(p->next != NULL && p->next->data < c){
        p = p->next;
    }

    //去重
    if(p->data != c){
        newNode->next = p->next;
        p->next = newNode;
    } else {
        delete newNode; //释放内存
    }
}

//根据字符串创建集合链表
Node* creatset(const string& str){
    Node* head = NULL;
    for(char c : str){
        if(c>='a' && c<='z')
            insert(head, c);
    }
    return head;
}

//
void printset(Node* head){
    Node* p = head;
    while(p != NULL){
        cout << p->data;
        p = p->next;
    }
    cout << endl;
}

//并集
Node* unionSet(Node* set1, Node* set2){
    Node* result = NULL;
    Node *p1 = set1;
    Node *p2 = set2;
    while(p1 != NULL && p2 != NULL){
        if(p1->data < p2->data){
            insert(result, p1->data);
            p1 = p1->next;
        } else if(p1->data > p2->data){
            insert(result, p2->data);
            p2 = p2->next;
        } else {
            insert(result, p1->data);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while(p1 != NULL){
        insert(result, p1->data);
        p1 = p1->next;
    }
    while(p2 != NULL){
        insert(result, p2->data);
        p2 = p2->next;
    }
/*
假设：
    Set1：a c e
    Set2：b c f
遍历：
    比较	    动作	      Result
    a vs b	  a<b → 插入a	    a
    c vs b	  b<c → 插入b	   a b
    c vs c	 相等 → 插入c	  a b c
    e vs f	 e<f → 插入e	 a b c e
    NULL vs f	插入f	    a b c e f
    最终结果：a b c e f
*/

    return result;
}

//交集
Node* intersectionSet(Node* set1, Node* set2){
    Node* result = NULL;
    Node *p1 = set1;
    Node *p2 = set2;
    while(p1 != NULL && p2 != NULL){
        if(p1->data == p2->data){
            insert(result, p1->data);
            p1 = p1->next;
            p2 = p2->next;
        } else if(p1->data < p2->data){
            p1 = p1->next;
        } else {
            p2 = p2->next;
        }
    }
    return result;
}

//差集 set1 - set2
Node* differenceSet(Node* set1, Node* set2){
    Node* result = NULL;
    Node *p1 = set1;
    while(p1 != NULL){
        bool isInSet2 = false;
        Node *p2 = set2;
        while(p2 != NULL){
            if(p1->data == p2->data){
                isInSet2 = true;
                break;
            }
            p2 = p2->next;
        }

        if(!isInSet2){
            insert(result, p1->data);
        }
        p1=p1->next;
    }
    return result;
}

void freeSet(Node* head){
    Node* p = head;
    while(p != NULL){
        Node* temp = p;
        p = p->next;
        delete temp;
    }
}

int main(){
    string s1, s2;
    cout<<"Please enter the first string: ";
    cin>>s1;
    cout<<"Please enter the second string: ";
    cin>>s2;

    Node* set1 = creatset(s1);
    Node* set2 = creatset(s2);

    int choice;
    while(choice!=-1){
        cout<<"Choose operation: 1. Union 2. Intersection 3. Difference"<<endl;
        cin>>choice;
        if(choice==-1) break;

        switch (choice)
        {
        case 1:
            cout << "Set1 and Set2 = ";
            printset(unionSet(set1, set2));
            break;
        case 2:
            cout << "Set1 * Set2 = ";
            printset(intersectionSet(set1, set2));
            break;
        case 3:
            cout << "Set1 - Set2 = ";
            printset(differenceSet(set1, set2));
            break;
        default:
            cout << "Invalid choice! Please enter 1 or o r 3" << endl;
            freeSet(set1);
            freeSet(set2);
            break;
        }
    }

    //释放内存
    freeSet(set1);
    freeSet(set2);

    return 0;
}