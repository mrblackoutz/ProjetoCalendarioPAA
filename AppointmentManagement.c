// AppointmentManagement.c - Implementation file for appointment management functions.

#include "AppointmentManagement.h" // Incluindo o arquivo de cabeçalho (.h) correspondente
#include <stdio.h> // Incluindo a biblioteca padrão para utilizar a função printf
#include <string.h> // Incluindo a biblioteca string para utilizar a função strcspn

// Implementação das funções de ordenação

void addAppointment() {
  FILE *fptr;
  Appointment newAppt;

  printf("Digite o nome do compromisso: ");
  fgets(newAppt.name, 50, stdin);
  newAppt.name[strcspn(newAppt.name, "\n")] = '\0'; // Remove o caractere de nova linha

  printf("Digite a descrição do compromisso: ");
  fgets(newAppt.desc, 100, stdin);
  newAppt.desc[strcspn(newAppt.desc, "\n")] = '\0'; // Remove o caractere de nova linha

  printf("Digite o local do compromisso: ");
  fgets(newAppt.place, 80, stdin);
  newAppt.place[strcspn(newAppt.place, "\n")] = '\0'; // Remove o caractere de nova linha

  printf("Digite a data do compromisso, neste formato exato -> '18/03/2024': ");
  while (1)
  {
    char date[11];
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0'; // Remove o caractere de nova linha

    if (sscanf(date, "%i/%i/%i", &newAppt.time.day, &newAppt.time.month, &newAppt.time.year) == 3)
    {
      break;
    }
    else
    {
      printf("Data inválida. Digite novamente no formato '18/03/2024': ");
    }
  }

  printf("Digite a hora do compromisso, neste formato exato -> '14:30': ");
  while (1)
  {
    char times[6];
    fgets(times, sizeof(times), stdin);
    times[strcspn(times, "\n")] = '\0'; // Remove o caractere de nova linha

    if (sscanf(times, "%i:%i", &newAppt.time.hour, &newAppt.time.minute) == 2)
    {
      break;
    }
    else
    {
      printf("Hora inválida. Digite novamente no formato '14:30': ");
    }
  }

  printf("Digite a duração do compromisso em minutos: ");
  scanf("%i", &newAppt.duration);

  printf("Digite a prioridade do compromisso (1-5): ");
  scanf("%i", &newAppt.priority);

  // Exibe os dados do compromisso
  printf("\nDados do compromisso:\n");
  printf("Nome: %s\n", newAppt.name);
  printf("Descrição: %s\n", newAppt.desc);
  printf("Local: %s\n", newAppt.place);
  printf("Data: %i/%i/%i\n", newAppt.time.day, newAppt.time.month, newAppt.time.year);
  printf("Hora: %i:%i\n", newAppt.time.hour, newAppt.time.minute);
  printf("Duração: %i minutos\n", newAppt.duration);
  printf("Prioridade: %i\n", newAppt.priority);

  // Abrir arquivo no modo append(acrescentar)
  fptr = fopen("entrada.csv", "a");

  // Novo compromisso
  Appointment newAppointment;

  char line[700];

  // Verificando se o arquivo está no diretório
  if(fptr != NULL) {

    // Ler conteúdo do arquivo
    while(fgets(line, 700, fptr)) {
      printf("%s", line);
    }

  // If the file does not exist
  } else {
    printf("Not able to open the file.");
  }

  // Close the file
  fclose(fptr);
}

void removeAppointment() {
    // Sua implementação aqui
    return;
}
