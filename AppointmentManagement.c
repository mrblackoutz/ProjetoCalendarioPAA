// AppointmentManagement.c - Implementation file for appointment management functions.

#include "AppointmentManagement.h" // Incluindo o arquivo de cabeçalho (.h) correspondente
#include <stdio.h>                 // Incluindo a biblioteca padrão para utilizar a função printf
#include <string.h>                // Incluindo a biblioteca string para utilizar a função strcspn

#define MAX_APPOINTMENTS 1000

int readAppointmentsFromFile(Appointment appointments[], int *count)
{
  FILE *fptr;
  char durationStr[10]; // String suficiente para a duração
  int success;          // Variável para verificar o sucesso de sscanf

  *count = 0; // Inicia a contagem em 0

  fptr = fopen("entrada.csv", "r");
  if (fptr == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return 0; // Retorna 0 se não conseguir abrir o arquivo
  }

  while (*count < MAX_APPOINTMENTS &&
         fscanf(fptr, "%d;%d;%d;%d;%d;%9[^;];%d;%49[^;];%99[^;];%79[^\n]\n",
                &appointments[*count].time.year,
                &appointments[*count].time.month,
                &appointments[*count].time.day,
                &appointments[*count].time.hour,
                &appointments[*count].time.minute,
                durationStr,
                &appointments[*count].priority,
                appointments[*count].name,
                appointments[*count].desc,
                appointments[*count].place) == 10)
  {

    // Corrija vírgula no durationStr
    for (int i = 0; durationStr[i] != '\0'; ++i)
    {
      if (durationStr[i] == '.')
      {
        durationStr[i] = ',';
        break;
      }
    }

    success = sscanf(durationStr, "%f", &appointments[*count].duration);
    if (success != 1)
    {
      fprintf(stderr, "Erro na leitura da duração do compromisso.\n");
      continue; // Pula este registro e tenta ler o próximo
    }

    (*count)++; // Incremento da contagem de compromissos
  }

  fclose(fptr);

  return 1; // Retorna 1 se a leitura for bem-sucedida
}

void addAppointment()
{
  FILE *fptr;
  Appointment newAppt;

  char date[11], times[6], durationStr[10];

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

  printf("Digite a duração do compromisso em horas (use , ou . como delimitador decimal): ");
  scanf("%4s", durationStr); // Lê até 9 caracteres para evitar overflow

  // Substituir ',' por '.' para padronizar como ponto flutuante
  for (int i = 0; durationStr[i] != '\0'; i++)
  {
    if (durationStr[i] == '.')
    {
      durationStr[i] = ',';
      break;
    }
  }

  // Agora converter a string formatada para float
  if (sscanf(durationStr, "%f", &newAppt.duration) != 1)
  {
    printf("Erro na leitura da duração. Tente novamente.\n");
    return; 
  }

  printf("Digite a prioridade do compromisso (1-5): ");
  scanf("%i", &newAppt.priority);

  // Exibe os dados do compromisso
  printf("\nDados do compromisso:\n");
  printf("Nome: %s\n", newAppt.name);
  printf("Descrição: %s\n", newAppt.desc);
  printf("Local: %s\n", newAppt.place);
  printf("Data: %i/%i/%i\n", newAppt.time.day, newAppt.time.month, newAppt.time.year);
  printf("Hora: %i:%i\n", newAppt.time.hour, newAppt.time.minute);
  printf("Duração: %4f horas\n", newAppt.duration);
  printf("Prioridade: %i\n", newAppt.priority);

  // Abrir arquivo no modo append(acrescentar)
  fptr = fopen("entrada.csv", "a");
  if (fptr != NULL)
  {
    // Escrevendo os dados formatados no arquivo CSV
    fprintf(fptr, "%04i;%02i;%02i;%02i;%02i;%f;%d;%s;%s;%s\n",
            newAppt.time.year,
            newAppt.time.month,
            newAppt.time.day,
            newAppt.time.hour,
            newAppt.time.minute,
            newAppt.duration,
            newAppt.priority,
            newAppt.name,
            newAppt.desc,
            newAppt.place);
    // Fechando o arquivo
    fclose(fptr);
  }
  else
  {
    printf("Não foi possível abrir o arquivo para escrita.\n");
  }
}

void removeAppointment()
{
  Appointment appointments[MAX_APPOINTMENTS];
  int count = 0, toDelete;
  FILE *fptr;

  // Ler o arquivo CSV e armazenar os dados no array
  if (!readAppointmentsFromFile(appointments, &count))
  {
    printf("Falha na leitura dos compromissos do arquivo.\n");
    return;
  }

  // Lista os compromissos com um índice numérico
  printf("Compromissos agendados:\n");
  for (int i = 0; i < count; i++)
  {
    printf("%d - %s (%04i-%02i-%02i %02i:%02i)\n",
           i + 1,
           appointments[i].name,
           appointments[i].time.year,
           appointments[i].time.month,
           appointments[i].time.day,
           appointments[i].time.hour,
           appointments[i].time.minute);
  }

  // Pede ao usuário para escolher um compromisso para excluir
  printf("Digite o número do compromisso que deseja excluir: ");
  if (scanf("%d", &toDelete) != 1 || toDelete < 1 || toDelete > count)
  {
    printf("Número inválido.\n");
    return;
  }

  // Exclui o compromisso do array
  for (int i = toDelete - 1; i < count - 1; i++)
  {
    appointments[i] = appointments[i + 1];
  }
  count--; // Decrementa a contagem dos compromissos

  // Atualiza o arquivo CSV excluindo o compromisso
  fptr = fopen("entrada.csv", "w");
  if (fptr == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(fptr, "%04i;%02i;%02i;%02i;%02i;%f;%d;%s;%s;%s\n",
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
  fclose(fptr);
  printf("Compromisso excluído com sucesso.\n");
  return;
}
