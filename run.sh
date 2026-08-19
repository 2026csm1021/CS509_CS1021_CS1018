#!/bin/bash

echo "======================================"
echo "     CS509 LAB ASSIGNMENTS (Buddy)"
echo "======================================"
echo "1. Lab Assignment 01"
echo "2. Lab Assignment 02"
echo "3. Lab Assignment 03"
echo "4. Exit"
echo "======================================"

read -p "Enter your choice : " choice

case $choice in

    1)
        (
            cd LAB_ASSIGNMENT_01 || exit
            ./run
        )
        ;;

    2)
        (
            cd LAB_ASSIGNMENT_02 || exit
            ./run
        )
        ;;

    3)
        (
            cd LAB_ASSIGNMENT_03 || exit
            ./Driver.exe
        )
        ;;

    4)
        echo "Exiting..."
        exit 0
        ;;

    *)
        echo "[ERROR] Invalid Choice."
        ;;
esac