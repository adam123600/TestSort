#include "Sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>



#define DEBUG // warunkowa kompilacja

typedef void( *pFSort )( int*, int ); // typ wskaznikowy na funkcje sortujace

void CreateTab( int** pTab, int nSize ); // tworzeie tablicy
void RandomNumber( int* pTab, int nSize ); // zapelnianie losowymi
void PrintTab( int* pTab, int nSize ); // drukowanie tablicy
void CopyTab( int* pTabCopy, int* pTabOrginal, int nSize ); // kopiowanie tablicy
void Sort( int* pTabO, int* pTabI, pFSort sort, int nSize ); // funcja sortujaca


int main( int argc, char** argv )
{
	srand( (unsigned)time( NULL ) );

	if( argc != 2 )
	{
		printf( "Aby wlaczyc poprawnie program wpisz: TestSort.exe <rozmiar tablicy do posortowania>\n\n" );
		return 1;
	}


	int nSize = atoi( argv[1] ); // atoi- funkcja zbierajca liczbe z ciagu znakow np: "   20031a ds a s 123" bedzie: 20031

	const char* tabName[] = { "BubbleSort", "InsertionSort", "SelectionSort", "MixedSort", "HalfSort", "NaturalSort", "HeapSort" };
	pFSort tab[] = { BubbleSort, InsertionSort, SelectionSort, MixedSort, HalfSort, Sort, HeapSort };

	int* pTabOrginal = NULL;
	CreateTab( &pTabOrginal, nSize );

	RandomNumber( pTabOrginal, nSize ); // wypelnienie losowymi liczbami tablicy oryginalnej

	int* pTabCopy = NULL;
	CreateTab( &pTabCopy, nSize );


	printf( "\nSize: %d \n\n", nSize );

	int sortNo = sizeof( tab ) / sizeof( pFSort );
	for( int i = 0; i <sortNo; i++ ) // SORTOWANIA
	{
		printf( "%s\n", tabName[i] );
		Sort( pTabCopy, pTabOrginal, tab[i], nSize );
	}
		
	
	//////////////////////// MERGE SORT

		int* pTabHelp = NULL; // tablica pomocnicza do Merge
		CreateTab( &pTabHelp, nSize );
		CopyTab( pTabCopy, pTabOrginal, nSize );
		
		clock_t start1 = clock(); // start czasu

		MergeSort( pTabCopy, pTabHelp, nSize, 0, nSize - 1 );

		double time1 = (double)( clock() - start1 ) / CLOCKS_PER_SEC; // koniec czasu

		printf( "MergeSort:\n" );
		printf( "Sorted in: %.3lf\n\n", time1 );

	////////////////////////////////////////////////



	////////////////////////// QUICK SORT

		CopyTab( pTabCopy, pTabOrginal, nSize );

		clock_t start2 = clock();

		QuickSort( pTabCopy, 0, nSize - 1 );

		double time2 = (double)( clock() - start2 ) / CLOCKS_PER_SEC;

		printf( "QuickSort:\n" );
		printf( "Sorted in: %.3lf\n\n", time2 );

	////////////////////////////

		
	//	memcpy( pTabCopy, pTabOrginal, sizeof( int )* nSize );
	//	PrintTab( pTabOrginal, nSize );
	//	printf( "\n\n" );
	//	HeapSort( pTabCopy, nSize );
	//	PrintTab( pTabCopy, nSize );





#ifdef DEBUG

	printf( "-------------------------------------------------" );
	printf( "\nWARUNKOWA KOMPILACJA:\n\n" );
	
	if( nSize < 100 )
	{
		printf( "NIEPOSORTOWANE:\n" );

		for( int i = 0; i < nSize; i++ )
			printf( "%d ", pTabOrginal[i] );

		printf( "\n\nPOSORTOWANE:\n\n" );

		for( int i = 0; i < nSize; i++ )
			printf( "%d ", pTabCopy[i] );

		printf( "\n\n" );
	}


	else
	{
		printf( "NIEPOSORTOWANE:\n" );
		printf( "\nPOCZATEK:\n" );
		for( int i = 0; i < 51; i++ )
		{
			printf( "%d ", pTabOrginal[i] );
			if( !( i % 11 ) ) printf( "\n" );
		}

		printf( "\n\nKONIEC:\n" );

		for( int i = nSize - 50; i < nSize; i++ )
		{
			printf( "%d ", pTabOrginal[i] );
			if( !( i % 11 ) ) printf( "\n" );
		}

		printf( "\n\n\n\nPOSORTOWANE:\n\n" );
		printf( "POCZATEK:\n" );

		for( int i = 0; i < 51; i++ )
		{
			printf( "%d ", pTabCopy[i] );
			if( !( i % 11 ) ) printf( "\n" );
		}
		printf( "\n\n" );

		printf( "KONIEC:\n" );
		for( int i = nSize - 50; i < nSize; i++ )
		{
			printf( "%d ", pTabCopy[i] );
			if( !( i % 11 ) ) printf( "\n" );
		}
		printf( "\n\n" );
	}
	printf( "-------------------------------------------------------" );
	printf( "\n\n" );
#endif

	// Zwalnianie pamieci
	free( pTabOrginal );
	free( pTabCopy );
	free( pTabHelp );
	pTabOrginal = NULL;
	pTabCopy = NULL;
	pTabHelp = NULL;


	system("pause");
	return 0;
}


void CreateTab( int** pTab, int nSize )
{
	*pTab = (int*)malloc( sizeof( int )* nSize );
	if( !(*pTab) )
	{
		perror( "ERROR MEMORY ALLOCATION CREATE TAB\n\n" );
		return;
	}
	memset( *pTab, 0, sizeof( int )* nSize );
}

void CopyTab( int* pTabCopy, int* pTabOrginal, int nSize )
{
	memcpy( pTabCopy, pTabOrginal, sizeof( int )*nSize );
}

void PrintTab( int* pTab, int nSize )
{
	for( int i = 0; i < nSize; i++ )
		printf( "%d ", *pTab++ );
}


void RandomNumber( int* pTab, int nSize )
{
	for( int i = 0; i < nSize; i++ )
		pTab[i] = rand() % nSize;
}

void Sort( int* pTabO, int* pTabI, pFSort sort, int nSize )
{
	CopyTab( pTabO, pTabI, nSize );

	clock_t start = clock(); // start czasu

	sort( pTabO, nSize ); // sortowanie

	double time = (double)( clock() - start ) / CLOCKS_PER_SEC; // koniec czasu

	printf( "Sorted in: %.3lf\n\n", time );
}
