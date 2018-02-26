/* file: /cmds/creator/cd.c
 * filesystem navigation
 * zed @ Lilypad Mudlib
*/

#include <command.h>

int main(string dir) {
    string path;// = resolve_path(this_player()->query_cwd(), dir);

    if(!dir) {
        path = "/"; //need to finish the home dirs|then set cwd to creator\admin home dir
        this_player()->set_cwd(path);
        write(path+"\n");
        return 1;
    }
    if(dir) {
        path = resolve_path(this_player()->query_cwd(), dir);
        if(directory_exists(path)) {
            this_player()->set_cwd(path);
            write(resolve_path(this_player()->query_cwd()) + "\n");
        }
        else {
            path = resolve_path(this_player()->query_cwd(), dir);
            write(path+" does not exist.\n");
            return 1;
        }
    }
    return 1;
}