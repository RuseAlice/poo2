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

1. toate clase vor conține obligatoriu constructori de inițializare, parametrizati și de
copiere, destructor, iar operatorii >>,<<,= să fie supraincarcati.
2. ilustrarea conceptelor de moștenire și functii virtuale (pure – unde se considera
mai natural)
3. citirea informațiilor complete a n obiecte, memorarea și afisarea acestora
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
- DEQUE:Coada - cu operatiile de adaugare și stergere modificate corespunzator.
- PriorityQueue:Coada - cu operatiile de adaugare și stergere modificate
corespunzator.

Clasele derivate trebuie sa contina cel puțin constructori parametrizati prin
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
    char info;

    Nod *next;
public:

    Nod(char i=0,   Nod *urm = NULL)
    {
        info=i;
        next= urm;

    }
    Nod(const Nod &n)
    {
        info=n.info;
        next=n.next;
    }

    ~Nod()
    {

    }

    friend void set_info(char a);
    friend void set_next(Nod *n);
    friend char get_info();
    friend Nod get_next();
    friend istream &operator>>(istream &i, Nod &n);
    friend ostream &operator<<(ostream &i, Nod &n);
    virtual void citire(istream &i, Nod &n);
    virtual void afisare(ostream &i, Nod &n);
    virtual bool  operator==(const Nod &n);
    Nod& operator=(const Nod &n );
///operator =
    friend class Coada;
};

class NodPrioritate :public Nod
{

    int priorit;
public:

    NodPrioritate():Nod()
    {

        this->priorit = 0;
    }

    NodPrioritate(char x, NodPrioritate *n, int p):Nod(x, n)
    {

        this->priorit=p;
    }
    NodPrioritate(const NodPrioritate &n):Nod(n)
    {

        priorit=n.priorit;
        ///Nod(n);
    }

    virtual ~NodPrioritate() { }

    friend istream &operator>>(istream &i, NodPrioritate &n);
    friend ostream &operator<<(ostream &i, NodPrioritate &n);
    NodPrioritate& operator=(const NodPrioritate &n );
    bool operator==(const NodPrioritate &n);
    void citire(istream &i, NodPrioritate &n);
    void afisare(ostream &i, NodPrioritate &n);
    friend class Priority_queue;
};

void Nod::afisare(ostream &i, Nod &n)
{
    i<<n.info;
    i<<n.next;
}

void Nod::citire(istream &i, Nod &n)
{

    i>>n.info;
    i>>*n.next;
}



ostream  &operator<<(ostream &i, Nod &n)
{

    n.afisare(i, n);
}


istream  &operator>>(istream &i, Nod &n) ///--------------------
{
    n.citire(i, n);


}

bool Nod:: operator==(const Nod &n)
{   if(this->info!=n.info)
   // if( this->get_info()!=n.get_info() )
        return 0;
    else
        return 1;
}



void NodPrioritate::citire(istream &i, NodPrioritate &n)
{

    i>>n;
    i>>n.priorit;
}

void NodPrioritate::afisare(ostream &i, NodPrioritate &n)
{

    i<<n;
    i<<n.priorit;
}

istream &operator>>(istream &i, NodPrioritate &n)
{
    n.citire(i, n);


}
ostream &operator<<(ostream &i, NodPrioritate &n)
{
    n.afisare(i, n);



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
class Coada
{protected:

    Nod *prim;
    Nod *ultim;
    int dim_max;
public:

    Coada()  ///constructor fara parametrii
    {
        prim=0;
        ultim=0;
        dim_max=0;

    }

    Coada(Nod vect[20], int d)  ///constructor cu parametrii
    {
        int i;

         Nod n;
        prim= &vect[0];
        n=*prim;
        for( i=1; i<sizeof(vect)-1; i++)
        {
            n.next=&vect[i];
            n=*n.next;
        }

        ultim=&vect[i];
        dim_max=d;
    }

    Coada(const Coada &c) ///copy constructor
    {

         Nod n, m;
        m=*c.prim;
        prim=c.prim;
        n=*prim;
        while (m.next)
            {
                n.next=m.next;
                n=*n.next;
                m=*m.next; ///----------------------------------
            }

///ultim=c.ultim;
        dim_max=c.dim_max;

    }
    ~Coada()
    {
        delete[]this;
    }

    friend istream &operator>>(istream &i, Coada &c);
    friend ostream &operator<<(ostream &i, Coada &c);
    virtual void citire(istream &i, Coada &c);
    virtual void afisare(ostream &i, Coada &c);
    virtual void push(char x)
    {
         Nod n;
        n.info=x;
        n.next=0;
        *this->ultim->next=n;
        delete(&n);
    }

    virtual void pop()
    {
        Nod p=*prim;
        this->prim=p.next;
        delete(&p);
    }

    virtual Coada& operator=(const Coada &c );
    virtual Coada& operator-(Coada &c);
    virtual Coada& operator+(const Coada & c);
///push
///pop
///=
///-



};





class DEQUE : public Coada
{
public:

    DEQUE()
    {
        ///constructor fara parametrii
        Coada();

    }


    DEQUE(Nod vect[20], int d):Coada(vect, d)
    {
        ///constructor cu parametrii
        ///Coada.Coada(Nod vect[20], int d);

    }



    DEQUE(const DEQUE &c):Coada(c)
    {


    }

    ~DEQUE()
    {
        delete[]this;
    }
    friend istream &operator>>(istream &i, DEQUE &c);
    friend ostream &operator<<(ostream &i, DEQUE &c);
    void citire(istream &i, DEQUE &c);
    void afisare(ostream &i, DEQUE &c);
    void pop(int opt);
    void push(int opt, char litera);
    DEQUE& operator=(const DEQUE &d );
    DEQUE& operator-(DEQUE &c);
    DEQUE& operator+(const DEQUE & c);
};

class Priority_queue : public Coada
{
public:


    Priority_queue() ///constructor fara parametrii
    {
        prim=0;
        ultim=0;
        dim_max=0;
        //this->prim->priorit=0;
        //this->ultim->priorit=0;
    }

    Priority_queue(NodPrioritate vect[20], int d) ///constructor cu parametrii
    {int i;
         NodPrioritate n;
        this->prim=&vect[0];
        n=*prim;
        for(i=1; i<sizeof(vect)-1; i++)
        {
            n.get_next()=vect[i];
            n=n.get_next();


        }

        ultim=vect[i];
        dim_max=d;

    }
    Priority_queue(const Priority_queue &c)///copy constructor
    {

         NodPrioritate n, m;
        m=c.prim;
        prim=c.prim;
        n=prim;
        for(while m.next)
            {
                n.next=m.next;
                n=n.next;
                m=m.next;
            }

///ultim=c.ultim;
        dim_max=c.dim_max;

    }

    ~Priority_queue()
    {
        delete[]this;
    }

    friend istream &operator>>(istream &i, Priority_queue &c);
    friend ostream &operator<<(ostream &i, Priority_queue &c);
    void citire(istream &i, Priority_queue &c);
    void afisare(ostream &i, Priority_queue &c);
    Priority_queue& operator-(Priority_queue &c);
    Priority_queue& operator+(const Priority_queue & c);
};


istream  &operator>>(istream &i, Coada &c)
{
   c.citire(i, c);

}
void Coada::citire(istream &i, Coada &c)
{
    new Nod n;
    i>>dim_max;
    i>>n;
    for(int j=0; j<dim_max-2;j++)
    {
        this->prim= n;
        i>>n.next;
        n=n.next;
    }
    ultim=n;
    delete(*n);
}

ostream  &operator<<(ostream &i, Coada &c)
{

    c.afisare(i, c);
}
void Coada:: afisare(ostream &i, Coada &c)
{

    i<<dim_max;
    i<<prim;
    Nod n=prim;
    for(int j=0; j<dim_max;j++)
    {
        i<<n.next;
        &n=n.next;
    }

}


Coada& Coada::  operator-(Coada &c)
{
     Nod n=this->prim, m=c.prim;
    while(n==m)
    {

        n=n.next;
        m=m.next;
        this->pop();
        c.pop();
        delete(&n);
        delete(&m);
    }
    return this;

}
Coada& Coada :: operator+(const Coada & c)
{
     Nod n=c.prim;
     Coada e=this;
    while(n!=null)
    {
        e.push(n);
        n=n.next;
    }
    return e;
}

DEQUE& DEQUE::operator-(DEQUE &c)
{
    return this-c;
}
DEQUE& DEQUE::operator+(const DEQUE & c)
{

    return this+c;
}

Priority_queue& Priority_queue::operator-(Priority_queue &c)
{
    return this-c;

}
Priority_queue& Priority_queue::operator+(const Priority_queue & c)
{

    return this+c;
}

void Priority_queue:: pop()
{
     NodPrioritate n=this->prim;
    int maxim=n.priorit;
    while(n.next!=null)
    {
        n=n.next;
        if(maxim<n.priorit)
            maxim=n.priorit;
    }
    while(n.next!=null)
    {
        n=n.next;
        if(n.next.priorit==maxim)
        {
            n.next=n.next.next;

        }
    }
    delete(n);
}
void Priority_queue::  push(char litera, int p)
{
     NodPrioritate n(litera, p);
    this->ultim.next=n;
    this->ultim=n;
    delete(n);
}

void Nod::set_info(char a)
{
    this->info=a;
}
void Nod::set_next(Nod *n)
{
    this->next=n;
}
char Nod::get_info()
{
    return this->info;
}
Nod* Nod::get_next()
{
    return this->next
}

Nod& Nod:: operator=(const Nod &n )
{
    this->info=n.info;
    this->next=n.next;

}

Coada& Coada::operator=(const Coada &c )
{
    this->dim_max=c.dim_max;
    this->prim-c.prim;
    this->ultim=c.ultim;
    new Nod n=this->prim;
    new Nod m=c.prim;
    for(int i=0; i<dim_max-1; i++)
    {
        n.next=m.next;
        n=n.next;
        m=m.next;

    }

    return *this;
}


void DEQUE:: pop(int opt)
{
///0-pop normal (front)
///1-rear pop
    if(opt)
    {
         Nod n=*this->prim;
        this->ultim=null;
        for(int i=0; i<dim_max-1)
        {
            n=n.next;

        }
        n.next=null;
        delete(this->ultim);
        this->ultim=n;
        delete(n);
    }
    else Coada::pop();

}
void DEQUE ::push(int opt, char litera)
{
    ///0-stg, 1-dr
    if(opt==0)
    {
        new Nod n=this->prim;
        this->prim=new Nod m(litera, n);
        delete(n);
        delete(m);
    }
    else
        Coada::push(litera);
}
DEQUE& DEQUE:: operator=(const DEQUE &d )
{

    this=d;


}

istream DEQUE ::&operator>>(istream &i, DEQUE &c)
{
    i>>c;

}
ostream DEQUE::&operator<<(ostream &i, DEQUE &c)
{

    i<<c;

}
istream Priority_queue::&operator>>(istream &i, Priority_queue &c)
{

    i>>c;

}
ostream Priority_queue::&operator<<(ostream &i, Priority_queue &c)
{

    i<<c;

}





int main()
{ Coada[10] ;
DEQUE[10];
Priority_queue[10];
int n=2;

///citire
for(int i=0;i<n;i++)
{
    f>>Coada[i];
}
for(int i=0;i<n;i++)
{
    f>>DEQUE[i];
}
for(int i=0;i<n;i++)
{
    f>>Priority_queue[i];

}
///functii

Coada[1].pop();
DEQUE[0].pop)();
DEQUE[0].push(f);
Priority_queue.pop();
Priority_queue.pop();



///afisare
for(int i=0;i<n;i++)
{
    cout<<Coada[i];
    cout<<"\n";
}
for(int i=0;i<n;i++)
{
    cout<<DEQUE[i];
    cout<<"\n";
}
for(int i=0;i<n;i++)
{
    cout<<Priority_queue[i];
    cout<<"\n";

}

    return 0;
}
