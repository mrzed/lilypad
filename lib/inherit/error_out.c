// Thanks to the rmanis\lil project for this.
// http://github.com/rmanis/lil
// hijacked by Zed - Lilypad Mudlib

int error_out(string str);
int error_out(string str) {
#ifndef __NO_ADD_ACTION__
    return notify_fail(str + "\n");
#else
    previous_object()->tell(sprintf("%s\n", str));
    return 0;
#endif
}