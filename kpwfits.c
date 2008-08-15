#include        "local.h"
/*
 ***************************************************************************
 *
 *  kpwfits  --  Quick FLOAT Image Writer
 */
int kpwfits(fn,nx,ny,im)
char fn[];
int nx,ny;
float im[];
{
    fitsfile *fptr;
    int status = 0;
    long nn, naxes[2];
    long naxis = 2;
    long fpix = 1;
/*
 */
    if ( fits_create_file(&fptr, fn, &status) )
        return(-status);
    naxes[0] = nx;
    naxes[1] = ny;
    nn = naxes[0]*naxes[1];
    if ( fits_create_img(fptr, FLOAT_IMG, naxis, naxes, &status) )
        return(-status);
    if ( fits_write_img(fptr, TFLOAT, fpix, nn, im, &status) )
         return(-status);
    if ( fits_close_file(fptr, &status) )       /* close the FITS file */
         return(-status);
    printf("Wrote %d %d Into %s\n", nx,ny,fn);
    return(0);
}
