#include <iostream>
#include <iomanip>
using namespace std;

struct Car
{
    int num;  // 车号
    int time; // 到达时间
};

// ===== 顺序栈（停车场） =====
struct SeqStack
{
    Car *data; // 存储车的数组
    int top;  // 栈顶指针
    int maxSize;

    SeqStack(int size) : top(-1), maxSize(size)
    {
        data = new Car[maxSize];
    }

    ~SeqStack() { delete[] data; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == maxSize - 1; }

    void push(Car c)
    {
        if (!isFull())
            data[++top] = c;
    }
    Car pop()
    {
        if (!isEmpty())
            return data[top--];
        return Car{-1, -1};// 栈空返回无效车
    }
};

// ===== 链式队列（便道） =====
struct QNode
{
    Car car;
    QNode *next;
    QNode(Car c) : car(c), next(nullptr) {}
};

struct LinkQueue
{
    QNode *front;
    QNode *rear;

    LinkQueue() : front(nullptr), rear(nullptr) {}
    ~LinkQueue()
    {
        while (front)
        {
            QNode *p = front;
            front = front->next;
            delete p;
        }
    }

    bool isEmpty() { return front == nullptr; }

    void enQueue(Car c)
    {
        QNode *node = new QNode(c);
        if (rear == nullptr)
            front = rear = node;
        else
        {
            rear->next = node;
            rear = node;
        }
    }

    Car deQueue()
    {
        if (isEmpty())
            return Car{-1, -1};
        QNode *p = front;
        Car c = p->car;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete p;
        return c;
    }
};

// ===== 模拟操作 =====
void carArrive(SeqStack &parking, LinkQueue &waiting, int carNum, int time)
{
    if (!parking.isFull())
    {
        parking.push(Car{carNum, time});
        cout << "Car " << carNum << " arrived at time " << time 
            << " and entered parking lot." << endl;
    }
    else
    {
        waiting.enQueue(Car{carNum, time});
        cout << "Car " << carNum << " arrived at time " << time
            << " and is waiting in queue." << endl;
    }
}

void carDepart(SeqStack &parking, LinkQueue &waiting, int carNum, int time, double rate = 1.0)
{
    SeqStack temp(parking.maxSize);
    bool found = false;
    Car c;

    // 从栈顶寻找要离开的车
    while (!parking.isEmpty())
    {
        c = parking.pop();
        if (c.num == carNum)
        {
            found = true;
            break;
        }
        else
            temp.push(c);
    }

    if (!found)
    {
        cout << "Car " << carNum << " not found in parking lot!" << endl;
        // 还原栈
        while (!temp.isEmpty())
        {
            parking.push(temp.pop());
        }
        return;
    }

    int stay = time - c.time;
    cout << "Car " << carNum << " departed at time " << time
         << ", stayed " << stay << " units, fee = " << fixed << setprecision(2)
         << stay * rate << endl;

    // 将临时栈的车放回原栈
    while (!temp.isEmpty())
    {
        parking.push(temp.pop());
    }

    // 若有等待的车，进入停车场
    if (!waiting.isEmpty())
    {
        Car next = waiting.deQueue();
        next.time = time; // 更新进入时间
        parking.push(next);
        cout << "Car " << next.num << " moved from waiting lane into parking lot." << endl;
    }
}

// ===== 主程序 =====
int main()
{
    int capacity;
    cout << "Enter parking lot capacity: ";
    cin >> capacity;

    SeqStack parking(capacity);
    LinkQueue waiting;

    cout << "Enter commands (A num time / D num time / E):" << endl;
    char op;
    int num, t;
    while (cin >> op)
    {
        if (op == 'E')
            break;
        cin >> num >> t;
        if (op == 'A')
            carArrive(parking, waiting, num, t);
        else if (op == 'D')
            carDepart(parking, waiting, num, t);
        else
            cout << "Invalid command!" << endl;
    }

    cout << "Simulation ended." << endl;
    return 0;
}