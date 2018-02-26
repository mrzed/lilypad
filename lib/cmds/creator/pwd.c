#include <command.h>
#include <globals.h>

int main (string arg) {
    write(this_user()->query_cwd() + "\n");
    return 1;
}