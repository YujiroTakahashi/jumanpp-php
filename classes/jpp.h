#ifndef PHP_CLASSES_FTEXT_H
#define PHP_CLASSES_FTEXT_H

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#include <jumanpp/jumanpp.h>

extern "C" {

#include "php.h"
#include "php_ini.h"
#include "main/SAPI.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "SAPI.h"
#include "php_jumanpp.h"

#endif /* __cplusplus */

typedef void *JumanppHandle;

typedef struct _php_jumanpp_object {
    JumanppHandle handle;
    zval error;
    zend_object zo;
} php_jumanpp_object;

static inline php_jumanpp_object *php_jumanpp_from_obj(zend_object *obj) {
    return (php_jumanpp_object*)((char*)(obj) - XtOffsetOf(php_jumanpp_object, zo));
}

#define Z_JUMANPP_P(zv) php_jumanpp_from_obj(Z_OBJ_P((zv)))

PHP_METHOD(jumanpp, __construct);
PHP_METHOD(jumanpp, __destruct);
PHP_METHOD(jumanpp, analyze);
PHP_METHOD(jumanpp, wakati);

#ifdef __cplusplus
}   // extern "C"
#endif /* __cplusplus */

#endif /* PHP_CLASSES_FTEXT_H */