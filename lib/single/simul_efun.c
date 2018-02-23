// mudlib: Lilypad
// file:   /single/simul_efun.c
// modifed by zed @ Lilypad Mudlib 2018-02-16
// changed references to /u to use variable defined in dirs.h
// USER_DIR

#pragma show_error_context
#include <globals.h>
#include <lpctypes.h>

string colorize(string color, string str);

int directory_exists(string dirname) {
    return (file_size(dirname) == -2);
}

int same(mixed x, mixed y) {
    if (typeof(x) != typeof(y)) return 0;
    switch (typeof(x)) {
    case INT:
    case STRING:
    case OBJECT:
    case FLOAT:
    return x == y;
    case MAPPING:
    if (x == y) return 1; // speed up this case
    if (sizeof(x) != sizeof(y)) return 0;
    if (!same(keys(x), keys(y))) return 0;
    if (!same(values(x), values(y))) return 0;
    return 1;
    case ARRAY:
    if (x == y) return 1; // speed up this case
    if (sizeof(x) != sizeof(y)) return 0;
    for (int i = 0; i < sizeof(x); i++) {
        if (!same(x[i], y[i])) return 0;
    }
    return 1;
    case BUFFER:
    case FUNCTION:
    case CLASS:
    error("Not implemented.");
    }
}

void cat(string file) {
    write(read_file(file));
}

varargs int getoid(object ob) {
    int id;

    sscanf(file_name(ob || previous_object()), "%*s#%d", id);
    return id;
}

string user_cwd(string name) {
   return (USER_DIR + name[0..0] + "/" + name);
}

string user_path(string name) {
   return (user_cwd(name) + "/");
}

// Get the owner of a file.  Used by log_error() in master.c.

string file_owner(string file) {
    string temp;

    if (file[0] != '/') file = "/" + file;

    if (sscanf(file, USER_DIR+"/%s/%s/%*s", temp, temp) == 2) {
        return temp;
    }
    return 0;
}

#include <lpctypes.h>

// dump_variable, author: Huthar@Portals, TMI
// - returns a printable representation of any variable.
// Changed by Symmetry@IdeaExchange, Tmi-2 5/4/95
// - the format is retained
// Beek - changed to use foreach()
string dump_variable(mixed arg) {
   string rtn;
   mixed x, y;

   switch(typeof(arg)) {
   case OBJECT: return "("+file_name(arg)+")";
   case STRING: return "\""+arg+"\"";
   case INT: return "#"+arg;
   case ARRAY:
       {
       rtn = "ARRAY\n";
       foreach (y in arg)
           rtn += sprintf("[%d] == %s\n", x++, dump_variable(y));

       return rtn;
       }

   case MAPPING:
       {
       rtn = "MAPPING\n" +
           implode(values(map_mapping(arg,
                      (: sprintf("[%s] == %s", $1, $2) :))), "\n");
       return rtn;
       }

     case FUNCTION:
     case CLASS:
     case FLOAT:
     case BUFFER:
       {
       return sprintf("%O\n", arg);
       }

       return "UNKNOWN";
   }
}
// Add colorization to texts
// Zed @ Lilypad Mudlib
// 2018-02-16

varargs string colorize(string color, string arg2, string arg3) {
    string reset = "RESET";
    string msg = arg2;
    if (arg3) {
        reset = upper_case(arg2);
        msg = arg3;
    }
    return sprintf("%%^%s%%^%s%%^%s%%^", upper_case(color), msg, reset);
}

/*
// Thanks to Huthar for resolve_path.
// Rewrite by Symmetry 5/4/95
// Replaced with code from http://startfromlil.wordpress.com/
// by Zed - Lilypad Mudlib 2018-02-2018
*/

string resolve_path(string curr, string newer) {
    int i, j, size;
    string *tmp;

    switch(newer) {
    case 0:
    case "":
    case ".":
        return curr;

    case "~":
        return user_path((string)this_player()->query_name());

#ifndef __NO_ENVIRONMENT__
    case "here":
        return file_name(environment())+".c";
#endif

    default:
        if (newer[0..1] == "~/")
            newer = user_path((string)this_player()->query_name())
                  + newer[2..];
        else {
            switch(newer[0]) {
            case '~':
            {
                i = strsrch(newer, '/');
                if (i < 0)
                    newer = user_path(newer[1..]);
                else
                    newer = user_path(newer[1..i-1]) + newer[i..];
                break;
            }
            case '/':
                break;
            default:
                newer = curr + "/" + newer;
            }
        }

        if (newer[<1] != '/')
            newer += "/";
        size = sizeof(tmp = regexp(explode(newer, "/"), "."));

        i = j = 0;

        while (i < size) {
            switch(tmp[i]) {
            case "..":
                if (j) {
                    while (j-- && !tmp[j]);
                    if (j >= 0)
                        tmp[j] = 0;
                    else
                        j++;
                }
            case ".":
                tmp[i++] = 0;
                break;
            default:
                j = ++i;
                break;
            }
        }
        return "/"+implode(tmp, "/");
    }
}


// domain_file should return the domain associated with a given file.

string domain_file(string) {
    return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.

string creator_file(string) {
    return ROOT_UID;
}

// author_file should return the name of the author of a specific file.

string author_file(string) {
    return ROOT_UID;
}

void simul() {
}

int file_exists(string filename) {
    return sizeof(stat(filename)) > 0;
}

//timestamp code from Quixadhal
string timestamp(int theTime) {
    mixed array timeinfo = localtime(theTime);
    return sprintf("%04d-%02d-%02d %02d:%02d:%02d %s",
            timeinfo[5], timeinfo[4], timeinfo[3],
            timeinfo[2], timeinfo[1], timeinfo[0],
            timeinfo[9]);
}