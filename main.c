#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libs/colors.h"

char command[] = "cat /proc/bus/input/devices";
void showHelp();
void unbind(char *pHandler);
bool isHandler(char *buffer, char *targetHandler);
void getAddresses(char *addressString, char *addressToChange);
void unbindAddress(char *address);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("use -h or --help for quick help");
    return EXIT_SUCCESS;
  } else if (argc > 3) {
    printf("undefined behaviour, aborting...");
    return EXIT_FAILURE;
  }
  
  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    showHelp();
    return EXIT_SUCCESS;
  } else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
    system(command);
  } else if (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--unbind") == 0) {
    unbind(argv[2]);
  }


  return EXIT_SUCCESS;
}

void unbind(char *pHandler) {
  FILE *commandOutput;
  char buffer[256];

  commandOutput = popen(command, "r");

  if (commandOutput == NULL) {
    printf("Failed to execute command");
    return;
  }

  char lastAddress[256];
  while (fgets(buffer, 255, commandOutput) != NULL) {
    if (buffer[0] == 'S') {
      redColor();
      strcpy(lastAddress, buffer);
    }
    if (buffer[0] == 'H') {
      if (isHandler(buffer, pHandler)) {
        char address[256];
        getAddresses(lastAddress, address);
        unbindAddress(address);
        return;
      }
      continue;
    }
    resetColor();
  }
  yellowColor();
  printf("Handler %s wasn't found", pHandler);
  resetColor();
}

void showHelp() {
  printf("-l, --list = list all devices\n\
-u, --unbind <Handler> = unbind device that's attached to the handler");
}

void getAddresses(char *addressString, char *addressToChange) {
  redColor();
  char *splittedAddress = strtok(addressString, "/");
  splittedAddress = strtok(NULL, "/");
  char addresses[50][256];
  int i = 0;
  printf("Please enter the index of the address you want to unbind\n");
  while (splittedAddress != NULL) {
    strcpy(addresses[i], splittedAddress);
    printf("%d: %s\n", i, splittedAddress);
    splittedAddress = strtok(NULL, "/");
    i++;
  }
  int returnIndex;
  scanf("%d", &returnIndex);
  resetColor();
  strcpy(addressToChange, addresses[returnIndex]);
}

bool isHandler(char *buffer, char *targetHandler) {
  char *handler = strtok(&buffer[12], " ");
  while (*handler != '\n') {
    if (strcmp(handler, targetHandler) == 0) {
      return true;
    } 
    handler = strtok(NULL, " ");
  }
  return false;
}

void unbindAddress(char *address) {
  printf("unbind this: %s", address);
  char echo[256] = "echo ";
  strcat(echo, address);
  strcat(echo, "> /sys/bus/hid/drivers/hid-generic/unbind");
  system(echo);
}
