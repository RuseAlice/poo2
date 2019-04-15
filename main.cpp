/**
clasa coada sa fie prietena a clasei nod si sa contina metode de: push; pop; top
(afisarea varfului cozii);
afisarea cozii, concomitent cu golirea ei, realizata prin
supraincarcarea operatorului<<;
supraincarcarea operatorului >>, realizata prin
push-uri succesive;
concatenarea a doua cozi de caractere, obtinand o alta coada
de caractere, implementata prin supraincarcarea operatorului +;
diferenta a doua cozi de caractere, care sa supraincarce operatorul - si sa fie constea in eliminarea
din prima coada a tuturor elementelor de la inceputul acelei prime cozi care
coincid cu elementele de la inceputul celei de-a doua cozi, atat ca informatie (adica
valoare, caracterul pe care il contin), cat si ca pozitie in coada; aceasta ultima
metoda va efectua pop-uri succesive pe ambele cozi;

1. toate clase vor con?ine obligatoriu constructori de ini?ializare, parametrizati ?i de
copiere, destructor, iar operatorii >>,<<,= sa fie supraincarcati.
2. ilustrarea conceptelor de mo?tenire ?i functii virtuale (pure – unde se considera
mai natural)
3. citirea informa?iilor complete a n obiecte, memorarea ?i afisarea acestora
4. Fiecare din temele de mai jos au o tema din Tema1 corespunzatoare. Veti gasi
care anume in dreptul temei respective. Asta inseamna ca trebuie implementate
si cerintele din Tema1 respective.
5. Operatorii trebuie implementati ca functii membre ale claselor, nu ca functii
friend.(mai putin in cazul operatorilor >> si <<)
6. Accentul se pune pe mosteniri, functii virtuale. (Un design ce presupune functii
virtuale pure/clase abastracte/interfete este apreciat)
7. Daca considerati ca aveti un design mai bun pentru implementarea mostenirilor si
in general a temei puteti sa il folositi si la prezentare sa spuneti de ce ati
implementat asa insa trebuie sa aveti in continuare implementate atat mosteniri
cat si functii virtuale.
8. Cerintele obligatorii de la Tema1 se pastreaza si aici (cele cu verde). De exemplu,
toate clasele vor trebui sa fie implementate folosind alocare dinamica.
9. Aveti grija sa dealocati memoria si sa implementati constructorii de copiere,
operatorii = si >> bine.
10. Nu aveti voie sa folositi STL.

Se dau urmatoarele clase:
- Nod (char info, nod*next)
- Coada (nod * prim, nod * ultim, int dim_max);
- DEQUE:Coada - cu operatiile de adaugare ?i stergere modificate corespunzator.
- PriorityQueue:Coada - cu operatiile de adaugare ?i stergere modificate
corespunzator.

Clasele derivate trebuie sa contina cel pu?in constructori parametrizati prin
care sa se evidentieze transmiterea parametrilor catre constructorul din clasa
de baza si destructor.
*/


#include <iostream>
#include <fstream>
#include <stddef.h>

using namespace std;


ifstream fin("date.in");
ofstream fout("date.out");

class Nod
{
protected:
	char info;
	Nod *next;

public:
	Nod(char i = 0, Nod *urm = NULL);
	Nod(const Nod &n);
	virtual ~Nod() { }
	void set_info(char a);
	void set_next(Nod *m);
	char get_info();
	Nod* get_next();

	friend istream &operator>>(istream &i, Nod &n);
	friend ostream &operator<<(ostream &i, Nod &n);
	virtual void citire(istream &i);
	virtual void afisare(ostream &i);
	virtual bool  operator==(const Nod &n);
	Nod& operator=(const Nod &n);
	friend class Coada;
};

char Nod::get_info() {
	return info;
}

Nod* Nod::get_next() {
	return next;
}

void Nod::set_info(char a) {
	info = a;
}

void Nod::set_next(Nod* n) {
	next = n;
}

Nod::Nod(char i, Nod *urm)
{
	info = i;
	next = urm;

}

Nod::Nod(const Nod &n)
{
	info = n.info;
	next = n.next;
}

void Nod::afisare(ostream &i)
{
	i << info;
}

void Nod::citire(istream &i)
{
	i >> info;
}

ostream  &operator<<(ostream &i, Nod &n)
{
	n.afisare(i);
	return i;
}

istream  &operator>>(istream &i, Nod &n)
{
	n.citire(i);
	return i;
}

bool Nod:: operator==(const Nod &n)
{
	if (this->info != n.info ||  next != n.next)
		return 0;
	return 1;
}

Nod& Nod:: operator=(const Nod &n)
{
	this->info = n.info;
	this->next = n.next;
	return *this;
}

/* ----------------------------------------------------------------------------------------------*/

class Coada
{
protected:
	Nod *prim;
	Nod *ultim;
	int dim_max;
	int dim;

public:
	Coada();  ///constructor fara parametri
	Coada(Nod vect[20], int dim, int d);  ///constructor cu parametri
	Coada(const Coada &c); ///copy constructor
	virtual ~Coada()
	{
		delete[]this;
	}
    void set_prim(Nod *n);
    void set_ultim(Nod *n);
    void set_dim_max(int x);
    void set_dim(int x);
    Nod * get_prim();
    Nod * get_ultim();
    int get_dim_max();
    int get_dim();
	friend istream &operator>>(istream &i, Coada &c);
	friend ostream &operator<<(ostream &i, Coada &c);
	virtual void citire(istream &i);
	virtual void afisare(ostream &i);
	virtual void push(Nod* n);
	virtual void pop();
	virtual Coada& operator=(const Coada &c);
	virtual Coada& operator-(Coada &c);
	virtual Coada& operator+(const Coada & c);
};

Coada::Coada()  ///constructor fara parametri
{
	prim = NULL;
	ultim = NULL;
	dim_max = 100;
	dim=0;
}

    void Coada::set_prim(Nod *n){
    prim=n;
    }
    void Coada:: set_ultim(Nod *n){
    ultim=n;
    }
    void Coada::set_dim_max(int x){
    dim_max=x;
    }
    void Coada::set_dim(int x){
    dim=x;
    }
    Nod * Coada::get_prim(){
    return prim;
    }
    Nod * Coada::get_ultim(){
    return ultim;
    }
    int Coada::get_dim_max(){
    return dim_max;
    }
    int Coada::get_dim(){
    return dim;
    }
Coada::Coada(Nod vect[20], int dim, int d)  ///constructor cu parametri
{
	this->dim_max = dim;
	prim->set_info(vect[0].get_info());
	prim->set_next(&vect[1]);
	ultim->set_info(vect[d-1].get_info());
	ultim->set_next(NULL);
	int i;

         Nod n;
        n=*prim;

        for( i=1; i<d-1; i++)
        {
            n.set_info(vect[i].get_info());
            n.set_next(&vect[i+1]);

        }
        dim=d;
}

Coada::Coada(const Coada &c) ///copy constructor
{

	Nod n, m;
	m = *c.prim;
	prim = c.prim;
	n = *prim;
	while (m.next)
	{
		n.next = m.next;
		n = *n.next;
		m = *m.next;
	}

	///ultim=c.ultim;
	dim_max = c.dim_max;

}

istream  &operator>>(istream &i, Coada &c)
{
	c.citire(i);
return i;
}

void Coada::citire(istream &i)
{
	/**Nod n;
	i >> dim_max;
	i>> d;
	i >> n;
	prim.set_info(n);
	for (int j = 0; j<d; j++)
	{

		i >> n.next;
		n = *n.next;
	}
	*ultim = n;
	delete(&n);
	*/
	Nod vect[20];
	int d, dim;
	///dim
	i>>d;
	///dim max
	i>>dim;
	for(int j=0;j<d;j++)
        i>>vect[j];
	this->dim_max = dim;
	prim->set_info(vect[0].get_info());
	prim->set_next(&vect[1]);
	ultim->set_info(vect[d-1].get_info());
	ultim->set_next(NULL);
	int j;

         Nod n;
        n=*prim;

        for( j=1; j<d-1; j++)
        {
            n.set_info(vect[j].get_info());
            n.set_next(&vect[j+1]);

        }
        dim=d;
}

ostream  &operator<<(ostream &i, Coada &c)
{

	c.afisare(i);
	return i;
}

void Coada::afisare(ostream &i)
{

	i << dim_max;
	i<<" ";
	i<<dim;
	i<<" ";
	i << prim->get_info();
	i<<" ";
	Nod n = *prim;
	for (int j = 0; j<dim_max; j++)
	{
		n = *n.get_next();
		i << n.get_info();
		i<<" ";
	}

}

void Coada::push(Nod* n)
{
	///dimensiunea trebuie sa se modifice
	if ( dim + 1 <= dim_max )
	{
	    if(prim==NULL)
          {
              prim=n;
              ultim=n;
              dim++;
          }

        else
        {
            ultim->set_next(n);
            ultim=n;
              dim++;
        }

	}
	else
	cout<<"Nu mai avem spatiu";
}

void Coada::pop()
{
	if(dim == 0 )
        cout<<"Coada este goala";
    else
    {
        Nod *p = prim->next;
        delete(&prim);
        this->prim = p;
        dim--;
    }

}

Coada& Coada::operator=(const Coada &c)
{
	dim_max = c.dim_max;
	this->set_prim( c.prim);
	ultim = c.ultim;
	Nod n = *this->prim;
	Nod m = *c.prim;
	for (int i = 0; i<dim - 1; i++)
	{
		n.set_next(  m.get_next());
		n = *n.next;
		m = *m.next;

	}

	return *this;
}


Coada& Coada::  operator-(Coada &c)
{
	Nod n = *this->prim, m = *c.prim;
	while (n == m)
	{

		n = *n.next;
		m = *m.next;
		this->pop();
		c.pop();

	}
	return *this;

}
Coada& Coada :: operator+(const Coada & c)
{
	Nod n = *c.prim;
	Coada e = *this;
	while (n.next !=NULL)
	{
		e.push(&n);
		n = *n.next;
	}
	return e;
}
///------------------------------------------------------------------------------

class DEQUE : public Coada
{
public:

    DEQUE():Coada(){ }
    DEQUE(Nod vect[20], int d, int dim):Coada(vect, d, dim){ }
    DEQUE(const DEQUE &c):Coada(c){ }
    virtual ~DEQUE()
    {
        delete[]this;
    }
    friend istream &operator>>(istream &i, DEQUE &c);
    friend ostream &operator<<(ostream &i, DEQUE &c);
    void citire(istream &i);
    void afisare(ostream &i);
    void pop(int opt);
    void push(int opt, Nod p);
    DEQUE& operator=(const DEQUE &d );
    DEQUE& operator-(DEQUE &c);
    DEQUE& operator+(const DEQUE & c);
};

void DEQUE:: pop(int opt)
{
///0-pop normal (front)
///1-rear pop
    if(opt)
    {
         Nod n=*this->prim;
        this->ultim=NULL;
        for(int i=0; i<dim-1;i++)
        {
            n=*n.get_next();

        }
        n.set_next(NULL);
        delete(this->ultim);
        this->ultim=&n;

    }
    else Coada::pop();

}
void DEQUE ::push(int opt, Nod p)
{
    ///0-stg, 1-dr
    if(opt==0)
    {
         Nod n=*this->prim;

        this->prim=&p;
        p.set_next(&n);
    }
    else
        Coada::push(&p);
}


DEQUE& DEQUE::operator-(DEQUE &c)
{
Nod n = *this->prim, m = *c.prim;
	while (n == m)
	{

		n = *n.get_next();
		m = *m.get_next();
		this->pop(0);
		c.pop(0);

	}
	return *this;
}
DEQUE& DEQUE::operator+(const DEQUE & c)
{
Nod n = *c.prim;
	DEQUE e = *this;
	while (n.get_next() !=NULL)
	{
		e.push(1, n);
		n = *n.get_next();
	}
	return e;

}

DEQUE& DEQUE:: operator=(const DEQUE &d )
{

    *this=d;

return *this;
}

void DEQUE::citire(istream &i)
{
    /** Nod n;
    i>>dim_max;
    i>>dim;
    i>>n;
    this->prim= &n;
    for(int j=0; j<dim;j++)
    {

        i>>n.next;
        n=*n.next;
    }
    *ultim=n;*/

Nod vect[20];
	int d, dim;
	///dim
	i>>d;
	///dim max
	i>>dim;
	for(int j=0;j<d;j++)
        i>>vect[j];
	this->dim_max = dim;
	prim->set_info(vect[0].get_info());
	prim->set_next(&vect[1]);
	ultim->set_info(vect[d-1].get_info());
	ultim->set_next(NULL);
	int j;

         Nod n;
        n=*prim;

        for( j=1; j<d-1; j++)
        {
            n.set_info(vect[j].get_info());
            n.set_next(&vect[j+1]);

        }
        dim=d;
}

void DEQUE:: afisare(ostream &i)
{

    i<<dim_max;
    i<<dim;
    i<<prim->get_info();
    Nod n=*prim;
    for(int j=0; j<dim;j++)
    {
        i<<n.get_next()->get_info();
        n=*n.get_next();
    }

}

istream &operator>>(istream &i, DEQUE &c)
{
    c.citire(i);
    return i;
}
ostream &operator<<(ostream &i, DEQUE &c)
{

    c.afisare(i);
    return i;
}
///------------------------------------------------------------------------------------


class NodPrioritate :public Nod
{
    NodPrioritate *next;
    int priorit;
public:

    NodPrioritate();
    NodPrioritate(char x, NodPrioritate *n, int p);
    NodPrioritate(const NodPrioritate &n);
    virtual ~NodPrioritate() { }
    friend istream &operator>>(istream &i, NodPrioritate &n);
    friend ostream &operator<<(ostream &i, NodPrioritate &n);
    NodPrioritate& operator=(const NodPrioritate &n );
    bool operator==(const NodPrioritate &n);
    void citire(istream &i);
    void afisare(ostream &i);
    void set_info(char a);
    void set_next(NodPrioritate *m);
    char get_info();
    NodPrioritate* get_next();
    friend class Priority_queue;
};



NodPrioritate::NodPrioritate():Nod()
    {
        this->priorit = 0;
    }

NodPrioritate::NodPrioritate(char x, NodPrioritate *n, int p):Nod(x, n)
    {
        this->priorit=p;
    }
NodPrioritate:: NodPrioritate(const NodPrioritate &n):Nod(n)
    {
        priorit=n.priorit;
        ///Nod(n);
    }


void NodPrioritate::citire(istream &i)
{

    this->Nod::citire(i);
    i>>priorit;
}

void NodPrioritate::afisare(ostream &i)
{

    i<<this;
    i<<priorit;
}

istream &operator>>(istream &i, NodPrioritate &n)
{
    n.citire(i);
return i;

}
ostream &operator<<(ostream &i, NodPrioritate &n)
{
    n.afisare(i);

return i;

}

/**NodPrioritate& NodPrioritate:: operator=(const NodPrioritate &n )
{
    this->info=n.info;
    this->next=n.next;

}
*/

///----------------------------------------------metode set get NodPrioritate
void NodPrioritate::set_info(char a)
{
    info=a;
}
void NodPrioritate::set_next(NodPrioritate *m)
{
    next=m;
}
char NodPrioritate::get_info()
{
    return info;
}
NodPrioritate* NodPrioritate:: get_next()
{
    return next;
}


NodPrioritate& NodPrioritate:: operator=(const NodPrioritate &n )///const
{
    *this=n;
    this->priorit=n.priorit;
return *this;
}


bool NodPrioritate :: operator==(const NodPrioritate &n)///const
{
    if(this->priorit == n.priorit && *this==n  )
        return 1;
    else
        return 0;


}

///------------------------------------------------------------------------


class Priority_queue : public Coada
{
protected:
    NodPrioritate *prim;
    NodPrioritate *ultim;
public:


    Priority_queue(); ///constructor fara parametrii
    Priority_queue(NodPrioritate vect[20], int d, int dim); ///constructor cu parametrii
    Priority_queue(const Priority_queue &c); ///copy constructor
    virtual ~Priority_queue()
    {
        delete[]this;
    }

    friend istream &operator>>(istream &i, Priority_queue &c);
    friend ostream &operator<<(ostream &i, Priority_queue &c);
    void citire(istream &i);
    void afisare(ostream &i);
    void pop();
    void push( NodPrioritate n);
    Priority_queue& operator-(Priority_queue &c);
    Priority_queue& operator+(const Priority_queue & c);
};

Priority_queue:: Priority_queue() ///constructor fara parametri
    {
        prim=0;
        ultim=0;
        dim_max=0;
        //this->prim->priorit=0;
        //this->ultim->priorit=0;
    }

   Priority_queue:: Priority_queue(NodPrioritate vect[20], int d, int dim) ///constructor cu parametri
    {int i;
         NodPrioritate n;
        this->prim=&vect[0];
        n=*prim;
        for(i=1; i<d; i++)
        {
            n.set_next(&vect[i]);
            n=*n.get_next();


        }

        ultim=&vect[i];
        dim_max=d;

    }
   Priority_queue:: Priority_queue(const Priority_queue &c)///copy constructor
    {

         NodPrioritate n, m;
        m=*c.prim;
        prim=c.prim;
        n=*prim;
        while( m.get_next())
            {
                n.set_next(m.get_next());
                n=*n.get_next();
                m=*m.get_next();
            }

///ultim=c.ultim;
        dim_max=c.dim_max;

    }

Priority_queue& Priority_queue::operator-(Priority_queue &c)
{
//    return this-c;

}
Priority_queue& Priority_queue::operator+(const Priority_queue & c)
{

   // return this+c;
}

void Priority_queue:: pop()
{
     NodPrioritate n=*prim;
    int maxim=n.priorit;
    while(n.next!=NULL)
    {
        n=*n.next;
        if(maxim<n.priorit)
            maxim=n.priorit;
    }
    while(n.next!=NULL)
    {
        n=*n.next;
        if(n.next->priorit==maxim)
        {
            n.next=n.next->next;

        }
    }

}
void Priority_queue::  push(NodPrioritate n)
{

    this->ultim->set_next(&n);
    this->ultim=&n;

}

void Priority_queue::citire(istream &i)
{
     NodPrioritate n;
    i>>dim_max;
    i>>dim;
    i>>n;
    for(int j=0; j<dim;j++)
    {
        this->prim= &n;
        i>>*n.next;
        n=*n.next;
    }
    *ultim=n;

}



void Priority_queue:: afisare(ostream &i)
{

    i<<dim_max;
    i<<prim->get_info();
    NodPrioritate n=*prim;
    for(int j=0; j<dim;j++)
    {
        i<<n.get_next()->get_info();
        n=*n.next;
    }

}

istream &operator>>(istream &i, Priority_queue &c)
{

    c.citire(i);
    return i;
}
ostream &operator<<(ostream &i, Priority_queue &c)
{

    c.afisare(i);
    return i;
}




///------------------------------------------------------------------------
int main()
{
	Coada C;
	Nod a, b, c;
	cin >> a >> b >> c;
	cout << a << b << c;
	//C.push(&a);
	//C.push(&b);
	///C.afisare(cout);
	cin>>C;
	cout<<C;
}

