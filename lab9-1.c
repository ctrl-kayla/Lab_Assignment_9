/* Kayla Butler
COP 3502 Section 3
Lab Assignment 9
11 April 2024*/
#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType record;
	int used;
};

// Compute the hash function
int hash(int x)
{
	return x % 31;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].used)
		{
			printf("Index %d -> %d, %c, %d ->", i, pHashArray[i].record.id, pHashArray[i].record.name, pHashArray[i].record.order);
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType *pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * recordSz);

	if (pHashArray == NULL)
		return -1;

	for (int i = 0; i < recordSz; i++)
	{
		pHashArray[i].used = 0;
	}

	for (int i = 0; i < recordSz; i++)
	{
		int idx = hash(pRecords[i].id);
		while (pHashArray[idx].used)
		{
			idx = (idx +1) % recordSz;
		}
		pHashArray[idx].record = pRecords[i];
		pHashArray[idx].used = 1;
	}

	displayRecordsInHash(pHashArray, recordSz);

	free(pRecords);
	free(pHashArray);

	return 0;

}