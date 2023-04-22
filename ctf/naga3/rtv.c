#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/prctl.h>

struct measurement_t {
    char command[128];
    unsigned long long runtime;
} Measurements[] = {
    {"sleep 1", 0L},
    {"env", 0L},
    {"md5sum /etc/passwd", 0L},
    {"ls -l /etc/passwd", 0L},
    {"dd if=/dev/zero of=/dev/null bs=1M count=100", 0L},
};

#define MEASUREMENTCOUNT (sizeof(Measurements) / sizeof(struct measurement_t))
int measurementCount = MEASUREMENTCOUNT;

void report_measurements(int s) {
    int i;
    for(i = 0; i < measurementCount; i++) {
        //printf("Reporting command %d\n", i);
        write(s, &i, sizeof(i));
        write(s, &(Measurements[i].runtime), sizeof(unsigned long long));
    }
}

void make_measurements(int s) {
    struct timeval pre, post;
    int i;
    char cmd[256];

    for(i = 0; i < measurementCount; i++) {
        gettimeofday(&pre, NULL);
        sprintf(cmd, "PARENTPID=%d %s > /dev/null 2> /dev/null", getpid(), Measurements[i].command);
        system(cmd);
        gettimeofday(&post, NULL);
        Measurements[i].runtime = (post.tv_sec - pre.tv_sec) * 1000000 + post.tv_usec - pre.tv_usec;
    }
}

void print_measurements() {
    int i;
    for(i = 0; i < measurementCount; i++) {
        printf("Command[%d] \"%s\" executed in %llu""us\n", i, Measurements[i].command, Measurements[i].runtime);
    }
}

void read_measurements(int s) {
    int i = 0;
    unsigned long long t;
    int rc;
    while(1) {
        if((rc = read(s, &i, sizeof(i))) < sizeof(i)) {
            printf("Truncated read: %d instead of %d\n", rc, sizeof(i));
            exit(1);
        }
        if((rc = read(s, &t, sizeof(t))) < sizeof(t)) {
            printf("Truncated read: %d instead of %d\n", rc, sizeof(t));
            exit(1);
        }

        //printf("Measurement %d read: %llu\n", i, t);
        Measurements[i].runtime = t;

        if(i == measurementCount - 1) return;
    }
}

int main(int argc, char *argv[]) {
        int p[2];

        if(pipe(p) < 0) {
            fprintf(stderr, "Pipe Failed.\n");
            exit(1);
        }

        switch (fork()) {
            case -1:
                perror("main: fork");
                exit(1);
            case 0:
                setresuid(getuid(), getuid(), getuid());
                setresgid(getgid(), getgid(), getgid());
                prctl(PR_SET_DUMPABLE, 1, 0, 0, 0);
                prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);

                make_measurements(p[1]);
                report_measurements(p[1]);
                break;
            default:
                printf("Command runtime verification tool v1.0\n");
                printf("Please wait while command runtimes are being verified...\n");
                read_measurements(p[0]);
                print_measurements();
                break;
        }
    return 0;
}