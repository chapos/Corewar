# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    toaster.zsh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oevtushe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/03 11:19:01 by oevtushe          #+#    #+#              #
#    Updated: 2018/09/05 11:30:59 by oevtushe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ul="\033[4m"
fst="\033[38;5;88m"
scd="\033[38;5;124m"
trd="\033[38;5;160m"
frt="\033[38;5;196m"

function init_usr_input()
{
	loaded=()
	echo -n "Which ${fg[green]}options$reset_color would you like to use: "
	read -rA ops
	if [[ -n $ops ]]
	then
		echo "Options is: ${fg[green]}$ops$reset_color"
	fi
	echo -n "How much ${fg[green]}players$reset_color would you like to set: "
	read -r nplayers
	if (( nplayers <= 0 || nplayers > 4 ))
	then
		echo "Wrong number, ${fg[red]}terminating$reset_color ..."
		exit 3
	fi
	echo -n "File to write output of ${fg[green]}$ours_prog$reset_color: "
	read -r tmp_fours
	echo -n "File to write output of ${fg[green]}$theirs_prog$reset_color: "
	read -r tmp_ftheirs
	if [[ -n $tmp_fours ]] && [[ -n $tmp_ftheirs ]]
	then
		fours=$tmp_fours
		ftheirs=$tmp_ftheirs
	fi
	echo -n "Champ ${fg[green]}names$reset_color (${fg[cyan]}globing enabled$reset_color): "
	read -r read_from
	if [[ -z $read_from ]]
	then
		echo "This field can't be empty, ${fg[red]}try again$reset_color ."
		exit 6
	fi
	echo -n "Write ${fg[green]}diff$reset_color to: "
	read -r tmp_fdname
	if [[ -n $tmp_fdname ]]
	then
		fdname=$tmp_fdname
	fi
}

# $1 -> how much players, $2 -> cur idx
function check_it()
{
	if [[ $ours_prog_said != "" ]] || [[ $theirs_prog_said != "" ]]
	then
		echo "One of the programs or both are trying to say something !\nCheck file: $ferr"
		echo "$ours_prog_said" >> $ferr
		echo "$theirs_prog_said" >> $ferr
		exit 2
	fi
	differ=$(diff -q $ftheirs $fours)
	if [[ $differ != "" ]]
	then
		echo "Oh no ..."
		diff $ftheirs $fours > $fdname
		echo "Diff is writen to $fdname"
		echo "Would you like to open ${fg[green]}VIM$reset_color ? (y/n)"
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
		for ((i=si;i<=$arr_size;i++))
		do
			echo "$fours" > $fstate
			echo "$ftheirs" >> $fstate
			echo "$read_from" >> $fstate
			echo "$fdname" >> $fstate
			echo "$ops" >> $fstate
			echo "$i" >> $fstate
			echo "${fg[yellow]}Current files$reset_color [${fg[green]}$i$reset_color]/$arr_size: ${fst}${ul}$my_arr[$i]$reset_color"
			theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" 2>&1 1>$ftheirs)
			ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" 2>&1 1>$fours)
			check_it
		done
	elif (( $1 == 2 ))
	then
		for ((i=si;i<=$arr_size;i++))
		do
			for ((j=sj;j<=$arr_size;j++))
			do
				echo "$fours" > $fstate
				echo "$ftheirs" >> $fstate
				echo "$read_from" >> $fstate
				echo "$fdname" >> $fstate
				echo "$ops" >> $fstate
				echo "$i $j" >> $fstate
				echo "${fg[yellow]}Current files$reset_color [${fg[green]}$i $j$reset_color]/$arr_size: ${fst}${ul}$my_arr[$i]$reset_color ${scd}${ul}$my_arr[$j]$reset_color"
				theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$ftheirs)
				ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" 2>&1 1>$fours)
				check_it
			done
			sj=1
		done
	elif (( $1 == 3 ))
	then
		for ((i=si;i<=$arr_size;i++))
		do
			for ((j=sj;j<=$arr_size;j++))
			do
				for ((k=sk;k<=$arr_size;k++))
				do
					echo "$fours" > $fstate
					echo "$ftheirs" >> $fstate
					echo "$read_from" >> $fstate
					echo "$fdname" >> $fstate
					echo "$ops" >> $fstate
					echo "$i $j $k" >> $fstate
					echo "${fg[yellow]}Current files$reset_color [${fg[green]}$i $j $k$reset_color]/$arr_size: ${fst}${ul}$my_arr[$i]$reset_color ${scd}${ul}$my_arr[$j]$reset_color ${trd}${ul}$my_arr[$k]$reset_color"
					theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$ftheirs)
					ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" 2>&1 1>$fours)
					check_it
				done
				sk=1
			done
			sj=1
		done
	elif (( $1 == 4 ))
	then
		for ((i=si;i<=$arr_size;i++))
		do
			for ((j=sj;j<=$arr_size;j++))
			do
				for ((k=sk;k<=$arr_size;k++))
				do
					for ((m=sm;m<=$arr_size;m++))
					do
						echo "$fours" > $fstate
						echo "$ftheirs" >> $fstate
						echo "$read_from" >> $fstate
						echo "$fdname" >> $fstate
						echo "$ops" >> $fstate
						echo "$i $j $k $m" >> $fstate
						echo "${fg[yellow]}Current files$reset_color [${fg[green]}$i $j $k $m$reset_color]/$arr_size: ${fst}${ul}$my_arr[$i]$reset_color ${scd}${ul}$my_arr[$j]$reset_color ${trd}${ul}$my_arr[$k]$reset_color ${frt}${ul}$my_arr[$m]$reset_color"
						theirs_prog_said=$(./$theirs_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$ftheirs)
						ours_prog_said=$(./$ours_prog $ops "$my_arr[$i]" "$my_arr[$j]" "$my_arr[$k]" "$my_arr[$m]" 2>&1 1>$fours)
						check_it
					done
					sm=1
				done
				sk=1
			done
			sj=1
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

autoload colors
colors

if [[ -e $fstate ]]
then
	st=$(cat $fstate)
	mess=(${(f)st})
	fours=$mess[1]
	ftheirs=$mess[2]
	read_from=$mess[3]
	fdname=$mess[4]
	if [[ ${#mess} == 5 ]]
	then
		ppos=5
		oppos=0
	else
		oppos=5
		ppos=6
	fi
	loaded=(${(s/ /)mess[$ppos]})
	if (( ${#loaded} > 0  && ${#loaded} < 5 ))
	then
		echo "You have a file with previous toaster state.\nWould you like to start from last checkpoint [${fg[green]}$loaded$reset_color] {np=${fg[green]}${#loaded}$reset_color} {${fg[green]}$fours$reset_color,${fg[green]}$ftheirs$reset_color} (y/n)?"
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
		echo "Bad state file, ${fg[red]}terminating$reset_color."
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
my_arr=($(eval "echo $read_from"))
arr_size=${#my_arr}

echo "${fg[cyan]}Starting ...${reset_color}"
# Start here
enter_point $nplayers
echo "You are so lucky ! Everything is ${fg[green]}ok$reset_color !"
