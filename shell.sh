#!/bin/bash

# Vérification des arguments
if [ $# -lt 2 ]; then
    echo "Usage :"
    echo "  $0 fichier.dat src|max|real"
    echo "  $0 fichier.dat leaks ID_USINE"
    exit 1
fi

INPUT=$1
MODE=$2


# Vérification fichier d'entrée
if [ ! -f "$INPUT" ]; then
    echo "Erreur : fichier $INPUT introuvable"
    exit 1
fi

#Compilation
echo "Compilation du projet..."
make
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation"
    exit 1
fi


# Exécution selon le mode
case "$MODE" in
    src)
        echo "Calcul des volumes source"
        ./wildwater "$INPUT" src histo_src.dat
        ;;
    max)
        echo "Calcul de la capacité maximale"
        ./wildwater "$INPUT" max histo_max.dat
        ;;
    real)
        echo "Calcul du volume réel"
        ./wildwater "$INPUT" real histo_real.dat
        ;;
    leaks)
        if [ $# -ne 3 ]; then
            echo "Usage : $0 fichier.dat leaks ID_USINE"
            exit 1
        fi
        ./wildwater "$INPUT" leaks "$3"
        echo "Résultat écrit dans leaks.dat"
        exit 0
        ;;
    *)
        echo "Mode inconnu : $MODE"
        exit 1
        ;;
esac

# Génération du graphique
if [ -f histo.gp ]; then
    echo "Génération du graphique avec gnuplot..."
    gnuplot histo.gp
else
    echo "Avertissement : histo.gp absent, graphique non généré"
fi

