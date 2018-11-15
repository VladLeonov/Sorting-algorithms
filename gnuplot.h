#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <cstdio>
#include <string>
#include <iostream>

#ifdef WIN32
    #define GNUPLOT_NAME "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\""
#else
    #define GNUPLOT_NAME "gnuplot -persist"
#endif

using std::string;
using std::cerr;

class Gnuplot {
public:
    Gnuplot();
    ~Gnuplot();
    void operator ()(const string & command);

protected:
    FILE *gnuplotpipe;
};


Gnuplot::Gnuplot() {
    #ifdef WIN32
        gnuplotpipe = _popen(GNUPLOT_NAME, "w");
    #else
        gnuplotpipe  = popen(GNUPLOT_NAME, "w");
    #endif

    if (!gnuplotpipe)
    {
        cerr << ("Gnuplot not found !");
    }
}


Gnuplot::~Gnuplot() {
    fprintf(gnuplotpipe,"exit\n");

    #ifdef WIN32
       _pclose(gnuplotpipe);
    #else
        pclose(gnuplotpipe);
    #endif
}

void Gnuplot::operator()(const string & command) {
    fprintf(gnuplotpipe,"%s\n",command.c_str());
    fflush(gnuplotpipe);
}

#endif //GNUPLOT_H
