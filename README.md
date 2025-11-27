# Proyecto Final de Programación Bajo Plataformas Abiertas-EI-0117
Este progrma consta de 3 modulos individuales en los que se calcular el resultado de la ley de Ohm, la potencia eléctrica y el calculo de resistores por medio de código de colores. 

## Requerimentos del programa 
Es necesario ejecutarlo en una computadora con sistema operativo Linux o MacOS. Si nunca ha utilizado las librerias gtk, es necesario que ejecute las siguientes lineas en la temrinal.

## Linux(Devian/Ubuntu)
sudo apt-get update
sudo apt-get install build-essential libgtk-4-dev pkg-config

## macOS
*Instalar Homebrew (si no lo tienes)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

*Instalar dependencias
brew install gtk4 pkg-config

## ¿Cómo compilar?
Para compilar este proyecto es muy sencillo, solamente debes  clonar este repositorio en tu computadora, a través de la terminal acceder al directorio "Proyecto-EI-0117" que ya clonaste y entrar a él mediante "cd Proyecto-EI-0117". Una vez dentro escribes en la terminal "make" y ya vas a obtener el ejecutable, que contiene un Makefile, que compila todo a través de comandos. Si el programa no genera ningun error o advertencia, el programa compila bien y por lo tanto se puede ejecutar.

## Para ejecutarlo
una vez compilo, debes ingresar le comando "ls" y se mostraran los archivos en el repositorio, ahí vas a ver uno que no posee extensión y con el nombre "calculadora-electronica". Una vez lo tienes solo basta con ejecutar "./calculadora-electronica" y se va desplegar una ventana nueva con la aplicación. 
