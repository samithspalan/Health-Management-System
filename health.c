#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient Structure
typedef struct Patient {
    int patientId;
    char name[50];
    int age;
    char gender[10];
    char medicalHistory[200];
    char diagnosis[200];
    char prescribedMedicine[100];
    int pin; // Security PIN for access
    struct Patient* next; // Pointer to next patient
} Patient;

// Appointment Structure
typedef struct Appointment {
    int appointmentId;
    int patientId;
    char date[11];
    char time[6];
    char doctor[50];
    char status[15]; // Scheduled, Cancelled, Completed
    struct Appointment* next; // Pointer to next appointment
} Appointment;

// Emergency Case Structure (Priority Queue Node)
typedef struct EmergencyCase {
    int severity; // Higher number indicates higher priority
    int patientId;
    char issue[100];
    struct EmergencyCase* next; // Pointer to next emergency case
} EmergencyCase;

// Doctor Structure
typedef struct Doctor {
    char name[50];
    char specialization[50];
    struct Doctor* next;
} Doctor;

// Global Linked Lists
Patient* patientHead = NULL;        // Head of the patient linked list
Appointment* appointmentHead = NULL; // Head of the appointment linked list
EmergencyCase* emergencyHead = NULL; // Head of the emergency priority queue
Doctor* doctorHead = NULL;          // Head of the doctor linked list

// Function Prototypes
void addPatient();
void printPatientRecords();
void addAppointment();
void handleAndPrintEmergencies();
void printPatientReceipt();
void searchPatientByName();
void viewDoctors();
void addDoctor();

// Utility Functions
Patient* findPatientById(int patientId);
void enqueueEmergency(int severity, int patientId, const char* issue);

// Function Implementations

void addPatient() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Memory allocation failed.\n");
        return;
    }
    static int patientCounter = 0;
    newPatient->patientId = ++patientCounter;
    printf("Enter patient name: ");
    scanf(" %[^\n]", newPatient->name);
    printf("Enter age: ");
    scanf("%d", &newPatient->age);
    printf("Enter gender: ");
    scanf(" %[^\n]", newPatient->gender);
    printf("Enter medical history: ");
    scanf(" %[^\n]", newPatient->medicalHistory);
    printf("Enter diagnosis: ");
    scanf(" %[^\n]", newPatient->diagnosis);
    printf("Enter prescribed medicine: ");
    scanf(" %[^\n]", newPatient->prescribedMedicine);
    printf("Set a security PIN for access: ");
    scanf("%d", &newPatient->pin);

    newPatient->next = patientHead;
    patientHead = newPatient;

    printf("Patient added successfully! Patient ID: %d\n", newPatient->patientId);
}

void printPatientRecords() {
    Patient* temp = patientHead;
    if (!temp) {
        printf("No patient records found.\n");
        return;
    }
    printf("Patient Records:\n");
    while (temp) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s\n", temp->patientId, temp->name, temp->age, temp->gender);
        temp = temp->next;
    }
}

void addAppointment() {
    Appointment* newAppointment = (Appointment*)malloc(sizeof(Appointment));
    if (!newAppointment) {
        printf("Memory allocation failed.\n");
        return;
    }
    static int appointmentCounter = 0;
    newAppointment->appointmentId = ++appointmentCounter;

    printf("Enter patient ID: ");
    scanf("%d", &newAppointment->patientId);

    Patient* patient = findPatientById(newAppointment->patientId);
    if (!patient) {
        printf("Patient ID not found.\n");
        free(newAppointment);
        return;
    }

    printf("Enter appointment date (dd/mm/yyyy): ");
    scanf(" %[^\n]", newAppointment->date);
    printf("Enter appointment time (hh:mm): ");
    scanf(" %[^\n]", newAppointment->time);
    printf("Enter doctor's name: ");
    scanf(" %[^\n]", newAppointment->doctor);
    strcpy(newAppointment->status, "Scheduled");

    newAppointment->next = appointmentHead;
    appointmentHead = newAppointment;

    printf("Appointment added successfully!\n");
}

void handleAndPrintEmergencies() {
    int choice;
    printf("\n--- Emergency Management ---\n");
    printf("1. Add Emergency Case\n");
    printf("2. View Emergency Cases\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int severity, patientId;
        char issue[100];
        printf("Enter patient ID: ");
        scanf("%d", &patientId);

        Patient* patient = findPatientById(patientId);
        if (!patient) {
            printf("Patient ID not found.\n");
            return;
        }

        printf("Enter emergency severity (1-10): ");
        scanf("%d", &severity);
        printf("Enter emergency issue: ");
        scanf(" %[^\n]", issue);

        enqueueEmergency(severity, patientId, issue);
        printf("Emergency case added to queue.\n");
    } else if (choice == 2) {
        EmergencyCase* temp = emergencyHead;
        if (!temp) {
            printf("No emergency cases.\n");
            return;
        }
        printf("Emergency Cases:\n");
        while (temp) {
            printf("Severity: %d | Patient ID: %d | Issue: %s\n", temp->severity, temp->patientId, temp->issue);
            temp = temp->next;
        }
    } else {
        printf("Invalid choice. Returning to main menu.\n");
    }
}

void enqueueEmergency(int severity, int patientId, const char* issue) {
    EmergencyCase* newCase = (EmergencyCase*)malloc(sizeof(EmergencyCase));
    if (!newCase) {
        printf("Memory allocation failed.\n");
        return;
    }
    newCase->severity = severity;
    newCase->patientId = patientId;
    strcpy(newCase->issue, issue);
    newCase->next = NULL;

    if (!emergencyHead || emergencyHead->severity < severity) {
        newCase->next = emergencyHead;
        emergencyHead = newCase;
        return;
    }

    EmergencyCase* temp = emergencyHead;
    while (temp->next && temp->next->severity >= severity) {
        temp = temp->next;
    }
    newCase->next = temp->next;
    temp->next = newCase;
}
void printPatientReceipt() {
    int patientId, pin;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);

    Patient* patient = findPatientById(patientId);
    if (!patient) {
        printf("Patient ID not found.\n");
        return;
    }

    printf("Enter PIN to access records: ");
    scanf("%d", &pin);

    if (patient->pin != pin) {
        printf("Invalid PIN. Access denied.\n");
        return;
    }

    printf("\n--- Patient Receipt ---\n");
    printf("Patient ID: %d\n", patient->patientId);
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Diagnosis: %s\n", patient->diagnosis);
    printf("Prescribed Medicine: %s\n", patient->prescribedMedicine);
    printf("Medical History: %s\n", patient->medicalHistory);
    printf("-----------------------\n");
}

void addDoctor() {
    Doctor* newDoctor = (Doctor*)malloc(sizeof(Doctor));
    if (!newDoctor) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter doctor's name: ");
    scanf(" %[^\n]", newDoctor->name);
    printf("Enter specialization: ");
    scanf(" %[^\n]", newDoctor->specialization);

    newDoctor->next = doctorHead;
    doctorHead = newDoctor;

    printf("Doctor added successfully!\n");
}

void viewDoctors() {
    Doctor* temp = doctorHead;
    if (!temp) {
        printf("No doctors available.\n");
        return;
    }
    printf("Available Doctors:\n");
    while (temp) {
        printf("Name: %s | Specialization: %s\n", temp->name, temp->specialization);
        temp = temp->next;
    }
}

void searchPatientByName() {
    char name[50];
    printf("Enter patient name: ");
    scanf(" %[^\n]", name);

    Patient* temp = patientHead;
    int found = 0;

    while (temp) {
        if (strcasecmp(temp->name, name) == 0) {
            printf("Patient ID: %d | Name: %s | Age: %d | Gender: %s\n",
                   temp->patientId, temp->name, temp->age, temp->gender);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("No patient found with the name '%s'.\n", name);
}

Patient* findPatientById(int patientId) {
    Patient* temp = patientHead;
    while (temp) {
        if (temp->patientId == patientId)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Health Management System ---\n");
        printf("1. Add Patient\n");
        printf("2. Print Patient Records\n");
        printf("3. Add Appointment\n");
        printf("4. Emergency Management\n");
        printf("5. Print Patient Receipt\n");
        printf("6. Search Patient by Name\n");
        printf("7. Add Doctor\n");
        printf("8. View Doctors\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                printPatientRecords();
                break;
            case 3:
                addAppointment();
                break;
            case 4:
                handleAndPrintEmergencies();
                break;
            case 5:
                printPatientReceipt();
                break;
            case 6:
                searchPatientByName();
                break;
            case 7:
                addDoctor();
                break;
            case 8:
                viewDoctors();
                break;
            case 9:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}