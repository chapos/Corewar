# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    toaster.zsh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/03 11:19:01 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/03 15:48:14 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

function init_usr_input()
{
	loaded=()
	echo -n "Which options would you like to use: "
	read -rA ops
	if [[ -n $ops ]]
	then
		echo "Options is: $ops"
	fi
	echo -n "How much players would you like to set: "
	read -r nplayers
	if (( nplayers <= 0 || nplayers > 4 ))
	then
		echo "Wrong number, terminating ..."
		exit 3
	fi
}

# $1 -> how much players, $2 -> cur idx
function check_it()
{
	if [[ $ours_prog_said != "" ]] || [[ $theirs_prog_said != "" ]]
	then
		echo "One of the programs or both is trying to say something !\nCheck file: $ferr"
		echo "$ours_prog_said" >> $ferr
		echo "$theirs_prog_said" >> $ferr
		exit 2
	fi
	differ=$(diff -q $ftheirs $fours)
	if [[ $differ != "" ]]
	then
		echo "Oh fuck ..."
		diff $ftheirs $fours > $fdname
		echo "Diff is writen to $fdname"
		echo "Would you like to open VIM ? (y/n)"
		read -q -s answer
		if [[ $answer == "y" ]]
		then
			vim -O $fours $ftheirs $fdname
		fi
		echo "Continue ? (y/n)"
		answer=""
		read -q -s answer
		if [[ $answer == "n" ]]
		then
			exit 0
		fi
	else
		echo "OK !"
	fi
}

function enter_point()
{
	if (( $1 == 1 ))
	then
		for ((i=si;i<$arr_size;i++))
		do
			echo "$ops" > $fstate
			echo "$i" >> $fstate
			echo "Current files [$i]/$arr_size: $my_arr[$i]"
			theirs_prog_said=$(./$theirs_prog $ops -a "$my_arr[$i]" 2>&1 1>$ftheirs)
			ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" 2>&1 1>$fours)
			check_it
		done
	elif (( $1 == 2 ))
	then
		for ((i=si;i<$arr_size;i++))
		do
			for ((j=sj;j<$arr_size;j++))
			do
				echo "$ops" > $fstate
				echo "$i $j" >> $fstate
				echo "Current files [$i $j]/$arr_size: $my_arr[$i] $my_arr[$j]"
				theirs_prog_said=$(./$theirs_prog $ops -a "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$ftheirs)
				ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$fours)
				check_it
			done
		done
	elif (( $1 == 3 ))
	then
		for ((i=si;i<$arr_size;i++))
		do
			for ((j=sj;j<$arr_size;j++))
			do
				for ((k=sk;k<$arr_size;k++))
				do
					echo "$ops" > $fstate
					echo "$i $j $k" >> $fstate
					echo "Current files [$i $j $k]/$arr_size: $my_arr[$i] $my_arr[$j]" "$my_arr[$k]"
					theirs_prog_said=$(./$theirs_prog $ops -a "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$ftheirs)
					ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$fours)
					check_it
				done
			done
		done
	elif (( $1 == 4 ))
	then
		for ((i=si;i<$arr_size;i++))
		do
			for ((j=sj;j<$arr_size;j++))
			do
				for ((k=sk;k<$arr_size;k++))
				do
					for ((m=sm;m<$arr_size;m++))
					do
						echo "$ops" > $fstate
						echo "$i $j $k $m" >> $fstate
						echo "Current files [$i $j $k $m]/$arr_size: $my_arr[$i] $my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]"
						theirs_prog_said=$(./$theirs_prog $ops -a "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$ftheirs)
						ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$fours)
						check_it
					done
				done
			done
		done
	fi
}

ftheirs="/tmp/theirs"
fours="/tmp/ours"
ferr="toaster.err"
fdname="err.diff"
fstate="toaster_state.st"
answer=""
nplayers=1

ours_prog="corewar_ours"
theirs_prog="corewar"
ops=""

ours_prog_said=""
theirs_prog_said=""
st=""

if [[ -e $fstate ]]
then
	st=$(cat $fstate)
	mess=(${(f)st})
	if [[ ${#mess} == 1 ]]
	then
		ppos=1
		oppos=0
	else
		oppos=1
		ppos=2
	fi
	loaded=(${(s/ /)mess[$ppos]})
	if (( ${#loaded} > 0  && ${#loaded} < 5 ))
	then
		echo "You have a file with previous toaster state.\nWould you like to start from last checkpoint [$loaded] {np=${#loaded}} (y/n)?"
		read -q -s answer
		if [[ $answer == "y" ]]
		then
			nplayers=${#loaded}
			ops=(${(s/ /)mess[$oppos]})
		else
			loaded=()
			init_usr_input
		fi
	else
		echo "Bad state file, terminating."
		exit 4
	fi
else
	init_usr_input
fi

si=$(( loaded[1] ? loaded[1] : 1))
sj=$(( loaded[2] ? loaded[2] : 1))
sk=$(( loaded[3] ? loaded[3] : 1))
sm=$(( loaded[4] ? loaded[4] : 1))

nplayers=$(( nplayers ))
my_arr=(champs/**/*.cor)
arr_size=${#my_arr}

echo "Starting ..."
# Start here
enter_point $nplayers
