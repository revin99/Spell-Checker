#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  dict_node_tag
{
    char str[50]; //stores the word
    struct dict_node_tag *next;
}dictnode;

typedef struct MRU_NODE
{
    char word[50];
    int freq;
    struct MRU_NODE* next;
}MRU;


typedef struct MIS_NODE
{
    char word[50];
    int freq;
    struct MIS_NODE*next;
}MIS;


void displaydict(dictnode *arr[])
{
    dictnode *hptr = (dictnode *)malloc(sizeof(dictnode));
     for(int i=0;i<52;i++)
    {
        hptr=arr[i];
        dictnode *ptr=hptr;
        if(i%2==0) //capital letters
        {
            printf("%c ->\t",'A'+i/2);
        }
        else
        {
            printf("%c ->\t",'a'+i/2);
        }
        
        while(ptr!=NULL)
        {
            printf("%s ",ptr->str);
            ptr=ptr->next;
        }
        printf("\n");
    }
}
MRU* SortedMerge(MRU* a, MRU* b); 
void FrontBackSplit(MRU* source, 
                    MRU** frontRef, MRU** backRef);
void MergeSort(MRU** headRef) 
{ 
    MRU* head = *headRef; 
    MRU* a; 
    MRU* b; 
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) { 
        return; 
    } 
  
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b); 
  
    /* Recursively sort the sublists */
    MergeSort(&a); 
    MergeSort(&b); 
  
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b); 
} 
MRU* SortedMerge(MRU* a, MRU* b) 
{ 
    MRU* result = NULL; 
  
    /* Base cases */
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
  
    /* Pick either a or b, and recur */
    if (strcmp(a->word,b->word)<0) { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 
    return (result); 
} 
void FrontBackSplit(MRU* source, 
                    MRU** frontRef, MRU** backRef) 
{ 
    MRU* fast; 
    MRU* slow; 
    slow = source; 
    fast = source->next; 
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    /* 'slow' is before the midpoint in the list, so split it in two  
    at that point. */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 
void swap(MRU *a, MRU *b) 
{ 
    int temp = a->freq; 
    a->freq = b->freq; 
    b->freq = temp; 

    char tempword[50];
    strcpy(tempword,a->word);
    strcpy(a->word,b->word);
    strcpy(b->word,tempword);
} 
void swapf(MIS *a, MIS *b) 
{ 
    int temp = a->freq; 
    a->freq = b->freq; 
    b->freq = temp; 

    char tempword[50];
    strcpy(tempword,a->word);
    strcpy(a->word,b->word);
    strcpy(b->word,tempword);
} 

void bubbleSort(MRU*start) 
{ 
    int swapped, i; 
    MRU  *ptr1; 
    MRU *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (strcmp(ptr1->word,ptr1->next->word)>0) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 

void displayMRU(MRU *head)
{
    MRU *ptr = head;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->word,"")!=0)
        {
            printf("%s ",ptr->word);
            printf("%d\n",ptr->freq);
        }
        ptr=ptr->next;
    }



}
void displayMRUsorted(MRU *head)
{
    //must be displayed according to alphabetical order
    // so first sort according to alphabetical order then print 
    MRU *temphead = head;

    bubbleSort(temphead);
    MRU *ptr = temphead;
    printf("after sorting\n");
      while(ptr!=NULL)
    {
        if(strcmp(ptr->word,"")!=0)
        {
            printf("%s ",ptr->word);
            printf("%d\n",ptr->freq);
        }
        ptr=ptr->next;
    }


   
}

void displayMIS(MIS *last)
{
    printf("\n displaying mis list\n");
    MIS *ptr = last;
    if(last==NULL) printf("\nMIS list is empty\n");
    else
    {
        int swapped;
        MIS *lptr;
        do
        { 
            swapped = 0; 
            MIS *ptr1 = last; 
  
        while (ptr1->next != last) 
        { 
            if (ptr1->freq<ptr1->next->freq) 
            {  
                swapf(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = last; 
        }while(swapped);

        printf("%s ",last->word);
        printf("%d \n",last->freq);
        
        ptr=last->next;
        while(ptr!=last)
        {
            printf("%s ",ptr->word);
            printf("%d \n",ptr->freq);
           ptr=ptr->next;
        }
     
    }
    
    
}

void sortedinsert(dictnode*arr[],int index,char buf[])
{
    //insert into arr[index]'s list 

  //  printf("sorted insert for string %s\n",buf);
    dictnode *hptr = arr[index];
    dictnode *newptr = (dictnode*)malloc(sizeof(dictnode));
    strcpy(newptr->str,buf);
    newptr->next=NULL;
    if(hptr==NULL) //empty linked list
    {
           // printf("1\n");
            hptr=newptr;
            hptr->next=NULL;
          //  printf("%s\n",hptr->str);
            arr[index]= hptr; //equivalent to return statement
    }
    else if(strcmp(newptr->str,hptr->str) <=0) // this newptr needs to become new head since it's smaller than current head
    {
       // printf("2\n");
        dictnode *tempptr;
        tempptr=hptr;
        hptr= newptr;
        newptr->next=tempptr;
        arr[index]=hptr;
    }
    else            //must traverse the array to find proper position of node and insert it there
    {
        
        //printf("3\n");
        dictnode *tempptr = hptr; dictnode *prev=NULL; int flag=0;
        while(tempptr!=NULL && flag==0)
        {
            if(strcmp(newptr->str,tempptr->str) <=0) //this node's string is larger than our word so insert before it
            {
                    prev->next= newptr;
                    newptr->next = tempptr;
                    flag =1;
            }
            prev= tempptr;
            tempptr= tempptr->next;
        }

        if(flag==0) // traversed whole list but didnt find means it must be last element
        {
            prev->next= newptr;
            newptr->next=NULL;
        }

    }


}


void findindex(char buf[],dictnode*arr[])
{
    char c = buf[0]; //first character of the word
    int index;
    if(c<=90) //if cap letter
    {
        //must accordingly insert in even indexed value of arr. 0th->A;2nd->B;4th->C;.....;50th->Z
        index = c-'A'; // value 0->A;1->B;2->C...;25->Z
        index=(index*2); //its proper positioning in our arr
    }
    else        //if small letter
    {
        //must accordingly insert in odd indexed value of arr. 1st->a;3rd->b;.....51st->z
        index = c-'a'; //value 0->a;1->b;2->c;....25->z
        index=(index*2)+1; //proper positioning in arr
    }
    
   // printf("%s %c %d\n",buf,c,index);

    //now we've correct index of where to insert our word according to the word's first character

    sortedinsert(arr,index,buf);
    //printf("came out of sorted insert\n");
    

}


MRU * init(MRU *head)
{
    
    MRU *ptr = head;
    ptr->freq=0;
    strcpy(ptr->word,"");
    for(int i=2;i<=10;i++)
    {
        MRU *nptr = (MRU*)malloc(sizeof(MRU));
        nptr->freq=0;
        strcpy(nptr->word,"");
        nptr->next=NULL;
        ptr->next=nptr;
        ptr = ptr->next;
    }
    return head;
}


int checkinMRU(char word[],MRU **head)
{
    /* function checks if passed value of word is present in MRU
       if present it returns status true(i.e "1") and updates the word's frequency else returns false(i.e"0") */
   // printf("Came in checkmru function ");
    MRU *ptr = *head;
    int flag=0;
    while(ptr!=NULL && flag==0)
    {
        if(strcmp(word,ptr->word)==0) //if word found in MRU
        {
            flag =1;
            ptr->freq++;
        }
        ptr=ptr->next;
    }

    printf("checked in MRU and now returns %d\n",flag);

    return flag; //returns 0 if not in MRU or returns 1 if found in MRU
}

int checkindict(char word[],dictnode *arr[])
{

    char c = word[0]; // first character of word;
    int index;
    if(c<=90) //if cap letter
    {
        //must accordingly insert in even indexed value of arr. 0th->A;2nd->B;4th->C;.....;50th->Z
        index = c-'A'; // value 0->A;1->B;2->C...;25->Z
        index=(index*2); //its proper positioning in our arr
    }
    else        //if small letter
    {
        //must accordingly insert in odd indexed value of arr. 1st->a;3rd->b;.....51st->z
        index = c-'a'; //value 0->a;1->b;2->c;....25->z
        index=(index*2)+1; //proper positioning in arr
    }

    //now we search in arr[index] if word is present
    int flag=0;

    dictnode *ptr = arr[index];
    while(ptr!=NULL && flag==0)
    {
        if(strcmp(word,ptr->str)==0) //if word is found
            flag=1;
        ptr=ptr->next;
    }

    printf("Checked in dictionary and now returns %d\n",flag);

    return flag; // if found it returns 1 else returns 0

}


void insertinMRU(char word[],MRU **head)
{
    //function first checks for occurrence of word in mru. if present adds to freq or else adds to starting of mru erasing the last node
      //  printf("came inside insertomru func\n");     
       MRU *ptr = *head;
        int flag=0;
       while(ptr!=NULL && flag==0)
       {
           if(strcmp(ptr->word,word)==0)
           {
               ptr->freq++;
               flag=1;
           }
           ptr = ptr->next;
       }
       if(flag==0) //not present in MRU
       {
           //printf("came inside flag =0 condition\n");
           //add to start of list but make sure list is only 10 long
           MRU *newptr = (MRU*)malloc(sizeof(MRU));
           strcpy(newptr->word,word);
           newptr->freq=1;
           newptr->next=*head;
           *head = newptr;
          
                /////////////////////// deleting last extra node //////////////////////////
                 MRU *ptr = *head,*prev=NULL;
                while(ptr->next!=NULL){
                    prev = ptr;
                    ptr=ptr->next;
               } 
               free(ptr);
               prev->next=NULL;   
           

       }
        //*head = tempptr;
        
}


MIS* insert_mis(char word[],MIS* mislast)
{
    /* check the mis list for prev occurrence of word, 1> if found incr it's freq 
                                                       2> insert a new node with freq 1
        Note that it maintains a circular linked list of nodes 
                                                        */

    printf("Coming in mislist with word %s\n",word);
    MIS *ptr = mislast;
    int flag=0;
    if(mislast!=NULL){
        ptr=mislast->next;
        while(ptr!=mislast && flag==0)
        {
            if(strcmp(ptr->word,word)==0)
            {
                ptr->freq++;
                flag=1;
            }
            ptr=ptr->next;
        }
    }
    
    if(flag==0) //if not found in misspelt words then insert at end
    {
         printf("inserting into into mis\n");
        MIS *nptr = (MIS*)malloc(sizeof(MIS));
        strcpy(nptr->word,word);
        nptr->next=NULL;
        nptr->freq=1;

        if(mislast==NULL) // means empty list
        {
            printf("inserting first into mis\n");
            mislast=nptr;
            mislast->next=mislast;
        }
        else //add to end 
        {
            printf("inserting at end into mis\n");
            nptr->next=mislast->next;
            mislast->next=nptr;
            mislast=nptr;
        }
        
    }
    return mislast;
}



main()
{


    ////////////////////////////////////////////// DICTIONARY CREATION //////////////////////////////////////////////
    
    
    dictnode *arr[52];
    dictnode *hptr = (dictnode *)malloc(sizeof(dictnode));
    hptr=NULL;
    for(int i=0;i<52;i++) arr[i] = hptr;
    /* 0th entry -> A starting words
       1st entry -> a starting words
       ...
       ...
       ...
       50th entry-> Z starting words
       51st entry ->z starting words
    */

    FILE *fp;
    dictnode *newptr = (dictnode *)malloc(sizeof(dictnode));
    newptr->next=NULL;
    fp = fopen("dict.txt","r");
    char buf1[50];
    while(!feof(fp))
    {
        fscanf(fp,"%s",buf1);
        findindex(buf1,arr);
        //printf("%s\n",buf);
    }

    


    //////////////////////////////////////////////////////// DICTIONARY CREATION ENDS /////////////////////////////////////////////////






    MRU *head = (MRU*)malloc(sizeof(MRU));
    head = init(head);
    displayMRU(head);

    MIS *mislast = (MIS*)malloc(sizeof(MIS));
    mislast=NULL;

    FILE *fptr;
    fptr = fopen("inputw.txt","r");

    char buf[50]; int i=0;
    
    while(!feof(fptr)){
        fscanf(fptr,"%s",buf);
       int i,j; 
       int pos=-1; // remains -1 if no hyphen in word or takes value of hyphen 
        for (i=0;buf[i]!='\0';i++) {
        while (!((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 'Z') || buf[i] == '\0')) {
            if(buf[i]=='-'){
                    pos=i;
            }
            for (j = i; buf[j] != '\0'; j++) {
                buf[j] = buf[j + 1];
            }
            buf[j] = '\0';
        }
    }
    if(pos==-1) //only one word
    {
        puts(buf);
        if( checkinMRU(buf,&head)) // if word was found in MRU, then well and good since it's freq updates in this function only
        {
            //do nothing here since word found in MRU which means proper spelt 
        }
        else
        {
            //if not found, must check for word in the dictionary array of sorted list

                
            if(checkindict(buf,arr)) //if found in dictionary then well and good
            {
                //if found in dict, add to starting of MRU 
               
                insertinMRU(buf,&head);
                  
            }
            else
            {
                //found neither in MRU neither in dictionary, must be added to mispelt words circular list
                mislast = insert_mis(buf,mislast);
                
            }
            
        } 
    }
    else
    {
        char buf1[50]; char buf2[50];
        int i;
        for( i=0;i<pos;i++)
        {
            buf1[i]=buf[i];
        }
        buf1[pos]='\0';
        for(int j=0,i=pos;buf[i]!='\0';i++,j++)
        {
            buf2[j]=buf[i];
        }
        buf2[i]='\0';



        puts(buf1);
        puts(buf2);

        if( checkinMRU(buf1,&head)) // if word was found in MRU, then well and good since it's freq updates in this function only
        {}
        else
        {
            //if not found, must check for word in the dictionary array of sorted list

            if(checkindict(buf1,arr)) //if found in dictionary then well and good
            {
                 //if found in dict, 1>add to MRU if vacancy
                insertinMRU(buf1,&head);
            }
            else
            {
                //found neither in MRU neither in dictionary, must be added to mispelt words circular list
                 mislast = insert_mis(buf1,mislast);
               
            }
            
        }

        if( checkinMRU(buf2,&head)) // if word was found in MRU, then well and good since it's freq updates in this function only
        {}
        else
        {
            //if not found, must check for word in the dictionary array of sorted list

            if(checkindict(buf2,arr)) //if found in dictionary then well and good
            {
                 //if found in dict, 1>add to MRU 
                insertinMRU(buf2,&head);
            }
            else
            {
                //found neither in MRU neither in dictionary, must be added to mispelt words circular list
                 mislast = insert_mis(buf2,mislast);
               
            }
            
        }
    }
    } //end of while loop of extracting words from txt file

        printf("************************DICTIONARY SPELL CHECKER***************************\n");
        int choice =0;
        while(choice!=4)
        {
            printf("Enter from following choices\n1.Display Dictionary\n2.Display MRU list\n3.Display MIS list\n4.To exit\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1: displaydict(arr);
                        break;

                case 2: printf("MRu after sorting\n");
                        displayMRUsorted(head);
                        break;
                case 3: displayMIS(mislast);
                        break;
            }
        }
}
