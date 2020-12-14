
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
		transaction.dataset = (int*)malloc(14 * sizeof(int));
		while(token) {
			int y = atoi(token);
			if(y != 0) {
				transaction.dataset[count1] = y;
				count1++;
			}
			token = strtok(NULL, " ");
		}
		transaction.id = count2;
	 	pairdata->database[count2] = transaction;
		count2++;
	}
	fclose(fp);
	for(int i = 0; i < lines; i++) {
		pairdata->indeces[i] = 0;
	}
	prefix->flag = false;
	return lines;
}



void print_pattern(struct Prefix* prefix, struct Pairdata* projected,int lines) {
	for(int i = 0; i < 14 && prefix->pattern[i] != -1; i++) {
		printf("%d ", prefix->pattern[i]);
	}
	printf("\n(");
	int i = 0;
	for(i = 0; i < lines;i++) {
		int temp = projected->database[i].id;
		if(temp != -1) {
			printf("%d ", temp);
		} else {
			break;
		}
	}
	printf("): %d\n",i);
}


void pattern_add(struct Prefix* prefix,int key) {
                for(int i = 0; i < 14;i++) {
                        if(prefix->pattern[i] == -1) {
                                prefix->pattern[i] = key;
                                return;
                        }
                }
        return;
}

void pattern_delete(struct Prefix* prefix) {
	int sum = 0;
        for(int i = 0; i < 14;i++) {
               if(prefix->pattern[i] > 0) {
                        sum++;
               }
        }
	if(sum == 0 || sum == 1) {
		for(int i = 0; i < 14;i++) {
					 prefix->pattern[i] = -1;

		}
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
		if(t1->database[i].id == -1) {
			t1->indeces[i] = val;
			struct Transaction transaction;
			transaction.dataset = (int*)malloc(14 * sizeof(int));
			for(int j = 0; j < 14 && t2->dataset[j] != 0;j++) {
				int tmp = t2->dataset[j];
                		transaction.dataset[j] = tmp;
			}
			transaction.id = iid;
			t1->database[i] = transaction;
		}
}


void function(struct Pairdata *pairdata, struct Pairdata *projected,int i, int lines,int y) {
                for(int j = projected->indeces[i];  j+1 < 14; j++) {
                                if(projected->database[i].dataset[j] == y) {
                                        database_copy(pairdata,&projected->database[i],projected->database[i].id,lines,j+1);
                                        return;

                                }
                     }
}


void project(struct Pairdata* projected,struct Prefix* prefix,int lines) {

	int cal = 0;
	for(int i = 0; i < lines; i++) {
		if(projected->database[i].id != -1) {
			cal++;
		}
	}
	if(cal < prefix->min_sup) {
		return;
	}

	if(prefix->pattern[0] != -1) {
		print_pattern(prefix,projected,lines);
	}
	int sum = 0;
	for(int i = 0; i < 14; i++) {
		if(prefix->pattern[i] != -1){
			sum++;
		}
	}
	if(prefix->max_pat != 0 && sum == prefix->max_pat)
		return;

	map_int_t map;
	map_init(&map);

	for(int i = 0; i < lines;i++){
		//printf("in the first map loop %d\n",i);
		if(projected->database[i].id != -1) {
			int* itemset1 = projected->database[i].dataset;
			int size1 = sizeof(struct Transaction);

		for(int j = projected->indeces[i]; j < size1 && itemset1[j]!= 0;j++) {

			int tmpint = itemset1[j];
			char tmpkey[9];
			sprintf(tmpkey,"%d",tmpint);
			const char* key = tmpkey;
			int *val = map_get(&map,key);
			if(val) {
	                	*val = *val+1;
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
		tran.dataset = (int*)malloc(sizeof(int) * 14);

		pairdata.database[i] = tran;
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
            tran.dataset = (int*)malloc(sizeof(int) * 14);
            pairdata.database[i] = tran;
      }
      pairdata.indeces = (int*)malloc(lines * sizeof(int*));
      }
}
