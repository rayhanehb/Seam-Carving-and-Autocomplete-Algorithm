#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "autocomplete.h"

void detab(char *line, double *sum){

    while (! isdigit(*line)){
        line++;
    }
    while (isdigit(*line)){
        *sum= *sum * 10 + (*line)-'0';
        line++;
    }

    }

void getword(char *line, char *word){

    while (isspace(*line)){
        line++;

    }
    while (isdigit(*line)){
        line++;
    }
    while(isspace(*line)){
        line++;
    }
    int i =0;

    while (*line!='\n'){
        word[i]=*line;
        line++;
        i++;

    }
}

int compnames(const void *pa, const void *pb){

	struct term *id1 = (struct term *)pa;
	struct term *id2 = (struct term *)pb;

	return strcmp(id1->term , id2->term);

}

int compweight(const void *p, const void *q){
    int l = ((struct term *)p)->weight;
    int r = ((struct term *)q)->weight;
    return (r - l);

}
int highest_match(struct term *terms, int nterms, char *substr){


   int low=0;
   int mid;
   int high= nterms-1;
   //printf("%d",high);
   int res=-1;
    int a =strlen(substr);
    //printf("%d",a);


   while(low <= high)
   {
        mid = (low + high) / 2;
        //char test;
        //strcpy(test,terms[mid].term);
       //printf("%d\n",mid);
        //char *check;
        //strcpy(*check,terms[mid].term);
        //int ans = strncmp(substr,terms[mid].term,a);

        if (strncmp(substr,terms[mid].term,a)<0){
            high = mid - 1;
            }

        else if (strncmp(substr,terms[mid].term,a)>0){
         low = mid + 1;
        }
        else{
          res = mid;
          low = mid+1;
       }
   }
   //printf("%s\n",terms[res].term);
   return res;

}

int lowest_match(struct term *terms, int nterms, char *substr){


   int low=0;
   int mid;
   int high= nterms-1;
   //printf("%d",high);
   int res=-1;
    int a =strlen(substr);
    //printf("%d",a);


   while(low <= high)
   {
        mid = (low + high) / 2;

        if (strncmp(substr,terms[mid].term,a)<0){
            high = mid - 1;
            }

        else if (strncmp(substr,terms[mid].term,a)>0){
         low = mid + 1;
        }
        else{
          res = mid;
          high = mid-1;
       }
   }
   //printf("%s\n",terms[res].term);
   return res;

}


void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){

    //printf("%s",terms[0].term);
    int strt = lowest_match(terms,nterms,substr);
    int end = highest_match(terms,nterms,substr);
    int length = end-strt+1;
    *answer = (struct term *)malloc(sizeof(struct term)*length);
    int k=0;

   // for (int r=0;r<nterms;r++){

    //   printf("%s %f\n",(*terms)[r].term,(*terms)[r].weight);



 //  }
    for (int i=strt;i<end+1;i++){


        (*answer)[k].weight =terms[i].weight;

        strcpy((*answer)[k].term,terms[i].term);
        k++;
    }
    qsort(*answer,length,sizeof(struct term),compweight);

    //for(int j=0;j<length;j++){
      // printf("%s, %d",(*answer)[j].term,(*answer)[j].weight);

   // }

}



void read_in_terms(struct term **terms, int *pnterms, char *filename){

    char line[200];
    FILE *fp = fopen(filename, "r");
    fgets(line, sizeof(line), fp);
    int N = atoi(line);
    //int N = sizeof(line)/sizeof(int);
    int k =0;
    *pnterms = N;
    //printf("%d\n",*pnterms);
    //printf("%d\n",N);
    *terms = (struct term *)malloc(sizeof(struct term)*N);
    for(int i = 1; i < N+1; i++){
        fgets(line, sizeof(line), fp);
        //printf("%s",line);
        int sizeline = sizeof(line)/sizeof(int);
        //printf("%s",line);
        //char wnum[100];

        double sum=0;
        char word[100]="";
        detab(&line,&sum);
        getword(&line,&word);
       // printf("%d",i);

        //printf("%f\n",sum);
        //printf("%s\n",word);


        (*terms)[i-1].weight = sum;

        strcpy((*terms)[i-1].term,word);
        k++;


        }

        qsort(*terms,N,sizeof(struct term),compnames);




//
//    for (int r=0;r<N;r++){
//
//      printf("%s %f\n",(*terms)[r].term,(*terms)[r].weight);
//
//
//
//   }

   //printf("%s",(*terms)[82641].term);
}




