// get help from the sulosion from the staff to the exam a from last year q4
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct AdptArray_{ // defint the struct
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC c_fun, DEL_FUNC d_fun, PRINT_FUNC p_fun) {
    PAdptArray adpt_arr = (PAdptArray) malloc(sizeof(struct AdptArray_)); // define the size of the adptarry in the memory
    if (adpt_arr == NULL) { // if we get null its nean ther is a problem with the memory
        return NULL;
    }
    adpt_arr->ArrSize = 0; // initiel the size to 0
    adpt_arr->pElemArr = (PElement*) calloc(0,sizeof (PElement)) ;// put in the memory the first element
    adpt_arr->delFunc = d_fun;
    adpt_arr->copyFunc = c_fun;
    adpt_arr->printFunc = p_fun;
    return adpt_arr;
}

void DeleteAdptArray(PAdptArray adpt_arr) {// function that dealte adpt arry clan the memory and relse (free) the memory
    if (adpt_arr == NULL) { // if the arr is empty its mean we done
        return;}
    for (int i = 0; i < adpt_arr->ArrSize; i++) {// we go over all the arr size
        if (adpt_arr->pElemArr[i] != NULL) { // if the palce i in the arr is not empty we dalete him. 
            adpt_arr->delFunc(adpt_arr->pElemArr[i]);
        }
    }
    free(adpt_arr->pElemArr);//free the elment arr and the arr him self.
    free(adpt_arr);
}

PElement GetAdptArrayAt(PAdptArray adpt_arr, int index) {
    if (adpt_arr == NULL || index < 0 || index >= adpt_arr->ArrSize||adpt_arr->pElemArr[index] == NULL) { // if the arr is empty or the index is unvalid or the index is greter then the size of the arr 
                                                                                            // or the elment in the index is null
        return NULL;
    }
    return adpt_arr->copyFunc(adpt_arr->pElemArr[index]);// return the pelment of the index in the arr
}

Result SetAdptArrayAt(PAdptArray adpt_arr, int index, PElement elem) {
    if (adpt_arr == NULL || index < 0) {  // if the arr is empty or the index is not valid return fail.
        return FAIL;
    }
    if (index >= adpt_arr->ArrSize) {//if the index bigger then the current size
        PElement* newpElemArr = (PElement*) realloc(adpt_arr->pElemArr, (index + 1) * sizeof(PElement));// alocate size for the next elment
        if (newpElemArr == NULL) { // if the alcoatr memory is faild return faild
            return FAIL;
        }
        for (int i = adpt_arr->ArrSize; i < index + 1; i++) {// put null in al the ciels to the index
            newpElemArr[i] = NULL;
        }
        adpt_arr->pElemArr = newpElemArr;// update the elment arry in the arr
        adpt_arr->ArrSize = index + 1;//incer the index by 1
    }
    if (adpt_arr->pElemArr[index] != NULL) { // if thier is elment in the ciel alredy
        adpt_arr->delFunc(adpt_arr->pElemArr[index]);//clear the ciel in the index
    }
    adpt_arr->pElemArr[index] = adpt_arr->copyFunc(elem);//put the new ekment in the ciel and return success
    return SUCCESS;
}

void PrintDB(PAdptArray adpt_arr) {
    if (adpt_arr == NULL) {// if the arr is empty return nothing
        return;
    }
    for (int i = 0; i < adpt_arr->ArrSize; i++) {//go over all the arr 
        if (adpt_arr->pElemArr[i] != NULL) { // if the elment in the index is not null
            adpt_arr->printFunc(adpt_arr->pElemArr[i]);//print the lement
        }
    }
}

int GetAdptArraySize(PAdptArray adpt_arr) { // return the size of the arry
    if (adpt_arr == NULL) {
        return 0;} // return 0 becuse she is empty
    
    return adpt_arr->ArrSize; // else we go to the arr size in the arr and return the size
}