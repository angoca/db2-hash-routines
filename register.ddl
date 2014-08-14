--#SET TERMINATOR @

BEGIN
  DECLARE CONTINUE HANDLER FOR SQLSTATE '42704'
    BEGIN END;
  EXECUTE IMMEDIATE 'DROP FUNCTION php_md5';
  EXECUTE IMMEDIATE 'DROP FUNCTION apr_md5';
  EXECUTE IMMEDIATE 'DROP FUNCTION apr_crypt';
  EXECUTE IMMEDIATE 'DROP FUNCTION apr_sha1';
  EXECUTE IMMEDIATE 'DROP FUNCTION apr_sha256 ';
  EXECUTE IMMEDIATE 'DROP FUNCTION bcrypt';
  EXECUTE IMMEDIATE 'DROP FUNCTION validate_pw';

  EXECUTE IMMEDIATE 'DROP PROCEDURE php_md5';
  EXECUTE IMMEDIATE 'DROP PROCEDURE apr_md5';
  EXECUTE IMMEDIATE 'DROP PROCEDURE apr_crypt';
  EXECUTE IMMEDIATE 'DROP PROCEDURE apr_sha1';
  EXECUTE IMMEDIATE 'DROP PROCEDURE apr_sha256';
  EXECUTE IMMEDIATE 'DROP PROCEDURE bcrypt';
  EXECUTE IMMEDIATE 'DROP PROCEDURE validate_pw';
END @

CREATE FUNCTION php_md5(VARCHAR(120))
       SPECIFIC UDF_PHP_MD5
       RETURNS VARCHAR(32)
       NOT FENCED
       DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!phpmd5' @

CREATE FUNCTION apr_md5(VARCHAR(120))
       SPECIFIC UDF_APR_MD5
       RETURNS VARCHAR(37)
       NOT FENCED
       NOT DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!aprmd5' @

CREATE FUNCTION apr_crypt(VARCHAR(120))
       SPECIFIC UDF_APR_CRYPT
       RETURNS VARCHAR(13)
       NOT FENCED
       NOT DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!aprcrypt' @

CREATE FUNCTION apr_sha1(VARCHAR(120))
       SPECIFIC UDF_APR_SHA1
       RETURNS VARCHAR(33)
       NOT FENCED
       DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!aprsha1' @

CREATE FUNCTION apr_sha256(VARCHAR(120))
       SPECIFIC UDF_APR_SHA256
       RETURNS VARCHAR(52)
       NOT FENCED
       DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!aprsha256' @

CREATE FUNCTION bcrypt(VARCHAR(120))
       SPECIFIC UDF_BCRYPT
       RETURNS VARCHAR(60)
       NOT FENCED
       DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!bcrypt' @

CREATE FUNCTION validate_pw(VARCHAR(120),VARCHAR(120))
       SPECIFIC UDF_VALIDATE_PW
       RETURNS INTEGER
       NOT FENCED
       DETERMINISTIC
       NO SQL
       NO EXTERNAL ACTION
       LANGUAGE C
       RETURNS NULL ON NULL INPUT
       PARAMETER STYLE SQL
       EXTERNAL NAME 'hash!validate' @

CREATE PROCEDURE php_md5(IN in VARCHAR(120), OUT hash CHAR(32))
       SPECIFIC SP_PHP_MD5
       DYNAMIC RESULT SETS 0
       NO SQL
       DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!phpmd5' @

CREATE PROCEDURE apr_md5(IN in VARCHAR(120), OUT hash CHAR(37))
       SPECIFIC SP_APR_MD5
       DYNAMIC RESULT SETS 0
       NO SQL
       NOT DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!aprmd5' @

CREATE PROCEDURE apr_crypt(IN in VARCHAR(120), OUT hash CHAR(13))
       SPECIFIC SP_APR_CRYPT
       DYNAMIC RESULT SETS 0
       NO SQL
       NOT DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!aprcrypt' @

CREATE PROCEDURE apr_sha1(IN in VARCHAR(120), OUT hash CHAR(33))
       SPECIFIC SP_APR_SHA1
       DYNAMIC RESULT SETS 0
       NO SQL
       DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!aprsha1' @

CREATE PROCEDURE apr_sha256(IN in VARCHAR(120), OUT hash CHAR(52))
       SPECIFIC SP_APR_SHA256
       DYNAMIC RESULT SETS 0
       NO SQL
       DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!aprsha256' @

CREATE PROCEDURE bcrypt(IN in VARCHAR(120), OUT hash CHAR(52))
       SPECIFIC SP_BCRYPT
       DYNAMIC RESULT SETS 0
       NO SQL
       DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!bcrypt' @

CREATE PROCEDURE validate_pw(IN password VARCHAR(120), IN hash VARCHAR(120), OUT is_valid INTEGER)
       SPECIFIC SP_VALIDATE_PW
       DYNAMIC RESULT SETS 0
       NO SQL
       DETERMINISTIC
       LANGUAGE C
       PARAMETER STYLE SQL
       NO DBINFO
       NOT FENCED
       PROGRAM TYPE SUB
       EXTERNAL NAME 'hash!validate' @
