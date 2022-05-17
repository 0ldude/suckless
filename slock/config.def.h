/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nobody";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#282828",     /* after initialization */
	[INPUT] =  "#458588",   /* during input */
	[FAILED] = "#CC241D",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;

/* Background image path, should be available to the user above */
static const char* background_image = "/home/yalo/Pictures/1920x1080-dark-archlinux2.png";
