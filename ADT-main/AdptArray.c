#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AdptArray_
{
	int size;
	PElement *pelement;
	DEL_FUNC delFunction;
	COPY_FUNC copyFunction;
	PRINT_FUNC printFunction;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC _copyFunction, DEL_FUNC _delFunction ,PRINT_FUNC _printFunction)
{
	PAdptArray adpA = (PAdptArray)malloc(sizeof(AdptArray));
	if (adpA == NULL)
		return NULL;
	adpA->size = 0;
	adpA-> delFunction=_delFunction;
	adpA->copyFunction= _copyFunction;
	adpA->printFunction= _printFunction;
	adpA->pelement=NULL;
	return adpA;
}

void DeleteAdptArray(PAdptArray adpA)
{
	if (adpA==NULL)
		return;
	for (int i=0;i<adpA->size;i++)
	{
        if (adpA->pelement[i]!=NULL)
		       adpA->delFunction((adpA->pelement)[i]);
	}
	free(adpA->pelement);
	free(adpA);
}

Result SetAdptArrayAt(PAdptArray adpA, int index, PElement p)
{
	PElement* newPelement;
	if (adpA==NULL)
		return FAIL;
	if(index >= adpA->size)
	{
		newPelement = (PElement*)calloc((index+1), sizeof(PElement));
		if(newPelement==NULL)
			return FAIL;
		memcpy(newPelement, adpA->pelement, (adpA->size)*sizeof(PElement));
		free (adpA->pelement);
		adpA->pelement=newPelement;
	}
 if (adpA->pelement[index]!=NULL)
	    adpA->delFunction(adpA->pelement[index]);
	(adpA->pelement)[index] = adpA->copyFunction(p);
	if(index>=adpA->size)
		adpA->size=index+1;
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adpA, int index){
    if (adpA==NULL||index>= adpA->size||adpA->pelement[index]==NULL){
        return NULL;}
	PElement* copyPelment;
	copyPelment=adpA->copyFunction(adpA->pelement[index]);
	return copyPelment;
}
int GetAdptArraySize(PAdptArray adpA)
{
    if(adpA!=NULL)
	    return(adpA->size);
        return 0;
}
void PrintDB(PAdptArray adpA){
    if(adpA!=NULL){
        for (int i=0;i<adpA->size;i++)
        {
            if (adpA->pelement[i]!=NULL)
                adpA->printFunction(adpA->pelement[i]);
        }
    }
}