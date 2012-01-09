/*
 * $Header: /usr/gapps/asde/cvs-vault/sdb/launchmon/src/linux/lmon_api/lmon_be.cxx,v 1.12.2.5 2008/02/20 17:37:57 dahn Exp $
 *--------------------------------------------------------------------------------
 * Copyright (c) 2008 - 2012, Lawrence Livermore National Security, LLC. Produced at
 * the Lawrence Livermore National Laboratory. Written by Dong H. Ahn <ahn1@llnl.gov>.
 * LLNL-CODE-409469. All rights reserved.
 *
 * This file is part of LaunchMON. For details, see 
 * https://computing.llnl.gov/?set=resources&page=os_projects
 *
 * Please also read LICENSE.txt -- Our Notice and GNU Lesser General Public License.
 *
 * 
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *--------------------------------------------------------------------------------
 *
 *  Update Log:
 *              Nov 23 2011 DHA: Added CDTI tool control messaging
 *              Oct 31 2011 DHA: File created
 *
 */

#ifndef HAVE_LAUNCHMON_CONFIG_H
#include "config.h"
#endif

#include <lmon_api/lmon_api_std.h>

#ifndef LINUX_CODE_REQUIRED
#error This source file requires a LINUX-like OS
#endif

#include <sys/types.h>
#include <signal.h>

#include "lmon_be_internal.hxx"
#include "../../sdbg_rm_map.hxx"
#include "lmon_api/lmon_proctab.h"
#include "lmon_api/lmon_say_msg.hxx"
#include "lmon_be_sync_mpi_generic.hxx"


//////////////////////////////////////////////////////////////////////////////////
//
// LAUNCHMON MPI-Tool SYNC LAYER (Generic)
//           PUBLIC INTERFACE
//


lmon_rc_e
LMON_be_procctl_init_generic ( MPIR_PROCDESC_EXT* ptab,
                               int psize )
{
  return ( LMON_be_procctl_stop_generic ( ptab, psize ) );
}


lmon_rc_e
LMON_be_procctl_stop_generic ( MPIR_PROCDESC_EXT* ptab,
                               int psize )
{
  lmon_rc_e rc = LMON_OK;
  int i;

  for (i=0; i < psize; ++i)
    {
      if ( ( kill(ptab[i].pd.pid, SIGSTOP ) != 0 )
           && ( rc == LMON_OK ) )
        {
          LMON_say_msg ( LMON_BE_MSG_PREFIX, true,
            "Sending SIGSTOP to %d returned an error (%s).",
              ptab[i].pd.pid, strerror(errno) );
          errno = 0;
          rc = LMON_EINVAL;
        }
    }

  return rc;
}


lmon_rc_e
LMON_be_procctl_run_generic ( int signum, 
                              MPIR_PROCDESC_EXT* ptab,
                              int psize )
{
  lmon_rc_e rc = LMON_OK;
  int sendsig = (signum == 0)? SIGCONT : signum;
  int i;

  for (i=0; i < psize; ++i)
    {
      if ( ( kill ( ptab[i].pd.pid, sendsig ) != 0 )
           && rc == LMON_OK)
        {
          LMON_say_msg ( LMON_BE_MSG_PREFIX, true,
            "Sending SIGCONT to %d returned an error (errno: %d).", 
            ptab[i].pd.pid, strerror(errno) );
          errno = 0;
          rc = LMON_EINVAL;
        }
    }

  return rc;
}


lmon_rc_e
LMON_be_procctl_perf_generic ( 
                   MPIR_PROCDESC_EXT *ptab,
                   int psize,
                   long unsigned int membase,
                   unsigned int numbytes,
                   unsigned int *fetchunit,
                   unsigned int *usecperunit)
{
  return LMON_EINVAL;
}


lmon_rc_e
LMON_be_procctl_initdone_generic ( MPIR_PROCDESC_EXT* ptab,
                                   int psize)
{
  return LMON_OK;
}


lmon_rc_e
LMON_be_procctl_done_generic ( MPIR_PROCDESC_EXT* ptab,
                               int psize)
{
  return LMON_OK;
}
