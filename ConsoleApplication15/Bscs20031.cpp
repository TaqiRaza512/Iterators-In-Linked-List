#include<iostream>
using namespace std;


template<typename T>
class List
{
private:
	class Node
	{
	private:
		Node* Next;
		Node* Previous;
		T Data;
		friend class List;
	public:
		Node(T D=0, Node* N=nullptr, Node* Pre = nullptr)
		{
			Next = N;
			Previous = Pre;
			Data = D;
		}
		friend ostream& operator<<(ostream&, Node& N)
		{
			return cout << N.Data << &N << "==>" << N.Next;
		}
	};
	Node* Tail;
	Node* Head;
	int size;

public:

	class Fl_Iterator
	{
		Node* fi;
	public:
		Fl_Iterator(Node* N)
		{
			fi = N;
		}
		Fl_Iterator& operator++()
		{
			fi = fi->Next;
			return *this;
		}
		bool operator==(Fl_Iterator T)
		{
			return this->fi == T->fi;
		}
		bool operator!=(Fl_Iterator T)
		{
			return this->fi != T.fi;
		}
		T& operator*()
		{
			return fi->Data;
		}
	};
	class Reverse_Iterator
	{
		Node* ri;
	public:
		Reverse_Iterator(Node* N)
		{
			ri = N;
		}
		Reverse_Iterator& operator++()
		{
			ri = ri->Previous;
			return *this;
		}
		bool operator==(Reverse_Iterator T)
		{
			return this->ri == T->ri;
		}
		bool operator!=(Reverse_Iterator T)
		{
			return this->ri != T.ri;
		}
		T& operator*()
		{
			return ri->Data;
		}
	};
	class General_Iterator
	{
		Node* ri;
	public:
		General_Iterator(Node* N)
		{
			ri = N;
		}
		General_Iterator& operator++()
		{
			ri = ri->Next;
			return *this;
		}
		General_Iterator& operator--()
		{
			ri = ri->Previous;
			return *this;
		}
		bool operator==(General_Iterator T)
		{
			return this->ri == T->ri;
		}
		bool operator!=(General_Iterator T)
		{
			return this->ri != T.ri;
		}
		T& operator*()
		{
			return ri->Data;
		}
	};
	List()
	{
		Head = Tail = nullptr;
		size = 0;
	}
	Fl_Iterator fbegin()
	{
		return Fl_Iterator(Head);
	}
	Fl_Iterator fend()
	{
		return Fl_Iterator(nullptr);
	}
	Reverse_Iterator rbegin()
	{
		return Reverse_Iterator(Tail);
	}
	Reverse_Iterator rend()
	{
		return Reverse_Iterator(nullptr);
	}
	General_Iterator gbegin()
	{
		return General_Iterator(Head);
	}
	General_Iterator gend()
	{
		return General_Iterator(nullptr);
	}
	bool IsEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}
	void InsertAtEnd(T D)
	{
		Node* Temp = new Node(D);
		if (Head == nullptr)
		{
			Tail = Temp;
			Head = Tail;
		}
		else 
		{
			Tail->Next = Temp;
			Temp->Previous = Tail;
			Tail = Temp;
		}
		size++;
	}
	void InsertAtFront(T D)
	{
		Node* Temp=new Node(D);
		if (Head == nullptr)
		{
			Head = Tail = Temp;
		}
		else
		{
			Head->Previous = Temp;
			Temp->Next = Head;
			Head = Temp;

		}
		size++;
	}
	void InsertAtAfter(Fl_Iterator ForwardIterator, T Data)
	{
		Node Temp;
		Temp->Previous = ForwardIterator;
		Temp->Next = ForwardIterator->Next;
		ForwardIterator->Next = Temp;
		Temp->Next->Previous = ForwardIterator->Next;
		size++;
	}
	void InsertAtBefore(Fl_Iterator ForwardIterator, T Data)
	{
		Node Temp;
		ForwardIterator--;
		InsertAtAfter(ForwardIterator, Data);
	}
	List& Splice(List T,int index)
	{
		int ri;
		Fl_Iterator p;

		for (ri=0,p = this->fbegin();index<ri, p != this->fend(); ++p,ri++)
		{
		}
		Node temp;
		temp =p;
		p.Next=T.Head;
		T.Tail = temp;
		return T;
	}
	friend ostream& operator<<(ostream&,List T)
	{

		for (Fl_Iterator p=T.fbegin();p!=T.fend(); ++p)
		{
			cout << *p<<"==>";
		}
		return cout;
	} 
};
class Node
{
private:

public:
	int data;
	Node* Next;

	Node(int D = 0, Node* N = nullptr)
	{
		data = D;
		N = Next;
	}
};


class MyLinkedList
{

private:
	friend class Node;

	Node* head;
	Node* tail;
public:
	int size;
	bool IsEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}
	MyLinkedList()
	{
		head = tail = nullptr;
		size = 0;
	}
	int get(int index)
	{
		if (index >= size)
			return -1;
		int ri;
		Node* Temp = head;
		for (ri = 0; ri <= (index); ri++)
		{
			if (ri == 0)
				Temp = head;
			else
				Temp = Temp->Next;
		}
		return Temp->data;
	}
	void addAtHead(int val)
	{
		if (IsEmpty())
		{
			tail = head = new Node(val);
		}
		else
		{
			Node* Temp = head;
			head = new Node(val);
			head->Next = Temp;
		}
		size++;
	}
	void addAtTail(int val)
	{
		if (IsEmpty())
		{
			tail = head = new Node(val);
		}
		else
		{
			Node* Temp = tail;
			tail = new Node(val);
			Temp->Next = tail;
		}
		size++;
	}
	void addAtIndex(int index, int val)
	{
		if (index > size)
			return;
		if (index == 0)
		{
			addAtHead(val);

			return;
		}
		else if (index == size)
		{
			addAtTail(val);

			return;

		}
		size++;

		Node* Temp = head;
		Node* Previous = head;
		Node* After = head->Next;
		Node* Addres = new Node(val);
		int ri;
		for (ri = 0; ri < (index + 1); ri++)
		{
			if (ri == 0)
			{
				Temp = head;
				After = head->Next;
			}
			else
			{
				Previous = Temp;
				Temp = Temp->Next;
				After = Temp->Next;
			}
		}
		Previous->Next = Addres;
		Addres->Next = Temp;
	}
	void deleteAtIndex(int index)
	{
		if (IsEmpty())
			return;
		if (index >= size)
			return;

		if (index == 0)
		{
			head = head->Next;
			size--;
			return;
		}
		Node* Temp = head;
		Node* After = head->Next;
		Node* Previous = head;
		int ri;
		for (ri = 0; ri < (index + 1); ri++)
		{
			if (ri == 0)
			{
				Temp = head;
				After = head->Next;
			}
			else
			{
				Previous = Temp;
				Temp = Temp->Next;
				if (Temp->Next == nullptr)
				{

					Previous->Next = nullptr;
					tail = Previous;
					size--;

					return;
				}
				if (Temp == nullptr)
				{
					After = Temp;
				}
				else
				{
					After = Temp->Next;
				}
			}
		}
		if (index == size - 1)
		{
			tail = Previous;
			tail->Next = nullptr;

		}
		else
		{
			Previous->Next = After;

		}
		size--;

	}
	friend ostream& operator<<(ostream&, MyLinkedList T)
	{
		for (Node* Temp = T.head; Temp != nullptr; Temp = Temp->Next)
		{
			cout << Temp->data << " ";
		}
		cout << endl;
		return cout;

	}
};

class Stack {
	MyLinkedList S; // no other memory than this.
public:

	Stack()
	{
		S.size = 0;
	}
	void Push(int V)
	{
		S.addAtTail(V);
	}
	int Pop()
	{
		S.deleteAtIndex(S.size-1);
	}
	bool IsEmpty()
	{
		if (S.size == 0)
			return true;
		return false;
	}

};

class Queue 
{
	MyLinkedList S; // no other memory than this.
public:
	Queue()
	{
		S.size = 0;
	}
	void Enqueue(int V) 
	{
		S.addAtTail(V);
	}
	int Dequeue()
	{
		S.deleteAtIndex(0);
	}
	bool IsEmpty()
	{
		if (S.size == 0)
			return true;
		return false;
	}
};




int main()

{



//	List<int>L;
//	List<int> P;
//	P.InsertAtEnd(5);
//	P.InsertAtEnd(90);
//
//	L.InsertAtEnd(7);
//	L.InsertAtEnd(3);
//	L.InsertAtEnd(2);
//	L.InsertAtFront(26);
//	L.InsertAtFront(20);
//	//cout<<L.Splice(P,2);
//
//	cout << L;
//	/*cout << endl << endl;
//	cout << L;
//	for (List<int>::Reverse_Iterator p = L.rbegin(); p != L.rend(); ++p)
//	{
//		if(p!=nullptr)
//			(*p)--;
//	}
//	cout << endl << endl;
//	cout << L;*/

}