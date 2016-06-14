# Verify if exist an ssh key, if not create one.
if ! test -f ~/.ssh/id_rsa.pub && ! test -f ~/.ssh/id_rsa
	then
		ssh-keygen -N "" -q -f ~/.ssh/id_rsa
		ssh-add
fi

# Verify if exist the authorized_keys file, if not, create it.
if ! test -f ~/.ssh/authorized_keys
	then
		cat ~/.ssh/id_rsa.pub > ~/.ssh/authorized_keys
fi

count=0

# Send authorized keys for all nodes.
while read ip; do
	if test $count != 0
		then
			rsync -aq ~/.ssh/authorized_keys $ip:~/.ssh/
fi
count=$count+1

done < hosts
