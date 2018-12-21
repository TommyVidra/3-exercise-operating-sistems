#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

int SemId; /* identifikacijski broj skupa semafora */
void SemGet(int n)
{ /* dobavi skup semafora sa ukupno n semafora */
   SemId = semget(IPC_PRIVATE, n, 0600);
   if (SemId == -1)
   {
      printf("Nema semafora!\n");
      exit(1);
   }
}
int SemSetVal(int SemNum, int SemVal)
{ /* postavi vrijednost semafora SemNum na SemVal */
   return semctl(SemId, SemNum, SETVAL, SemVal);
}
int SemOp(int SemNum, int SemOp)
{ /* obavi operaciju SemOp sa semaforom SemNum */
   struct sembuf SemBuf;
   SemBuf.sem_num = SemNum;
   SemBuf.sem_op = SemOp;
   SemBuf.sem_flg = 0;
   return semop(SemId, &SemBuf, 1);
}
void SemRemove(void)
{ /* uništi skup semafora */
   (void)semctl(SemId, 0, IPC_RMID, 0);
}

int broj_posjetitelja, broj_okretaja, broj_mjesta;

void posjeti(void)
{
	sleep(1);
	printf("cekanje na zastavicu za ulaz\n");
   SemOp(1, -1);
	sleep(1);
   printf("Usao\n");


	sleep(1);
   SemOp(4, 1);
	sleep(1);
   SemOp(2, -1);


	sleep(1);
   printf("Sisao\n");
	sleep(1);
   SemOp(3, 1);
}

void vrtu(void)
{

      int i = 1;
      while (i <= broj_mjesta)
      {
			
			sleep(1);
			SemOp(1, 1);
			 printf("Postavljen je vrtuljak\n");
	 		++i;
      }

      i = 1;
      while (i <= broj_mjesta)
      {
			sleep(1);
			SemOp(4, -1);
	 		printf("posjetitelj sjeda\n");
			 ++i;
      }

      printf("Pokrece se vrtuljak\n");
		int u;
		for(u = 0; u < 5; ++u){

				printf("| | | |");
				printf("\t\t. . . . \n");
				sleep(1);
				if(u%2 == 1){
					printf("\t^ ^ ^ ^\n");
					sleep(1);
				}
				printf("| | | |");
				printf("\t\t- - - - \n");
				sleep(1);
		}
      printf("Vrtuljak se zaustavlja\n");

      i = 1;
      while (i <= broj_mjesta)
      {
			sleep(1);
			SemOp(2, 1);
	 		printf("Postavlja se kraj\n");
	 		++i;
      }

      i = 1;
      while (i <= broj_mjesta)
      {
			sleep(1);
			SemOp(3, -1);
	 		printf("Posjetitelj silazi\n");
	 		++i;
      }
}

void Prekid(int sig){
	printf("Doslo je do prekida, unistavam semafore i izlazim\n");
	SemRemove();
	exit(0);
}

int main(int arg, char* args[])
{

   if (arg != 4)
   {
      printf("Premalo/previse vrijednosti, izlazim\n");
      exit(0);
   }

	printf ("Zapoceo je program\n");
	broj_posjetitelja = atoi(args[1]);
	broj_okretaja = atoi(args[2]);
   broj_mjesta = atoi(args[3]);
  
   sigset(SIGINT, Prekid);

	printf("Stvaram semafore: vrtuljak, kraj, sisao, sjeo\n");
	SemGet(4);
	//1. = vrtuljak, 2. = kraj, 3. = sisao, 4. = sjeo
	printf("Postavljam vrijednosti za semafore na 0\n");
	SemSetVal(1, 0);
	SemSetVal(3, 0);
	SemSetVal(2, 0);
	SemSetVal(4, 0);

   int i, j = 1;
   for (i = 1; i <= broj_okretaja; ++i){
      for (j = 1; j <= broj_posjetitelja; ++j){
			sleep(1);
	 		if(fork() == 0){

			printf("Posjetitelj\n");
	    	posjeti();
	    	exit(1);
	 		}
      }
      vrtu();
   }
   
	sleep(1);
	printf("Unistavam skup semafora\n");
	SemRemove();
   return 0;
}
