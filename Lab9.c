#include <stdio.h>
#include <stdlib.h>
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
 struct RecordType *pData;
};

// Compute the hash function
int hash(int x)
{
    return x % 10;
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
    int i, j;

    for (i = 0; i < hashSz; i++)
    {
        if (pHashArray[i].pData != NULL)
        {
            printf("Index %d:", i);
            for (j = 0; pHashArray[i].pData[j].id != -1 && j < 10; j++)
            {
                printf(" -> %d, %c, %d", pHashArray[i].pData[j].id, pHashArray[i].pData[j].name, pHashArray[i].pData[j].order);
            }
            printf("\n");
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
    int hashSize = 10;
    struct HashType *pHashArray = malloc(hashSize * sizeof(struct HashType));
    if (pHashArray == NULL)
    {
        fprintf(stderr, "Insufficient memory to create hash");
        return -1;
    }

    int i, loc;
    for (i=0; i<hashSize; ++i)
    {
        pHashArray[i].pData = NULL;
    }

    for (i=0; i<recordSz; ++i)
    {
        loc = hash(pRecords[i].id);
        if(pHashArray[loc].pData == NULL)
        {
            pHashArray[loc].pData = malloc((recordSz+1) * sizeof(struct RecordType));
            pHashArray[loc].pData[0].id = 0;
        }


    int j = 0;
    while(pHashArray[loc].pData[j].id != 0)
    {
        ++j;

    }
    pHashArray[loc].pData[j].id = pRecords[i].id;
    pHashArray[loc].pData[j].name = pRecords[i].name;
    pHashArray[loc].pData[j].order = pRecords[i].order;
}


displayRecordsInHash(hashArray, hashSz);

// free memory
for (i = 0; i < hashSz; ++i)
{
    if (hashArray[i].pData != NULL)
    {
        free(hashArray[i].pData);
    }
}
free(pData);
  return 0;

}