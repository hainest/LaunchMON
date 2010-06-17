/*
 * $Header: /usr/gapps/asde/cvs-vault/sdb/launchmon/src/lmon_api/lmon_lmonp_msg.h,v 1.9.2.3 2008/03/06 00:13:57 dahn Exp $
 *--------------------------------------------------------------------------------
 * Copyright (c) 2008, Lawrence Livermore National Security, LLC. Produced at 
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
 *
 *  Update Log:
 *        Dec  23 2009 DHA: Removed header file macroes for header files that
 *                          would exit on almost all UNIX based platforms,
 *                          facilitaing binary distribution.
 *        Mar 13 2009 DHA: Added large nTasks support
 *        Feb 09 2008 DHA: Added LLNS Copyright 
 *        Dec 19 2006 DHA: Created file.
 */

#ifndef LMON_API_LMON_MSG_H
#define LMON_API_LMON_MSG_H 1

#include <lmon_api/common.h>

BEGIN_C_DECLS

////////////////////////////////////////////////////////////////////
//
// Data Structure...
//
//
 

typedef enum _lmonp_msg_class_e {
  /*
   * msg class for FE client to/from FE launchmon engine 
   */
  lmonp_fetofe                         = 0,

  /*
   * msg class for FE client to/from BE master tool daemon
   */
  lmonp_fetobe                         = 1,

  /*
   * msg class for FE client to/from middleware tool daemon
   */
  lmonp_fetomw                         = 2

} lmonp_msg_class_e;


/* 
 * msg types defined here for FE-launchmon engine comm 
 */ 
typedef enum _lmonp_fe_to_fe_msg_e {
  /*
   * engine->FE: a job launcher hits the launch function with 
   * MPIR_DEBUG_SPAWNED state 
   */
  lmonp_stop_at_launch_bp_spawned      = 0, 

  /*
   * engine->FE: A job launcher hits the launch function with 
   * MPIR_DEBUG_ABORTING state 
   * Semantics is defined in README.ERROR_HANDLE (D)
   */
  lmonp_stop_at_launch_bp_abort        = 1,

  /*
   * engine->FE: process table filled (typically right after 
   * lmonp_stop_at_launch_bp_spawned)
   */
  lmonp_proctable_avail                = 2,

  /*
   * engine->FE: resource handle filled (typically right after 
   * lmonp_stop_at_launch_bp_spawned)
   */
  lmonp_resourcehandle_avail           = 3,

  /*
   * engine->FE: we don't yet communicate following seven events 
   */
  lmonp_stop_at_first_exec             = 4, 
  lmonp_stop_at_first_attach           = 5,
  lmonp_stop_at_loader_bp              = 6,
  lmonp_stop_at_thread_creation        = 7,
  lmonp_stop_at_thread_death           = 8,
  lmonp_stop_at_fork_bp                = 9,
  lmonp_stop_not_interested            = 10,

  /*
   * engine->FE: job launcher terminated
   */
  lmonp_terminated                     = 11,
  
  /*
   * engine->FE: The main thread of the launcher exited
   * Semantics is defined in README.ERROR_HANDLE (D)
   */
  lmonp_exited                         = 12,
  
  /*
   * engine->FE: The detach done
   */
  lmonp_detach_done                    = 13,
 
  /*
   * engine->FE: The kill done
   */
  lmonp_kill_done                      = 14,

  /*
   * engine->FE: engine failed and done its cleanup.
   * Semantics is defined in README.ERROR_HANDLE (A) 
   */
  lmonp_stop_tracing                   = 15,

  /*
   * engine->FE: back-end daemons exited.
   * Semantics is defined in README.ERROR_HANDLE (C.2)
   */
  lmonp_bedmon_exited                  = 16,

  /*
   * engine->FE: back-end daemons exited.
   * Semantics is defined in README.ERROR_HANDLE (C.2)
   */
  lmonp_mwdmon_exited                  = 17,

  /*
   * FE->engine: please detach command
   */
  lmonp_detach                         = 18,

  /*
   * FE->engine: please kill command
   */
  lmonp_kill                           = 19,
 
  /*
   * FE->engine: please shutdownbe command
   */
  lmonp_shutdownbe                     = 20,

  /*
   * end of enumerator marker
   */
  lmonp_invalid                        = 30

} lmonp_fe_to_fe_msg_e;


/* 
 * msg types defined here for FE-BE comm 
 */ 
typedef enum _lmonp_fe_to_be_msg_e {
  
  /*
   * FE->BE: security check message
   */
  lmonp_febe_security_chk              = 0,

  /*
   * FE->BE: proctab message
   */
  lmonp_febe_proctab                   = 1,

  /*
   * FE->BE: usrdata message
   */
  lmonp_febe_usrdata                   = 2,

  /*
   * FE->BE: launch
   */
  lmonp_febe_launch                    = 3,

  /*
   * FE->BE: attach 
   */
  lmonp_febe_attach                    = 4,

  /*
   * BE->FE: BE hostnames message
   */
  lmonp_befe_hostname                  = 5,

  /*
   * BE->FE: usrdata message
   */
  lmonp_befe_usrdata                   = 6,

  /*
   * BE->FE: BE ready message
   */
  lmonp_be_ready                       = 7,

} lmonp_fe_to_be_msg_e;


/* 
 * msg types defined here for FE-MIDDLEWARE comm 
 */ 
typedef enum _lmonp_fe_to_mw_msg_e {

  lmonp_femw_security_chk            = 0,

  lmonp_femw_proctab                 = 1,

  lmonp_femw_usrdata                 = 2,

  lmonp_femw_hostname                = 3,

  lmonp_mwfe_usrdata                 = 4,

  lmonp_mw_ready                     = 5,

} lmonp_fe_to_mw_msg_e;


//! my_lmon_kind_e
/*!
  defines id types of communication parties in LMON APIs
*/
typedef enum  _my_lmon_kind_e {

  /*
   * LAUNCHMON engine
   */
  lmon_fe_driver,

  /* 
   * WATCHDOG thread residing in FE process, monitoring launchmon engine 
   */
  lmon_fe_watchdog,

  /*
   * FE 
   */
  lmon_fe,

  /*
   * BE
   */
  lmon_be,
 
  /*
   * MIDDLEWARE
   */
  lmon_mw

} my_lmon_kind_e;


//! lmonp_t
/*!
    lmonp protocol


*/
/* The first 32 bits                                                    */ 
/*     0 - 2: MSG class: defines communication pair                     */
/*    3 - 15: MSG type                                                  */
/*   16 - 31: Initial Security KEY or num task info                     */
/*                                                                      */
/* The second 32 bits                                                   */
/*    0 - 31: Additional security key info or                           */
/*            the num of unique exec_name and the num of unique hostname*/
/*            This, in combination with the previous 16 bits describes  */
/*            proctable lmon payload (see the note below)               */
/*                                                                      */
/* The third 32 bits                                                    */ 
/*    0 - 31: LMON PAYLOAD LENGTH                                       */
/*                                                                      */
/* The forth 32 bits                                                    */
/*    0 - 31: USR PAYLOAD LENGTH                                        */
/*                                                                      */
/*            LMON PAYLOAD (max = unsigned integer max)                 */
/*            USR PAYLOAD  (max = unsigned integer max)                 */
/*                                                                      */

//! Note: lmonp_t's lmonp_febe_proctab format
/*!
    each per-task is 16 bytes, each of 4 bytes are used to store
    1. executable string index
    2. hostname string index
    3. pid
    4. mpi rank

    1 and 2 are offset value from the end of such per-task elements
    ( = 16Bytes x num_proc )

    16Bytes x num_proc + the size of string table constitues 
    lmon_payload_length.
*/

typedef struct _lmonp_t {
  lmonp_msg_class_e msgclass            : 3;

  union u0{
    lmonp_fe_to_fe_msg_e fetofe_type    : 13;
    lmonp_fe_to_be_msg_e fetobe_type    : 13;
    lmonp_fe_to_mw_msg_e fetomw_type    : 13;
  } type;

  union u1{
    unsigned short security_key1        : 16; /* unused yet */
    unsigned short num_tasks            : 16;
  } sec_or_jobsizeinfo;

  union u2{
    unsigned int security_key2          : 32; /* unused yet */
    struct unique_str {
      unsigned short num_exec_name      : 16;
      unsigned short num_host_name      : 16;
    } exec_and_hn;
  } sec_or_stringinfo;

  unsigned int long_num_tasks           : 32; /* use for large nTasks */
  unsigned int lmon_payload_length      : 32;
  unsigned int usr_payload_length       : 32;

} lmonp_t;


////////////////////////////////////////////////////////////////////
//
// External Interfaces...
//
//

//! void lmon_timedaccept
/*!
    Timed accept 
*/

int lmon_timedaccept ( int s, struct sockaddr *addr,
                       socklen_t *addrlen, int toutsec );

//! void set_client_name ( const char* cn );
/*!
    Which spatial component is using this lmonp message? 
*/
void set_client_name ( const char* cn );


//! int print_msg_header ( my_lmon_kind_e rw, lmonp_t* msg );
/*!
    print_msg_header: debug routine, printing message type and comm parties
                       0 on success, -1 on error
*/
int print_msg_header ( my_lmon_kind_e rw, lmonp_t* msg );


//! init_msg_header ( lmonp_t* msg );
/*! 
  int init_msg_header: zero outthe header portion of lmonp message
                       0 on success, -1 on error
*/
int init_msg_header ( lmonp_t* msg );


//! 
/*! 
  The functions looks at the header of msg before shipping the 
  entire msg via fd
*/
int write_lmonp_long_msg ( int fd, lmonp_t* msg, int msglength );


//! int read_lmonp_msgheader ( int fd, lmonp_t* msg )
/*! 
  The functions reads only the header portion of an
  lmonp message via fd.
*/
int read_lmonp_msgheader ( int fd, lmonp_t* msg );


//! int read_lmonp_payloads ( int fd, void* buf, int length )
/*! 
  The functions reads the payloads portion of an
  lmonp message via fd.
*/
int read_lmonp_payloads ( int fd, void* buf, int length );


//! int set_msg_header (lmonp_t* msg, ...
/*! 
  a helper function setting the lmonp header 
*/
int set_msg_header ( 
                 lmonp_t* msg, 
	         lmonp_msg_class_e mc, 
		 int type, 
		 unsigned short seckey_or_numtasks, 
		 unsigned int security_key2,
		 unsigned short num_exec_name,
		 unsigned short num_host_name,
		 unsigned int lntasks,
		 unsigned int lmonlen, 
		 unsigned int usrlen );


//! get_lmonpayload_begin, get_usrpayload_begin, get_strtab_begin
/*!
  message offset search routines 
*/
char* get_lmonpayload_begin ( lmonp_t *msg );
char* get_usrpayload_begin ( lmonp_t *msg );
char* get_strtab_begin ( lmonp_t *msg );
int parse_raw_RPDTAB_msg (lmonp_t *proctabMsg, void *pMap);

ssize_t lmon_write_raw ( int fd, void *buf, size_t count );
ssize_t lmon_read_raw ( int fd, void *buf, size_t count );

END_C_DECLS

#endif /* LMON_API_LMON_MSG_H */
