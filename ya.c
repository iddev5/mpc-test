#include <stdio.h>
#include <stdlib.h>

#include <mpc.h>

int main() {
    mpc_parser_t *ident = mpc_new("ident");
    mpc_parser_t *num = mpc_new("num");
    mpc_parser_t *string = mpc_new("string");
    mpc_parser_t *cchar = mpc_new("char");
    mpc_parser_t *factor = mpc_new("factor");
    mpc_parser_t *strfact = mpc_new("strfact");
    mpc_parser_t *term = mpc_new("term");
    mpc_parser_t *param = mpc_new("param");
    mpc_parser_t *func = mpc_new("func");
    mpc_parser_t *nval = mpc_new("nval");
    mpc_parser_t *val = mpc_new("val");
    mpc_parser_t *expr = mpc_new("expr");
    mpc_parser_t *let = mpc_new("let");
    mpc_parser_t *iif = mpc_new("if");
    mpc_parser_t *wwhile = mpc_new("while");
    mpc_parser_t *block = mpc_new("block");
    mpc_parser_t *body = mpc_new("body");
    mpc_parser_t *prog = mpc_new("prog");

    FILE *f = fopen("rules.yp", "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *grammar = malloc(sizeof(char) * (size + 1));
    fread(grammar, size, 1, f);
    grammar[size] = '\0';

    fclose(f);

    mpc_err_t *err = mpca_lang(MPCA_LANG_DEFAULT, grammar,
        ident, num, string, cchar, factor, strfact, term, param, func, nval, val, expr, let, iif, wwhile, block, body, prog, NULL
    );

    if (err != NULL) {
      mpc_err_print(err);
      mpc_err_delete(err);
      exit(1);
    }

    mpc_result_t res;

    char str[] =
    "let x = () {\n"
    "   while x == true { \n"
    "       print(\"hello\" ** (10 + 2));\n"
    "   }\n"
    "};";

    if (mpc_parse("input", str, prog, &res)) {
        mpc_ast_print(res.output);
        mpc_ast_delete(res.output);
    }
    else {
        mpc_err_print(res.error);
        mpc_err_delete(res.error);
    }

    mpc_cleanup(6, ident, num, string, cchar, factor, strfact, term, param, func, nval, val, expr, let, iif, wwhile, block, body, prog);
    free(grammar);
}
