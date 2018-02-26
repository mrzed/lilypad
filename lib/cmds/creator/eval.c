// fixed indents
// used string in place of the file path every place
// added arg verification (no executin eval without an arg)
// added globals.h include to tmp file creation to allow the following:
// > eval return DAEMON_D->func(); instead of:
// > eval return "/path/to/daemon"->func();
// zed @ lilypad

#include <globals.h>

int main(string arg) {
    string filename = "/tmp_eval_file.c";
    string USAGE = "Usage: eval <lpc command(s)>\n";

    if(!arg) {
        notify_fail(USAGE);
        return 0;
    }
    /* clean up first */
    if (file_size(filename) != -1)
    rm (filename);
    if (find_object(filename))
    destruct(find_object(filename));

    /* start parsing */
    printf("Parsing eval: "+arg+"\n");
    write_file(filename,"#include <globals.h>\nmixed eval() { "+arg+"; }\n");
    //write_file(filename,"mixed eval() { "+arg+"; }\n");
    printf("Result = %O\n", filename->eval());
    return 1;
}