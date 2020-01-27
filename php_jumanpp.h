#ifndef PHP_JUMANPP_H
#define PHP_JUMANPP_H

#define PHP_JUMANPP_VERSION	"0.1.0"

extern zend_module_entry jumanpp_module_entry;
#define phpext_jumanpp_ptr &jumanpp_module_entry

ZEND_BEGIN_MODULE_GLOBALS(jumanpp)
	char *model_dir;
ZEND_END_MODULE_GLOBALS(jumanpp)

#ifdef ZTS
# define JUMANPP_G(v) TSRMG(jumanpp_globals_id, zend_jumanpp_globals *, v)
# ifdef COMPILE_DL_JUMANPP
ZEND_TSRMLS_CACHE_EXTERN()
# endif
#else
# define JUMANPP_G(v) (jumanpp_globals.v)
#endif

#endif  /* PHP_JUMANPP_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
