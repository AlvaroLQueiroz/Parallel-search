Configuring
1. Put the IP of all PC's in the 'hosts' file. Note: The first ip in the file must be the IP of master PC.
2. Run the script "ssh_configure.ssh" for configure the ssh key in all nodes. Note: All nodes must be logged in with the same user.
3. Run the script "configure.sh" to compile, give permission and distribute the program for all nodes. This script also setting up the network with the "lamboot".

Running

To execute the program in a cluster, run
$ sh remote_run.sh <amount of nodes> <input_file> <target>
