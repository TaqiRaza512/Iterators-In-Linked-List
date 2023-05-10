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
		friend class List;
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
		Fl_Iterator& operator--()
		{
			fi = fi->Previous;
			return *this;
		}
		bool operator==(Fl_Iterator T)
		{
			return this->fi == T.fi;
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
		Node* Forward=ForwardIterator.fi;
		Node* Temp=new Node(Data);
		if (ForwardIterator == nullptr)
		{
			InsertAtFront(Data);
			return;
		}
		Temp->Previous = Forward;
		Temp->Next = Forward->Next;
		Forward->Next = Temp;
		Temp->Next->Previous = Forward->Next;
		size++;
	}
	void InsertAtBefore(Fl_Iterator ForwardIterator, T Data)
	{
		Node Temp;
		--ForwardIterator;
		InsertAtAfter(ForwardIterator, Data);
	}
	void RemoveAt(Fl_Iterator ForwardIterator)
	{
		Node* Forward= ForwardIterator.fi;
		Node* Temp = Forward->Next;
		Forward->Next = Temp->Next;
		Temp->Next->Previous = Forward;
		size--;
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
		cout << endl;
		for (Fl_Iterator p=T.fbegin();p!=T.fend(); ++p)
		{
			cout << *p<<"==>";
		}
		return cout;
	} 
};


int main()

{



	List<int>L;
	List<int> P;
	P.InsertAtEnd(5);
	P.InsertAtEnd(90);
	cout << P;
	cout << endl;

	L.InsertAtEnd(7);
	L.InsertAtEnd(3);
	L.InsertAtEnd(2);
	L.InsertAtFront(26);

	L.InsertAtFront(20);
	cout << L;
	cout << endl;
	cout<<L.Splice(P,2);
	cout << L;
	/*cout << endl << endl;
	cout << L;

	for (List<int>::Reverse_Iterator p = L.rbegin(); p != L.rend(); ++p)
	{
		if(p!=nullptr)
			(*p)--;
	}
	cout << endl << endl;
	cout << L;*/

	cout << L;
	List<int>::Fl_Iterator p = L.fbegin();
	L.InsertAtAfter(p,45);
	L.InsertAtBefore(p, 56);
	L.RemoveAt(p);
	cout << endl << L;

}