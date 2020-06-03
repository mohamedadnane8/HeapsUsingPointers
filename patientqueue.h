// The prototypes for the Priority Queue of patients.
#include "patient.h"

typedef struct q PatientQueue;

PatientQueue *newPQ(int);
PatientQueue *PQAppend(PatientQueue *, Patient *);
Patient *PQMaxServe(PatientQueue **);
void printPQ(PatientQueue *);
int PQEmpty(PatientQueue *);
int PQFull(PatientQueue *);