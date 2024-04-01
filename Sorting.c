// Sorting.c - Implementation file for sorting functions related to appointment management.

#include "Sorting.h"               // Incluindo o arquivo de cabeçalho (.h) correspondente
#include "AppointmentManagement.h" // Incluindo o arquivo de cabecalho (.h) correspondente

// Implementação das funções de ordenação

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Incluído para utilizar a função strcmp

#define MAX_APPOINTMENTS 1000

// comparação por data
int compareByDate(const void *a, const void *b)
{
  const Appointment *appA = (const Appointment *)a;
  const Appointment *appB = (const Appointment *)b;

  // Comparar ano
  if (appA->time.year != appB->time.year)
  {
    return appA->time.year - appB->time.year;
  }
  // Comparar mês
  if (appA->time.month != appB->time.month)
  {
    return appA->time.month - appB->time.month;
  }
  // Comparar dia
  return appA->time.day - appB->time.day;
}

// comparação por data e hora
int compareByDateTime(const void *a, const void *b)
{
  const Appointment *appA = (const Appointment *)a;
  const Appointment *appB = (const Appointment *)b;

  // Reutiliza compareByDate
  int dateComparison = compareByDate(a, b);
  if (dateComparison != 0)
    return dateComparison;

  // Comparar hora
  if (appA->time.hour != appB->time.hour)
  {
    return appA->time.hour - appB->time.hour;
  }
  // Comparar minutos
  return appA->time.minute - appB->time.minute;
}

// comparação por data seguida de prioridade
int compareByDatePriority(const void *a, const void *b)
{
  int primary = compareByDate(a, b);
  if (primary != 0)
    return primary;

  const Appointment *appA = (const Appointment *)a;
  const Appointment *appB = (const Appointment *)b;
  // Prioridades mais altas devem vir primeiro, então subtraímos de forma inversa
  return appB->priority - appA->priority;
}

// comparação por local, prioridade e duração
int compareByLocationPriorityDuration(const void *a, const void *b)
{
  const Appointment *appA = (const Appointment *)a;
  const Appointment *appB = (const Appointment *)b;

  // Comparar local
  int placeComparison = strcmp(appA->place, appB->place);
  if (placeComparison != 0)
    return placeComparison;

  int datePriorityComparison = compareByDatePriority(a, b);
  if (datePriorityComparison != 0)
    return datePriorityComparison;

  // Comparar duração (presumivelmente, menor duração vem primeiro)
  return appA->duration - appB->duration;
}

void sortBy(Appointment *appointments, int count, int (*compar)(const void *, const void *), const char *outputFileName)
{
  qsort(appointments, count, sizeof(Appointment), compar);
  // Escrever para um arquivo CSV
  FILE *outputFile = fopen(outputFileName, "w");
  if (outputFile == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo de saída.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    // Formate e escreva cada compromisso no arquivo de saída
    fprintf(outputFile, "%d;%d;%d;%d;%d;%.1f;%d;%s;%s;%s\n",
            appointments[i].time.year,
            appointments[i].time.month,
            appointments[i].time.day,
            appointments[i].time.hour,
            appointments[i].time.minute,
            appointments[i].duration,
            appointments[i].priority,
            appointments[i].name,
            appointments[i].desc,
            appointments[i].place);
  }

  fclose(outputFile);
  // Mensagem ao usuário
  printf("Os dados foram ordenados e gravados com sucesso em '%s'.\n", outputFileName);
}

void sortByDate()
{
  Appointment appointments[MAX_APPOINTMENTS];
  int count;

  if (!readAppointmentsFromFile(appointments, &count))
  {
    printf("Erro ao ler compromissos do arquivo.\n");
    return;
  }
  sortBy(appointments, count, compareByDate, "saida.csv");
}

void sortByDateTime()
{
  Appointment appointments[MAX_APPOINTMENTS];
  int count;

  if (!readAppointmentsFromFile(appointments, &count))
  {
    printf("Erro ao ler compromissos do arquivo.\n");
    return;
  }
  sortBy(appointments, count, compareByDateTime, "saida.csv");
}

void sortByDatePriority()
{
  Appointment appointments[MAX_APPOINTMENTS];
  int count;

  if (!readAppointmentsFromFile(appointments, &count))
  {
    printf("Erro ao ler compromissos do arquivo.\n");
    return;
  }
  sortBy(appointments, count, compareByDatePriority, "saida.csv");
}

void sortByLocationPriorityDuration()
{
  Appointment appointments[MAX_APPOINTMENTS];
  int count;

  if (!readAppointmentsFromFile(appointments, &count))
  {
    printf("Erro ao ler compromissos do arquivo.\n");
    return;
  }
  sortBy(appointments, count, compareByLocationPriorityDuration, "saida.csv");
}
