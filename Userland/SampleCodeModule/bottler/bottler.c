// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "bottler.h"

void bottler(int argc, char **argv) {
    printStringLen("                                                                             ", 80);
    newline();
    printStringLen("                                   (%(                                     ", 80);
    newline();
    printStringLen("      Welcome to", 17);
    printStringLen("                  %%%%%                                      ", 80);
    newline();
    printStringLen("        BottlerOS", 18);
    printStringLen("                  %%%                                      ", 80);
    newline();
    printStringLen("                              %%%%%%%%%%%%%                                 ", 80);
    newline();
    printStringLen("                          %%%%%%%%%%%%%%%%%%%%%                             ", 80);
    newline();
    printStringLen("                        %%%%%%%           %%%%%%%                           ", 80);
    newline();
    printStringLen("                      %%%%%                   %%%%%                         ", 80);
    newline();
    printStringLen("                     %%%%%                     %%%%%                        ", 80);
    newline();
    printStringLen("                    %%%%% ", 27);
    printStringLen(" %%%%           %%%% ", 22);
    printStringLen(" %%%%%                       ", 30);
    newline();
    printStringLen("                    %%%%%  ", 28);
    printStringLen(" (%             %(  ", 21);
    printStringLen(" %%%%%                       ", 30);
    newline();
    printStringLen("                    %%%%%%%                   %%%%%%%                       ", 80);
    newline();
    printStringLen("                    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                       ", 80);
    newline();
    printStringLen("                 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                    ", 80);
    newline();
    printStringLen("                %%%%%%%%%%%%%%%%%%%%%%% ", 41);
    printStringLen(" %  %* ", 8);
    printStringLen(" %%%%%%%%%                   ", 30);
    newline();
    printStringLen("                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                   ", 80);
    newline();
    printStringLen("                %%**%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/%%                   ", 80);
    newline();
    printStringLen("                %%* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% /%%                   ", 80);
    newline();
    printStringLen("                %%* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% /%%                   ", 80);
    newline();
    printStringLen("                %%%  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%%                   ", 80);
    newline();
    printStringLen("              ,%%%%%   %%%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%.                 ", 80);
    newline();
    printStringLen("                %%.         %%%%%%%%%%%%%%%%%         .%%                   ", 80);
    newline();
    printStringLen("                              %%%%%%%%%%%%%                                 ", 80);
    newline();
    printStringLen("                                 %%%%%%%                                    ", 80);
    newline();
    printStringLen("                                                                            ", 80);
    newline();
    sys_sleep(3);

    winClear();
    sys_exit();
}