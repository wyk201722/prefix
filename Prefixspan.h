
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
        //printf("pattern_add\n");
	if(prefix->flag) {
		
                for(int i = 0; i < sizeof(struct Transaction);i++) {
                        if(prefix->pattern[i] == -1) {
                                prefix->pattern[i] = key;
                                return;
                        }
                }

        } else {
                prefix->flag = true;
	
                prefix->pattern = (int*)malloc(sizeof(int) * 20);
                for(int i = 0; i < 20; i++) {
                       	prefix->pattern[i] = -1;

                }

        }
        return;


}

void pattern_delete(struct Prefix* prefix) {
        for(int i = 0; i < sizeof(struct Transaction);i++) {
               if(prefix->pattern[i] == -1 && i != 0) {
                        prefix->pattern[i-1] = -1;
                        return;
               }
        }
}


void database_copy(struct Pairdata* t1, struct Transaction* t2, int lines,int val) {
	//printf("in the copy\n");	
	for(int i = 0; i < lines; i++) {
		
		if(t1->database[i].id == -1) {
			t1->indeces[i] = val;
		
			//printf("number of i %d\n",i);
			struct Transaction transaction;
		
			transaction.dataset = (int*)malloc(20 * sizeof(int));
			for(int j = 0; j < sizeof(struct Transaction) && t2->dataset[j] != 0;j++) {
						
				int tmp = t2->dataset[j];

				//printf("value of tmp %d\n",tmp);
                		transaction.dataset[j] = tmp;
			}
			transaction.id = t2->id;
			t1->database[i] = transaction;
			return;

		} else {
			return;
		}
		
		
	}

}


void function(struct Pairdata *pairdata, struct Pairdata *projected,int i, int lines,int y) {
		if(projected->database[i].id == -1) {
			return;
		}
                     for(int j = projected->indeces[i]; j < sizeof(struct Transaction) && projected->database[i].dataset[j] != 0; j++) {
                                if(projected->database[i].dataset[j] == y) {
                                        //printf("before copy\n");
                                        database_copy(pairdata,&projected->database[i],lines,j+1);
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

	if(prefix->max_pat != 0 && (int)(sizeof(prefix->pattern)/sizeof(prefix->pattern[0])) == prefix->max_pat)
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

	//printf("after create map\n");
	/*const char *key;
	map_iter_t iter = map_iter(&map);
	while((key = map_next(&map, &iter))) {
		printf("key:%s    value:%d\n", key, *map_get(&map, key));
	}
	*/

	struct Pairdata pairdata;
	pairdata.database = (Transaction*)malloc(lines * sizeof(Transaction));
	for(int i = 0; i < lines; i++) {
		pairdata.database[i].id = -1;
	}
	pairdata.indeces = (int*)malloc(lines * sizeof(int*));
	


	const char *key1;
        map_iter_t iter1 = map_iter(&map);


        while(key1 = map_next(&map, &iter1)) {
		int y = atoi(key1);
		//printf("in the first while %d\n", y);
		for(int i = 0; i < lines; i++) {
				
		
			function(&pairdata,projected,i,lines,y);
			/*for(int j = projected->indeces[i]; j < sizeof(struct Transaction) && itemset[j] != 0; j++) {
			//	printf("value of itemset[j] %d\n",itemset[j]);
				if(itemset[j] == y) { 
					printf("before copy\n");
					database_copy(&pairdata,&projected->database[i],lines,j+1);
					printf("before break\n");
					return;
					
				}
			}	
	function(struct Pairdata *pairdata, struct Pairdata *projected,int i, int lines,int y) {
				for(int j = projected->indeces[i]; j < sizeof(struct Transaction) && projected->database[i].dataset[j] != 0; j++) {
				if(itemset[j] == y) {
                                        printf("before copy\n");
                                        database_copy(&pairdata,&projected->database[i],lines,j+1);
                                        printf("before break\n");
                                        return;

                                }
				}
	}*/
		}
		printf("before resurrsion\n");
		pattern_add(prefix, y);	
		project(&pairdata,prefix,lines);
		pattern_delete(prefix);
		//free(pairdata.database);
		//free(pairdata.indeces);
	//	map_deinit(&map);
               


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
