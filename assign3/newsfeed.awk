BEGIN{print "\n\t\tIncoming News Feed Summary\n"}
BEGIN{print "\t\taccepted \trejected \tcanceled"}

BEGIN{sa = 0; sr = 0; sc = 0}
BEGIN{na = 0; nr = 0; nc = 0}
BEGIN{qa = 0; qr = 0; qc = 0 }

/j swrinde/{sa+=1}
/+ swrinde/{sa+=1}
/c swrinde/{sa+=1}
/- swrinde/{sr+=1}
/c swrinde/{sc+=1}
/j news.cais.net/{na+=1}
/+ news.cais.net/{na+=1}
/c news.cais.net/{na+=1}
/- news.cais.net/{nr+=1}
/c news.cais.net/{nc+=1}
/[j]  [?]/{qa+=1}
/[+][?]/{qa+=1}
/[c] [?]/{qa+=1}
/[-] [?]/{qr+=1}
/[c] [?]/{qc+=1}

END{print "swrinde:\t" sa "\t\t" sr "\t\t" sc}
END{print "news.cais.net:\t" na "\t\t" nr "\t\t" nc}
END{print "?:\t\t" qa "\t\t" qr "\t\t" qc}
NR==1{a= $1;b= $2;c= $3}
END{print"\nStart Time = " a,b,c, "\t" , "End Time =" $NR, $1, $2, $3, "\n"}
