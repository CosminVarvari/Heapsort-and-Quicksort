/*Comparand numarul de operatii in algoritmul QuickSort si in algoritmul HeapSort, in cazul mediu, putem observa ca algoritmul QuickSort face mai putine operatii, iar cu cat ii dam dimensiunea mai mare,
face mai putine operatii fata de HeapSort.
Numarul de operatii dintre QuickSort in cazul mediu si QuickSort in cazul defavorabil este unul urias, numarul de operatii in cazul defavorabil va fi foarte mare fata de numarul de operatii din cazul mediu
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Profiler.h"
Profiler profiler("nume");
// demo(exemplu de vector), comentariu, G1 HEAP VS QUICK PE MEDIU SI G2 QUICK MEDIU VS WORST
int part(int v[],int mini,int maxi,int n)
{
    Operation QSort1=profiler.createOperation("QSorta", n);
    Operation QSort2=profiler.createOperation("QSorti",n);
    int piv=v[maxi];
    int i= mini-1;
    for(int j=mini;j<=maxi;j++)
    {
        QSort1.count();
        if (v[j]<piv)
        {
            QSort2.count(3);
            i++;
            int x;
            x=v[j];
            v[j]=v[i];
            v[i]=x;

        }

    }
    int x=v[maxi];
    v[maxi]=v[i+1];
    v[i+1]=x;
    QSort2.count(3);
    return (i+1);
}
int part2(int v[],int mini,int maxi)
{
    int piv=v[maxi];
    int i= mini-1;
    for(int j=mini;j<=maxi;j++)
    {

        if (v[j]<piv)
        {
            i++;
            int x;
            x=v[j];
            v[j]=v[i];
            v[i]=x;

        }

    }
    int x=v[maxi];
    v[maxi]=v[i+1];
    v[i+1]=x;
    return (i+1);
}
void QSort(int v[],int mini,int maxi,int n)
{
    if(mini < maxi)
    {
       int pw= part(v,mini,maxi,n);
        QSort(v, mini, pw - 1,n);
        QSort(v, pw + 1, maxi,n);
    }
}
void Heapify(int v[],int n1, int i,int n)
{
    Operation hs3 = profiler.createOperation("hsa", n);
    Operation hs4 = profiler.createOperation("hsi", n);
    int maxi=i;
    int l=2*i+1;
    int r=2*i+2;
    hs3.count();
     if (l < n1 )
     {
         hs3.count();
         if(v[l]>v[maxi])
         {
          hs4.count();
          maxi = l;}

     }
     hs3.count();
     if (r < n1)
     {
         hs3.count();
        if(v[r] > v[maxi])
        {
         maxi = r;
         hs4.count();
        }
     }
     hs3.count();
    if (maxi != i) {
        hs4.count(3);
        int x=v[i];
        v[i]=v[maxi];
        v[maxi]=x;
        Heapify(v, n1, maxi,n);
    }
}
void Heapsort(int v[], int n)
{
    int n1=n;
    for (int i = n/2-1; i >= 0; i--)
    {
        Heapify(v,n1,i,n);
    }
    for (int i = n - 1; i > 0; i--) {
        int x=v[0];
        v[0]=v[i];
        v[i]=x;
        Heapify(v ,i, 0,n);
    }

}

int QuickSelect(int v[],int mini,int maxi,int i)
{
        int p=part2(v,mini,maxi);
        if(p-mini==i-1)
            return v[p];
        if(p-mini > i-1)
            return QuickSelect(v,mini,p-1,i);
        return QuickSelect(v,p+1,maxi,i-p+mini-1);
    return 0;

}
void Afis(int v[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

int main()
{
  int v[10001],n;
  //DEMO

  n=15;
  FillRandomArray(v,n,1,100,false,0);
  printf("QuickSort\n");
  QSort(v,0,n-1,n);
  Afis(v,n);
  printf("HeapSort\n");
  FillRandomArray(v,n,1,100,false,0);
  Heapsort(v,n);
  Afis(v,n);
  printf("QuickSelect\n");
  FillRandomArray(v,n,1,100,false,0);
  Afis(v,n);
  printf("%d",QuickSelect(v,0,n-1,5));


    for(int n=100;n<=100;n=n+100)
        for(int t=1;t<=5;t++)
        {
            FillRandomArray(v,n,0,10000,false,0);
            Heapsort(v,n);
            FillRandomArray(v,n,0,10000,false,0);
            QSort(v,0,n-1,n);
        }
    profiler.divideValues("QSorta",5);
    profiler.divideValues("QSorti",5);
    profiler.divideValues("hsa",5);
    profiler.divideValues("hsi",5);
    profiler.addSeries("SumaQuickSortMediu","QSorta","QSorti");
    profiler.addSeries("SumaHeapSortMediu","hsi","hsa");
    profiler.createGroup("QuickSort vs HeapSort mediu","SumaQuickSortMediu","SumaHeapSortMediu");
    for(int n=100;n<=100;n=n+100)
        for(int t=1;t<=5;t++)
        {
         FillRandomArray(v,n,0,10000,false,1);
            QSort(v,0,n-1,n);
        }
    profiler.divideValues("QSorta",5);
    profiler.divideValues("QSorti",5);
    profiler.addSeries("SumaQuickSortWorst","QSorta","QSorti");
    profiler.createGroup("QuickWvsM","SumaQuickSortMediu","SumaQuickSortWorst");
    profiler.showReport();
}
