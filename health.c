#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    int patientId;
    char name[50];
    int age;
    char gender[10];
    char medicalHistory[200];
} Patient;

typedef struct {
    int appointmentId;
    int patientId;
    char date[11]; // Increased size to accommodate null terminator
    char time[6];  // Increased size to accommodate null terminator
    char doctor[50];
} Appointment;

void addPatient(Patient patients[], int *patientCount) {
    Patient newPatient;
    newPatient.patientId = *patientCount + 1; // Generate unique patient ID
    printf("Enter patient name: ");
    scanf(" %[^\n]", newPatient.name);
    printf("Enter age: ");
    scanf("%d", &newPatient.age);
    printf("Enter gender: ");
    scanf(" %[^\n]", newPatient.gender);
    printf("Enter medical history: ");
    scanf(" %[^\n]", newPatient.medicalHistory);

    patients[*patientCount] = newPatient;
    (*patientCount)++;
    printf("Patient added successfully! Patient ID: %d\n", newPatient.patientId);
}

void printMedicalDetails(Patient patients[], int patientCount) {
    int patientId;
    printf("Enter patient ID to view medical details: ");
    scanf("%d", &patientId);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientId == patientId) {
            printf("Medical History for %s:\n%s\n", patients[i].name, patients[i].medicalHistory);
            return;
        }
    }
    printf("Patient ID %d not found.\n", patientId);
}

void addAppointment(Appointment appointments[], int *appointmentCount, int patientId) {
    Appointment newAppointment;
    newAppointment.appointmentId = *appointmentCount + 1;
    newAppointment.patientId = patientId;
    printf("Enter appointment date (dd/mm/yyyy): ");
    scanf(" %[^\n]", newAppointment.date);
    printf("Enter appointment time (hh:mm): ");
    scanf(" %[^\n]", newAppointment.time);
    printf("Enter doctor's name: ");
    scanf(" %[^\n]", newAppointment.doctor);

    appointments[*appointmentCount] = newAppointment;
    (*appointmentCount)++;
    printf("Appointment added successfully!\n");
}

void checkNotifications(Appointment appointments[], int appointmentCount) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char currentDate[11];
    sprintf(currentDate, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int found = 0;
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].date, currentDate) == 0) {
            printf("Reminder: Appointment for patient ID %d with Dr. %s at %s today.\n",
                   appointments[i].patientId, appointments[i].doctor, appointments[i].time);
            found = 1;
        }
    }
    if (!found) {
        printf("No appointments for today.\n");
    }
}

int main() {
    Patient patients[100];
    Appointment appointments[100];
    int patientCount = 0;
    int appointmentCount = 0;
    int choice, patientId;

    while (1) {
        printf("\nHealth Management System\n");
        printf("1. Add Patient\n");
        printf("2. Print Medical Details\n");
        printf("3. Add Appointment\n");
        printf("4. Check Notifications\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                printMedicalDetails(patients, patientCount);
                break;  
            case 3:
                printf("Enter patient ID for appointment: ");
                scanf("%d", &patientId);
                addAppointment(appointments, &appointmentCount, patientId);
                break;
            case 4:
                checkNotifications(appointments, appointmentCount);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}