//  Hospital Beds Management System
//  Created by Saul Montes De Oca Martinez on 14/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  
 * struct patient will have all data related to patients including the bed asigned to him/her
 * struct containing bed data? probably will contain bed number and patient asigned 
 * Add more beds to system method 5 by 5
 * 
 * Requirments:
 *  Should let add more patients and asign a bed to a patient, if there arent any beds free the patient is added anyway
 *  Method to know which patient is asigned to a bed
 * 
 * Algorithm:
 * First create a patientList
 * Create bedList and asign patient-bed
 * Ask for
 * 
*/
typedef struct {
    char *firstName;
    char *lastName;
    int age;
    unsigned long phoneNumber;
    int active;
    int bedAssigned;
} patient;

typedef struct
{
    int occupied;
    int patientNumber;
} bed;

int findFreeBed(bed * beds, int totalNumberOfBeds)
{
    bed *finalBed = beds + totalNumberOfBeds;
    bed *bedIterator;
    int position = 0;

    for (bedIterator = beds; bedIterator < finalBed; ++bedIterator)
    {
        if (bedIterator->occupied == 0)
        {
            return position;
        }
        position++;
    }
    return -1;
}
void printOptions()
{
    printf("-------------------- Hospital bed management --------------------\n");
    printf("\n");
    printf("Enter a valid option:\n");
    printf("\t1) Enter new patient\n");
    printf("\t2) Discharge patient from hospital\n");
    printf("\t3) List of patients\n");
    printf("\t4) List of beds\n");
    printf("\t5) Add 5 more beds\n");
    printf("\n");
    printf("\t0) Exit\n");
}

int main(int argc, char **argv)
{
    patient * listOfPatients = (patient *) malloc(sizeof(patient));

    int totalNumberOfBeds = 10;
    bed *beds = (bed *)malloc(sizeof(bed) * totalNumberOfBeds);

    bed *finalBed;
    bed *bedIterator;
    int bedNumber;

    int freeBedPosition;
    bed * freeBed;

    int totalNumberOfPatients = 1;
    patient *formerPatient = listOfPatients;
    patient *patientIterator;
    int patientNumber;
    int bedToDischarge;

    freeBedPosition = findFreeBed(beds, totalNumberOfBeds);

    freeBed = beds + freeBedPosition;
    freeBed->occupied = 1;
    freeBed->patientNumber = totalNumberOfPatients -1;

    //Adding first patient
    listOfPatients->firstName = (char *) malloc(sizeof(char) * 20);
    listOfPatients->lastName = (char *) malloc(sizeof(char) * 30);
    strcpy(listOfPatients->firstName, "Saul");
    strcpy(listOfPatients->lastName, "Montes De Oca");
    listOfPatients->age = 22;
    listOfPatients->active = 1;
    listOfPatients->phoneNumber = 5555199023;
    listOfPatients->bedAssigned = freeBedPosition;

    // printf("First patient is: %s %s, Age: %d, phone number: %lu, Bed Assigned: %d\n",
    //     listOfPatients->firstName,
    //     listOfPatients->lastName,
    //     listOfPatients->age,
    //     listOfPatients->phoneNumber,
    //     listOfPatients->bedAssigned);

    int answer;
    do
    {
        printOptions();
        scanf("%d", &answer);

        switch (answer)
        {
            case 1:
                printf("******************** New Patient ********************\n");
                printf("\n");
                //enter patient
                totalNumberOfPatients++;
                listOfPatients = (patient *)realloc(listOfPatients, sizeof(patient) * (totalNumberOfPatients));
                formerPatient = listOfPatients + totalNumberOfPatients -1;
                formerPatient->firstName = (char *) malloc(sizeof(char) * 20);
                formerPatient->lastName = (char *) malloc(sizeof(char) * 30);

                printf("Patient's first name : ");
                scanf(" %[^\n]", formerPatient->firstName);
                // fgets(formerPatient->firstName, 20, stdin);
                

                printf("Patient's last name : ");
                scanf(" %[^\n]", formerPatient->lastName);
                // fgets(formerPatient->lastName, 30, stdin);

                printf("Patient's age : ");
                scanf(" %d", &formerPatient->age);

                printf("Patient's contact number : ");
                scanf(" %lu", &formerPatient->phoneNumber);

                formerPatient->active = 1;

                freeBedPosition = findFreeBed(beds, totalNumberOfBeds);
                if (freeBedPosition != -1)
                {
                    freeBed = beds + freeBedPosition;
                    freeBed->occupied = 1;
                    freeBed->patientNumber = totalNumberOfPatients - 1;
                    printf("Bed assigned : %d\n", freeBedPosition + 1);
                } else
                {
                    printf("There aren't any beds available. Please ingress more beds.\n");
                }
                formerPatient->bedAssigned = freeBedPosition;
                // printf("Second patient is: %s %s, Age: %d, phone number: %lu, Bed Assigned: %d\n",
                //        formerPatient->firstName,
                //        formerPatient->lastName,
                //        formerPatient->age,
                //        formerPatient->phoneNumber,
                //        formerPatient->bedAssigned);
                printf("**************************  |  ***********************\n");
                printf("\n");
                printf("\n");

                break;

            case 2:
                printf("******************** Discharge Patient ********************\n");
                printf("\n");
                finalBed = beds + totalNumberOfBeds;
                bedNumber = 1;
                printf("Number of beds: %d\n", totalNumberOfBeds);
                for (bedIterator = beds; bedIterator < finalBed; bedIterator++)
                {
                    formerPatient = listOfPatients + bedIterator->patientNumber;

                    // printf("Bed %d %d\n", bedNumber, bedIterator->occupied);
                    if (bedIterator->occupied == 1)
                    {
                        // printf("%d", bedIterator->occupied);
                        printf("Bed %d\t Occupied by patient: %s %s\n", bedNumber, formerPatient->firstName, formerPatient->lastName);
                    }
                    else
                    {
                        printf("Bed %d\t Free\n", bedNumber);
                    }
                    bedNumber++;
                }
                printf("\n");
                printf("Enter the patient's bed number which you want to discharge (Go back enter 0):\n");
                scanf("%d", &bedToDischarge);
                if (bedToDischarge != 0)
                {
                    finalBed = beds + bedToDischarge - 1;
                    if (finalBed->occupied != 1)
                    {
                        printf("\n");
                        printf("**************************  |  **************************\n");
                        printf("****************** Bed is already free  *****************\n");
                        printf("**************************  |  **************************\n");
                    }
                    else
                    {
                        //Freeing from list of patients
                        formerPatient = listOfPatients + finalBed->patientNumber;
                        formerPatient->active = 0;
                        //Freeing bed
                        finalBed->occupied = 0;
                        finalBed->patientNumber = 0;
                        printf("\n");
                        printf("**************************  |  **************************\n");
                        printf("************* Patient discharged correctly  *************\n");
                        printf("**************************  |  **************************\n");
                    }
                    
                }
                printf("\n");
                break;

            case 3:
                printf("******************** Patients List ********************\n");
                printf("\n");
                formerPatient = listOfPatients + totalNumberOfPatients;
                patientNumber = 1;
                for (patientIterator = listOfPatients; patientIterator < formerPatient; ++patientIterator)
                {
                    if (patientIterator->active == 1)
                    {
                        printf("Patient #%d\n", patientNumber);
                        printf("\tName: %s %s\n", patientIterator->firstName, patientIterator->lastName);
                        printf("\tAge: %d\n", patientIterator->age);
                        printf("\tContact number: %lu\n", patientIterator->phoneNumber);
                        if (patientIterator->bedAssigned == -1)
                        {
                            printf("\tBed not assigned\n");
                        }
                        else
                        {
                            printf("\tBed assigned: %d\n", patientIterator->bedAssigned + 1);
                        }

                        printf("\n");
                    }
                    
                    ++patientNumber;
                }
                printf("**************************  |  ***********************\n");
                printf("\n");
                printf("\n");
                break;

            case 4:
                printf("******************** Beds List ********************\n");
                printf("\n");
                finalBed = beds + totalNumberOfBeds;
                bedNumber = 1;
                printf("Number of beds: %d\n", totalNumberOfBeds);
                for (bedIterator = beds; bedIterator < finalBed; bedIterator++)
                {
                    formerPatient = listOfPatients + bedIterator->patientNumber;
                    // printf("Bed %d %d\n", bedNumber, bedIterator->occupied);
                    if (bedIterator->occupied == 1)
                    {
                        // printf("%d", bedIterator->occupied);
                        printf("Bed %d\t Occupied by patient: %s %s\n", bedNumber, formerPatient->firstName, formerPatient->lastName);
                    }
                    else
                    {
                        printf("Bed %d\t Free\n", bedNumber);
                    }
                    bedNumber++;
                }
                printf("\n");
                printf("**************************  |  ***********************\n");
                printf("\n");
                printf("\n");
                break;

            case 5:
                totalNumberOfBeds += 5;
                //reallocate memory to totalNumberOfBeds
                beds = (bed *)realloc(beds, sizeof(bed) * (totalNumberOfBeds));
                printf("**************************  |  **************************\n");
                printf("************ 5 more beds added succesfully  *************\n");
                printf("**************************  |  **************************\n");
                printf("\n");
                printf("\n");
                break;

            case 0:
                answer = 0;
                printf("**************************  |  *****************************\n");
                printf("******************** See you next time  ********************\n");
                printf("**************************  |  *****************************\n");
                printf("\n");
                break;

            default:
                printf("**************************  |  **************************\n");
                printf("************* Please enter a valid option  **************\n");
                printf("**************************  |  **************************\n");
                printf("\n");
                break;
        }
    } while (answer != 0);

    // Freeing lisOfPatients
    patient *lastPatient = listOfPatients + totalNumberOfPatients;
    for (patientIterator = listOfPatients; patientIterator < lastPatient; ++patientIterator)
    {
        free(patientIterator->firstName);
        free(patientIterator->lastName);
    }
    free(listOfPatients);
    //freeing beds
    free(beds);

    return 0;
}