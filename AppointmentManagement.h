// AppointmentManagement.h - Header file for appointment management functions.

#ifndef APPOINTMENT_MANAGEMENT_H
#define APPOINTMENT_MANAGEMENT_H

// Define struct for Appointment
typedef struct Time {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} Time;

typedef struct Appointment {
  Time time;
  float duration;
  int priority;
  char name[50];
  char desc[100];
  char place[80];
} Appointment;

// Function prototypes for managing appointments.

/**
 * Adds a new appointment to the schedule.
 */
void addAppointment();

/**
 * Removes an existing appointment from the schedule.
 */
void removeAppointment();

/**
 * Displays all appointments in the schedule.
 */
int readAppointmentsFromFile(Appointment appointments[], int *count)

#endif // APPOINTMENT_MANAGEMENT_H
