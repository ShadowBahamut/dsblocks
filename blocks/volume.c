#include <stdio.h>

#include "../util.h"
#include "volume.h"

#define ICONsnh                          COL1 " " COL0
#define ICONsnl                          COL1 " " COL0
#define ICONsm                          COL2 " " COL0
#define ICONhn                          COL1 " " COL0
#define ICONhm                          COL2 " " COL0

#define PULSEINFO                       (char *[]){ SCRIPT("pulse_info.pipewire.sh"), NULL }

#define PAVUCONTROL                     (char *[]){ "alsamixer", NULL }
#define NORMALIZEVOLUME                 (char *[]){ SCRIPT("pulse_normalize.sh"), NULL }
//#define TOGGLEMUTE                      (char *[]){ "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL }
#define TOGGLEMUTE                      (char *[]){"NULL"}

size_t
volumeu(char *str, int sigval)
{
	static char *icons[] = { ICONsnh, ICONhn, ICONhm };
        char buf[32];
        char threshold[32] = "02%                             ";
	size_t l;

        if (!(l = getcmdout(PULSEINFO, buf, sizeof buf - 1))) {
                *str = '\0';
                return 1;
        }
        buf[l] = '\0';
        if (buf == "02%"){
	printf("It works!");	
	}
	printf("%s/n", buf+1);
	return SPRINTF(str, "%s%s", icons[buf[0] - '0'], buf + 1);
}

void
volumec(int button)
{
        switch(button) {
                case 1:
                        cspawn(TOGGLEMUTE);
                        break;
                case 2:
                        cspawn(TOGGLEMUTE);
                        //cspawn(NORMALIZEVOLUME);
                        break;
                case 3:
                        cspawn(TOGGLEMUTE);
                        //cspawn(PAVUCONTROL);
                        break;
        }
}
