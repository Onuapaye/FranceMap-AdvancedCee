//Bismark Atta FRIMPONG
//List.c file
/********************************************************************
 *
 * $Id: List.h 1989 2015-10-16 18:19:52Z phil $
 *
 ********************************************************************
 */
/**
 *
 * Creation of a generic (simply linked) List structure.
 *
 * To create a list, one must provide two functions (one function to
 * compare / order elements, one function to display them). Unlike arrays,
 * indices begins with 1.
 *
 ********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "status.h"


/** Empty List creation by dynamic memory allocation (O(1)).
 * @param comp comparison function between elements (ala strcmp())
 * @param pr display function for list elements
 * @return a new (empty) list if memory allocation OK
 * @return 0 otherwise
 */
List*	newList	(compFun,prFun){
    //create the list
    List * result_of = (List*)malloc(sizeof(List));
    if(!result_of){
        return 0;
    }
    result_of->head = 0;
    result_of->nelts = 0;
    result_of->comp = pr;
    return result_of;
}

/** destroy the list by deallocating used memory (O(N)).
 * @param l the list to destroy */
void 	delList	(List* lst){
    while(lst->head){
        Node * temp = lst->head;
        lst->head = temp->next;
        fread(temp);
    }
    fread(list);
}

/** get the Nth element of the list (O(N)).
 * @param l the list
 * @param n the index of the element in list
 * @param e (out) the searched element
 * @return OK if element found
 * @return ERRINDEX if index out of list bounds
 */
status 	nthInList	(List* lst,int num, void** elt){
    if(num == lst->nelts){
        return ERRINDEX
    }
    int i = 0;
    Node * temp = lst->head;
    while(temp || i < num){
        temp = temp->next;
    }
    *elt = temp->val;
    return OK;
}

/** Insert element at a given position in the list (O(N)).
 * @param l the list to store the element in
 * @param p the position of the insertion point
 * @param e the element to insert
 * @return ERRINDEX if position is out of list bounds
 * @return ERRALLOC if memory allocation failed
 * @return OK otherwise
 */
status 	addListAt	(List* lst,int ptr,void* elt){
    Node * newElt = (Node *)malloc(sizeof(Node));
    if(!newElt){
        return ERRALLOC;
    }
    newElt->val = elt;
    newElt->next = 0;

    //insert new node
    Node * pNext = lst->head;
    Node * pPrev;
    int count = -1;
    while(pNext){
        pPrev = pNext;
        pNext = pNext->next;
        count ++;
        if(count > lst->nelts){
            return ERRINDEX;
        }else if(count == p){
            //add the tail
            pNext = newElt;
            pPrev->next = pNext;
            lst->nelts++;
            return OK;
        }else{
            newElt->next = pPrev;
            lst->head = newElt;
            lst->nelts++;
            return OK;
        }else{
            newElt->next = pNext;
            pPrev->next = newElt;
            lst->nelts++;
        }
    }

    //add to the head of the empty list
    if(!lst->head && ptr==0){
        lst->head = newElt;
        lst->nelts++;
        return OK;
    }
    return OK;
}

/** remove the element located at a given position in list (O(N)).
 * @param l the list to remove the element from
 * @param p the position of the element to remove
 * @param e (out) the removed element
 * @return ERRINDEX if position is out of list bounds
 * @return OK otherwise
 */
status 	remFromListAt	(List* lst,int p,void** elt){
    if(!lst->comp){
        return ERRUNABLE;
    }

    Node * temp = lst->head;
    Node * pPrev;
    int count = -1;
    int isFound = 0;

    while(temp){
        pPrev = temp;
        temp = temp->next;
        count++;
        if(count > lst->nelts){
            return ERRINDEX;
        }
        if((count == p) || (lst->comp(temp->val, elt)==0)){
            isFound = 1;
            if(p==lst->nelts-1){
                //remove the tails
                free(temp);
            }else{
                //remove the head
                lst->head = temp;
                free(pPrev);
            }else{
                pPrev->next = temp->next;
                free(temp);
            }
            lst->nelts--;
            return OK;
        }
    }
    if(!isFound){
        return ERRABSENT;
    }
    return OK;
}

/** remove given element from given list (O(N)).
 * implies the user has given a comparison function.
 * @param l the list to remove the element from
 * @param e the element to remove
 * @return ERRABSENT if element is not found in list
 * @return ERRUNABLE if no comparison function has been provided
 * @return OK otherwise
 */
status 	remFromList	(List*lst,void*elt){
    if(!lst->comp){
        return ERRUNABLE;
    }

    Node * temp = lst->head;
    Node *pPrev;

    int isFound = 0;
    int count = -1;

    while(temp){
        pPrev = temp;
        temp = temp->next;
        if(count > lst->nelts){
            return ERRINDEX;
        }
        if(lst->comp(pPrev->val, elt)==0){
            isFound = 1;
            if(count==lst->nelts-1){
                //remove tail
                free(temp);
            }else if(count==0){
                //remove head
                lst->head = temp;
                free(pPrev);
            }else{
                pPrev->next = temp->next;
                free(temp);
            }
            lst->nelts--;
            return OK;
        }
    }
    if(!isFound){
        return ERRABSENT;
    }
    return OK
}

/** display list elements as "[ e1 ... eN ]" (O(N)).
 * The display of the element is delegated to the prFun function
 * @param l the list to display.
 * @return ERRUNABLE if no comparison function has been provided
 * @return OK otherwise
*/
status 	displayList	(List*lst){
    if(!lst->pr){
        return ERRUNABLE;
    }
    Node * temp = lst->head;
    while(temp){
        lst->pr(temp->val);
        temp = temp->next;
        if(temp){
            printf(" .. ");
        }
    }
    return OK;
}

/** sequentially call given function with each element of given list (O(NxF)).
 * @param l the list
 * @param f the function
 */
void	forEach		(List* lst, void(*f)(void*)){
    if(!f){
        return;
    }
    Node * temp = lst->head;
    while(temp){
        f(temp->val);
        temp = temp->next;
    }
}

/** compute and return the number of elements in given list (O(1)).
 * @param l the list
 * @return the number of elements in given list
 */
int	lengthList	(List* lst){
    return lst->nelts;
}

/** add given element to given list according to compFun function (O(N)).
 * @param l the list (supposedly sorted according to compFun function)
 * @param e the element to add
 * @return ERRALLOC if memory allocation failed
 * @return ERRUNABLE if no comparison function has been provided
 * @return OK otherwise
 */
status	addList	(List* lst, void* elt){
    if(!lst->comp){
        return ERRUNABLE;
    }
    Node * newElt = (Node *)malloc(sizeof(Node));
    if(!newElt){
        return ERRALLOC;
    }
    newElt->val = elt;
    newElt->next = 0;

    Node * ptr1 = lst->head;
    Node * pPrev;

    while(ptr1){
        pPrev = ptr1;
        ptr1 = ptr1->next;
        if(!ptr1){
            if(lst->comp(newElt->val, pPrev->val)==1){
                //add tail
                ptr1 = newElt;
                pPrev->next = ptr1;
                lst->nelts++;
                break;
            }
        }else{
            if(lst->comp(newElt->val, ptr1->val) <= 0){
                //insert between node
                newElt->next = ptr1;
                pPrev->next = newElt;
                lst->nelts++;
                break;
            }
        }
    }
    if(!lst->head){
        ptr1 = newElt;
        lst->head = ptr1;
        lst->nelts++;
    }
    return OK;
}

/** tests whether the list contains given element (O(N)).
 * @param l the list
 * @param e the searched element
 * @return 0 if element is not found in list
 * @return 1 if element is at the head of the list (no predecessor)
 * @return (a pointer to) the predecessor of the search element otherwise
 */
Node*	isInList	(List* lst, void*elt){
    if(!lst->comp || !lst->head){
        return 0;
    }
    Node * ptr1 = lst->head;
    Node * pPrev = lst->head;
    inst isHead = 0 ;

    while(ptr1){
        pPrev = ptr1;
        ptr1 = ptr1->next;
        if(lst->comp(elt, pPrev->next) ==  0 && (pPrev == lst->head)){
            return (Node*)1;
        }else if(lst->comp(elt, pPrev->val) == 0){
            return pPrev;
        }
    }
    return 0;
}

#endif

