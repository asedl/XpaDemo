/*  $Archive:   V:/PVCS/VM/mgstrutl/archives/USERDLL.H-arc  $ */
/* $Revision:   1.0  $ */
/*     $Date:   29 Oct 2001 17:50:28  $ */
/*   $Author:   Sedlmeier  $ */

/*------------------------------------------------------------------------*/
/*                                                                        */
/*------------------------------------------------------------------------*/
#ifndef USERPROC_USER_H
#define USERPROC_USER_H
#define DRIVER_LABEL_SIZE          8

/* alex 22.07.97 */
#ifndef __OS2 
#define NULL_PTR                   ((void far *) 0)
#define USER_FAR                   far
#else
#define NULL_PTR                   ((void  *) 0)
#define USER_FAR                   
#endif /* __OS2 */

#define USERPROC_MAX_PARM          30

typedef
unsigned char  Uchar;
typedef
unsigned short Ushort;
typedef
unsigned long Ulong;
#endif

#define MIN(a,b)                    (((a) < (b)) ? (a) : (b))

#define MODULE_LABEL_LEN            256
#define FUNC_NAME_LEN               128

#define USERPROC_ALPHA              'A'   /* parameter is string           */
#define USERPROC_BLOB               'B'   /* parameter is blob             */
#define USERPROC_LONG               'L'   /* --/--/--/-- pointer to long   */
#define USERPROC_DOUBLE             'D'   /* --/--/--/-- pointer to double */

#define USERPROC_DELIM              '.'   /* "module.func_name" delimiter */

#define DRIVER_TYPE_USERPROC        'U'

/*------------------------------------------------------------------------*/
/* Tipes                                                                  */
/*------------------------------------------------------------------------*/
#pragma pack (1)
typedef     /* structure used internally for communication */
struct
{
	void USER_FAR *next_ext_item;
	Ushort         sign;                     /* must be EXT_SIGNATURE */
	Ushort         psp_seg;
	Ushort         driver_type;               /* DRIVER_TYPE_USERPROC */
	Uchar          driver_label[DRIVER_LABEL_SIZE];
	void USER_FAR *driver_info;
	Ushort         use_cnt;
} EXT_ITEM;

typedef     /* structure defining module function */
struct
{
	Uchar USER_FAR *func_name;  /* name (label) of a function */
	void  USER_FAR *func_addr;  /* pointer to function        */
	Ushort          arg_cnt;    /* number of arguments        */
	Uchar USER_FAR *arg_attrs;  /* string of attributes 'A','L','D' */
}  FUNC_DSC;

typedef     /* structure defining module */
struct
{
	Ushort             use_cnt;         /* only for Magic use            */
	void     USER_FAR *ini_func_addr;   /* called upon initialization    */
	void     USER_FAR *trm_func_addr;   /* called upon termination       */
	Ushort             func_cnt;        /* number of functions in module */
	FUNC_DSC USER_FAR *func_dsc_tbl;    /* function table                */
	Uchar    USER_FAR *module_name;     /* name (label) of module        */
	Ushort             context_hdl;
} EXT_MODULE;
#pragma pack ()

/*-----------------------------------------------------------------------*/
/* Functions                                                             */
/*-----------------------------------------------------------------------*/
/* alex 22.07.97 */
#ifndef __OS2
void cdecl userproc_ext(EXT_MODULE *ext_module, Ulong mem_required);
#else
void userproc_ext(EXT_MODULE *ext_module, Ulong mem_required);
#endif