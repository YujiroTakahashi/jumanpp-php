#include "jpp.h"

/* {{{ proto void jumanpp::__construct()
 */
PHP_METHOD(jumanpp, __construct)
{
    php_jumanpp_object *jpp_obj;
    zval *object = getThis();
    char *model;
    size_t model_len;

    if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &model, &model_len)) {
        return;
    }

    jpp_obj = Z_JUMANPP_P(object);

    croco::Jumanpp *jumanpp = new croco::Jumanpp((model));
    jpp_obj->handle = static_cast<JumanppHandle>(jumanpp);
}
/* }}} */

/* {{{ proto void jumanpp::__destruct()
 */
PHP_METHOD(jumanpp, __destruct)
{
    php_jumanpp_object *jpp_obj;
    zval *object = getThis();

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    jpp_obj = Z_JUMANPP_P(object);

    delete static_cast<croco::Jumanpp*>(jpp_obj->handle);
}
/* }}} */

/* {{{ proto array jumanpp::analyze(string txt)
 */
PHP_METHOD(jumanpp, analyze)
{
    php_jumanpp_object *jpp_obj;
    zval *object = getThis();
    char *text;
    size_t text_len;

    if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &text, &text_len)) {
        return;
    }
    jpp_obj = Z_JUMANPP_P(object);
    croco::Jumanpp *jumanpp = static_cast<croco::Jumanpp*>(jpp_obj->handle);

    std::vector<croco::Jumanpp::Node> nodes = jumanpp->analyze(text);

    array_init(return_value);
    zend_ulong idx = 0;

    for (auto &node : nodes) {
        zval surfaceVal, readingVal, baseformVal, posVal, subposVal,
            conjTypeVal, conjFormVal, featVal, redirectVal, posIdVal,
            subposIdVal, conjTypeIdVal, conjFormIdVal, featflagVal;
        ZVAL_STRING(&surfaceVal,  node.surface.c_str());
        ZVAL_STRING(&readingVal,  node.reading.c_str());
        ZVAL_STRING(&baseformVal, node.baseform.c_str());
        ZVAL_STRING(&posVal,      node.pos.c_str());
        ZVAL_STRING(&subposVal,   node.subpos.c_str());
        ZVAL_STRING(&conjTypeVal, node.conjType.c_str());
        ZVAL_STRING(&conjFormVal, node.conjForm.c_str());
        ZVAL_STRING(&featVal,     node.feat.c_str());
        ZVAL_STRING(&redirectVal, node.redirect.c_str());
        ZVAL_LONG(&posIdVal,      node.posId);
        ZVAL_LONG(&subposIdVal,   node.subposId);
        ZVAL_LONG(&conjTypeIdVal, node.conjTypeId);
        ZVAL_LONG(&conjFormIdVal, node.conjFormId);
        ZVAL_LONG(&featflagVal,   node.featflag);

        zval rowVal;
        array_init(&rowVal);

        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "surface",    sizeof("surface") -1,    &surfaceVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "reading",    sizeof("reading") -1,    &readingVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "baseform",   sizeof("baseform") -1,   &baseformVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "pos",        sizeof("pos") -1,        &posVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "subpos",     sizeof("subpos") -1,     &subposVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "conjType",   sizeof("conjType") -1,   &conjTypeVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "conjForm",   sizeof("conjForm") -1,   &conjFormVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "feat",       sizeof("feat") -1,       &featVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "redirect",   sizeof("redirect") -1,   &redirectVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "posId",      sizeof("posId") -1,      &posIdVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "subposId",   sizeof("subposId") -1,   &subposIdVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "conjTypeId", sizeof("conjTypeId") -1, &conjTypeIdVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "conjFormId", sizeof("conjFormId") -1, &conjFormIdVal);
        zend_hash_str_add(Z_ARRVAL_P(&rowVal), "featflag",   sizeof("featflag") -1,   &featflagVal);

        add_index_zval(return_value, idx, &rowVal);
        idx++;
    }
}
/* }}} */

/* {{{ proto string jumanpp::wakati(string txt)
 */
PHP_METHOD(jumanpp, wakati)
{
    php_jumanpp_object *jpp_obj;
    zval *object = getThis();
    char *text;
    size_t text_len;

    if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s", &text, &text_len)) {
        return;
    }
    jpp_obj = Z_JUMANPP_P(object);
    croco::Jumanpp *jumanpp = static_cast<croco::Jumanpp*>(jpp_obj->handle);

    std::string wakati = jumanpp->wakati(text);

    ZVAL_STRING(return_value, wakati.c_str());
}
/* }}} */

