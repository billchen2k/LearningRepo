#include <iostream>

using namespace std;

class Node //组成双向链表的节点
{
      public:
	int data;
	Node *pNext;
	Node *pLast;
};

class List //构造一个双向链表
{
      private:
	Node *pHead;
	Node *pTail;
	int length;

      public:
	List(int length)#include<iostream>

using namespace std;

class Node          //组成双向链表的节点
{
public:
    int data;
    Node * pNext;
    Node * pLast;
};

class List      //构造一个双向链表
{
private:
    Node * pHead;
    Node * pTail;
    int length;
public:
    List(int length)    //创建双向链表
    {
        this->length=length;
        pHead=new Node();
        pHead->pLast=NULL;
        pTail=pHead;
        for(int i=0;i<length;i++)
        {
            Node * temp=new Node();
            cout<<"please enter the no"<<i+1<<" Node's data:";
            cin>>temp->data;
            temp->pNext=NULL;
            temp->pLast=pTail;
            pTail->pNext=temp;
            pTail=temp;
        }
    }
    
    void traverseList()    //正向遍历
    {
        Node * p=pHead->pNext;
        while(p!=NULL)
        {
            cout<<p->data<<endl;
            p=p->pNext;
        }
    }
    
    void traverseListReturn()    //逆向遍历
    {
        Node * p=pTail;
        while(p->pLast!=NULL)
        {
            cout<<p->data<<endl;
            p=p->pLast;
        }
    }
    
    void sortList()     //冒泡排序
    {
        Node * p=new Node();
        Node * q=new Node();
        int temp;
        for(p=pHead->pNext;p->pNext!=NULL;p=p->pNext)
        {
            for(q=p->pNext;q!=NULL;q=q->pNext)
            {
                if(q->data<p->data)
                {
                    temp=q->data;
                    q->data=p->data;
                    p->data=temp;
                }
            }
        }
    }
    
    void sortListByInsertWay()        //插入排序
    {
        if(pHead->pNext==NULL||pHead->pNext->pNext==NULL)
        {
            return;
        }
        Node * p2=pHead->pNext->pNext;
        Node * p1=pHead;
        pHead->pNext->pNext=NULL;
        while(p2)
        {
            Node * pN=p2->pNext;
            while(p1->pNext)
            {
                if(p2->data<p1->pNext->data)
                {
                    p2->pNext=p1->pNext;
                    p2->pLast=p1;
                    p1->pNext->pLast=p2;
                    p1->pNext=p2;
                    break;
                }
                p1=p1->pNext;
            }
            if(p1->pNext==NULL)
            {
                p2->pNext=NULL;
                p2->pLast=p1;
                p1->pNext=p2;
            }
            p2=pN;
        }
        
        //重新查找pTail的位置
        Node * pt=pHead;
        while(pt->pNext)
        {
            pt=pt->pNext;
        }
        pTail=pt;
    }
    
    void changeList(int num,int position)    //修改链表中指定位置的节点
    {
        Node * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack !"<<endl;
            return;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        p->data=num;
    }
    
    void insertList(int num,int position)    //插入数据
    {
        Node * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack !"<<endl;
            return;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        Node * temp=new Node();
        temp->data=num;
        temp->pNext=p;
        temp->pLast=p->pLast;
        p->pLast->pNext=temp;
        p->pLast=temp;
        length++;
    }
    
    void clearList()      //清空
    {
        Node * q;
        Node * p=pHead->pNext;
        while(p!=NULL)
        {
            q=p;
            p=p->pNext;
            delete q;
        }
        p=NULL;
        q=NULL;
    }
    
    void deleteList(int position)   //删除指定位置的节点
    {
        Node * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack !"<<endl;
            return;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        p->pLast->pNext=p->pNext;
        p->pNext->pLast=p->pLast;
        delete p;
        length--;
    }
    
    int getItemInList(int position)      //查找指定位置的节点
    {
        Node * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack !"<<endl;
            return 0;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        return p->data;
    }
    
    ~List()
    {
        Node * q;
        Node * p=pHead->pNext;
        while(p!=NULL)
        {
            q=p;
            p=p->pNext;
            delete q;
        }
        p=NULL;
        q=NULL;
    }
    
};

int main()
{
    List l(3);
    l.traverseList();
    cout<<"AFTER SORT------------------------------------------------------"<<endl;
//    l.sortList();             //冒泡排序
    l.sortListByInsertWay();    //插入排序
    l.traverseList();
    cout<<"AFTER INSERT-----------------------------------------------------"<<endl;
    l.insertList(55,1);
    l.traverseList();
    cout<<"AFTER DELETE-----------------------------------------------------"<<endl;
    l.deleteList(1);
    l.traverseList();
    cout<<"Return Traverse---------------------------------------------"<<endl;
    l.traverseListReturn();
    cout<<"Find the Second Node's data:"<<l.getItemInList(2)<<endl;
    return 0;
}    //创建双向链表
	{
		this->length = length;
		pHead = new Node();
		pHead->pLast = NULL;
		pTail = pHead;
		for (int i = 0; i < length; i++) {
			Node *temp = new Node();
			cout << "please enter the no" << i + 1 << " Node's data:";
			cin >> temp->data;
			temp->pNext = NULL;
			temp->pLast = pTail;
			pTail->pNext = temp;
			pTail = temp;
		}
	}

	void traverseList()     //正向遍历
	{
		Node *p = pHead->pNext;
		while (p != NULL) {
			cout << p->data << endl;
			p = p->pNext;
		}
	}

	void traverseListReturn()     //逆向遍历
	{
		Node *p = pTail;
		while (p->pLast != NULL) {
			cout << p->data << endl;
			p = p->pLast;
		}
	}

	void sortList() //冒泡排序
	{
		Node *p = new Node();
		Node *q = new Node();
		int temp;
		for (p = pHead->pNext; p->pNext != NULL; p = p->pNext) {
			for (q = p->pNext; q != NULL; q = q->pNext) {
				if (q->data < p->data) {
					temp = q->data;
					q->data = p->data;
					p->data = temp;
				}
			}
		}
	}

	void sortListByInsertWay() //插入排序
	{
		if (pHead->pNext == NULL || pHead->pNext->pNext == NULL) {
			return;
		}
		Node *p2 = pHead->pNext->pNext;
		Node *p1 = pHead;
		pHead->pNext->pNext = NULL;
		while (p2) {
			Node *pN = p2->pNext;
			while (p1->pNext) {
				if (p2->data < p1->pNext->data) {
					p2->pNext = p1->pNext;
					p2->pLast = p1;
					p1->pNext->pLast = p2;
					p1->pNext = p2;
					break;
				}
				p1 = p1->pNext;
			}
			if (p1->pNext == NULL) {
				p2->pNext = NULL;
				p2->pLast = p1;
				p1->pNext = p2;
			}
			p2 = pN;
		}

		//重新查找pTail的位置
		Node *pt = pHead;
		while (pt->pNext) {
			pt = pt->pNext;
		}
		pTail = pt;
	}

	void changeList(int num, int position)     //修改链表中指定位置的节点
	{
		Node *p = pHead->pNext;
		if (position > length || position <= 0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++) {
			p = p->pNext;
		}
		p->data = num;
	}

	void insertList(int num, int position)     //插入数据
	{
		Node *p = pHead->pNext;
		if (position > length || position <= 0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++) {
			p = p->pNext;
		}
		Node *temp = new Node();
		temp->data = num;
		temp->pNext = p;
		temp->pLast = p->pLast;
		p->pLast->pNext = temp;
		p->pLast = temp;
		length++;
	}

	void clearList()       //清空
	{
		Node *q;
		Node *p = pHead->pNext;
		while (p != NULL) {
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}

	void deleteList(int position)    //删除指定位置的节点
	{
		Node *p = pHead->pNext;
		if (position > length || position <= 0) {
			cout << "over stack !" << endl;
			return;
		}
		for (int i = 0; i < position - 1; i++) {
			p = p->pNext;
		}
		p->pLast->pNext = p->pNext;
		p->pNext->pLast = p->pLast;
		delete p;
		length--;
	}

	int getItemInList(int position)       //查找指定位置的节点
	{
		Node *p = pHead->pNext;
		if (position > length || position <= 0) {
			cout << "over stack !" << endl;
			return 0;
		}
		for (int i = 0; i < position - 1; i++) {
			p = p->pNext;
		}
		return p->data;
	}

	~List() {
		Node *q;
		Node *p = pHead->pNext;
		while (p != NULL) {
			q = p;
			p = p->pNext;
			delete q;
		}
		p = NULL;
		q = NULL;
	}
};

int main() {
	List l(3);
	l.traverseList();
	cout << "AFTER SORT------------------------------------------------------" << endl;
	//    l.sortList();             //冒泡排序
	l.sortListByInsertWay(); //插入排序
	l.traverseList();
	cout << "AFTER INSERT-----------------------------------------------------" << endl;
	l.insertList(55, 1);
	l.traverseList();
	cout << "AFTER DELETE-----------------------------------------------------" << endl;
	l.deleteList(1);
	l.traverseList();
	cout << "Return Traverse---------------------------------------------" << endl;
	l.traverseListReturn();
	cout << "Find the Second Node's data:" << l.getItemInList(2) << endl;
	return 0;
}