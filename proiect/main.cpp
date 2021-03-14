#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void copy_vec(int a[], int b[], int N)      ///copiez vectorul a in b
{
    for (int i = 0; i<N; i++)
        b[i] = a[i];
}
bool test_egal(int a[], int b[], int N)     ///testez daca elementele lui a = b
{
    for (int i = 0; i<N; i++)
        if (a[i]!=b[i])
            return false;
    return true;
}

int maxim(int v[], int N)                   ///folosit de count si radixsort
{
    int mx = v[0];
    for (int i = 1; i<N; i++)
        if (v[i]>mx)
            mx = v[i];
    return mx;
}
void printv(int v[], int N)
{
    for (int i = 0; i<N; i++)
        cout<<v[i]<<' ';
}

void BubbleSort(int v[], int N)
{
    int ok;

    do
    {
        ok = 0;
        for (int i = 0; i < N-1; i++)
            if (v[i]>v[i+1])
                {int aux = v[i];
                 v[i] = v[i+1];
                  v[i+1] = aux;
                   ok = 1;
                }
    }
    while (ok);
}


void CountSort(int v[], int N)
{
    int i;
    int Max = maxim(v,N);
    int* c = new int[Max+1];
    for (int i = 0; i<Max+1; i++)
        c[i] = 0;
    for (i = 0; i<N; i++)
        c[v[i]]++;
    i = 0;
    for (int j = 0; j<Max+1; j++)
        for (int k = 0; k<c[j]; k++)
            v[i] = j, i++;

}


void MergeSort(int v[],int ls,int ld)
{
    if (ld > ls)
    {
        int m = (ld+ls)/2;
        MergeSort(v, ls, m);
        MergeSort(v, m+1, ld);
        int i = ls, j = m+1, id = 0;
        int* c = new int[ld-ls+1];
        while (i <= m && j <= ld)
                if (v[i] < v[j])
                    c[id++] = v[i++];
                else
                    c[id++] = v[j++];
        while (i <= m) c[id++] = v[i++];
        while (j <= ld) c[id++] = v[j++];

        id = 0;
        for (i = ls; i<=ld; i++)
            v[i] = c[id++];
        delete[] c;

    }
}

void RadixSort(int v[], int N)
{
    int bz = 16; /// 2^4
    int Max = maxim(v,N);
    for (int i = 0; Max >> 4 * i > 0; i++)
    {
        int count_v[16] = {0};
        int* auxiliar = new int[N];
        for (int j = 0; j<N; j++)
            count_v[(v[j]>>4*i)%16]++;
        for (int j = 1; j<16; j++)
            count_v[j] += count_v[j-1];
        for (int j = N-1; j >= 0; j--)
            auxiliar[count_v[(v[j]>>4*i)%16] - 1] = v[j], count_v[(v[j]>>4*i)%16]--;
        for (int j = 0; j<N; j++)
            v[j] = auxiliar[j];
        delete[] auxiliar;
    }
}


void QuickSort(int v[], int st, int dr)
{
    if (dr - st >= 2)
    {
        int x = v[st], y = v[(st+dr)/2], z = v[dr-1], i = st - 1, j=dr;

        if (y>x && y<z || y>z && y<x ) x=y;
        else if (z>x && z<y || z>y && z<x ) x=z;

        while (i<j)
        {
            do  {j--;} while (v[j] > x);
            do  {i++;} while (v[i] < x);
            if (i<j)
            {
                int aux = v[i];
                v[i] = v[j], v[j] = aux;
            }
        }
        QuickSort(v,st,j+1);
        QuickSort(v,j+1,dr);
    }
}

int main()
{
    ifstream f("teste.txt");
    int nr_teste, N, Max;
    f>>nr_teste;
    for (int test = 1; test<=nr_teste; test++)
        {
            f>>N>>Max;
            int* a = new int[N]; int* b = new int[N]; int* c = new int[N];

            srand(time(NULL));
            clock_t begin,end;
            double time_spent;

            for (int i = 0; i<N; i++)
                a[i] = (rand()*rand())%(Max+1);

            copy_vec(a,b,N);
            copy_vec(a,c,N);

///         Incepem sortarile         ///

            cout<<"\nTimpii de executare pentru testul: "<<test<<"\tN = "<<N<<" Max = "<<Max<<endl;
            cout<<"\tBubbleSort: ";
            if (N>100000)
                cout<<"test oprit (dureaza prea mult)\n";
            else
                {
                    begin = clock();
                    BubbleSort(b,N);
                    end = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    sort(c,c+N);
                    cout<<time_spent<<" secunde ";
                    if (test_egal(b,c,N))
                        cout<<"corect\n";
                    else
                        cout<<"gresit\n";

                }

///         CountSort         ///

            copy_vec(a,b,N);
            copy_vec(a,c,N);
            cout<<"\tCountSort: ";
            begin = clock();
            CountSort(b,N);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            sort(c,c+N);
            cout<<time_spent<<" secunde ";
            if (test_egal(b,c,N))
                cout<<"corect\n";
            else
                cout<<"gresit\n";

///         RadixSort         ///

            copy_vec(a,b,N);
            copy_vec(a,c,N);
            cout<<"\tRadixSort: ";
            begin = clock();
            RadixSort(b,N);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            sort(c,c+N);
            cout<<time_spent<<" secunde ";
            if (test_egal(b,c,N))
                cout<<"corect\n";
            else
                cout<<"gresit\n";

///         MergeSort         ///

            copy_vec(a,b,N);
            copy_vec(a,c,N);
            cout<<"\tMergeSort: ";
            begin = clock();
            MergeSort(b,0,N-1);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            sort(c,c+N);
            cout<<time_spent<<" secunde ";
            if (test_egal(b,c,N))
                cout<<"corect\n";
            else
                cout<<"gresit\n";

///         QuickSort         ///

            copy_vec(a,b,N);
            copy_vec(a,c,N);
            cout<<"\tQuickSort: ";
            begin = clock();
            QuickSort(b,0,N);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            sort(c,c+N);
            cout<<time_spent<<" secunde ";
            if (test_egal(b,c,N))
                cout<<"corect\n";
            else
                cout<<"gresit\n";

///         Sort STL         ///

            copy_vec(a,b,N);
            cout<<"\tSort STL: ";
            begin = clock();
            sort(b,b+N);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            sort(c,c+N);
            cout<<time_spent<<" secunde;\n";


            delete[] a; delete[] b; delete[]c;
        }

}
