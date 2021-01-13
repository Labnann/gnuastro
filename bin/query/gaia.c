/*********************************************************************
Gaia Query: retrieve tables from Gaia catalog.
Query is part of GNU Astronomy Utilities (Gnuastro) package.

Original author:
     Mohammad akhlaghi <mohammad@akhlaghi.org>
Contributing author(s):
Copyright (C) 2020-2021, Free Software Foundation, Inc.

Gnuastro is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

Gnuastro is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with Gnuastro. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <config.h>

#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>

#include <gnuastro-internal/checkset.h>

#include "main.h"

#include "ui.h"





void
gaia_prepare(struct queryparams *p)
{
  /* Make sure that atleast one type of constraint is specified. */
  if(p->query==NULL && p->center==NULL && p->overlapwith==NULL)
    error(EXIT_FAILURE, 0, "no '--query', '--center' or '--overlapwith' "
          "specified. At least one of these options are necessary in the "
          "Gaia dataset");

  /* If '--center' is given, '--radius' is also necessary. */
  if(p->center || p->overlapwith)
    {
      /* Make sure the radius is given, and that it isn't zero. */
      if(p->overlapwith==NULL && p->radius==NULL && p->width==NULL)
        error(EXIT_FAILURE, 0, "the '--radius' ('-r') or '--width' ('-w') "
              "options are necessary with the '--center' ('-C') option");

      /* If no dataset is explicitly given, then use default one and let
         the user know. */
      if( p->datasetstr==NULL)
        {
          gal_checkset_allocate_copy("edr3", &p->datasetstr);
          error(EXIT_SUCCESS, 0, "using '%s' dataset since no dataset "
                "was explicitly requested (with '--dataset')",
                p->datasetstr);
        }

      /* Use simpler names for the commonly used datasets. */
      if( !strcmp(p->datasetstr, "edr3") )
        {
          free(p->datasetstr);
          gal_checkset_allocate_copy("gaiaedr3.gaia_source", &p->datasetstr);
        }
      else if( !strcmp(p->datasetstr, "dr2") )
        {
          free(p->datasetstr);
          gal_checkset_allocate_copy("gaiadr2.gaia_source", &p->datasetstr);
        }
      else if( !strcmp(p->datasetstr, "dr1") )
        {
          free(p->datasetstr);
          gal_checkset_allocate_copy("gaiadr1.gaia_source", &p->datasetstr);
        }
      else if( !strcmp(p->datasetstr, "hipparcos") )
        {
          free(p->datasetstr);
          gal_checkset_allocate_copy("public.hipparcos", &p->datasetstr);
        }
      else if( !strcmp(p->datasetstr, "tycho2") )
        {
          free(p->datasetstr);
          gal_checkset_allocate_copy("public.tycho2", &p->datasetstr);
        }
    }

  /* Set the URLs, note that this is a simply-linked list, so we need to
     reverse it in the end to have the same order here. */
  gal_list_str_add(&p->urls, "https://gea.esac.esa.int/tap-server/tap/sync", 0);

  /* Name of RA Dec columns to use in Gaia. */
  p->ra_name="ra";
  p->dec_name="dec";
}
