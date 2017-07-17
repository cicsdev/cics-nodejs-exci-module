/* Licensed Materials - Property of IBM                               */
/*                                                                    */
/* SAMPLE                                                             */
/*                                                                    */
/* (c) Copyright IBM Corp. 2017 All Rights Reserved                   */
/*                                                                    */
/* US Government Users Restricted Rights - Use, duplication or        */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp   */
/*                                                                    */

#ifndef __entry_h
#define __entry_h

/*
 * Structure and type declarations.
 */

#define STORAGE_ERROR           -3


/*
 * Function prototypes.
 */

#ifdef __cplusplus
extern "C" {
#endif

int execCicsLinkCommarea(char * applid, char * program, void * commarea, int iCommareaLen);

int execCicsLinkChannel(char * applid, char * program, char * channel);

int execCicsPutContainerString(char * container, char * channel, char * data, int iDataLength);

char * execCicsGetContainerString(char * container, char * channel, int ccsid);

#ifdef __cplusplus
}
#endif
#endif
