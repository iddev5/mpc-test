ident   : /[a-zA-Z_][a-zA-Z0-9_]*/;
num     : /[0-9]+/;
string  : /\"(\\\\.|[^\"])*\"/;
char    : /\'.\'/;

plugin  : "@plugin " <ident> ';';
using   : "@using " <ident> ';';
method  : "@method " <ident> (/ *\[ */ <num> / *\]/)? / *= */ <ident> ';';

preproc : '#' /.+/;
code    : /.+/;

prog    : /^/ <preproc>* <plugin> <using>* <method>* <code>* /$/;
