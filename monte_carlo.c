#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
//liczba watkow
#define LICZ_WATK 30000

//wykorzystane zmienne
float arg[LICZ_WATK];
float cal=0;
float kolo=0;
float pi=0;

void *funk_watk(void *threadid)
{
  //odleglosc
  float odl=0;
  //id watku
  long int watek = (long)threadid;
  //inicjalizacja rand()
  time_t t;
  srand((unsigned) time(&t));
  //funkcja dziala tylko raz
  if(watek == 0){
    for(int i =0;i<LICZ_WATK;++i)
      {
	//zmienne losowe z przedzialu 0-1
	arg[i]=rand()%1000;
	arg[i]=arg[i]/1000;
      }
  }
  if(watek>1)
    {
      //liczenie odleglosci euklidesowej
      odl=sqrt( (arg[watek]-0.5)*(arg[watek]-0.5) + (arg[watek-1]-0.5)*(arg[watek-1]-0.5) );
      //numer pomiaru
      cal=cal+1;
      //punkt wewnatrz kola
      if(odl<=0.5)
	kolo=kolo+1;
    }
  pthread_exit(NULL);
}



int main()
{
  //wektor watkow
  pthread_t tab_watk[LICZ_WATK];
  int w;
  //tworzenie/wywolanie watkow
  for(long int i=0;i<LICZ_WATK;++i){
    w = pthread_create(&tab_watk[i], NULL, funk_watk, (void *) i);
    //blad
    if (w!=0) {
      printf("Cos poszlo nie tak :(\n");
      exit(-1);
    }
  }
  //aproksymacja
  pi=kolo/cal;
  printf("Aproksymacja pi: %f\n", pi*4);
  pthread_exit(NULL);
  return pi*4;
}
