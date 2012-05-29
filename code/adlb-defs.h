
/**
 * Basic definitions used by the ADLB Data module
 * */

#ifndef ADLB_DEFS_H
#define ADLB_DEFS_H

#include <list_i.h>
#include <list.h>
#include <list_l.h>

typedef long adlb_datum_id;

typedef enum
{
  /** The datum was created but no value has been stored */
  ADLB_DATA_UNSET,
  /** A value was stored */
  ADLB_DATA_SET
} adlb_data_status;

typedef enum
{
  ADLB_DATA_TYPE_NULL = 0,
  ADLB_DATA_TYPE_INTEGER,
  ADLB_DATA_TYPE_FLOAT,
  ADLB_DATA_TYPE_STRING,
  ADLB_DATA_TYPE_BLOB,
  ADLB_DATA_TYPE_FILE,
  ADLB_DATA_TYPE_CONTAINER
} adlb_data_type;

typedef struct
{
  adlb_data_type type;
  adlb_data_status status;
  union
  {
    struct
    {
      long value;
    } INTEGER;
    struct
    {
      double value;
    } FLOAT;
    struct
    {
      char* value;
      int length;
    } STRING;
    struct
    {
      void* value;
      int length;
    } BLOB;
    struct
    {
      char* path;
    } FILE;
    struct
    {
      /** type of container keys */
      adlb_data_type type;
      /** Map from subscript to member TD */
      struct table* members;
    } CONTAINER;
  } data;
  struct list_i listeners;
} adlb_datum;

typedef enum
{
  ADLB_DATA_SUCCESS,
  /** Out of memory */
  ADLB_DATA_ERROR_OOM,
  /** Attempt to declare the same thing twice */
  ADLB_DATA_ERROR_DOUBLE_DECLARE,
  /** Attempt to set the same datum twice */
  ADLB_DATA_ERROR_DOUBLE_WRITE,
  /** Attempt to read an unset value */
  ADLB_DATA_ERROR_UNSET,
  /** Data set not found */
  ADLB_DATA_ERROR_NOT_FOUND,
  /** Parse error in number scanning */
  ADLB_DATA_ERROR_NUMBER_FORMAT,
  /** Invalid input */
  ADLB_DATA_ERROR_INVALID,
  /** Attempt to read/write ADLB_DATA_ID_NULL */
  ADLB_DATA_ERROR_NULL,
  /** Attempt to operate on wrong data type */
  ADLB_DATA_ERROR_TYPE,
  /** Slot count fell below 0 */
  ADLB_DATA_ERROR_SLOTS_NEGATIVE,
  /** Exceeded some implementation-defined limit */
  ADLB_DATA_ERROR_LIMIT,
  /** Unknown error */
  ADLB_DATA_ERROR_UNKNOWN,
} adlb_data_code;

#define ADLB_DATA_ID_NULL 0

/**
   Container member that is not yet linked
   Used by insert-atomic functionality
 */
#define ADLB_DATA_ID_UNLINKED -1

/**
   The maximal string length of a container subscript
 */
#define ADLB_DATA_SUBSCRIPT_MAX 1024

/**
   The maximal length of an ADLB datum (string, blob, etc.)
 */
#define ADLB_DATA_MAX (1024*1024)

#endif
