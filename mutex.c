/*
  Basic example of a Mutex.

  Shared state in multi-threading can cause issues.
  Operations are not atomic. For example, an increment will
    (i) read in value,
    (ii) incremnet,
    (iii) write result to varialbe.

  If not implemented properly, multi-threading may cause race conditions - undesirable situations
  when threads attempt to perform 2 or more operations (e.g. increment above) at the same time.

  Fortunately, Mutex (Mutual Exclusion Locks) can be used to protect data whilst a thread is
  updating its value.
  
  This program shows the differences between increment with/out mutex, causing a race condition
  in the later.

 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


void *functionC(void* input);
void *without_mutex_functionC(void* input);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;
int iterations = 10000000;
int counter_no_mutex = 0;
int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2, thread3, thread4;

   /* Create independent threads each of which will execute functionC */

   if( (rc1=pthread_create( &thread1, NULL, &functionC, 1)) )
   {
      printf("Thread creation failed: %s\n", rc1);
   } else {
     printf("Thread 1 %d\n", pthread_self());
   }

   if( (rc2=pthread_create( &thread2, NULL, &functionC, 1)) )
   {
      printf("Thread creation failed: %s\n", rc2);
   } else {
     printf("Thread 2 %d\n", pthread_self());
   }



   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);


   
   assert(counter == 2 * iterations);
   printf("After %d iterations, counter WITH mutex value %d, expect %d \n", iterations, counter, iterations * 2);
   
   printf("\n\n\n");

   if( (rc1=pthread_create( &thread3, NULL, &without_mutex_functionC, 1)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   } else {
     printf("Thread 3 %d\n", pthread_self());
   }

   if( (rc2=pthread_create( &thread4, NULL, &without_mutex_functionC, 1)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   } else {
     printf("Thread 4 %d\n", pthread_self());
   }

   pthread_join( thread3, NULL);
   pthread_join( thread4, NULL);
   
   assert(counter_no_mutex != 2 * iterations);
   printf("After %d iterations, counter WITHOUT mutex value %d, expect %d\n", iterations, counter_no_mutex, iterations * 2);


   exit(0);
}

void *functionC(void* input)
{

  for (int i=0; i < iterations; i++) {

    // notice that we lock the critical region (where state is being changed).
    pthread_mutex_lock( &mutex1 );
    counter += (int) input;
    pthread_mutex_unlock( &mutex1 );
  }


}

void *without_mutex_functionC(void* input)
{

  for (int i=0; i < iterations; i++) {
    counter_no_mutex += (int)input;
  }
    printf("Counter %d no mutex value: %d\n", pthread_self(), counter_no_mutex);
}
