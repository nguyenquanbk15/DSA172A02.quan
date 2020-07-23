/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : Student code for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

/// Initialize and Finalize any global data that you use in the program

struct Data {
    AVLTree<AVLTree<VM_LAT_Record>> db_LAT;
    AVLTree<AVLTree<VM_LONG_Record>> db_LONG;
    AVLTree<VM_Record> db_Tree;
    int flag;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

bool _insertLatAVL(AVLNode<AVLTree<VM_LAT_Record>>* &pR, VRecord &key, bool &taller, int &Num_Tree) {
    if(pR == NULL) {
        VM_LAT_Record* NewData = new VM_LAT_Record(key);
        //AVLNode<VM_LAT_Record>* NewNode = new AVLNode<VM_LAT_Record>((*NewData));
        AVLTree<VM_LAT_Record>* NewTree = new AVLTree<VM_LAT_Record>();
        NewTree->insert((*NewData));
        NewTree->increaseCount();
        AVLNode<AVLTree<VM_LAT_Record>>* NewNode = new AVLNode<AVLTree<VM_LAT_Record>>((*NewTree));

        pR = NewNode;
        Num_Tree++;
        taller = true;
    }
    else {
        AVLNode<VM_LAT_Record>* pRChild = pR->_data._getpRoot();
        if(strcmp(pRChild->_data.LAT_data->id, key.id) == 0) {
            VM_LAT_Record* NewData = new VM_LAT_Record(key);
            pR->_data.insert((*NewData));
            pR->_data.increaseCount();

            taller = false;
        }
        else if(strcmp(pRChild->_data.LAT_data->id, key.id) > 0) {
            _insertLatAVL(pR->_pLeft, key, taller, Num_Tree);
            if(taller){
                if(pR->_bFactor == LH) {
                    LeftBalance<AVLTree<VM_LAT_Record>>(pR, taller);
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = LH;
                }
                else {
                    pR->_bFactor = EH;
                    taller = false;
                }
            }
        }
        else {
            _insertLatAVL(pR->_pRight, key, taller, Num_Tree);
            if(taller) {
                if(pR->_bFactor == LH) {
                    pR->_bFactor = EH;
                    taller = false;
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = RH;
                }
                else {
                    RightBalance<AVLTree<VM_LAT_Record>>(pR, taller);
                }
            }
        }
    }

    return true;
}

bool _createLatAVL(AVLTree<AVLTree<VM_LAT_Record>> &db, VRecord &key, int &Num) {
    AVLNode<AVLTree<VM_LAT_Record>>* pR = db._getpRoot();
    bool taller;
    _insertLatAVL(pR, key, taller, Num);
    db._setpRoot(pR);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////

bool _insertLongAVL(AVLNode<AVLTree<VM_LONG_Record>>* &pR, VRecord &key, bool &taller, int &Num_Tree) {
    if(pR == NULL) {
        VM_LONG_Record* NewData = new VM_LONG_Record(key);
        //AVLNode<VM_LAT_Record>* NewNode = new AVLNode<VM_LAT_Record>((*NewData));
        AVLTree<VM_LONG_Record>* NewTree = new AVLTree<VM_LONG_Record>();
        NewTree->insert((*NewData));
        NewTree->increaseCount();
        AVLNode<AVLTree<VM_LONG_Record>>* NewNode = new AVLNode<AVLTree<VM_LONG_Record>>((*NewTree));

        pR = NewNode;
        Num_Tree++;
        taller = true;
    }
    else {
        AVLNode<VM_LONG_Record>* pRChild = pR->_data._getpRoot();
        if(strcmp(pRChild->_data.LONG_data->id, key.id) == 0) {
            VM_LONG_Record* NewData = new VM_LONG_Record(key);
            pR->_data.insert((*NewData));
            pR->_data.increaseCount();

            taller = false;
        }
        else if(strcmp(pRChild->_data.LONG_data->id, key.id) > 0) {
            _insertLongAVL(pR->_pLeft, key, taller, Num_Tree);
            if(taller){
                if(pR->_bFactor == LH) {
                    LeftBalance<AVLTree<VM_LONG_Record>>(pR, taller);
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = LH;
                }
                else {
                    pR->_bFactor = EH;
                    taller = false;
                }
            }
        }
        else {
            _insertLongAVL(pR->_pRight, key, taller, Num_Tree);
            if(taller) {
                if(pR->_bFactor == LH) {
                    pR->_bFactor = EH;
                    taller = false;
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = RH;
                }
                else {
                    RightBalance<AVLTree<VM_LONG_Record>>(pR, taller);
                }
            }
        }
    }

    return true;
}

bool _createLongAVL(AVLTree<AVLTree<VM_LONG_Record>> &db, VRecord &key, int &Num) {
    AVLNode<AVLTree<VM_LONG_Record>>* pR = db._getpRoot();
    bool taller;
    _insertLongAVL(pR, key, taller, Num);
    db._setpRoot(pR);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool _insertAVL(AVLNode<VM_Record>* &pR, VRecord &key, bool &taller, int &Num_Tree) {
    if(pR == NULL) {
        //VM_LONG_Record* NewData = new VM_LONG_Record(key);
        //AVLNode<VM_LAT_Record>* NewNode = new AVLNode<VM_LAT_Record>((*NewData));
        //AVLTree<VM_LONG_Record>* NewTree = new AVLTree<VM_LONG_Record>();
        //NewTree->insert((*NewData));
        //NewTree->increaseCount();
        //AVLNode<AVLTree<VM_LONG_Record>>* NewNode = new AVLNode<AVLTree<VM_LONG_Record>>((*NewTree));
        VM_Record* NewData = new VM_Record(key);
        AVLNode<VM_Record>* NewNode  = new AVLNode<VM_Record>(*(NewData));
        pR = NewNode;
        Num_Tree++;
        taller = true;
    }
    else {
        //AVLNode<VM_LONG_Record>* pRChild = pR->_data._getpRoot();
        L1Item<VRecord>* pID = pR->_data.LinkedList->getpHead();
        if(strcmp(pID->data.id, key.id) == 0) {
            VM_LONG_Record* NewData = new VM_LONG_Record(key);
            //pR->_data.insert((*NewData));
            //pR->_data.increaseCount();
            pR->_data + key;

            taller = false;
        }
        else if(strcmp(pID->data.id, key.id) > 0) {
            _insertAVL(pR->_pLeft, key, taller, Num_Tree);
            if(taller){
                if(pR->_bFactor == LH) {
                    LeftBalance<VM_Record>(pR, taller);
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = LH;
                }
                else {
                    pR->_bFactor = EH;
                    taller = false;
                }
            }
        }
        else {
            _insertAVL(pR->_pRight, key, taller, Num_Tree);
            if(taller) {
                if(pR->_bFactor == LH) {
                    pR->_bFactor = EH;
                    taller = false;
                }
                else if(pR->_bFactor == EH) {
                    pR->_bFactor = RH;
                }
                else {
                    RightBalance<VM_Record>(pR, taller);
                }
            }
        }
    }

    return true;
}

bool _createAVL(AVLTree<VM_Record> &db, VRecord &key, int &Num) {
    AVLNode<VM_Record>* pR = db._getpRoot();
    bool taller;
    _insertAVL(pR, key, taller, Num);
    db._setpRoot(pR);
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool _CreateAVLTree(L1List<VRecord>& recList, Data* &NewData) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    else {
        L1Item<VRecord>* pCurr = recList.getpHead();
        //int a = 1;
        int NumLAT = 0;
        int NumLONG = 0;
        while(pCurr != NULL) {
            bool taller;
            //cout << a++ << endl;
            _createLatAVL(NewData->db_LAT, pCurr->data, NumLAT);
            _createLongAVL(NewData->db_LONG, pCurr->data, NumLONG);
            pCurr = pCurr->pNext;
        }
        NewData->db_LAT._setCount(NumLAT);
        NewData->db_LONG._setCount(NumLONG);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////

bool _CCreateAVLTree(L1List<VRecord>& recList, Data* &NewData) {
    if(recList.getpHead() == NULL) {
        return false;
    }
    else {
        L1Item<VRecord>* pCurr = recList.getpHead();
        //int a = 1;
        int Num = 0;
        while(pCurr != NULL) {
            bool taller;
            //cout << a++ << endl;
            //_createLatAVL(NewData->db_LAT, pCurr->data, NumLAT);
            //_createLongAVL(NewData->db_LONG, pCurr->data, NumLONG);
            _createAVL(NewData->db_Tree, pCurr->data, Num);
            pCurr = pCurr->pNext;
        }
        //NewData->db_LAT._setCount(NumLAT);
        //NewData->db_LONG._setCount(NumLONG);
        NewData->db_Tree._setCount(Num);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////

bool initVGlobalData(void** pGData) { 
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    static Data* pGList = new Data;
    pGList->flag = 0;
    *pGData = pGList;
    
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}


///////////////////////////////////////////////////////////////////////////////////////////
///////     param[0]: STOP
///////     param[1]: Dữ liệu cần thiết cho function
///////     param[2]: Kết quả trả về

void _findID(AVLNode<VM_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    char* NodeID = pR->_data.Longitude->_getpRoot()->_data.LONG_data->id;
    void** Arr = (void**)param[1];
    char* Request = (char*)Arr[0];
    char* ID = getRequestID(Request);
    if(strcmp(ID, NodeID) == 0) {
        //int* stop = new int(1);
        int* stop = (int*) param[0];
        *stop = 1;
        param[2] = pR;
    }
    else if(strcmp(ID, NodeID) < 0) {
        int* stop = (int*) param[0];
        *stop = 0;
        direction = -1;
    }
    else {
        int* stop = (int*) param[0];
        *stop = 0;
        direction = 1;
    }
}

void CheckPassingPoint_Y(AVLNode<VM_LAT_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //*check = 0;
        return;
    }
    double P_y = pR->_data.LAT_data->y;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[1]);
    double delta_y = atof((char*)Arr[2]);
    if (P_y >= R_y - delta_y && P_y <= R_y + delta_y ){
        int* stop = (int*) param[0];
        *stop = 1;
        int* check = (int*)param[3];
        *check = 1;
        //param[2] = true; 
    }
    else {
        if (P_y < R_y - delta_y) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = 1;
        }
        else if (P_y > R_y + delta_y) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = -1;
        }
    }
}

void CheckPassingPoint_X(AVLNode<VM_LONG_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    double P_x = pR->_data.LONG_data->x;
    void** Arr = (void**)param[1];
    double R_x = atof((char*)Arr[1]);
    double delta_x = atof((char*)Arr[2]);
    if (P_x >= R_x - delta_x && P_x <= R_x + delta_x ){
        int* stop = (int*) param[0];
        *stop = 1;
        int* check = (int*)param[3];
        *check = 1;
        //param[2] = true; 
    }
    else {
        if (P_x < R_x - delta_x) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = 1;
        }
        else if (P_x > R_x + delta_x) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = -1;
        }
    }
}

void NumBer_NearPoint_Y(AVLNode<VM_LAT_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    double P_y = pR->_data.LAT_data->y;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[1]);
    double delta_y = atof((char*)Arr[2]);
    int* stop = (int*) param[0];
    *stop = 0;
    if (P_y >= R_y - delta_y && P_y <= R_y + delta_y ){
        direction = 0;
        int* Num = (int*)param[3];
        *Num = *Num + 1;
        //param[2] = true; 
    }
    else {
        if (P_y < R_y - delta_y) {
            direction = 1;
        }
        else if (P_y > R_y + delta_y) {
            direction = -1;
        }
    }
}

void NumBer_NearPoint_X(AVLNode<VM_LONG_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    double P_x = pR->_data.LONG_data->x;
    void** Arr = (void**)param[1];
    double R_x = atof((char*)Arr[1]);
    double delta_x = atof((char*)Arr[2]);
    int* stop = (int*) param[0];
    *stop = 0;
    if (P_x >= R_x - delta_x && P_x <= R_x + delta_x ){
        direction = 0;
        int* Num = (int*)param[3];
        *Num = *Num + 1;
        //param[2] = true; 
    }
    else {
        if (P_x < R_x - delta_x) {
            direction = 1;
        }
        else if (P_x > R_x + delta_x) {
            direction = -1;
        }
    }
}

void NumBer_PassingPoint_Y(AVLNode<VM_LAT_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        param[2] = NULL;
        return;
    }
    double P_y = pR->_data.LAT_data->y;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[2]);
    double delta_y = atof((char*)Arr[3]);
    if (P_y >= R_y - delta_y && P_y <= R_y + delta_y ){
        int* stop = (int*) param[0];
        *stop = 0;
        direction = 0;
        int** Num = (int**)param[2];
        *(Num[0])++;
        //param[2] = true; 
    }
    else {
        if (P_y < R_y - delta_y) {
            direction = 1;
        }
        else if (P_y > R_y + delta_y) {
            direction = -1;
        }
    }
}

void NumBer_PassingPoint_X(AVLNode<VM_LONG_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        param[2] = NULL;
        return;
    }
    double P_x = pR->_data.LONG_data->x;
    void** Arr = (void**)param[1];
    double R_x = atof((char*)Arr[2]);
    double delta_x = atof((char*)Arr[3]);
    if (P_x >= R_x - delta_x && P_x <= R_x + delta_x ){
        //int* stop = (int*) param[0];
        //*stop = 0;
        direction = 0;
        int* Num = (int*)param[2];
        *Num++;
        //param[2] = true; 
    }
    else {
        if (P_x < R_x - delta_x) {
            direction = 1;
        }
        else if (P_x > R_x + delta_x) {
            direction = -1;
        }
    }
}

void Check_PassingPoint(AVLNode<VM_LAT_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    double P_y = pR->_data.LAT_data->y;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[1]);
    double delta_y = atof((char*)Arr[3]);
    if (P_y >= R_y - delta_y && P_y <= R_y + delta_y ){
        int* stop = (int*) param[0];
        *stop = 1;
        double P_x = pR->_data.LAT_data->x;
        double R_x = atof((char*)Arr[2]);
        double delta_x = atof((char*)Arr[4]);
        if(P_x >= R_x - delta_x && P_x <= R_x + delta_x) {
            int* check = (int*)param[3];
            *check = 1;
        }
        //param[2] = true; 
    }
    else {
        if (P_y < R_y - delta_y) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = 1;
        }
        else if (P_y > R_y + delta_y) {
            int* stop = (int*) param[0];
            *stop = 0;
            direction = -1;
        }
    }
}

void NumBer_NearPoint(AVLNode<VM_LAT_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        //param[2] = NULL;
        return;
    }
    double P_y = pR->_data.LAT_data->y;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[1]);
    double delta_y = atof((char*)Arr[3]);
    int* stop = (int*) param[0];
    *stop = 0;
    if (P_y >= R_y - delta_y && P_y <= R_y + delta_y ){
        double P_x = pR->_data.LAT_data->x;
        double R_x = atof((char*)Arr[2]);
        double delta_x = atof((char*)Arr[4]);
        if(P_x >= R_x - delta_x && P_x <= R_x + delta_x) {
            direction = 0;
            int* Num = (int*)param[3];
            *Num = *Num + 1;
        }
        //param[2] = true; 
    }
    else {
        if (P_y < R_y - delta_y) {
            direction = 1;
        }
        else if (P_y > R_y + delta_y) {
            direction = -1;
        }
    }
}

void NumID_PassingPoint(AVLNode<VM_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        return;
    }
    int* check = (int*)param[3];
    *check = 0;
    pR->_data.Latitude->traverse(Check_PassingPoint, param);
    if(*check == 1) {
        int* Num = (int*)param[2];
        *Num = *Num + 1;
    }

    int* stop = (int*)param[0];
    *stop = 0;
    direction = 0;
    
}

void NumRecord_NearPoint(AVLNode<VM_Record>* pR, void** param, int& direction) {
    if(pR == NULL) {
        return;
    }
    int* NumID = (int*)param[3];
    *NumID = 0;
    pR->_data.Latitude->traverse(NumBer_NearPoint, param);
    int* Num = (int*)param[2];
    *Num = *Num + *NumID;

    int* stop = (int*)param[0];
    *stop = 0;
    direction = 0;
}

void Times_PassingPoint(AVLNode<VM_TIME_Record>* pR, void** param) {
    if(pR == NULL) {
        return;
    }
    double P_y = pR->_data.TIME_data->y;
    double P_x = pR->_data.TIME_data->x;
    void** Arr = (void**)param[1];
    double R_y = atof((char*)Arr[1]);
    double R_x = atof((char*)Arr[2]);
    double delta_y = atof((char*)Arr[3]);
    double delta_x = atof((char*)Arr[4]);
    int* flag = (int*)param[0];
    if(P_y >= R_y - delta_y && P_y <= R_y + delta_y) {
        if(P_x >= R_x - delta_x && P_x <= R_x + delta_x) {
            if(*flag == 0) {
                int* Num = (int*)param[3];
                *Num = *Num + 1;
            }
            *flag = 1;
        }
    }
    else {
        *flag = 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    Data* pGList = (Data*) pGData;
    
    //L1Item<VRecord>* pCurr = recList.getpHead();
    if(pGList->flag == 0) {
        //_CreateAVLTree(recList, pGList);
        _CCreateAVLTree(recList, pGList);
        pGList->flag++;
    }
    //cout << pGList->db_Tree._getpRoot()->_data.LinkedList->getpHead()->data.id << endl;
    //cout << pGList->db_Tree._getCount() << endl;
    //cout << pGList->db_Tree._getpRoot()->_data.LinkedList->getSize() << endl;
    
    //int a = 1;
    //a = pGList->db_LAT._getCount();
    //cout << pGList->db_LAT._getpRoot()->_data._getpRoot()->_data.LAT_data->id << endl;
    //cout << a << endl;
    //cout << pGList->db_LONG._getCount() << endl;
    
    char ArrayChar[REQUEST_CODE_SIZE];
    strcpy(ArrayChar, request.code);
    void** Arr = distributeCODE(ArrayChar);
    int Num_param = strlen((char*)Arr);
    int check = 0;
    int i = 2;                              /// Đối với request NVR và NRR thì chưa kiểm tra Arr[1]
    while(i < Num_param) {
        //cout << (char*)Arr[i] << endl;
        if(!isFloat((char*)Arr[i])) {
            check = 1;
            //cout << (char*)Arr[i] << endl;
            break;
        }
        i++;
    }

    void** param = new void*[MAX_PACKAGE];
    int stop = 0;
    param[0] = &stop;
    param[1] = Arr;
    param[2] = NULL;
    int result = 0;
    param[3] = &result;

    ////////////// LAT: y
    ////////////// LONG x

    if(check == 0) {
        if(strncmp((char*)Arr[0], "CYR", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LAT_Record>* child_tree = pID->_data.Latitude;
            child_tree->traverse(CheckPassingPoint_Y, param);
            int check = *(int*)param[3];
            if(check == 0) {
                cout << "no passing!" << endl;
            }
            else {
                cout << "passing" << endl;
            }
            
        }
        else if(strncmp((char*)Arr[0], "CXR", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LONG_Record>* child_tree = pID->_data.Longitude;
            child_tree->traverse(CheckPassingPoint_X, param);
            int check = *(int*)param[3];
            if(check == 0) {
                cout << "no passing!" << endl;
            }
            else {
                cout << "passing" << endl;
            }
            
        }
        else if(strncmp((char*)Arr[0], "NYR", 3) == 0) { 
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LAT_Record>* child_tree = pID->_data.Latitude;
            child_tree->traverse(NumBer_NearPoint_Y, param);
            int Num = *(int*)param[3];
            cout << "Number near point: " << Num << endl;
        }
        else if(strncmp((char*)Arr[0], "NXR", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LONG_Record>* child_tree = pID->_data.Longitude;
            child_tree->traverse(NumBer_NearPoint_X, param);
            int Num = *(int*)param[3];
            cout << "Number near point: " << Num << endl;
        }
        else if(strncmp((char*)Arr[0], "NPR", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_TIME_Record>* child_tree = pID->_data.Time;
            int* flag = (int*)param[0];
            *flag = 0;
            child_tree->traverseLNR(Times_PassingPoint, param);
            int Num = *(int*)param[3];
            cout << "times passing point: " << Num << endl;
        }
        else if(strncmp((char*)Arr[0], "NVR", 3) == 0) {
            int* Num = new int(0);
            param[2] = Num;
            pGList->db_Tree.traverse(NumID_PassingPoint, param);
            cout << "num ID passing point: " << (*Num) << endl;
        }
        else if(strncmp((char*)Arr[0], "NRR", 3) == 0) {
            int* Num = new int(0);
            param[2] = Num;
            pGList->db_Tree.traverse(NumRecord_NearPoint, param);
            cout << "num Record near point: " << (*Num) << endl;
        }
        else if(strncmp((char*)Arr[0], "CVP", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LAT_Record>* child_tree = pID->_data.Latitude;
            child_tree->traverse(Check_PassingPoint, param);
            int check = *(int*)param[3];
            if(check == 0) {
                cout << "no passing!" << endl;
            }
            else {
                cout << "passing" << endl;
            }
            
        }
        else if(strncmp((char*)Arr[0], "NRP", 3) == 0) {
            pGList->db_Tree.traverse(_findID, param);
            AVLNode<VM_Record>* pID = NULL;
            pID = (AVLNode<VM_Record>*)param[2];
            if(pID == NULL) {
                cout << "not found!" << endl;
            }
            else {
                cout << "success!, ID: " << pID->_data.Latitude->_getpRoot()->_data.LAT_data->id << endl;
            }
            
            AVLTree<VM_LAT_Record>* child_tree = pID->_data.Latitude;
            child_tree->traverse(NumBer_NearPoint, param);
            int Num = *(int*)param[3];
            cout << "Number near point: " << Num << endl;
        }
        else {
            cout << request.code << " : False" << endl;
        }
    }
    else {
        cout << request.code << " : Falseaaaaaaaaaaa" << endl;
    }

    return true;
}

