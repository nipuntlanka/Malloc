#include <stdio.h>
#include "mymalloc.h"
char memory[20000];
static int changeToNull = 1;
int MyMalloc(int size)
{
	if(changeToNull == 1)
	{
		int j =0;
		while(j<20000)
		{
			char *val = &memory[j];
			*val = NULL;
			j++;
		}
	}
	changeToNull = 0;
	
	if(memory[0]==NULL && (size+9)<20000)
	{
		int *next_chunk = &memory[0];//memory[0] next chunk address
		*next_chunk = 9+size;
		int *chunk_size = &memory[4];//define chunk size
		*chunk_size = size;
		memory[8] = '1';//define status
		printf("0\n");
	}
	else if((size+9)<20000)
	{
		
		int get_suite_place= search(size);
		if(get_suite_place == -1)
		{
			printf("no such a place\n");
		}
		else
		{
			printf("%d\n",get_suite_place);
		}
	}
	else
	{
		printf("cannot add\n");
	}
}

int search(int size)
{
	static int parser = 0;
    int i=0;
	while(parser+size<20000)
	{
		int *ptr_next_chunk = &memory[parser];
		int val_next_chunk = *ptr_next_chunk;//initially when parser=0 memory[0] is calling and get next chunk address
		int *ptr_size = &memory[parser+4];
		int val_size = *ptr_size;//get size
		char val_status = memory[parser+8]; //get status of chunk
		
		if(val_status == NULL && val_size>=size)
		{
			*ptr_next_chunk = parser+9+size;
			*ptr_size = size;
			memory[parser+8] = '1';
			int temp_val = parser;
			parser = val_next_chunk;
			return temp_val;
		}
		else if(val_status ==NULL && val_size == NULL && parser+size+9<20000)
		{
			*ptr_next_chunk = parser+9+size;
			*ptr_size = size;
			memory[parser+8] = '1';
			int temp_val = parser;
			parser = val_next_chunk;
			return temp_val;
		}
		else
		{
			parser = val_next_chunk;
		}
		
	}
	parser = 0;
	return -1;//no position find
}

void MyFree(int index)
{
	int *ptr_chunk_addr = &memory[index];
	int *ptr_chunk_size = &memory[index+4];
	memory[index+8] = NULL;
	printf("%d free\n",index);
}

