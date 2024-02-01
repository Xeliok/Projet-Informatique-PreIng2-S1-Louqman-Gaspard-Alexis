#! /bin/bash

######################################################################################################################################
#-------------------------------------------------------check executable C-----------------------------------------------------------#
######################################################################################################################################


#executable_t="exect"

#if [ ! -x "$executable_t" ]; then #condition to check if C program executable exists
#	echo 'executable creation' 
#	cd traitement\t
#	make all
#	cd #executable creation
#	if [ $? -ne 0 ]; then #condition to check if compilation succeeds
#		echo 'Compilation ERROR'
#		exit
#	fi
#fi 	

#executable_s="execs"

#if [ ! -x "$executable_s" ]; then #condition to check if C program executable exists
#	echo 'executable creation' 
#	gcc -o "$executable_s" traitement/traitementS.c #executable creation
#	if [ $? -ne 0 ]; then #condition to check if compilation succeeds
#		echo 'Compilation ERROR'
#		exit
#	fi
#fi 	


######################################################################################################################################
#--------------------------------------------------check temp and images files-------------------------------------------------------#
######################################################################################################################################


dossier_temp="temp"

dossier_images="images"


if [ ! -d "$dossier_temp" ]; then #condition to check if temp file exist
	mkdir -p "$dossier_temp" #create temp file if it doesn't exist 	
elif [ "$(ls -A $dossier_temp)" ]; then #condition to check if temp file is empty
	rm -r "$dossier_temp"/* #delete data from temp file
fi

if [ ! -d "$dossier_images" ]; then #condition to check if images file exist
	mkdir -p "$dossier_images" #create images file if it doesn't exist
fi


######################################################################################################################################
#---------------------------------------------------------check string---------------------------------------------------------------#
######################################################################################################################################


start_time=$(date +%s) #takes the current date

if [ ! -f $1 ]; then #condition to check if 1st string is valid
	echo 'ERROR, 1st string is not a valid file path.'
	echo -e "\nTotal treatment time : $(( $(date +%s) - start_time )) seconds" #displays total treatment time if there is an error
	exit
fi

if [ $# -lt 2 ]; then #condition to check if at least one option is selected
	echo 'ERROR, there must be at least one option, type " -h" after the path to see the valid options.'
	echo -e "\nTotal treatment time : $(( $(date +%s) - start_time )) seconds"
	exit 
fi

for string in "${@:2}"; do #for loop starting at the 2nd string
	if [[ $string != '-h' && $string != '-d1' && $string != '-d2' && $string != '-l' && $string != '-t' && $string != '-s' ]]; then #condition to check if string is valid 
	echo 'ERROR, option does no exist.'
	echo -e "\nTotal treatment time : $(( $(date +%s) - start_time )) seconds"
	exit
fi
done 


######################################################################################################################################
#--------------------------------------------------------------HELP------------------------------------------------------------------#
######################################################################################################################################


for string in "$@"; do

	if [ $string = '-h' ]; then #condition to check if -h is used
	        echo "-d1: Drivers with the most trips."
	        echo "-d2: Drivers with the greatest distance."
	        echo "-l: The 10 longuest routes."
	        echo "-t: The 10 most traveled cities."
	        echo "-s: Routes with the highest maximum distance - the minimum distance, with their average."
	        echo -e "\nTotal treatment time : $(( $(date +%s) - start_time )) seconds"
	        exit
	fi
done


######################################################################################################################################
#-------------------------------------------------------------OPTIONS----------------------------------------------------------------#
######################################################################################################################################


for string in "$@"; do

	if [[ $string = '-s' ]]; then
		echo 's'
		cut -d';' -f1,5 $1 > traitement/s/data_s.csv
		cd traitement/s/
		chmod -R a+rwx .
		touch temp_s.csv
		make
		s_time=$(date +%s)
		./execs > temp_s.csv
		make clean
		cd ../
		gnuplot gnuplot_s.gp
		rm s/temp_s.csv
		rm s/data_s.csv
		cd ../
		mv traitement/graphique_traitement_s.png images/
		echo "treatment_s time : $(( $(date +%s) - s_time )) seconds"
		
	elif [[  $string = '-d1' ]]; then
		d1_time=$(date +%s)
		echo 'd1'
		bash traitement/traitement_d1.sh
		echo "treatment_d1 time : $(( $(date +%s) - d1_time )) seconds"
		
	elif [[  $string = '-d2' ]]; then
		d2_time=$(date +%s)
		echo 'd2'
		bash traitement/traitement_d2.sh
		echo "treatment_d2 time : $(( $(date +%s) - d2_time )) seconds"
		
	elif [[  $string = '-l' ]]; then
		l_time=$(date +%s)
		echo 'l'
		bash traitement/traitement_l.sh
		echo "treatment_l time : $(( $(date +%s) - l_time )) seconds"
		
	elif [[  $string = '-t' ]]; then
		echo 't'
		cd traitement/t/
		make all
		touch temp_t.csv
		make clean
		mv exect ../..
		cd ../..
		t_time=$(date +%s)
		./exect $1 > traitement/t/temp_t.csv
		rm exect
		cd traitement/t/
		gnuplot gnuplot_t.gp
		rm temp_t.csv
		cd ../../
		mv traitement/t/graphique_traitement_t.png images/
		echo "treatment_t time : $(( $(date +%s) - t_time )) seconds"
	fi
done


end_time=$(date +%s)

echo -e "\nTotal treatment time : $(( end_time - start_time )) seconds" #displays total treatment time
