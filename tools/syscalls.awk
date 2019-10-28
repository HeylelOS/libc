
BEGIN {
	print ".text\n";
	FS="\t"
}

{
	print ".global " $2;
	print $2 ":";
	print "\tmov $" $1 ", %rax";
	print "\tsyscall";
	print "\tret\n"
}

