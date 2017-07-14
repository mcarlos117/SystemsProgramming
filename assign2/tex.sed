s/\\/\\verb+\\+/g
s/\%/\\%/g
s/\^/\\^/g
s/--/-\\hspace{.01cm}-/g
1s/^/\\documentstyle[11pt]{article}\n\\begin{document}\n\\\begin{center} {\\bf\n/
$a\\\end{description}\n\\end{document}
1a\\} \\end{center}\n\\begin{description}

s/NAME/\\item[NAME] \\hfill \\\\/
s/OPTIONS/\\item[OPTIONS] \\hfill \\\\/
s/SEE ALSO/\\item[SEE ALSO] \\hfill \\\\/
s/TESTS/\\item[TESTS] \\hfill \\\\/
s/ACTIONS/\\item[ACTIONS] \\hfill \\\\/
s/SYNOPSIS/\\item[SYNOPSIS] \\hfill \\\\/
s/DESCRIPTION/\\item[DESCRIPTION] \\hfill \\\\/
s/STANDARDS/\\item[STANDARDS] \\hfill \\\\/
s/OPERATORS/\\item[OPERATORS] \\hfill \\\\/
s/EXPRESSIONS/\\item[EXPRESSIONS] \\hfill \\\\/
s/HISTORY/\\item[HISTORY] \\hfill \\\\/
s/NOTICE/\\item[NOTICE] \\hfill \\\\/
s/BUGS/\\item[BUGS] \\hfill \\\\/
s/VERSION/\\item[VERSION] \\hfill \\\\/

/^[     ]*[-][a-zA-Z]/s/[     ]*$//
/^[     ]*[-][a-zA-Z]/s/$/ \\\\/
/^[     ]*[-][,]/s/$/ \\\\/
/^[     ]*[+][a-zA-Z]/s/$/ \\\\/
