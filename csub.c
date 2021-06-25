#include <stdio.h>
#include <stdlib.h>

#include <mpc.h>

int main(void) {
    mpc_parser_t *preproc = mpc_new("preproc");
    mpc_parser_t *ident = mpc_new("ident");
    mpc_parser_t *num = mpc_new("num");
    mpc_parser_t *string = mpc_new("string");
    mpc_parser_t *char_ = mpc_new("char");
    mpc_parser_t *plugin = mpc_new("plugin");
    mpc_parser_t *using = mpc_new("using");
    mpc_parser_t *method = mpc_new("method");
    mpc_parser_t *code = mpc_new("code");
    mpc_parser_t *prog = mpc_new("prog");

    FILE *f = fopen("rules.p", "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *grammar = malloc(sizeof(char) * (size + 1));
    fread(grammar, size, 1, f);
    grammar[size] = '\0';

    fclose(f);

    mpc_err_t *err = mpca_lang(MPCA_LANG_DEFAULT, grammar,
        preproc, ident, string, char_, num, plugin, using, method, code, prog, NULL
    );

    if (err != NULL) {
      mpc_err_print(err);
      mpc_err_delete(err);
      exit(1);
    }

    mpc_result_t res;

    char str[] =
    "@plugin test;\n"
    "@using renderer;\n"
    "@method at_beginning = _begin;\n"
    "@method at_step[1] = step_test;\n";

    if (mpc_parse("input", str, prog, &res)) {
        mpc_ast_print(res.output);
        mpc_ast_delete(res.output);
    }
    else {
        mpc_err_print(res.error);
        mpc_err_delete(res.error);
    }

    mpc_cleanup(8, preproc, ident, string, char_, num, plugin, using, method, code, prog);
    free(grammar);
}
