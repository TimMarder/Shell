int count_tok(char *input);

char **parse(char *line, int numtok);

char **mult_parse(char *line, int numtok);

void redirect_out(char **parsed);

void redirect_in(char **parsed);

void pipes(char **parsed);

int run_cmd(char *input);

void run_mult_cmd(char *input);
