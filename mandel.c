#include <stdio.h>
#include <plot.h>
#include <complex.h>
#include <math.h>

/*
Dependancies:
plotutils
libplot-dev
Build commands:
gcc -O2 -pipe -c mandel.c
gcc -o mandel mandel.o -lplot
*/

void plot (plPlotter *plotter, double x, double y, char colour[])
{
  pl_pencolorname_r (plotter, colour);
  pl_fpoint_r (plotter, x, y);
}

void mandelplane (plPlotter *plotter, int xmin, int ymin, int xmax, int ymax, long xpos, long ypos, long zoom, long maxiter)
{
  int x, y;
  double cx, cy;
  double complex z, c;
  for( x = xmin; x <= xmax; x++ )
  {
    cx = ( (double)x - xpos ) / zoom;
    for( y = ymin; y <= ymax; y++ )
    {
      cy = ( (double)y - ypos ) / zoom;
      c = cx + cy * I;
      z = 0 + 0 * I;
      int iteration = 0;
      while (pow(creal(z), 2)+pow(cimag(z), 2) < 4 && iteration < maxiter) {
            z = z*z+c;
            iteration++;
      }
      if (iteration >= maxiter) {
        plot (plotter, x, y, "white");
      } else if (iteration >=16) {
        plot (plotter, x, y, "red");
      } else if (iteration >=12) {
        plot (plotter, x, y, "orange");
      } else if (iteration >=9) {
        plot (plotter, x, y, "yellow");
      } else if (iteration >=7) {
        plot (plotter, x, y, "green");
      } else if (iteration >=6) {
        plot (plotter, x, y, "blue");
      } else if (iteration >=5) {
        plot (plotter, x, y, "purple");
      }
    }
  }
}

int main (int argc, char **argv)
{
  plPlotter *plotter;
  plPlotterParams *plotter_params;

  /* set a Plotter parameter */
  plotter_params = pl_newplparams ();
  pl_setplparam (plotter_params, "PAGESIZE", "letter");
  pl_setplparam (plotter_params, "BG_COLOR", "black");

  /* create a PNG Plotter that writes to standard output */
  if ((plotter = pl_newpl_r ("png", stdin, stdout, stderr,
                             plotter_params)) == NULL)
    {
      fprintf (stderr, "Couldn't create Plotter\n");
      return 1;
    }

  if (pl_openpl_r (plotter) < 0)      /* open Plotter */
    {
      fprintf (stderr, "Couldn't open Plotter\n");
      return 1;
    }
  pl_fspace_r (plotter, 0, 0, 1000, 1000); /* set coor system */
  pl_erase_r (plotter);               /* erase graphics display */
  if ( argc == 1 ) {
    mandelplane (plotter, 0, 0, 1000, 1000, 790, 500, 380, 100);
  } else {
    mandelplane (plotter, 0, 0, 1000, 1000, strtoul(argv[1],NULL,10),
                                            strtoul(argv[2],NULL,10),
                                            strtoul(argv[3],NULL,10),
                                            strtoul(argv[4],NULL,10));
  }
  if (pl_closepl_r (plotter) < 0)     /* close Plotter */
    {
      fprintf (stderr, "Couldn't close Plotter\n");
      return 1;
    }

  if (pl_deletepl_r (plotter) < 0)    /* delete Plotter */
    {
      fprintf (stderr, "Couldn't delete Plotter\n");
      return 1;
    }
  return 0;
}
