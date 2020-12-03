
#include "map.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef map_t(unsigned int) uint_map_t;

typedef struct Transaction{
	int id;
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
			int y = atoi(token);
			if(y != 0) {
				transaction.dataset[count1] = y;
				count1++;
			}
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
	
	prefix->flag = false;
	
	return lines;
}



void print_pattern(struct Prefix* prefix, struct Pairdata* projected) {
	
	
	for(int i = 0; i < 20 && prefix->pattern[i] != -1; i++) {
		printf("%d ", prefix->pattern[i]);
	}
	printf("\n(");
	int count = 0;
	for(int i = 0; i < 1000;i++) {
		if(projected->database[i].id != -1) {
			count++;
	  		printf("%d ",projected->database[i].id); 
		}	
	}

	printf("): %d\n",count);
	
}	


void pattern_add(struct Prefix* prefix,int key) {	
                for(int i = 0; i < 20;i++) {
                        if(prefix->pattern[i] == -1) {
                                prefix->pattern[i] = key;
                                return;
                        }
                }
        return;
}

void pattern_delete(struct Prefix* prefix) {
	int sum = 0;
        for(int i = 0; i < 20;i++) {
               if(prefix->pattern[i] != -1) {
                        sum++;
               }
        }
	if(sum == 0) {
		return;
	} else {
		prefix->pattern[sum-1] = -1;
	}
}


void database_copy(struct Pairdata* t1, struct Transaction* t2,int iid, int lines,int val) {
	int sum = 0;
	for(int i = 0; i < lines; i++) {
		if(t1->database[i].id != -1) {
			sum++;
		}

	}

	int i = sum;
	//printf("available slot %d\n", i);
		if(t1->database[i].id == -1) {
			t1->indeces[i] = val;
			struct Transaction transaction;	
			transaction.dataset = (int*)malloc(20 * sizeof(int));
			for(int j = 0; j < 20 && t2->dataset[j] != 0;j++) {
				int tmp = t2->dataset[j];
                		transaction.dataset[j] = tmp;
			}
			transaction.id = iid;
			t1->database[i] = transaction;
			//printf("id after copy %d\n", t1->database[i].id);
	
		}
			


}


void function(struct Pairdata *pairdata, struct Pairdata *projected,int i, int lines,int y) {
                for(int j = projected->indeces[i]; j < 20 ; j++) {
                                if(projected->database[i].dataset[j] == y) {
                                       // printf("id before copy %d   value of y%d\n", projected->database[i].id,y);
                                        database_copy(pairdata,&projected->database[i],projected->database[i].id,lines,j+1);
                                        //printf("before break\n");
                                        return;

                                }
                     }
}


void project(struct Pairdata* projected,struct Prefix* prefix,int lines) {
	
	if(lines < prefix->min_sup) {
		
		printf("wtf???? %d\n",prefix->min_sup);
		return;
	}
	
	if(prefix->pattern[0] != -1) {
		//printf("11111111111\n");
		print_pattern(prefix,projected);
	}
	int sum = 0;
	for(int i = 0; i < 20; i++) {
		if(prefix->pattern[i] != -1){
			sum++;
		}
	}
	if(prefix->max_pat != 0 && sum == prefix->max_pat)
		return;

	//printf("create map\n");	
		
	map_int_t map;
	map_init(&map);
	
	for(int i = 0; i < lines;i++){
		//printf("in the first map loop %d\n",i);
		if(projected->database[i].id != -1) {	
			int* itemset1 = projected->database[i].dataset;
		
		
		int size1 = sizeof(struct Transaction);
	
		for(int j = projected->indeces[i]; j < size1 && itemset1[j]!= 0;j++) {
			
			//	printf("in the second map loop %d\n",itemset1[j]);
			
			int tmpint = itemset1[j];
			char tmpkey[9];
			sprintf(tmpkey,"%d",tmpint);
			
			//printf("copy of int %s\n", tmpkey); 
			const char* key = tmpkey;

			int *val = map_get(&map,key);
			if(val) {
	                	*val = *val+1;
				//printf("val %d    \n",*val);
			} else {
				map_set(&map,key,1);
			}
			}
		} else {
			break;
		}
	}
	struct Pairdata pairdata;
	pairdata.database = (Transaction*)malloc(lines * sizeof(Transaction));
	for(int i = 0; i < lines; i++) {
		struct Transaction tran;
		tran.id = -1;
		tran.dataset = (int*)malloc(sizeof(int) * 20);

		pairdata.database[i] = tran;
		//printf("initial id-value %d\n", pairdata.database[i].id);
	}
	pairdata.indeces = (int*)malloc(lines * sizeof(int*));
	


	const char *key1;
        map_iter_t iter1 = map_iter(&map);


        while(key1 = map_next(&map, &iter1)) {
		int y = atoi(key1);
		for(int i = 0; i < lines; i++) {
				
			if(projected->database[i].id != -1) {
				function(&pairdata,projected,i,lines,y);
			}
		}
		
		pattern_add(prefix, y);	
		project(&pairdata,prefix,lines);
		pattern_delete(prefix);
		
        	for(int i = 0; i < lines; i++) {
                struct Transaction tran;
                tran.id = -1;
                tran.dataset = (int*)malloc(sizeof(int) * 20);

                pairdata.database[i] = tran;
                //printf("initial id-value %d\n", pairdata.database[i].id);
        	}
        	pairdata.indeces = (int*)malloc(lines * sizeof(int*));
		//free(pairdata.database);
		//free(pairdata.indeces);
        }
        
	

}


/*
void pattern_add(struct Prefix* prefix,int key) {
	if(prefix->flag) {
		for(int i = 0; i < sizeof(struct Transaction);i++) {
			if(prefix->pattern[i] == -1) {
				prefix->pattern[i] = key;
				return;
			}
		}

	} else {
		prefix->flag = true;
		prefix->pattern = (int*)malloc(sizeof(struct Transaction));
		for(int i = 0; i < sizeof(struct Transaction); i++) {
			prefix->pattern[i] = -1;

		}
	}	
	return;


}

void pattern_delete(struct Prefix* prefix) {
	for(int i = 0; i < sizeof(struct Transaction);i++) {
               if(prefix->pattern[i] == -1 && i != 0) {
                        prefix->pattern[i-1] = key;
                        return;
               }
        }
}*/
