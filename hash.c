/*
  +----------------------------------------------------------------------+
  | hash: hashing library for IBM DB2                                    |
  +----------------------------------------------------------------------+
  | Copyright (c) 2007-2012 Helmut K. C. Tessarek                        |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License"); you  |
  | may not use this file except in compliance with the License. You may |
  | obtain a copy of the License at                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Author: Helmut K. C. Tessarek                                        |
  +----------------------------------------------------------------------+
  | Website: http://mod-auth-ibmdb2.sourceforge.net                      |
  +----------------------------------------------------------------------+
*/

/* $Id: hash.c,v 1.2 2012/11/25 07:59:12 tessus Exp $ */

#include <stdio.h>
#include <sqludf.h>
#include <sqlca.h>
#include <sqlda.h>
#include "hash.h"

/*--------------------------------------------------*/
/* function md5: MD5 Hashing                        */
/*                                                  */
/*        input : varchar                           */
/*        output: varchar                           */
/*--------------------------------------------------*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN md5(	SQLUDF_CHAR      *in,
						SQLUDF_CHAR      out[33],
						SQLUDF_SMALLINT  *innull,
						SQLUDF_SMALLINT  *outnull,
						SQLUDF_TRAIL_ARGS) 
{
	char *t;
	
	if( *innull != 0 )
	{
		*outnull = -1;
		return;
	}

	t = mk_hash( in, ALG_MD5 );
	strcpy( out, t );
	free( t );

	*outnull = 0;
	return;
}

/*--------------------------------------------------*/
/* function apr_md5: MD5 Hashing as in the htpasswd */
/*                   program from Apache            */
/*                                                  */
/*        input : varchar                           */
/*        output: varchar                           */
/*--------------------------------------------------*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprmd5(	SQLUDF_CHAR      *in,
						SQLUDF_CHAR      out[38],
						SQLUDF_SMALLINT  *innull,
						SQLUDF_SMALLINT  *outnull,
						SQLUDF_TRAIL_ARGS) 
{
	char *t;

	if( *innull != 0 )
	{
		*outnull = -1;
		return;
	}

	t = mk_hash( in, ALG_APMD5 );
	strcpy( out, t );
	free( t );

	*outnull = 0;
	return;
}

/*--------------------------------------------------*/
/* function apr_crypt: Crypt fuction as in the      */
/*                     htpasswd program from Apache */
/*                                                  */
/*        input : varchar                           */
/*        output: varchar                           */
/*--------------------------------------------------*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprcrypt(	SQLUDF_CHAR      *in,
							SQLUDF_CHAR      out[14],
							SQLUDF_SMALLINT  *innull,
							SQLUDF_SMALLINT  *outnull,
							SQLUDF_TRAIL_ARGS) 
{
	char *t;

	if( *innull != 0 )
	{
		*outnull = -1;
		return;
	}

	t = mk_hash( in, ALG_CRYPT );
	strcpy( out, t );
	free( t );

	*outnull = 0;
	return;
}

/*--------------------------------------------------*/
/* function apr_sha1: SHA1 fuction as in the        */
/*                    htpasswd program from Apache  */
/*                                                  */
/*        input : varchar                           */
/*        output: varchar                           */
/*--------------------------------------------------*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprsha1(	SQLUDF_CHAR      *in,
							SQLUDF_CHAR      out[34],
							SQLUDF_SMALLINT  *innull,
							SQLUDF_SMALLINT  *outnull,
							SQLUDF_TRAIL_ARGS) 
{
	char *t;

	if( *innull != 0 )
	{
		*outnull = -1;
		return;
	}

	t = mk_hash( in, ALG_APSHA );
	strcpy( out, t );
	free( t );

	*outnull = 0;
	return;
}
   
/*--------------------------------------------------*/
/* function validate : validates the hash           */
/*                                                  */
/*        input1: varchar                           */
/*        input2: varchar                           */
/*        output: integer                           */
/*--------------------------------------------------*/

#ifdef __cplusplus
extern "C"
#endif
SQL_API_RC SQL_API_FN validate(	SQLUDF_CHAR      *password,
								SQLUDF_CHAR      *hash,
								SQLUDF_INTEGER	 *out,
								SQLUDF_SMALLINT  *passwordNullInd,
								SQLUDF_SMALLINT  *hashNullInd,
								SQLUDF_SMALLINT  *outNullInd,
								SQLUDF_TRAIL_ARGS) 
{
	apr_status_t status;
	char *md5, *result;
	
	*out = -1;
	*outNullInd = -1;
	
	if( *passwordNullInd != 0 || *hashNullInd != 0 )
	{
		*outNullInd = -1;
		return(0);
	}

	if( strlen(hash) == 0 )
	{
		strcpy(SQLUDF_STATE, "39701");
		strcpy(SQLUDF_MSGTX, "The second parameter (hash) must not be empty.");
		*outNullInd = 0;
		return(0);
	}

	if( strlen(hash) == 32 )
	{
		md5 = mk_hash( password, ALG_MD5 );
		
		if( apr_strnatcmp( hash, md5 ) == 0 )
		{
			*out = 1;
		}
		else
		{
			*out = 0;
		}
		
		free(md5);
		
		*outNullInd = 0;
		return(0);
	}

	status = apr_password_validate( password, hash );

	if( status == APR_SUCCESS )
	{
		*out = 1;
	}
	else
	{
		// maybe a different encrypted password (glibc2 crypt)?
		result = crypt( password, hash );
		if( strcmp( hash, result ) == 0 )
		{
			*out = 1;
		}
		else
		{
			*out = 0;
		}
	}
	
	*outNullInd = 0;
	return(0);
}
