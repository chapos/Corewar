#for name in champs/**/*.cor
#do
#	echo "Current file: $name"
#	./corewar -v 31 -a $name > /tmp/origin
#	./corewar_ours -v 31 $name > /tmp/ours
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
		for name3 in champs/**/*.cor
		do
			echo "Current files: $name1 $name2 $name3"
			./corewar -v 31 -a $name1 $name2 $name3 > /tmp/origin
			./corewar_ours -v 31 $name1 $name2 $name3 > /tmp/ours
			differ=$(diff -q /tmp/origin /tmp/ours)
			if [[ $differ != "" ]]
			then
				echo "Oh fuck ..."
				exit 1
			else
				echo "OK !"
			fi
		done
	done
done
