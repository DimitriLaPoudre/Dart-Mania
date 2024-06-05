/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** help for my_hunter
*/

#include "../include/my.h"

static void help_2(void)
{
    my_miniprintf("\nSETTING:\n");
    my_miniprintf("    Modifie le volume de la musique et");
    my_miniprintf(" des effets sonores\n");
    my_miniprintf("    et ajuste le nombre de frame par seconde ");
    my_miniprintf("à ta guise.\n\n");
    my_miniprintf("PAUSE:\n");
    my_miniprintf("    Mets ta partie en pause en demandant ");
    my_miniprintf("à Eric (ESC ou ESPACE)\n\n");
    my_miniprintf("RACCOURCIS:\n");
    my_miniprintf("    Utilise ESPACE pour ouvrir le menu ou ");
    my_miniprintf("jouer sans avoir a cliquer\n");
    my_miniprintf("    Utilise ESC pour ouvrir le menu ou quitter");
    my_miniprintf(" sans avoir à cliquer\n\n");
}

void help(void)
{
    my_miniprintf("\n/DART MANIA\\\n");
    my_miniprintf("\nBUT DU JEU:\n");
    my_miniprintf("    Exploses le plus de ballon possible pour faire");
    my_miniprintf(" augmenter ton score !\n");
    my_miniprintf("    Attention, plus tu exploses de ballon,");
    my_miniprintf(" plus ils vont vite.\n\n");
    my_miniprintf("MODE:\n");
    my_miniprintf("    Wizard:\n");
    my_miniprintf("        Viser les ballons avec ton doigt\n");
    my_miniprintf("        et CONCENTRE TOI (clic gauche) pour les faire");
    my_miniprintf(" EXPLOSER !\n\n");
    my_miniprintf("    Dart:\n");
    my_miniprintf("        Viser les ballons avec ton doigt\n");
    my_miniprintf("        et lance ta fléchette (clic gauche) pour les ");
    my_miniprintf("faire EXPLOSER !\n");
    my_miniprintf("        Attention dans ce mode les tirs ne sont ");
    my_miniprintf(" pas instantanés,\n");
    my_miniprintf("        mais tirer à coté ne te feras pas perdre de vie\n");
    help_2();
}
