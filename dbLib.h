/*
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 *               This library contains functions used for database management
 * =========================================================================================
 */

#ifndef A02_DBLIB_H
#define A02_DBLIB_H

#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

#include "dsaLib.h"
#include "requestLib.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define VDB_HEADER_TEXT     "VRecord data"
#define VDB_HEADER_SIZE     12

#define ID_MAX_LENGTH   16

struct VRecord {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  x, y;

    VRecord() {// default constructor
        id[0] = 0;
    }
    VRecord(const char* vID) {
        strcpy(id, vID);
    }
    VRecord(VRecord& vR) : timestamp(vR.timestamp),
                           x(vR.x), y(vR.y) {
        strcpy(id, vR.id);
    }
    VRecord(VRecord&& vR): timestamp(vR.timestamp),
                           x(vR.x), y(vR.y) {
        strcpy(id, vR.id);
    }

    bool operator==(VRecord& b) {
        return  strcmp(id, b.id) == 0 &&
                timestamp == b.timestamp;
    }

    VRecord& operator = (VRecord& b) {
        strcpy(id, b.id);
        timestamp = b.timestamp;
        x = b.x;
        y = b.y;
        return *this;
    }

};

struct VM_LAT_Record {
    VRecord *LAT_data = NULL;
    VM_LAT_Record(VRecord &b) {
        LAT_data = &b;
    }
    bool operator < (VM_LAT_Record &b) {
        if(LAT_data->y < b.LAT_data->y) return true;
        else return false;
    }
};

struct VM_LONG_Record {
    VRecord *LONG_data = NULL;
    VM_LONG_Record(VRecord &b) {
        LONG_data = &b;
    }
    bool operator < (VM_LONG_Record &b) {
        if(LONG_data->x < b.LONG_data->x) return true;
        else return false;
    }
};

struct VM_TIME_Record {
    VRecord* TIME_data = NULL;
    VM_TIME_Record(VRecord &b) {
        TIME_data = &b;
    }
    bool operator < (VM_TIME_Record &b) {
        if(TIME_data->timestamp < b.TIME_data->timestamp) {
            return true;
        }
        else return false;
    }
};

struct VM_Record {
    AVLTree<VM_LAT_Record>* Latitude = new AVLTree<VM_LAT_Record>();
    AVLTree<VM_LONG_Record>* Longitude = new AVLTree<VM_LONG_Record>();
    L1List<VRecord>* LinkedList = new L1List<VRecord>();
    AVLTree<VM_TIME_Record>* Time = new AVLTree<VM_TIME_Record>();
    //int count;
    
    VM_Record() {
        Latitude = NULL;
        Longitude = NULL;
        LinkedList = NULL;
        Time = NULL;
        //count = 0;
    }
    VM_Record(VRecord &b) {
        //VM_LAT_Record LAT(b);
        VM_LAT_Record* LATdata = new VM_LAT_Record(b);
        Latitude->insert(*(LATdata));
        //VM_LONG_Record LONG(b);
        VM_LONG_Record* LONGdata = new VM_LONG_Record(b);
        Longitude->insert(*(LONGdata));

        L1Item<VRecord>* Node = new L1Item<VRecord>(b);
        LinkedList->insertHead(b);
        VM_TIME_Record* TIMEdata = new VM_TIME_Record(b);
        Time->insert(*(TIMEdata));

        //count++;
    }
    VM_Record& operator + (VRecord& b) {
        VM_LAT_Record* LATdata = new VM_LAT_Record(b);
        Latitude->insert(*(LATdata));

        VM_LONG_Record* LONGdata = new VM_LONG_Record(b);
        Longitude->insert(*(LONGdata));
        
        LinkedList->insertHead(b);
        VM_TIME_Record* TIMEdata = new VM_TIME_Record(b);
        Time->insert(*(TIMEdata));
        return *this;
    }
    
};

/*
struct NodeLarge{ //lat/long/ID
    AVLTree<VM_LAT_Record>* a;
    AVLTree<VM_LONG_Record>* b;
    VRecord*
    NodeLarge + NodeLarge{
        AVLTree<Lat> + AVLTree<LAt>
        AVLTre + AVLTree
        ID = ID
    }
    NodeLarge == NodeLarge{
        this->VRRecord == that->VRRecord
    }
    NodeLarge(&VRRecord){
        this->VRRecod = *that->VRRecord
    }
}
*/
void    printVRecord(VRecord& vR);
void    strPrintTime(char* des, time_t& t);
void    loadVDB(char* fName, L1List<VRecord> &db);

#define __deg2rad(deg) (deg * pi / 180.0)
#define __rad2deg(rad) (rad * 180.0 / pi)

double  distanceVR(double lat1d, double lon1d, double lat2d, double lon2d);


#endif //A02_DBLIB_H

