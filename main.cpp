#include <iostream>
//#include <utility>

using namespace std;

template <typename Data_type>
class Node
{
private:
    Data_type data;
    Node *next;
    Node *previous;
public:
    explicit Node(const Data_type &value )
        :data(value),next(nullptr),previous(nullptr){};


    virtual ~Node()= default;//DO UZUPELNIENIA!!!!!!

        [[nodiscard]] Data_type getData ( )
            const { return data; }
        [[nodiscard]] Node *getNext ( )
            const { return next; }
        [[nodiscard]] Node *getPrevious ( )
            const { return previous; }
        void setPrevious ( Node *prevInp )
            { Node::previous = prevInp; }
        void setData ( Data_type dataInp )
            { Node::data = dataInp; }
        void setNext ( Node *node )
            { Node::next = node; }

};

template <typename Data_type>
class LinkedList
{
private:
    Node<Data_type> *last;
    Node<Data_type> *first;
    unsigned int size;

    //prywatne metody
    void addObject(const  Data_type &value, bool isFront);//jest utworzony interfejs dla nich bez zmiennej boolean
    void deleteObject(bool inFront) ;
    void incrementSize(){
        size++;
    }
    void decrementSize(){
        size--;
    }

public:

    LinkedList()
        :last(nullptr),first(nullptr),size(0){};//pusta
    virtual ~LinkedList ( ) =default;
    bool isEmpty(){
        if(size==0)return true;
        return false;
    }

    void setLast ( Node<Data_type> *lastInput )
        { LinkedList::last = lastInput; }
    void setFirst ( Node<Data_type> *firstInput )
        { LinkedList::first = firstInput; }
    void setSize ( const unsigned int sizeInput)
        { LinkedList::size = sizeInput;}

    [[nodiscard]] Node<Data_type> *getLast ( )
        const {return last;}
    [[nodiscard]] Node<Data_type> *getFirst ( )
        const {return first;}
    [[nodiscard]] unsigned int getSize ( )
        const { return size; }


    void addObjectFront(const Data_type &value);
    void addObjectBack(const Data_type &value);
    void addSortedObject( const Data_type &value, bool growing);
    //dla true porzadek rosnacy , false malejacy

    void deleteObjectFront() ;
    void deleteObjectBack() ;
    void deleteAllObject();

    Data_type getObject( unsigned int index);

    Node<Data_type>* getPointerObject( unsigned int index);

    void editObject( unsigned int index,const  Data_type &value);

    Node<Data_type>* searchObject(const Data_type &value);

    bool searchToDelete(const Data_type &value);

    void showList();

    void showList(unsigned int index);

    void showList(unsigned int start , unsigned int end);

    //Pracuje nad nimi
    //bool switchObject(unsigned int firstIndex , unsigned int secondIndex);//flag true == switch corectly
    //Pracuje nad nimi
    //void sortList(const bool descending);



};

template<typename Data_type>
void LinkedList<Data_type>::addObject( const  Data_type &value,const bool isFront )
{
    Node<Data_type>* addedNode = new Node(value);
    if(isEmpty()){//pusta, dodajemy 1 element
        setFirst(addedNode);
        setLast(addedNode);
        addedNode->setPrevious(nullptr);
        addedNode->setNext(nullptr);
        incrementSize();
        return;
    }
    else {
        Node<Data_type> *temp = nullptr;
        if(isFront) {
            temp = getFirst();
            setFirst(addedNode);
            getFirst()->setNext(temp);
            getFirst()->setPrevious(getLast());
            getLast()->setNext(getFirst());
            temp->setPrevious(getFirst());
        }
        else
        {
            temp = getLast();
            setLast(addedNode);
            getLast()->setNext(getFirst());
            getLast()->setPrevious(temp);
            getFirst()->setPrevious(getLast());
            temp->setNext(getLast());
        }
        incrementSize();
    }
}
template<typename Data_type>
void LinkedList<Data_type>::addObjectFront ( const Data_type &value)
{
    LinkedList<Data_type>::addObject(value, true);
}
template<typename Data_type>
void LinkedList<Data_type>::addObjectBack ( const Data_type &value)
{
    LinkedList<Data_type>::addObject(value, false);
}


template<typename Data_type>
void LinkedList<Data_type>::deleteObject (const bool inFront ) {
    if(isEmpty()){
        if(inFront) {
            throw std::out_of_range("\n'deleteObjectFront'\nProba skasowania obiektu z pustej listy!!!\n");
        }
        else
        {
            throw std::out_of_range("\n'deleteObjectBack'\nProba skasowania obiektu z pustej listy!!!\n");
        }
    }
    if(getFirst() == getLast()) // lista 1 elementowa
    {
        delete getFirst();
        setFirst(nullptr);
        setLast(nullptr);
        decrementSize();
        return;
    }else {
        Node<Data_type> *temp = nullptr;
        if ( inFront ) {
            temp = getFirst();
            setFirst(temp->getNext());
            getFirst()->setPrevious(getLast());
            getLast()->setNext(getFirst());
        } else {
            temp = getLast();
            setLast(temp->getPrevious());
            getLast()->setNext(getFirst());
            getFirst()->setPrevious(getLast());
        }
        delete temp;
        decrementSize();
    }
}
template<typename Data_type>
void LinkedList<Data_type>::deleteObjectFront(){
    LinkedList<Data_type>::deleteObject(true);
}
template<typename Data_type>
void LinkedList<Data_type>::deleteObjectBack(){// NIE DZIALA POPRAWNIE !!!!!!!!!!!
    LinkedList<Data_type>::deleteObject(false);
}
template<typename Data_type>
void LinkedList<Data_type>::deleteAllObject()
{
    while (!isEmpty()) {
        deleteObjectBack();
    }
}

template<typename Data_type>
Data_type LinkedList<Data_type>::getObject( unsigned int indexInput) {
        if(isEmpty()){throw std::out_of_range("\n'getObject'\n!!! Lista jest Pusta !!!");}
        if( indexInput > getSize()-1 ) { throw std::out_of_range("\n'getObject'\n!!! Index wiekszy od wielkosci listy !!!"); }
        else
        {
            Node<Data_type>  *temp = getFirst();
            for(unsigned int i = 0 ; i < indexInput ; i++)
            {
                temp=temp->getNext();
            }
            return temp->getData();
        }
    }

template<typename Data_type>
Node<Data_type>* LinkedList<Data_type>::getPointerObject( unsigned int indexInput) {
    if(isEmpty()){throw std::out_of_range("\n'getPointerObject'\n!!! Lista jest Pusta !!!");}
    if( indexInput > getSize()-1 ) { throw std::out_of_range("\n'getPointerObject'\n!!! Index wiekszy od wielkosci listy !!!"); }
    else
    {
        Node<Data_type>  *temp = getFirst();
        for(unsigned int i = 0 ; i < indexInput ; i++)
        {
            temp=temp->getNext();
        }
        return temp;
    }
}

template<typename Data_type>
void LinkedList<Data_type>::editObject ( unsigned int indexInput , const  Data_type &value ) {
    if(isEmpty()){throw std::out_of_range("\n'editObject'\n!!! Lista jest Pusta !!!");}
    if( indexInput > getSize()-1 ) { throw std::out_of_range("\n'editObject'\n!!! Index wiekszy od wielkosci listy !!!"); }
    else
    {
        Node<Data_type>  *temp = getFirst();
        for(unsigned int i = 0 ; i < indexInput ; i++)
        {
            temp=temp->getNext();
        }
        temp->setData(value);
    }
}

template<typename Data_type>
Node<Data_type>* LinkedList<Data_type>::searchObject (const Data_type &value)
{
    if(isEmpty()){
        cout<<"\n\n'searchObject'\n!!! Lista jest Pusta !!!";
        return nullptr;
    }
    else
    {
        Node<Data_type>  *temp = getFirst();
        bool found = false;
        for(unsigned int i = 0 ; i < getSize() ; i++) {
            if ( temp->getData() == value ) {
                found = true;
                break;
            }
            temp=temp->getNext();
        }
        if(found) {
            return temp;
        }
        else {
            cout<<"\n\nWARNING\t'searchObject' nie znaleziono obiektu wg podanego wzoru:'"<<value<<"'\n\n";
            return nullptr;
        }
    }
}
//----------------------------
template<typename Data_type>
bool LinkedList<Data_type>::searchToDelete(const Data_type &value) {
    Node<Data_type> *term = searchObject(value);
    if(term == nullptr )
    {
        cout<<"\n\nWARNING\t'searchToDelete'\n nie znaleziono obiektu wg podanego wzoru:'"<<value<<"'\n\n";
        return false;
    }
    else if(getFirst()->getData() == value) {
        try {
            deleteObjectFront();
            return true;
        }
        catch ( std::exception &error ) {
            throw std::invalid_argument("\n'searchToDelete' during used 'deleteObjectFront'\n");
        }
    } //sprawdzamy 1 i ostatni object
    else if(getLast()->getData() == value){

        try{
            deleteObjectBack();
            return true;
        }
        catch(std::exception &error)
        {
            throw std::invalid_argument("\n'searchToDelete' during used 'deleteObjectBack'\n");
        }
    }
    else
    {
        Node<Data_type> *leftObj = term->getPrevious();
        Node<Data_type> *rightObj = term->getNext();
        leftObj->setNext(rightObj);
        rightObj->setPrevious(leftObj);
        delete term;
        return true;
    }
}
//----------------------------

//mam tutaj mozliwe do dodwania funckje ale narazie niepotrzebne !!!
/*
template <typename Data_type>
bool  LinkedList<Data_type>::switchObject(unsigned int firstIndex , unsigned int secondIndex)
{
    if(firstIndex > getSize() || secondIndex > getSize())
    {
        throw std::out_of_range("\n'switchObject'\tPodano indeks wiekszy niz wiekosc listy!!!\n");
    }
    if(getSize()<=1)
    {
        throw std::out_of_range("\n'switchObject\tNie mozna wykonac funkcji zamiany dla listy mniejszej od 2 !!! \n");
    }
    if(firstIndex == secondIndex)
    {
        throw std::invalid_argument("\n'switchObject\tPodano te same indeksy, brak mozliwosci wykonania funckcji !!! \n");
    }

    Node<Data_type> *left = getPointerObject(firstIndex);
    Node<Data_type> *right = getPointerObject(secondIndex);

    //kopiowanie danych lewego pointera
    Node<Data_type> *leftNext = left->getNext();
    Node<Data_type> *leftPrev = left->getPrevious();
    Data_type tempLeftData = left->getData();

    left->setData(right->getData());
    left->setNext(right->getNext());
    left->setPrevious(right->getPrevious());

    right->setData(tempLeftData);
    right->setNext(leftNext);
    right->setPrevious(leftPrev);


    return true;
}

template <typename Data_type>
void LinkedList<Data_type>::sortList(const bool descending)//true == malejaco , false == rosnaco
{
    for ( unsigned int i = 0 ; i < getSize()-1 ; i++ ) {
        Data_type tempLeft = getObject(i);
        for(unsigned int j = i+1 ; j < getSize() ; j++)
        {
            Data_type tempRight = getObject(j);
            cout<<"\ni = "<<i <<" j = "<<j<<"  " <<tempLeft<<"  "<<tempRight;
            if(descending)
            {
                if(tempLeft<tempRight)
                {
                    switchObject(i,j);
                }
            }
            else
            {
                if(tempLeft>tempRight)
                {
                    switchObject(i,j);
                }
            }
        }
    }
}
*/
//mam tutaj mozliwe do dodwania funckje ale narazie niepotrzebne !!!

template<typename Data_type>
void LinkedList<Data_type>::addSortedObject ( const Data_type &value , bool growing )
{
    if(growing) {
        if ( isEmpty() || value <= getFirst()->getData()) {
            addObjectFront(value);
            return;
        }
        if ( value >= getLast()->getData()) {
            addObjectBack(value);
            return;
        }
        Node<Data_type> *Added = new Node(value);
        Node<Data_type> *current = getFirst();
        while(Added->getData() >= current->getData() )
        {
            current = current->getNext();
        }//kiedy sie wkonczy miejsce added jest przed current
        Node<Data_type> *leftToCurrent = current->getPrevious();
        leftToCurrent->setNext(Added);
        current->setPrevious(Added);
        Added->setNext(current);
        Added->setPrevious(leftToCurrent);
        incrementSize();
    }
    else
    {
        if ( isEmpty() || value <= getLast()->getData()) {
            addObjectBack(value);
            return;
        }
        if ( value >= getLast()->getData()) {
            addObjectFront(value);
            return;
        }
        Node<Data_type> *Added = new Node(value);

        Node<Data_type> *current = getLast();
        while(Added->getData() >= current->getData() )
        {
            current = current->getPrevious();
        }//kiedy sie wkonczy miejsce added jest za current
        Node<Data_type> *rightToCurrent = current->getNext();
        rightToCurrent->setPrevious(Added);
        current->setNext(Added);
        Added->setNext(rightToCurrent);
        Added->setPrevious(current);
        incrementSize();
    }
}

template<typename Data_type>
void LinkedList<Data_type>::showList ( ) {
    if(isEmpty()){
        throw std::out_of_range("\n\n'showList()'\n!!! Lista jest Pusta !!!");

    }
    Node<Data_type> *show = getFirst();
    for(int i = 0 ; i < getSize() ; i++)
    {
        cout<<"\nindex = "<<i<<" | data = "<<show->getData()<<" |  ptr = "<<show;
        show = show->getNext();
    }
}

template<typename Data_type>
void LinkedList<Data_type>::showList ( unsigned int index ) {
    if(isEmpty()){
        throw std::out_of_range("\n\n'showList(uint index)'\n!!! Lista jest Pusta !!!");

    }
    if( index > getSize()-1 ) {
        throw std::out_of_range("\n'showList(uint index)'\n!!! Index wiekszy od wielkosci listy !!!");
    }
    cout<< "\ndata = " << getObject(index) << " |  ptr = " << getPointerObject(index);
}



template<typename Data_type>
void LinkedList<Data_type>::showList ( unsigned int start, unsigned int end )
{
    if(isEmpty()){
        throw std::out_of_range("\n\n'showList(uint start , uint end)'\n!!! Lista jest Pusta !!!");

    }
    if(start>getSize()-1 || end>getSize()-1 )
    {
        throw std::out_of_range("\n'showList(uint start, uint end )'\n!!! Start/End  wiekszy od wielkosci listy !!!");
    }
    Node<Data_type> *show = getPointerObject(start);
    for(unsigned int i = start ; i < end ; i++)
    {
        cout<<"\nindex = "<<i<<" | data = "<<show->getData()<<" |  ptr = "<<show;
        show = show->getNext();
    }
}






/*struct Obj
{
    unsigned int wiek;
    std::string  imie;
    Obj(): wiek(0), imie("none"){};
    Obj(const unsigned int age): wiek(age), imie("none"){};
    Obj(std::string  name): wiek(0), imie(std::move(name)){};
    Obj(const unsigned int age,std::string  name): wiek(age), imie(std::move(name)){};

};
*/
void start()
{
    cout<<"\nPress enter to Continue\n>";
    string inp;
    cin>>inp;
    inp.clear();
}


int main ( ) {

    while ( true ) {
        LinkedList<int> a;
        try {
             int j = 2;
            a.addSortedObject(++j,false);a.addSortedObject(++j,false);a.addSortedObject(++j,false);a.addSortedObject(++j,false);a.addSortedObject(++j,false);a.addSortedObject(++j,false);a.addSortedObject(++j,false);
            a.showList();
            cout<<"\n";
            a.showList(2,5);









            break;
        }
        catch ( std::exception &error ) {
            std::cerr << "\nWyjatek!!! \t" << error.what();
            //czyszczenie pamieci !!!
            for ( int i = a.getSize() ; i > 0 ; i-- ) {
                a.deleteObjectBack();
            }
            break;//jak zrobisz poswoj to zmien na continue!!!
        }
    }
    return EXIT_SUCCESS;
}

