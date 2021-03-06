/*
  +----------------------------------------------------------------------+
  | db2hash.c: hashing library for IBM DB2                               |
  +----------------------------------------------------------------------+
  | Copyright (c) 2007-2018 Helmut K. C. Tessarek                        |
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
  | Website: http://tessus.github.io/db2-hash-routines                   |
  +----------------------------------------------------------------------+
*/

#include <stdio.h>
#include <sqludf.h>
#include <sqlca.h>
#include <sqlda.h>
#include "hash.h"

/*
  +----------------------------------------------------------------------+
  | function phpmd5: MD5 hashing (as in PHP)                             |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN phpmd5(SQLUDF_CHAR      *in,
                       SQLUDF_CHAR      out[33],
                       SQLUDF_SMALLINT  *innull,
                       SQLUDF_SMALLINT  *outnull,
                       SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_PHPMD5, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function aprmd5: MD5 hashing (as in Apache's htpasswd program)       |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprmd5(SQLUDF_CHAR      *in,
                       SQLUDF_CHAR      out[38],
                       SQLUDF_SMALLINT  *innull,
                       SQLUDF_SMALLINT  *outnull,
                       SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_APMD5, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function aprcrypt: crypt function (as in Apache's htpasswd program)  |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprcrypt(SQLUDF_CHAR      *in,
                         SQLUDF_CHAR      out[14],
                         SQLUDF_SMALLINT  *innull,
                         SQLUDF_SMALLINT  *outnull,
                         SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_CRYPT, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function aprsha1: SHA1 hashing (as in Apache's htpasswd program)     |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprsha1(SQLUDF_CHAR      *in,
                        SQLUDF_CHAR      out[34],
                        SQLUDF_SMALLINT  *innull,
                        SQLUDF_SMALLINT  *outnull,
                        SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_APSHA, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function aprsha256: SHA256 hashing (similar to the algorithm used    |
  |                                     in Apache's htpasswd program)    |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN aprsha256(SQLUDF_CHAR      *in,
                          SQLUDF_CHAR      out[53],
                          SQLUDF_SMALLINT  *innull,
                          SQLUDF_SMALLINT  *outnull,
                          SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_APSHA256, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha256: sha-256                                             |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha256(SQLUDF_CHAR      *in,
                       SQLUDF_CHAR      out[56],
                       SQLUDF_SMALLINT  *innull,
                       SQLUDF_SMALLINT  *outnull,
                       SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_SHA256, in, NULL);
	strcpy(out, t);
	free(t);

	if (strlen(out) == 0)
	{
		strcpy(SQLUDF_STATE, "39702");
		strcpy(SQLUDF_MSGTX, "The system's crypt library does not support sha-256.");
		*outnull = 0;
		return;
	}

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha256s: sha-256 with salt                                  |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          input : varchar             (salt)                          |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha256s(SQLUDF_CHAR      *in,
                        SQLUDF_CHAR      *salt,
                        SQLUDF_CHAR      out[56],
                        SQLUDF_SMALLINT  *innull,
                        SQLUDF_SMALLINT  *saltnull,
                        SQLUDF_SMALLINT  *outnull,
                        SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0 || *saltnull != 0)
	{
		*outnull = -1;
		return;
	}

	if (*saltnull == 0 && strlen(salt) != 8)
	{
		strcpy(SQLUDF_STATE, "39703");
		strcpy(SQLUDF_MSGTX, "salt must be exactly 8 characters long");
		*outnull = 0;
		return;
	}

	if (!is_valid_salt(salt))
	{
		strcpy(SQLUDF_STATE, "39704");
		strcpy(SQLUDF_MSGTX, "salt must be chosen from the set [a–zA–Z0–9./]");
		*outnull = 0;
		return;
	}

	t = mk_hash(ALG_SHA256, in, salt);
	strcpy(out, t);
	free(t);

	if (strlen(out) == 0)
	{
		strcpy(SQLUDF_STATE, "39702");
		strcpy(SQLUDF_MSGTX, "The system's crypt library does not support sha-256.");
		*outnull = 0;
		return;
	}

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha256hex: sha-256 64-character hex output (no salt)        |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha256hex(SQLUDF_CHAR      *in,
                          SQLUDF_CHAR      out[65],
                          SQLUDF_SMALLINT  *innull,
                          SQLUDF_SMALLINT  *outnull,
                          SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_SHA256HEX, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha1hex: sha-1 40-character hex output (no salt)            |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha1hex(SQLUDF_CHAR      *in,
                        SQLUDF_CHAR      out[41],
                        SQLUDF_SMALLINT  *innull,
                        SQLUDF_SMALLINT  *outnull,
                        SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_SHA1HEX, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha512: sha-512                                             |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha512(SQLUDF_CHAR      *in,
                       SQLUDF_CHAR      out[99],
                       SQLUDF_SMALLINT  *innull,
                       SQLUDF_SMALLINT  *outnull,
                       SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_SHA512, in, NULL);
	strcpy(out, t);
	free(t);

	if (strlen(out) == 0)
	{
		strcpy(SQLUDF_STATE, "39702");
		strcpy(SQLUDF_MSGTX, "The system's crypt library does not support sha-512.");
		*outnull = 0;
		return;
	}

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function sha512s: sha-512 with salt                                  |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          input : varchar             (salt)                          |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN sha512s(SQLUDF_CHAR      *in,
                        SQLUDF_CHAR      *salt,
                        SQLUDF_CHAR      out[99],
                        SQLUDF_SMALLINT  *innull,
                        SQLUDF_SMALLINT  *saltnull,
                        SQLUDF_SMALLINT  *outnull,
                        SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0 || *saltnull != 0)
	{
		*outnull = -1;
		return;
	}

	if (*saltnull == 0 && strlen(salt) != 8)
	{
		strcpy(SQLUDF_STATE, "39703");
		strcpy(SQLUDF_MSGTX, "salt must be exactly 8 characters long");
		*outnull = 0;
		return;
	}

	if (!is_valid_salt(salt))
	{
		strcpy(SQLUDF_STATE, "39704");
		strcpy(SQLUDF_MSGTX, "salt must be chosen from the set [a–zA–Z0–9./]");
		*outnull = 0;
		return;
	}

	t = mk_hash(ALG_SHA512, in, salt);
	strcpy(out, t);
	free(t);

	if (strlen(out) == 0)
	{
		strcpy(SQLUDF_STATE, "39702");
		strcpy(SQLUDF_MSGTX, "The system's crypt library does not support sha-512.");
		*outnull = 0;
		return;
	}

	*outnull = 0;
	return;
}

/*
  +----------------------------------------------------------------------+
  | function bcrypt: bcrypt (as in Apache's htpasswd program)            |
  |                                                                      |
  |          input : varchar             (password)                      |
  |          output: char                (hash)                          |
  +----------------------------------------------------------------------+
*/

#if BCRYPT_ALGO_SUPPORTED
#ifdef __cplusplus
extern "C"
#endif
void SQL_API_FN bcrypt(SQLUDF_CHAR      *in,
                       SQLUDF_CHAR      out[61],
                       SQLUDF_SMALLINT  *innull,
                       SQLUDF_SMALLINT  *outnull,
                       SQLUDF_TRAIL_ARGS)
{
	char *t;

	if (*innull != 0)
	{
		*outnull = -1;
		return;
	}

	t = mk_hash(ALG_BCRYPT, in, NULL);
	strcpy(out, t);
	free(t);

	*outnull = 0;
	return;
}
#endif

/*
  +----------------------------------------------------------------------+
  | function validate: validates the hash                                |
  |                                                                      |
  |          input1: varchar             (password)                      |
  |          input2: varchar             (hash)                          |
  |          output: integer             (status)                        |
  +----------------------------------------------------------------------+
*/

#ifdef __cplusplus
extern "C"
#endif
SQL_API_RC SQL_API_FN validate(SQLUDF_CHAR      *password,
                               SQLUDF_CHAR      *hash,
                               SQLUDF_INTEGER   *out,
                               SQLUDF_SMALLINT  *passwordNullInd,
                               SQLUDF_SMALLINT  *hashNullInd,
                               SQLUDF_SMALLINT  *outNullInd,
                               SQLUDF_TRAIL_ARGS)
{
	*out = -1;
	*outNullInd = -1;

	if (*passwordNullInd != 0 || *hashNullInd != 0)
	{
		*outNullInd = -1;
		return (0);
	}

	if (strlen(hash) == 0)
	{
		strcpy(SQLUDF_STATE, "39701");
		strcpy(SQLUDF_MSGTX, "The second parameter (hash) must not be empty.");
		*outNullInd = 0;
		return (0);
	}

	if (validate_hash(password, hash))
	{
		*out = 1;
	}
	else
	{
		*out = 0;
	}

	*outNullInd = 0;
	return (0);
}
