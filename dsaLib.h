/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>
#include <functional>

using namespace std;

enum Balance_factor {
    EH,
    LH,
    RH
};
enum TraverseMode {
    LNR,
    NLR,
    LRN
};
struct package {
    void **param;
    int stop;
    int direction;
};
class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};
/*
template <class T>
class List {
public:
    virtual void    clean() = 0;
    virtual void    clone(void*) = 0;
    virtual bool    isEmpty() = 0;
    virtual size_t  getSize() = 0;
    virtual T&      at(int i) = 0;
    virtual T&      operator[](int i) = 0;

    virtual bool    find(T& a, int& idx) = 0;
    virtual T*      find(T& a) = 0;
    virtual T*      find(T& a, std::function<bool (T&, T&)> eqCmp) = 0;
    virtual int     insert(int i, T& a) = 0;
    virtual int     insert(int i, T&& a) = 0;
    virtual int     remove(int i) = 0;
    virtual int     remove(T& a, std::function<bool (T&, T&)> eqCmp) = 0;

    virtual int     push_back(T& a) = 0;
    virtual int     push_back(T&& a) = 0;
    virtual int     insertHead(T& a) = 0;
    virtual int     insertHead(T&& a) = 0;
    virtual int     removeHead() = 0;
    virtual int     removeLast() = 0;

    virtual void    traverse(std::function<void (T&)> op) = 0;
    virtual void    traverse(std::function<void (T&, void*)> op, void* pParam) = 0;

    virtual void    reverse() = 0;
};
*/
template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;

    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &a, void* next) : data(a), pNext(next) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &&a, void* next) : data(std::move(a)), pNext(next) {}
};

template <class T>
//class L1List : public List<T> {
class L1List {
    L1Item<T>   *_pHead;
    size_t      _size;
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List() {
        clean();
    }

    //void    clean();
    void    clean() {
        if(_pHead == NULL) {
            _size = 0;
            return;
        }
        else {
            L1Item<T>* pCurr = _pHead;
            _pHead = NULL;
            while(pCurr) {
                L1Item<T>* pTemp = pCurr;
                pCurr = pCurr->pNext;
                delete pTemp;
            }
            _size = 0;
            return;
        }
    }

    void decreaseSize() {
        _size--;
    }

    L1Item<T>* getpHead() {
        return _pHead;
    }

    L1Item<T>* getFirst() {
        if(_pHead == NULL) return NULL;
        else {
            L1Item<T>* p = _pHead;
            _pHead = _pHead->pNext;
            p->pNext = NULL;
            _size--;
            return p;
        }
    }

    void    clone(void*);
    bool    isEmpty() { return _pHead == NULL; }
    size_t  getSize() { return _size; }

    T&      at(int i);
    T&      operator[](int i);

    bool    find(T& a, int& idx);
    T*      find(T& a);
    T*      find(T& a, std::function<bool (T&, T&)> eqCmp);//bool (*eqCmp)(T&, T&));
    int     insert(int i, T& a);
    int     insert(int i, T&& a);
    int     remove(int i);
    int     remove(T& a, std::function<bool (T&, T&)> eqCmp);

    int     push_back(T& a);
    int     push_back(T&& a);
    int     insertHead(T& a);
    int     insertHead(T&& a);
    int     removeHead();
    int     removeLast();

    void    reverse();

    void    traverse(std::function<void (T&)> op) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    //void    traverse(void (*op)(T&, void*), void* pParam) {
    void    traverse(std::function<void (T&, void*)> op, void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(std::move(a));
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(std::move(a));
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
    L1Item<T>   *p = new L1Item<T>(std::move(a));
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

/// Trả về tham khảo tới vị trí data cần tìm
/// Trả về ngoại lệ nếu ko hợp lệ.
template <class T>
T& L1List<T>::at(int i) {
    int idx = 0;
    L1Item<T>* current = _pHead;
    if (i < _size && i >= 0){
        while (idx < i){
            current = (current) ? current->pNext : 0;
            idx++;
        };
    }
    else throw -1;
    return current->data;
}

/// Giống như at(i)
template <class T>
T& L1List<T>::operator[](int i) {
    return this->at(i);
}

/// Trả về list đã dược đảo ngược
template <class T>
L1Item<T>* Reverse(L1Item<T>* pHead, int N) {
    if(N == 1) return pHead;
    else {
        L1Item<T>* pCurr = pHead;
        L1Item<T>* pPrev = NULL;
        while(pCurr->pNext){
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        pPrev->pNext = NULL;
        pCurr->pNext = pHead;
        pHead = pCurr;
        pHead->pNext = Reverse(pHead->pNext, N - 1);
        return pHead;
    }
}
/// Gọi hàm Reverse.

template <class T>
L1Item<T>* _reverse(L1Item<T>* pHead) {
    if(pHead->pNext == NULL) {
        return pHead;
    }
    else {
        L1Item<T>* Temp = pHead->pNext;
        pHead->pNext = NULL;
        L1Item<T>* NewpHead = _reverse(Temp);
        Temp->pNext = pHead;
        return NewpHead;
    }
}

template <class T>
void L1List<T>::reverse() {
    //if(this->_pHead == NULL) return;
    //else {
    //    this->_pHead = Reverse(this->_pHead, this->_size);
    //}
    if(this->_pHead == NULL) {
        return;
    }
    else {
        this->_pHead = _reverse(this->_pHead);
    }
}

/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
#ifdef AVL_USE_HEIGHT
    int         _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1) {}
#else
    int         _bFactor;
    //AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(EH) {}
#endif
};

template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
    int _count;
public:
    AVLTree() : _pRoot(NULL),_count(0){};
    ~AVLTree() { destroy(_pRoot); }

    AVLNode<T>* _getpRoot() {
        return _pRoot;
    }
    void _setpRoot(AVLNode<T>* &pHead) {
        _pRoot = pHead;
    }
    void increaseCount() {
        _count++;
    }
    void _setCount(int NewCount) {
        _count = NewCount;
    }
    int _getCount() {
        return _count;
    }
    bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
    bool insert(T& key) { return insert(_pRoot, key); }
    bool remove(T& key) { return remove(_pRoot, key); }
    //void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    //void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    //void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }

    //void traverse(void (*op)(T&), void** param) { traverseNLR(_pRoot, op); }
    void traverse(void (*op)(AVLNode<T>* pR, void**, int&), void** param) {_traverse(_pRoot, op, param);}
    void traverseLNR(void (*op)(AVLNode<T>* pR, void**), void** param) {_traverseLNR(_pRoot, op, param);}

protected:
    void destroy(AVLNode<T>* &pR);
    bool find(AVLNode<T> *pR, T& key, T* &ret);
    bool insert(AVLNode<T>* &pR, T& a);
    bool remove(AVLNode<T>* &pR, T& a);
    //void traverseNLR(AVLNode<T> *pR, void (*op)(T&));
    //void traverseLNR(AVLNode<T> *pR, void (*op)(T&));
    //void traverseLRN(AVLNode<T> *pR, void (*op)(T&));
    /*
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&, stop,direction)){
        int stop = 0;
        int direction = 0;
        op(pR, stop, direction);
        if (!stop && direction == 1){
            traverseLRN(pR->pLeft,op)
        }
        if (!stop && direction = -1){
            traverseLRN(pR->pRight,op)
        }
    }
    */
    void _traverse(AVLNode<T>* pHead, void (*op)(AVLNode<T>* pR, void**, int& direction), void** param) {
        if(pHead == NULL) {
            return;
        }
        else {
            //if (mode == NLR){}
            int direction = 0;
            op(pHead, param, direction);
            int* stop = (int*)param[0];
            if(*stop == 0 && direction == -1 || *stop == 0 && direction == 0) {
                _traverse(pHead->_pLeft, op, param);
            }
            if(*stop == 0 && direction == 1 || *stop == 0 && direction == 0) {
                _traverse(pHead->_pRight, op, param);
            }
            else {
                return;
            }
        }
    }
    void _traverseLNR(AVLNode<T>* pHead, void (*op)(AVLNode<T>* pR, void**), void** param) {
        if(pHead == NULL) {
            return;
        }
        else {
            _traverseLNR(pHead->_pLeft, op, param);
            op(pHead, param);
            _traverseLNR(pHead->_pRight, op, param);
        }
    }

    void rotLeft(AVLNode<T>* &pR);
    void rotRight(AVLNode<T>* &pR);
    void rotLR(AVLNode<T>* &pR);
    void rotRL(AVLNode<T>* &pR);

    bool balanceLeft(AVLNode<T>* &pR);
    bool balanceRight(AVLNode<T>* &pR);
};

template <class T>
void AVLTree<T>::destroy(AVLNode<T>* &pR) {
    if(pR == NULL) {
        return;
    }
    else {
        destroy(pR->_pLeft);
        destroy(pR->_pRight);
        AVLNode<T>* p = pR;
        pR = NULL;
        delete p;
    }
}

template <class T>
AVLNode<T>* RotateLeft(AVLNode<T>* pHead) {
    AVLNode<T>* Temp = pHead->_pRight;
    pHead->_pRight = Temp->_pLeft;
    Temp->_pLeft = pHead;
    return Temp;
}

template <class T>
AVLNode<T>* RotateRight(AVLNode<T>* pHead) {
    AVLNode<T>* Temp = pHead->_pLeft;
    pHead->_pLeft = Temp->_pRight;
    Temp->_pRight = pHead;
    return Temp;
}

template <class T>
void LeftBalance(AVLNode<T>* &pHead, bool &taller) {
    AVLNode<T>* LeftTree = pHead->_pLeft;
    if(LeftTree->_bFactor == LH) {
        //pHead = RotateRight(pHead);
        pHead->_bFactor = EH;
        LeftTree->_bFactor = EH;
        pHead = RotateRight(pHead);
        taller = false;
    }
    else {
        AVLNode<T>* RightTree = LeftTree->_pRight;
        if(RightTree->_bFactor == LH) {
            pHead->_bFactor = RH;
            LeftTree->_bFactor = EH;
        }
        else if(RightTree->_bFactor == EH) {
            LeftTree->_bFactor = EH;
            pHead->_bFactor = EH;
        }
        else {
            pHead->_bFactor = EH;
            LeftTree->_bFactor = LH;
        }
        RightTree->_bFactor = EH;
        pHead->_pLeft = RotateLeft(LeftTree);
        pHead = RotateRight(pHead);
        taller = false;
    }
}

template <class T>
void RightBalance(AVLNode<T>* &pHead, bool &taller) {
    AVLNode<T>* RightTree = pHead->_pRight;
    if(RightTree->_bFactor == RH) {
        //pHead = RotateLeft(pHead);
        pHead->_bFactor = EH;
        RightTree->_bFactor = EH;
        pHead = RotateLeft(pHead);
        taller = false;
    }
    else {
        AVLNode<T>* LeftTree = RightTree->_pLeft;
        if(LeftTree->_bFactor == RH) {
            pHead->_bFactor = LH;
            RightTree->_bFactor = EH;
        }
        else if(LeftTree->_bFactor == EH) {
            RightTree->_bFactor = EH;
            pHead->_bFactor = EH;
        }
        else {
            pHead->_bFactor = EH;
            RightTree->_bFactor = RH;
        }
        LeftTree->_bFactor = EH;
        pHead->_pRight = RotateRight(RightTree);
        pHead = RotateLeft(pHead);
        taller = false;
    }
}

template <class T>
void AVLinsert(AVLNode<T>* &pHead, T &Key, bool &taller) {
    if (pHead == NULL) {
        AVLNode<T>* NewNode = new AVLNode<T>(Key);
        pHead = NewNode;
        taller = true;
        return;
    }
    if(Key < pHead->_data) {
        AVLinsert(pHead->_pLeft, Key, taller);
        if(taller){
            if(pHead->_bFactor == LH) {
                LeftBalance(pHead, taller);
            }
            else if(pHead->_bFactor == EH) {
                pHead->_bFactor = LH;
            }
            else {
                pHead->_bFactor = EH;
                taller = false;
            }
        }
    }
    else {
        AVLinsert(pHead->_pRight, Key,taller);
        if(taller) {
            if(pHead->_bFactor == LH) {
                pHead->_bFactor = EH;
                taller = false;
            }
            else if(pHead->_bFactor == EH) {
                pHead->_bFactor = RH;
            }
            else {
                RightBalance(pHead, taller);
            }
        }
    }
}

template <class T>
bool AVLTree<T>::insert(AVLNode<T>* &pR, T& a) {
    bool taller;
    AVLinsert(pR, a, taller);
}

#endif //A02_DSALIB_H
