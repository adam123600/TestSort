
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void UpdateHeap( int* pTab, int l, int r );  // pomocnicza do HeapSort
int Copy( int* pTab, int* tmp, int nSize, int* i, int* ix ); // pomocnicza do Sort ( laczenie naturalne )
void CopySerie( int* pTab, int* tmp, int nSize, int* i, int* ix ); // pomocnicza do Sort ( laczenie naturalne )
void Merge( int* pTab, int* pTabHelp, int nSize, int l, int m, int r ); // pomocnicza do MergeSort

void BubbleSort( int* pTab, int nSize ) // sortowanie b¹belkowe 
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		for( int j = nSize - 1; j > i; j-- )
		{
			if (pTab[j-1] > pTab[j] )
			{
				int tmp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = tmp;
			}
		}
	}
}

void InsertionSort( int* pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int x = pTab[i];
		int j = i - 1;
		while( ( j >= 0 ) && ( pTab[j] > x ) )
			pTab[j + 1] = pTab[j--];
		
		pTab[j + 1] = x;
	}
}


void SelectionSort( int* pTab, int nSize )
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		int min = pTab[i];
		int index = i;
		for( int j = i + 1; j < nSize; j++ )
			if( pTab[j] < min )
			{
				min = pTab[j];
				index = j;
			}

		pTab[index] = pTab[i];
		pTab[i] = min;
	}
}

void MixedSort( int* pTab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize - 1;

	while( l < p )
	{
		for( int i = p; i >= l; i-- )
			if( pTab[i - 1] > pTab[i] )
			{

				int temp = pTab[i - 1];
				pTab[i - 1] = pTab[i];
				pTab[i] = temp;
				k = i;
			}
		l = k + 1;

		for( int j = l; j <= p; j++ )
			if( pTab[j - 1] > pTab[j] )
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		p = k - 1;
	}
}


void HalfSort( int* pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int x = pTab[i];
		int l = 0;
		int r = i - 1;

		while( l <= r )
		{
			int m = ( l + r ) / 2; // srodek- middle

			if( x < pTab[m] )
				r = m - 1;
			else
				l = m + 1;
		}

		for( int j = i - 1; j >= l; j-- )
			pTab[j + 1] = pTab[j];
		pTab[l] = x;
	}

}


void MergeSort( int* pTab, int* pTabHelp, int nSize, int l, int r ) // pTab[] tablica, pTabHelp[] pomocnicza, l,p - indeksy miedzy ktorymi sortuje
{
	// sortujemy miedzy l i p;
	if( l < r )
	{
		int m = ( l + r ) / 2;
		MergeSort( pTab, pTabHelp, nSize, l, m ); // lewa
		MergeSort( pTab, pTabHelp, nSize, m + 1, r ); // prawa
		Merge( pTab, pTabHelp, nSize, l, m, r ); // laczenie 

	}
}

void Merge( int *pTab, int *pTabHelp, int nSize, int l, int m, int r )
{
	memcpy( pTabHelp, pTab, sizeof( int )*nSize ); // kopiowanie 

	int i = l; // poczatek
	int j = m + 1; // srodek ( poczatek drugiego );
	int k = l; // poczatek polaczonych w pTab;

	while( ( i <= m ) && ( j <= r) )
	{
		if( pTabHelp[i] < pTabHelp[j] )
			pTab[k++] = pTabHelp[i++];
		else
			pTab[k++] = pTabHelp[j++];
	}
	while( i <= m )
		pTab[k++] = pTabHelp[i++];

}

void UpdateHeap( int* pTab, int l, int r ) // przywrocenie warunku stogu
{
	if( l == r ) return;

	int i = l;
	int j = 2 * i + 1;
	int temp = pTab[i];

	while( j <= r )
	{
		if( j < r )
			if( pTab[j] < pTab[j + 1] ) j++;
		
		if( temp >= pTab[j] ) break;

		pTab[i] = pTab[j];
		i = j;
		j = 2 * i + 1;
	}

	pTab[i] = temp;

/*
	int v = l;

	while( true )
	{
		int left = 2 * v;
		int right = left + 1;

		if( left > r ) return;
		//v nie ma nastepnika w kopcu
		//else v ma co najmniej jednego nastepnika

		int m = left; // indeks wiekszego z potomkow

		if( left < r )
			if( pTab[left] < pTab[right] )
				m = right;

		if( pTab[m] <= pTab[v] ) break; // dla warunku stogu juz jest zachowany
		// wymiana i dalej w glab

		int x = pTab[v];
		pTab[v] = pTab[m];
		pTab[m] = x;
		v = m;
	}

	*/

}

void HeapSort( int* pTab, int nSize )
{

	for( int i = nSize / 2; i >= 0; i-- )
		UpdateHeap( pTab, i, nSize - 1 );
	

	for( int i = nSize - 1; i > 0; i-- )
	{
		int tmp = pTab[i];
		pTab[i] = pTab[0];
		pTab[0] = tmp;
		UpdateHeap( pTab, 0, i - 1 );
	}

}

void QuickSort( int* pTab, int l, int r )
{
	int i = l; // l - left
	int j = r; // r - right
	int p = pTab[( l + r ) / 2]; // p - pivot ( middle )

	do
	{
		while( pTab[i] < p ) i++;
		while( pTab[j] > p ) j--;

		if( i <= j )
		{
			int tmp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = tmp;
			i++;
			j--;
		}

	} while( i < j );

	if( l < j ) QuickSort( pTab, l, j );
	if(i < r ) QuickSort( pTab, i, r ); 
}

void Sort( int* pTab, int nSize ) // laczenie naturalne
{
	int* tmp1 = (int*)malloc( nSize * sizeof( int ) ); // do zapamietywania serii
	int* tmp2 = (int*)malloc( nSize * sizeof( int ) ); // do zapamietywania serii

	if( !tmp1 || !tmp2 )
	{
		perror( "ERROR MEMORY ALLOCATION- Sort // laczenie naturalne" );
		return;
	}
	memset( tmp1, 0, sizeof( int )*nSize );
	memset( tmp2, 0, sizeof( int )* nSize );

	int nSerie;

	do
	{
		int i = 0;
		int j = 0;
		int k = 0;

		while( i < nSize ) // nie koniec tab zrodlowej
		{
			while( ( i < nSize - 1 ) && ( pTab[i] <= pTab[i + 1] ) ) 
			// nie koniec i jezeli i-ty mniejszy od i+1 szego
				tmp1[j++] = pTab[i++];
				// kopiujemy i-ty do tmp1 ( j++ )


			if (i < nSize )
				// dokopiowanie ostatniego z serii do tmp 1 ( j++ )
				tmp1[j++] = pTab[i++];

			while( ( i < nSize - 1 ) && ( pTab[i] <= pTab[i + 1] ) )
				// kopiujemy i-ty do tmp2 ( k++ )
				tmp2[k++] = pTab[i++];


			if( i < nSize )
				// dokopiowanie ostatniego z serii do tmp2 ( k++ )
				tmp2[k++] = pTab[i++];
		}

		int nLast1 = j; // koniec serii w tmp1
		int nLast2 = k; // koniec serii w tmp2

		//laczenie i zliczenie ilosci serii
		nSerie = 0;
		j = 0;
		k = 0;
		i = 0;

		//przenoszenie danych z sortowaniem ze zbiorow pomocniczych do tablicy glownej
		while( ( j < nLast1 ) && ( k < nLast2 ) ) // nie koniec tablicy tmp1 && nie koniec tablicy tmp2
		{
			int end = 0; // koniec serii = 0, mozna bool uzyc

			while( !end ) // ! koniec serii ( oby dwie serie )
			// nie ma konca tablicy z seriami 1 lub 2 ( jak sie jedna skonczy to koniec)
			{
				if( tmp1[j] <= tmp2[k] ) // j-ty serii 1 <= k-ty serii 2
				{
					// kopiuj z serii1 do tablicy wynikowej i sprawdz czy nie koniec serii
					// funkcja ma kopiowac do tablicy wynikowej i sprawdzac czy nie koniec serii


					end = Copy( pTab, tmp1, nLast1, &i, &j );
					
					if( end ) // koniec serii 1
						// dokopiowac koniec serii2
						CopySerie( pTab, tmp2, nLast2, &i, &k );
				}
				else
				{
					end = Copy( pTab, tmp2, nLast2, &i, &k );
					
					if( end )
						CopySerie( pTab, tmp1, nLast1, &i, &j );
				}
				
			}
			nSerie++;
		}

		while( j < nLast1 )
		{
			CopySerie( pTab, tmp1, nLast1, &i, &j );
			nSerie++;
		}



	}while(nSerie>1);

	free( tmp1 );
	free( tmp2 );
	tmp1 = NULL;
	tmp2 = NULL;

}

int Copy( int* pTab, int* tmp, int nSize, int* i, int* ix )
{
	pTab[( *i )++] = tmp[( *ix )++];
	if( *ix == nSize ) return 1;

	return tmp[*ix - 1] > tmp[*ix]; 
}


void CopySerie( int* pTab, int* tmp, int nSize, int* i, int* ix )
{
	int end = 0;

	do
	{
		end = Copy( pTab, tmp, nSize, i, ix );

	} while( !end );
}