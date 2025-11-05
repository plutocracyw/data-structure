//一元稀疏多项式计算器
#include <iostream>
#include <cmath>
using namespace std;

struct Term{
    int coef; //系数
    int expn; //指数
    Term* next;
    Term(int c, int e):coef(c),expn(e),next(NULL){}
};

void insertTerm(Term* &head, int coef, int expn){
    if(coef == 0) return; //系数为0，不插入
    Term* newTerm = new Term(coef, expn);
    if(head == NULL || expn > head->expn){
        newTerm->next = head;
        head = newTerm;
        return;
    }

    Term* p = head;
    Term* prev = NULL;


    while(p != NULL && p->expn > expn){
        prev=p;
        p=p->next;
    }

    if(p != NULL && p->expn == expn){
        p->coef += coef;//合并同类项
        if(p->coef == 0){
            //删除节点
            if(prev == NULL){
                head = p->next;
            } else {
                prev->next = p->next;
            }
            delete p;
        }
        delete newTerm; //释放新节点内存
    }
    else{
        newTerm->next = p;
        if(prev == NULL){
            head = newTerm;
        } else {
            prev->next = newTerm;
        }
    }
}

void printPoly(Term* head){
    if(head==NULL){
        cout << "0" << endl;
        return;
    }
    Term* p = head;
    bool first = true;
    while(p != NULL){
        if(!first && p->coef > 0) 
            cout << "+";
        if(p->expn == 0){
            cout << p->coef;
        } 
        else if(p->expn == 1){
            if(p->coef == 1) cout << "x";
        } else {
            cout << p->coef << "x^" << p->expn;
        }
        first = false;
        p = p->next;
    }
    cout << endl;
}

//加法
Term* addPoly(Term* A, Term* B){
    Term* result = NULL;
    Term *p = A;
    while(p != NULL){
        insertTerm(result, p->coef, p->expn);
        p = p->next;
    }
    p= B;;
    while(p != NULL){
        insertTerm(result, p->coef, p->expn);
        p = p->next;
    }
    return result;
}

//减法
Term* subPoly(Term* A, Term* B){
    Term* result = NULL;
    Term *p = A;
    while(p != NULL){
        insertTerm(result, p->coef, p->expn);
        p = p->next;
    }
    p= B;
    while(p != NULL){
        insertTerm(result, -p->coef, p->expn);
        p = p->next;
    }
    return result;
}

//乘法
Term* mulPoly(Term* A, Term* B){
    Term* result = NULL;
    for(Term* p = A; p != NULL; p = p->next){
        for(Term* q = B; q != NULL; q = q->next){
            insertTerm(result, p->coef * q->coef, p->expn + q->expn);
        }
    }
    return result;
}

//释放多项式内存
void freePoly(Term* head){
    Term* p = head;
    while(p != NULL){
        Term* temp = p;
        p = p->next;
        delete temp;
    }
}

//创建多项式
Term* createPoly(){
    Term* head = NULL;
    int n;
    cout << "Enter number of terms: ";
    cin >> n;
    for(int i=0; i<n; ++i){
        int coef, expn;
        cout << "Enter coefficient and exponent of term " << (i+1) << ": ";
        cin >> coef >> expn;
        insertTerm(head, coef, expn);
    }
    return head;
}

int main(){
    cout<<"Welcome to the Sparse Polynomial Calculator!"<<endl;
    cout << "Create first polynomial:" << endl;
    Term* poly1 = createPoly();
    cout << "First polynomial: ";
    printPoly(poly1);

    cout << "Create second polynomial:" << endl;
    Term* poly2 = createPoly();
    cout << "Second polynomial: ";
    printPoly(poly2);
    int choice;
    while(choice!=-1){
        cout<<"Choose operation: 1. Addition 2. Subtraction 3. Multiplication"<<endl;
        cin>>choice;
        if(choice==-1) break;
        
        switch(choice){
            case 1:{
                Term* result = addPoly(poly1, poly2);
                cout << "Result: ";
                printPoly(result);
                freePoly(result);
                break;
            }
            case 2:{
                Term* result = subPoly(poly1, poly2);
                cout << "Result: ";
                printPoly(result);
                freePoly(result);
                break;
            }
            case 3:{
                Term* result = mulPoly(poly1, poly2);
                cout << "Result: ";
                printPoly(result);
                freePoly(result);
                break;
            }
            default:
                cout << "Invalid choice! Please enter 1, 2 or 3" << endl;
                freePoly(poly1);
                freePoly(poly2);
                return 0;
        }
    }

    //释放内存
    freePoly(poly1);
    freePoly(poly2);

    return 0;
}