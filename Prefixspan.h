
#include "map.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef map_t(unsigned int) uint_map_t;

typedef struct Transaction{
	unsigned int id;
	int* dataset;
}Transaction;

typedef struct Pairdata {
  Transaction* database;
  int* indeces;
}Pairdata;

typedef struct Prefix{
  unsigned int min_sup;
  unsigned int max_pat;
  int* pattern;
  bool flag;
}Prefix;

int read(struct Pairdata* pairdata,struct Prefix* prefix) {
	
	//VECTOR_INIT(pairdata->database);
	//VECTOR_INIT(pairdata->indeces);
	unsigned int id = 0;
	
	FILE *fp = fopen("data", "r");
	if(fp == NULL) {
		perror("fopen()");
		return 0;
	}
	char buff[255];	
	int lines = 0;
	char c;
	for( c = getc(fp); c != EOF; c = getc(fp)) {
		if(c == '\n')
			lines++;
	}
	fclose(fp);

 	
	//prefix.pattern = (int*)malloc(lines * sizeof(int));
	pairdata->database = (Transaction*)malloc(lines * (sizeof(struct Transaction)));
	pairdata->indeces = (int*)malloc(lines * (sizeof(int)));
	const char s[2] = " ";
	fp = fopen("data", "r");
	if(fp == NULL) {
                perror("fopen()");
                return 0;
        }
	int count2 = 0;
	for(int i = 0; i < lines; i++) {	
		int count1 = 0;	
		
		fgets(buff, 255, (FILE*)fp);
		char* token = strtok(buff, " ");
		struct Transaction transaction;
		transaction.dataset = (int*)malloc(20 * sizeof(int));
		while(token) {
			transaction.dataset[count1] = atoi(token);
			count1++;
			//printf("tokens   %d\n", atoi(token));
			token = strtok(NULL, " ");
		}
	
		transaction.id = count2;
	 	pairdata->database[count2] = transaction;			
		count2++;
		/*for(int k = 0; k < sizeof(pairdata.database[count2].dataset)/sizeof(pairdata.database[count2].dataset[0]);k++) {
			printf("size of database %d\n",pairdata.database[count2].dataset[k]);
		}*/	
	}
	fclose(fp);
	for(int i = 0; i < lines; i++) {
		pairdata->indeces[i] = 0;
	}
	for(int k = 0; k < sizeof(struct Transaction);k++) {
                        printf("size of datasssseete %d\n",pairdata->database[933].dataset[k]);
                }
	printf("size of database %ld\n",sizeof(pairdata->database)/sizeof(pairdata->indeces[0] ));

	prefix->flag = false;
	
	return lines;
}



void print_pattern(struct Prefix* prefix, struct Pairdata* projected) {

	
	for(int i = 0; i < (sizeof(prefix->pattern)/sizeof(prefix->pattern[0])); i++) {
		printf("%d first ", prefix->pattern[i]);
	}
	printf("\n(");
	for(int i = 0; i < (int)(sizeof(projected->database)/sizeof(projected->database[0]));i++) {
	  	printf("%d ",projected->database[i].id);     
	}

	printf("): \n");
}	






void project(struct Pairdata* projected,struct Prefix* prefix,int lines) {
	
	if(lines < prefix->min_sup) {
		
		printf("wtf???? %d\n",prefix->min_sup);
		return;
	}
	
	if(prefix->flag) {
		printf("11111111111\n");
		print_pattern(prefix,projected);
	}

	if(prefix->max_pat != 0 && (int)(sizeof(prefix->pattern)/sizeof(prefix->pattern[0])) == prefix->max_pat)
		return;

	prefix->flag = true;
		
	map_int_t map;
	map_init(&map);
	
	for(int i = 0; i < lines;i++){
			
		int* itemset = projected->database[i].dataset;
		
		int size1 = sizeof(struct Transaction);
	
		for(int j = projected->indeces[i]; j < size1 && itemset[j]!= 0;j++) {
			char *tmpkey;
			sprintf(tmpkey, "%d", itemset[j]);	
			const char* key = tmpkey;
			int *val = map_get(&map,key);
			if(val) {
	                	*val = *val+1;
				printf("val %d    \n",*val);
			} else {
				map_set(&map,key,1);
			}
		}
	}
	/*
	const char *key;
	map_iter_t iter = map_iter(&map);
	while((key = map_next(&map, &iter))) {
		printf("key:%s    value:%d\n", key, *map_get(&map, key));
	}
	map_deinit(&map);*/


}
/*
	printf("after map table create\n"); 



	struct Pairdata pairdata;
	vector* new_database = pairdata.database;
	vector* new_indeces = pairdata.indeces;
	for(unsigned int i = 0; i < map->size; i++) {
		for(unsigned int j = 0; j < projected->database->pfVectorTotal(projected->database); j++) {
			transaction *tran = (projected->database->pfVectorGet(projected->database,j));
			vector* itemset = tran->dataset;
			for(unsigned int k = projected->indeces->pfVectorGet(projected->indeces,j); k < itemset->pfVectorTotal(itemset);k++) {
				if(itemset->pfVectorGet(itemset,k) == map->list[i]->key) {
					new_database->pfVectorAdd(new_database,tran);
					new_indeces->pfVectorAdd(new_indeces,k+1);
					break;
				}

	
			}

		}
		prefix->pattern->pfVectorAdd(prefix->pattern,map->list[i]->key);
		project(&pairdata,&prefix);
	}

}
*/
