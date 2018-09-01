#for name in champs/**/*.cor
#do
#	echo "Current file: $name"
#	./corewar -v 31 -a $name > origin
#	./corewar_ours -v 31 $name > ours
#	differ=$(diff -q origin ours)
#	if [[ $differ != "" ]]
#	then
#		echo "Oh fuck ..."
#		exit 1
#	else
#		echo "OK !"
#	fi
#done

for name1 in champs/**/*.cor
do
	for name2 in champs/**/*.cor
	do
		echo "Current files: $name1 $name2"
		./corewar -v 31 -a $name1 $name2 > origin
		./corewar_ours -v 31 $name1 $name2 > ours
		differ=$(diff -q origin ours)
		if [[ $differ != "" ]]
		then
			echo "Oh fuck ..."
			exit 1
		else
			echo "OK !"
		fi
	done
done
