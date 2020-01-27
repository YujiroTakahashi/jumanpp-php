#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/json/php_json.h"
#include "main/SAPI.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "SAPI.h"
#include "php_jumanpp.h"
#include "classes/jpp.h"

ZEND_DECLARE_MODULE_GLOBALS(jumanpp)

/* {{{ PHP_INI
*/
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("jumanpp.model_dir",  NULL, PHP_INI_SYSTEM, OnUpdateString, model_dir, zend_jumanpp_globals, jumanpp_globals)
PHP_INI_END()
/* }}} */

/* Handlers */
static zend_object_handlers jumanpp_object_handlers;

/* Class entries */
zend_class_entry *php_jumanpp_sc_entry;



/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_jumanpp_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_jumanpp_load, 0, 0, 1)
	ZEND_ARG_INFO(0, fileformat)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_jumanpp_word, 0, 0, 1)
	ZEND_ARG_INFO(0, word)
ZEND_END_ARG_INFO()
/* }}} */


/* {{{ php_sjumanpp_class_methods */
static zend_function_entry php_jumanpp_class_methods[] = {
	PHP_ME(jumanpp, __construct,	arginfo_jumanpp_load,  ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(jumanpp, __destruct,     arginfo_jumanpp_void,  ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
	PHP_ME(jumanpp, analyze,        arginfo_jumanpp_word,  ZEND_ACC_PUBLIC)
	PHP_ME(jumanpp, wakati,         arginfo_jumanpp_word,  ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */



static void php_jumanpp_object_free_storage(zend_object *object) /* {{{ */
{
	php_jumanpp_object *intern = php_jumanpp_from_obj(object);

	if (!intern) {
		return;
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

static zend_object *php_jumanpp_object_new(zend_class_entry *class_type) /* {{{ */
{
	php_jumanpp_object *intern;

	/* Allocate memory for it */
	intern = ecalloc(1, sizeof(php_jumanpp_object) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->zo.handlers = &jumanpp_object_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(jumanpp)
{
	zend_class_entry ce;

	memcpy(&jumanpp_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	/* Register Jumanpp Class */
	INIT_CLASS_ENTRY(ce, "Jumanpp", php_jumanpp_class_methods);
	ce.create_object = php_jumanpp_object_new;
	jumanpp_object_handlers.offset = XtOffsetOf(php_jumanpp_object, zo);
	jumanpp_object_handlers.clone_obj = NULL;
	jumanpp_object_handlers.free_obj = php_jumanpp_object_free_storage;
	php_jumanpp_sc_entry = zend_register_internal_class(&ce);

	REGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(jumanpp)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(jumanpp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Jumanpp support", "enabled");
	php_info_print_table_row(2, "Jumanpp module version", PHP_JUMANPP_VERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION
*/
static PHP_GINIT_FUNCTION(jumanpp)
{
	memset(jumanpp_globals, 0, sizeof(*jumanpp_globals));
}
/* }}} */

/* {{{ jumanpp_module_entry
*/
zend_module_entry jumanpp_module_entry = {
	STANDARD_MODULE_HEADER,
	"jumanpp",
	NULL,
	PHP_MINIT(jumanpp),
	PHP_MSHUTDOWN(jumanpp),
	NULL,
	NULL,
	PHP_MINFO(jumanpp),
	PHP_JUMANPP_VERSION,
	PHP_MODULE_GLOBALS(jumanpp),
	PHP_GINIT(jumanpp),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_JUMANPP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(jumanpp)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
