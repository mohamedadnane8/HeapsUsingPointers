// ER.c
// This is the Emergency Room management program.
// It uses a priority queue to manage patient input, (triage)
// so that all patients are noted and the most severe
// patients are treated quickly.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patientqueue.h"  

// Global time counter, is incremented after each operation.
int time = 0;

// Create a new patient record, by reading values from the keyboard.
Patient * getPatient() {
	Patient *newPatient = (Patient *) malloc ( sizeof(Patient));
	printf("Enter patient name:  ");
	gets(newPatient->name);
	printf("Enter patient ID:    ");
	scanf("%d", &newPatient->patientID);
	printf("Enter severity (1-4):");
	scanf("%d", &newPatient->severity);
	newPatient->arrivalTime = time;
	return newPatient;
	}

// Main program, reads one patient, and then processes patients until
// the queue is empty.
int main() {
	PatientQueue *theQueue = newPQ(4);
	Patient *thePatient;
	char action[2];
	int time = 0;
	
	thePatient = getPatient();
	theQueue = PQAppend(theQueue, thePatient);
	while(!PQEmpty(theQueue)){
		printf("Enter an action; 'a' for arrive, 'n' for next: ");
		scanf("%s", action);
		getchar();
		switch(action[0]) {
			case 'a': 
				if(PQFull(theQueue)) {
					printf("Too many patients!  Go somewhere else.\n");
					break;
					}
				thePatient = getPatient();
				theQueue = PQAppend(theQueue, thePatient);
				break;
			case 'n': 
				if(PQEmpty(theQueue)) {
					printf("No patients!  Take a break.\n");
					break;
					}
				thePatient = PQMaxServe(&theQueue);
				printf("Patient %s (%d, severity %d) helped after waiting %d.\n", 
					thePatient->name, thePatient->patientID, 
					thePatient->severity, time - thePatient->arrivalTime);
			}
		printf("Queue at time %d:\n", time++);
		printPQ(theQueue);
	}
}
