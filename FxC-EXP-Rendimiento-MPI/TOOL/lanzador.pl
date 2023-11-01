#!/usr/bin/perl

if (@ARGV[0]) {
  $numRep = $ARGV[0];
} else {
  usage();
}

print "\n Repeticiones de la experimentación: $numRep \n\n";

$path0 = `pwd`;
chomp($path0);
$Path = $path0;
$Path =~ s/\/TOOL$//;

print "$Path \n";

@Ejecutables = ("MM1c");
@VectorSize = ("100", "200", "400", "600", "800");
$totalCores = 3;  # 1 manager + 2 workers

foreach $exe(@Ejecutables) {
  foreach $ves(@VectorSize) {
    $file = "$Path/".
      "Soluciones/".
      "$exe".
      "-Size".
      "$ves".
      "-MPI".
      "$totalCores";
    for ($i = 0; $i < $numRep; $i++) {
        system("mpirun -np $totalCores $Path/BIN/$exe $ves 0 2>> $file");
        print "Ejecutando: $Path/BIN/$exe $ves\n";
    }
  }
}

exit(1);

sub usage {
  print "\n tst.pl: Uso incorrecto\n\n";
  print "\t revisar entradas o directorio de almacenaje \n\n\n";
  exit(1);
}
