#!/usr/bin/perl

use strict;
use warnings;

my $means;
my $std;
while (my $line = <STDIN>) {
	chomp($line);
	if ($line =~ m/\(.*\)/) {
		my @values = split(' ', $line);
		if ($#values <= 0) {
			next;
		}
	
		foreach my $meanStd (@values) {
			$meanStd =~ tr/()//d;
			my @arrayMean = split(',', $meanStd);
			$means = $means . "$arrayMean[0] ";
			$std = $std . "$arrayMean[1] ";
		}
		$means = substr($means, 0, -1) . "\n";
		$std = substr($std, 0, -1)  . "\n";
	}
}

print $means;
print $std;
