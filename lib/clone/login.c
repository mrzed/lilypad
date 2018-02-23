/* File:  /clone/login.c
 * Login object - This is the first thing to load when a player connets.
 * Zed - Lilypad
 * 2018-02-15
*/

#include <globals.h>

void catch_tell(string str) {
    receive(str);
}

private void create_user_object(string name) {
    object user;
    CHECKIN_D->set_online(name);
    write("\n");
    cat(MOTD);
    write("\n");
    user = new(USER_OB);
    user->set_name(name);
    exec(user, this_object());
    user->setup();
    user->move(VOID_OB);
    destruct(this_object());
}

void logon() {
    write("\n==================================\n");
    cat(BANNER);
    write("\n==================================\n");
    write("\nWelcome to "+MUD_NAME+ " " +MUDLIB_VER+"\n\n");
    write("Login: ");
    input_to("get_username", INPUT_TO_NOBYPASS);
}

void get_username(string name) {
    name = CHECKIN_D->normalize_acct_name(name);

    if(CHECKIN_D->acct_exists(name)) {
        write("Enter Password: ");
        input_to("get_passwd", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
    }
    else {
        if(CHECKIN_D->valid_acct_name(name)) {
            write("Welcome, " + name + "! Please enter a password: ");
            input_to("new_passwd", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
        }
        else {
            printf("\nLogin incorrect\n\n%s Login: ", MUD_NAME);
            input_to("get_username", INPUT_TO_NOBYPASS);
        }
    }
}

void get_passwd(string password, string name) {
    object user;

    if(CHECKIN_D->password_match(name, password)) {
        if(user = find_player(name)) {
            exec(user, this_object());
            user->reconnect();
            destruct(this_object());
        }
        else {
            create_user_object(name);
        }
    }
    else {
        printf("\nIncorrect Login!\n\n%s \nLogin: ", MUD_NAME);
        input_to("get_username", INPUT_TO_NOBYPASS);
    }
}

void new_passwd(string password, string name) {
    if(CHECKIN_D->valid_password(password)) {
        write("\nEnter it again: ");
        input_to("verify_new_passwd", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, password, name);
    }
    else {
        write("\nInvalid password.\n\nEnter a password: ");
        input_to("new_passwd", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
    }
}

void verify_new_passwd(string new_passwd, string password, string name) {
    if(new_passwd != password) {
        write("\nPasswords don't match.\n\nEnter a password: ");
        input_to("new_passwd", INPUT_TO_NOBYPASS|INPUT_TO_NOECHO, name);
        return;
    }
    else {
        write("\nEmail address: ");
        input_to("new_email_addr", INPUT_TO_NOBYPASS, name, password);
    }
}

void new_email_addr(string email, string name, string password) {
    if(CHECKIN_D->valid_email(email)) {
        if(!CHECKIN_D->acct_exists(name)) {
            CHECKIN_D->create_acct(name, password, email);
            create_user_object(name);
        }
        else {
            printf("Boo! Someone has already taken that name!\n\n%s Login: ", MUD_NAME);
            input_to("get_username", INPUT_TO_NOBYPASS);
            }
        }
    else {
        write("Invalid email.\n\nEnter an email address: ");
        input_to("new_email_addr", INPUT_TO_NOBYPASS, name, password);
    }
}
