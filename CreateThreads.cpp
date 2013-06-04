/**********************************
***********************************
Author: Pferd (RC)

Monday 03 June 2013 09:44:14 PM IST 
***********************************
**********************************/

/* This program creates multiple threads*/

#include<iostream>
#include<pthread.h>
#include <cstdlib>

using namespace std;

#define NUMBER_OF_THREADS 5

void *printMessage(void *id){

int Thread_id;
Thread_id= (int)id; // Type cast the void type to integer

cout<<"Thead id is"<<Thread_id<<endl; // Just print the thread id

pthread_exit(NULL); // Exit thread after completing the job

}

void resource(void){

cout<<"This is a resouce"<<endl;


}

int main(){

pthread_t threads[NUMBER_OF_THREADS]; // create 5 threads

int status,counter; // variables to catch the status and counter

for(counter=0;counter<NUMBER_OF_THREADS;counter++){

// For loop to create threads

cout<<"Main is creating the thread "<<counter<<endl;
status=pthread_create(&threads[counter],NULL,printMessage,(void *)counter); //pthread_create (thread, attr, start_routine, arg) 
// 1-Thread address, 2. thread attributes - NULL 3. pointer function to start thread 4. required arguments.

if(status){

// 1- error 

 cout<<"unable to create thread"<<endl;
 exit(-1);

} // end of if loop

}// end of for loop

pthread_exit(NULL); // end of thread

} // end of main
