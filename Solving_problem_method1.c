#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
int table_used=1,generated_item[2],generated=0;
char *item[]={"Engine","Chassis","Electric Supply"};
sem_t table;
void *agent(void *arg)
{
// agent thread function that has infinite number of ingredians
int i,j,k=0;
int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(count==6) exit(0);
if(table_used==1)
{
i=k;
j=i+1;
if(j==3)
j=0;
k=j;
generated_item[0]=i;
generated_item[1]=j;
printf("agent produces %s,%s\n",item[i],item[j]);
generated=1;
table_used=0;
count++;
}
sem_post(&table);

}
}
void *manufacturer(void *i)
{
//int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(table_used==0)
{
if(generated && generated_item[0]!=(int)i &&
generated_item[1]!=(int)i)
{
printf("Manufacturer%d completed his manufacturing \n",(int)i);
printf("\n");
//count++;
table_used=1;
generated=0;
}
}
sem_post(&table);
//if(count==5) exit(0);
}
}
main()
{
pthread_t manufacturer1,manufacturer2, manufacturer0,agnt;
sem_init(&table,0,1);
printf("Manufacturer0 has Engine\n");
printf("Manufacturer1 has Chasis\n");
printf("Manufacturer2 has Electric Supply\n");
pthread_create(&agnt,0,agent,0);
pthread_create(&smoker0,0,smokeri,(void*)0);
pthread_create(&smoker1,0,smokeri,(void*)1);
pthread_create(&smoker2,0,smokeri,(void*)2);
while(1);
}