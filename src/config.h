/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define if the X Window System is missing or not being used.  */
#define X_DISPLAY_MISSING 1

/* Define if libgc is present. */
#define HAVE_LIBGC 1

#ifdef HAVE_LIBGC
#  define GC_NAME_CONFLICT
#  define MALLOC	GC_malloc
#  define NEW		new (UseGC)
#else
#  define MALLOC	malloc
#  define NEW		new
#endif
