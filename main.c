#include <stdio.h>
#include <time.h>
#include "AppointmentManagement.h"
#include "Sorting.h"
#include <locale.h>

void drawClock()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  printf("       ,--.-----.--.\n");
  printf("       |--|-----|--|\n");
  printf("       |--|     |--|\n");
  printf("       |  |-----|  |\n");
  printf("     __|--|     |--|__\n");
  printf("    /  |  |-----|  |  \\\n");
  printf("   /   \\__|-----|__/   \\\n");
  printf("  /   ______---______   \\/\\\n");
  printf(" /   /               \\   \\/\n");
  printf("{   /                 \\   }\n");
  printf("|  {                   }  |-,\n");
  printf("|  |     %02d   :  %02d    |  | |\n", tm.tm_hour, tm.tm_min);
  printf("|  {                   }  |-'\n");
  printf("{   \\                 /   }\n");
  printf(" \\   `------___------'   /\\\n");
  printf("  \\     __|-----|__     /\\/\n");
  printf("   \\   /  |-----|  \\   /\n");
  printf("    \\  |--|     |--|  /\n");
  printf("     --|  |-----|  |--\n");
  printf("       |--|     |--|\n");
  printf("       |--|-----|--|\n");
  printf("       `--'-----`--'\n");
}

void drawMenu()
{
  printf("╔══════════════════════════════════╗\n");
  printf("║                                  ║\n");
  printf("║      AGENDA DE COMPROMISSOS      ║\n");
  printf("║                                  ║\n");
  printf("╠══════════════════════════════════╣\n");
  printf("║ 1. Adicionar compromisso         ║\n");
  printf("║ 2. Remover compromisso           ║\n");
  printf("║ 3. Ordenar por data              ║\n");
  printf("║ 4. Ordenar por data e horário    ║\n");
  printf("║ 5. Ordenar por data e prioridade ║\n");
  printf("║ 6. Ordenar por local, prioridade ║\n");
  printf("║    e duração (decrescente)       ║\n");
  printf("╚══════════════════════════════════╝\n");
}

int main(int argc, char *argv[])
{
  // Setar em Pt-BR para que as acentuações sejam exibidas corretamente
  setlocale(LC_ALL, "Portuguese.UTF-8");
  int opcao;

  // Exibindo o relógio
  drawClock();

  do
  {
    // Exibindo o menu
    drawMenu();
    printf("Escolha uma opção: ");
    // Coletando opção do usuário
    scanf("%d", &opcao);
    printf("____________________________________\n\n");

    switch (opcao)
    {
    case 1:
      addAppointment();
      break;
    case 2:
      removeAppointment();
      break;
    case 3:
      sortByDate();
      break;
    case 4:
      sortByDateTime();
      break;
    case 5:
      sortByDatePriority();
      break;
    case 6:
      sortByLocationPriorityDuration();
      break;
    case 7:
      printf("Saída do programa\n");
      break;
    default:
      printf("Opção inválida\n\n");
      break;
    }
  } while (opcao != 7);

  return 0;
}
