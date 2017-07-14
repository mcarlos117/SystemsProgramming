BEGIN{print "\n\t\t\tNews Reader Summary\n"}
BEGIN{print "\t\t lonestar \trunner \t\tringer \t\trings\n"}

BEGIN{al = 0; ar = 0; arr = 0; ars = 0 }
BEGIN{gl = 0; gr = 0; grr = 0; grs = 0 }
BEGIN{cl = 0; cr = 0; crr = 0; crs = 0 }
BEGIN{dl = 0; dr = 0; drr = 0; drs = 0 }
BEGIN{ul = 0; ur = 0; urr = 0; urs = 0 }

/lonestar.jpl.utsa.edu exit/ {al += $9}
/runner.jpl.utsa.edu exit/ {ar += $9}
/ringer.cs.utsa.edu exit/ {arr += $9}
/ring([0-9][0-9]).cs.utsa.edu exit/ {ars += $9}

/lonestar.jpl.utsa.edu exit/{gl = gl + $11}
/runner.jpl.utsa.edu exit/{gr = gr + $11}
/ringer.cs.utsa.edu exit/{grr = grr + $11}
/ring([0-9][0-9]).cs.utsa.edu exit/ {grs = grs + $11}

/lonestar.jpl.utsa.edu group utsa.cs.2413([ ]) /{cl = cl + $9}
/runner.jpl.utsa.edu group utsa.cs.2413([ ])/{cr = cr + $9}
/ringer.cs.utsa.edu group utsa.cs.2413([ ])/{crr = crr + $9}
/ring([0-9][0-9]).cs.utsa.edu group utsa.cs.2413([ ])/{crs = crs + $9}

/lonestar.jpl.utsa.edu group utsa.cs.2413.d/{dl = dl + $9}
/runner.jpl.utsa.edu group utsa.cs.2413.d/{dr = dr + $9}
/ringer.cs.utsa.edu group utsa.cs.2413.d/{drr = drr + $9}
/ring([0-9][0-9]).cs.utsa.edu group utsa.cs.2413.d/{drs = drs + $9}

/lonestar.jpl.utsa.edu times/{ul = ul + $13}
/runner.jpl.utsa.edu times/{ur = ur + $13}
/ringer.cs.utsa.edu times/{urr = urr + $13}
/ring([0-9][0-9]).cs.utsa.edu times/{urs = urs + $13}

END{print "Articles:\t" ,al "\t\t" ar "\t\t" arr "\t\t" ars}
END{print "Groups:\t\t" ,gl "\t\t" gr "\t\t" grr "\t\t" grs}
END{print "Cs2413:\t\t" ,cl "\t\t" cr "\t\t" crr "\t\t" crs}
END{print "Cs2413.d:\t",dl "\t\t" dr "\t\t" drr "\t\t" drs}
END{print "User Time:\t",ul "\t\t" ur "\t\t" urr "\t\t" urs}

NR==1{a=$1; b=$2; c=$3}
END{print"\nStart Time = " a,b,c, "\t" , "End Time =" $NR, $1, $2, $3, "\n"}
