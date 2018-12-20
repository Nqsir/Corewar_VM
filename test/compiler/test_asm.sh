#!/bin/sh

red="\e[1;31m"
green="\e[1;32m"
red="\e[1;31m"
blue="\e[1;34m"
yellow="\e[1;33m"
white="\e[1;37m"
normal="\e[1;0m"

dir_name=cor

if [ $1 ]
then
	secondes=$1
else
	secondes=0
fi

if [ $# == 2 ]
then
	shift
	args=($@)
	else
	args=($(ls ./../ressources/champs/))
fi

if [ ! -d "$dir_name" ]
then
	mkdir "$dir_name"
	printf "${white} Directory $dir_name created ! ${normal}\n"
fi

length=$((${#args[@]} - 1))
for i in $(seq 0 $length)
do
	elem=${args[i]%.*}
	echo  "<-------------------------------"
	printf "${red}"
	echo "\tTEST DE : {$elem}\n"
	printf "${green}"
	echo "**************<ASM>*************"
	echo $(./asm ../ressources/champs/$elem.s  && mv $elem.cor cor;)
	printf "${yellow}"
	echo "************<ASM_SRC>***********"
	echo "$(../ressources/asm_src ../ressources/champs/$elem.s  && mv ../ressources/champs/$elem.cor cor/$elem\src.cor;)\n"
	if [ -f "./cor/$elem.cor" ] && [ -f "./cor/${elem}src.cor" ]
	then
		printf "${red}"
	echo "************<DIFF>*************"
		echo "$(diff cor/$elem.cor cor/$elem\src.cor)"
		printf "${blue}\n"
	echo "************<CMP>**************"
		echo "$(cmp -l cor/$elem.cor cor/$elem\src.cor)"
	fi
		printf "${white}\n"
	echo "************<VALGRIND>**************"
		echo "$(valgrind ./asm ../ressources/champs/$elem.s && rm $elem.cor;)"
	printf "${normal}"
	echo "------------------------------->\n\n"
	sleep $secondes
done
